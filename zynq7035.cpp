//
// Created by hongyu on 2022/1/3.
//

#include <cstring>
#include "zynq7035.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <vector>

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
            __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

template<class T>
T *phy_mem_alloc(int32_t& fd,uint32_t phyaddr, int32_t& size) {
    void *map_base, *virt_addr;
    char dev_name[] = "/dev/mem";
    unsigned page_size, mapped_size, offset_in_page;
    off_t target = phyaddr;

    fd = open(dev_name, O_RDWR | O_SYNC);

    if (fd < 0) FATAL;

    mapped_size = page_size = sysconf(_SC_PAGESIZE);
    mapped_size += size; //允许访问的空间的大小,允许使用的内存空间的大小

    offset_in_page = (unsigned) target & (page_size - 1);

    if ((offset_in_page + 32) > page_size) {
        mapped_size *= 2;
    }

    mapped_size = size; //将实际的长度同时进行返回使用
    map_base = mmap(NULL, mapped_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~(off_t) (page_size - 1));

    virt_addr = (char *) map_base + offset_in_page;

    if (virt_addr == (void *) -1) FATAL;
    return (T*)virt_addr;
}

template<class T>
void phy_mem_free(T *mem, int32_t size,int fd) {
    if (munmap(mem, size) == -1)
        printf("phy mem free error: %s\n", strerror(errno));
    close(fd);
}

//单独的寄存器操作使用
template<class T>
void mem_write(T address,T value){
    void *map_base,*virt_addr;
    char dev_name[] = "/dev/mem";
    int fd;
    unsigned page_size,mapped_size,offset_in_page;
    off_t target = address;

    fd  =  open(dev_name,O_RDWR|O_SYNC);

    if(fd < 0) FATAL;

    mapped_size = page_size = sysconf(_SC_PAGESIZE);

    offset_in_page = (unsigned)target & (page_size -1);

    if((offset_in_page + 32) > page_size){
        mapped_size *=2;
    }

    map_base = mmap(NULL,mapped_size,PROT_READ|PROT_WRITE, MAP_SHARED,fd,target &~(off_t)(page_size-1));

    virt_addr = (char*)map_base + offset_in_page;

    if(virt_addr == (void*)-1) FATAL;

    *(volatile T*)virt_addr = value;

    if(munmap(map_base,mapped_size) == -1) FATAL;
    close(fd);
}

template<class T>
void mem_read(T address,T& value){
    void *map_base,*virt_addr;
    char dev_name[] = "/dev/mem";
    int fd;
    unsigned page_size,mapped_size,offset_in_page;
    off_t target = address;

    fd  =  open(dev_name,O_RDWR|O_SYNC);

    if(fd < 0) FATAL;

    mapped_size = page_size = sysconf(_SC_PAGESIZE);

    offset_in_page = (unsigned)target & (page_size -1);

    if((offset_in_page + 32) > page_size){
        mapped_size *=2;
    }

    map_base = mmap(NULL,mapped_size,PROT_READ|PROT_WRITE, MAP_SHARED,fd,target &~(off_t)(page_size-1));

    virt_addr = (char*)map_base + offset_in_page;

    if(virt_addr == (void*)-1) FATAL;

    value = *(volatile T*)virt_addr;

    if(munmap(map_base,mapped_size) == -1) FATAL;
    close(fd);
}

template<class T>
void mem_write(std::vector<std::pair<T,T>> w){
    for(int i = 0 ; i < w.size(); i++){
      //  printf("write value %#x = %#x\n",w[i].first,w[i].second);
        mem_write<T>(w[i].first,w[i].second);
    }
}

template<class T>
void mem_read(std::vector<std::pair<T,T&>> r){
    for(int i = 0 ; i < r.size(); i++){
        mem_read<T>(r[i].first,r[i].second);
    }
}

Zynq7035::Zynq7035(uint32_t addr,int32_t _size) { //FIXME:Remmber to add phy addr;
    phy_addr = addr;
    size = _size;
    virt_addr = phy_mem_alloc<uint32_t>(fd,phy_addr,size);
}

void Zynq7035::operator()(uint32_t addr,int32_t _size){
    phy_addr = addr;
    size = _size;
    virt_addr = phy_mem_alloc<uint32_t>(fd,phy_addr,size);
}

void Zynq7035::read(uint32_t offset,uint32_t& value){
    value = *(volatile uint32_t*)(virt_addr+offset);
}

void Zynq7035::write(uint32_t offset,uint32_t value){
    *(volatile uint32_t*)(virt_addr+offset) = value;
}

void Zynq7035::set_phy_addr(uint32_t addr,int32_t _size){
    this->operator()(addr,_size);
}

void Zynq7035::init_sample_dma(uint32_t dst, uint32_t src, int32_t size) {
    dma_dst = dst;
    dma_src = src;
    dma_size = size;
    //S2MM DMA Set
    std::vector<std::pair<uint32_t,uint32_t>> set_dma = { //AXI DMA SAMPLE SET
            std::make_pair(S2MM_CTR_REG,RESET_DMA_CHANNEL),
                    std::make_pair(S2MM_CTR_REG,COMMON_DMAC_SET),
                    std::make_pair(S2MM_PHY_PERE_REG,src),
                    std::make_pair(S2MM_PERE_LENTH_REG,size)};
    mem_write(set_dma);

    virtual_dma_src = phy_mem_alloc<uint32_t>(dma_fd,dma_src,dma_size);
}

//Zynq Axi Dma desc
void Zynq7035::init_sg_dma(uint32_t dst,uint32_t src,int32_t size) { //目前 size 不会使用
    // dma dst 没有使用
    dma_dst = dst;
    dma_src = src;
    dma_size = size;
    uint32_t SG_DESCRIPT_BUFFER_CONCTRL_REG = 0x03000000;
    std::vector<std::pair<uint32_t,uint32_t>> set_dma = {
            std::make_pair(SG_MM2S_DMACR,SG_RESET_DMA_CHANNEL),
            std::make_pair(SG_MM2S_DMACR,SG_MM2S_DMCR_SET),
            std::make_pair(SG_MM2S_CURDESC,src<<5),                                            //地址相接使用
            std::make_pair(SG_MM2S_TAILDESC,src<<5)                                                //目前只使用一个dma地址
    };

    mem_write(set_dma); //寄存器地址写入

    virtual_sg_desc_addr = phy_mem_alloc<uint32_t>(dma_fd,dma_src,dma_size); // 只有一个bd 申请一块儿内存进行使用
    virtual_dma_src = virtual_sg_desc_addr + 16; // 提供给sg desc 使用 需要掉本身使用的字节作为描述块使用,我这是需要使用的虚拟地址
    phy_sg_desc_addr = dma_src; // src dma_src phy_sg_desc_addr 他们是同一个地址
    phy_sg_desc_buf_addr = dma_src + 0x40; //作为使用发送的真实地址进行使用,实际已经偏移的地址空间

    SG_DESCRIPT_BUFFER_CONCTRL_REG |= dma_size; //FIXME: dma size 需要限制到 26 bit

    memset(virtual_sg_desc_addr,0x5A,dma_size); //FIXME: 对地址空间进行初始化,查看是否被修改
    xilinx_axidma_desc_hw first_bd = {
            .next_desc = phy_sg_desc_addr<<5, //FIXME: 需要对小地址做出检验,需要为文件开辟文件大小
            .next_desc_msb = 0x0,
            .buf_addr = phy_sg_desc_buf_addr,
            .buf_addr_msb = 0x0,
            .reserved1 = 0x0,
            .reserved2 = 0x0,
            .control = SG_DESCRIPT_BUFFER_CONCTRL_REG,
            .status = 0x0
    };
    memset(first_bd.app,0x0,sizeof(uint32_t)*XILINX_DMA_NUM_APP_WORDS); // first bd buffer empty
    memcpy(virtual_sg_desc_addr,&first_bd,sizeof(xilinx_axidma_desc_hw)); //将bd 的数据空间进行赋值,完成了数据填充
}

void Zynq7035::write2slave(std::vector<uint32_t> buf) {
    printf("No Use, Please empty\n");
}

void Zynq7035::dmawrite_sg(char *buf,uint32_t length) {
    if(!(dma_mode_mask&AXI_DMA_MODE::SG_DMA_MODE)){
        printf("SG_DMA_MODE Error\n");  //如果模式错误就无法使用SG DMA MODE
        return;
    }
    memcpy(virtual_dma_src,buf,length); //将数据copy 到 data buffer 中去
}

//这个是之前预留的测试接口现在不在使用了,但是以后测试还得使用
void Zynq7035::read2slave(std::vector<uint32_t> buf) {
        if(virtual_sg_desc_addr != nullptr) {
            xilinx_axidma_desc_hw rx_dma;
            memcpy(&rx_dma, virtual_sg_desc_addr, sizeof(xilinx_axidma_desc_hw));
            printf("descpt address: %#x \n", rx_dma.next_desc);
        }
        for(int i = 0 ; i < (dma_size)/4 ; i++){
            printf("%#x ",virtual_dma_src[i]);
            if( i%10 == 0 && i != 0) {
                printf("\n");
            }
        }
}

void Zynq7035::init_zynq7035(uint8_t _dma_mode_mask) {

    switch(_dma_mode_mask&(DIRECT_DMA_MODE|SG_DMA_MODE)){
        case DIRECT_DMA_MODE :
            this->init_sample_dma(0,dma_src,dma_size);
            break;
        case SG_DMA_MODE:
            this->init_sg_dma(0,dma_src,dma_size);
            break;
        case 0x3:
            this->init_sample_dma(0,dma_src,dma_size);
            this->init_sg_dma(0,dma_src,dma_size);
            break;
        default:
            printf("Init Zynq7035 Dma error ... ...\n");
            exit(1);
    }
}

//如果同时有两个,两个同时都可以进行初始化,userspace 下的测试模式
void Zynq7035::dmaread_sample(char *buf, uint32_t length) {
    if(!(dma_mode_mask&AXI_DMA_MODE::DIRECT_DMA_MODE)){
        printf("Not Use DIRECT DMA MODE\n");
        return;
    }

    if(length < dma_size){
        printf("buffer lenth not enough for dma read \n");
        return;
    }

    memcpy(buf,virtual_dma_src,dma_size); //copy data
}

Zynq7035::~Zynq7035() {
    if(virtual_dma_src != nullptr) { //dma sometimes not use
        phy_mem_free<uint32_t>(virtual_dma_src, dma_size, dma_fd);
    }
   phy_mem_free<uint32_t>(virt_addr,size,fd);
}