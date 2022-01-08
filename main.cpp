#include <cstdio>
#include "zynq7035.h"
#include <string>
#include "ftp.h"
#include <vector>

const static std::string Use = "UserSpace Dma Test \n\n"
                               "-u [ftp romte login name] \n"
                               "-p [ftp romte login password]\n"
                               "-rf [ftp romte get filename]\n"
                               "-dma_size [dma test mem calloc size\n]"
                               "-dma_addr [dma test mem phy addr\n]"
                               "-dma_mode [axi dma mode\n]\n"
                               "axi dma mode:\n"
                               "[DIRECT_DMA_MODE 0x1]\n"
                               "[SG_DMA_MODE 0x2]\n"
                               "[RO_MODE] 0x4\n"
                               "[WO_MODE] 0x8\n"
                               "if you want all please use 0xFF \n";

// 这是测试代码所以这部分代码可以共享一下,但是业务代码,只能用于简单的测试
// kernel 的部分,和 实际的业务代码, 就不好分享了,
// RW  测试模式下恐有些问题,不建议 0xFF
// 使用命令行的时候建议使用 bash 脚本 综合测试,之所以没有配置文件感觉太麻烦
// 直接从ftp 获取数据源进行测试, 会分享到 github 中 遵循 MIT 协议
// 根据 read 和 write 的模式 页可以进行设置

void args_parser(std::vector<std::string> args,Ftp& ftp_use,uint32_t& dma_addr,uint32_t& dma_size,uint8_t& _dma_mode_mask){ //
    // 命令行的解析函数,
    // 正常的命令行解析函数
    for(int i  = 0 ; i < args.size() ; i++){
        if(args[i] == std::string("-u")){
            ftp_use.login_name = args[++i];
        }else if(args[i] == std::string("-p")){
            ftp_use.login_password = args[++i];
        }else if(args[i] == std::string("-rf")){
            ftp_use.filename = args[++i];
        }else if(args[i] == std::string("-ra")){
            ftp_use.ftp_addr = args[++i];
        }else if(args[i] == std::string("-dma_size")){
            dma_size = (uint32_t)std::stoul(args[++i],nullptr,16);
        }else if(args[i] == std::string("-dma_addr")){
            dma_addr = (uint32_t)std::stoul(args[++i],nullptr,16);
        }else if(args[i] == std::string("-dma_mode")){
            _dma_mode_mask = (uint8_t)std::stoul(args[++i],nullptr,16);
        }
    }

    if(dma_size == 0 || dma_addr == 0 || \
        ftp_use.login_name.size() == 0  || \
        ftp_use.login_password.size() == 0 || ftp_use.filename.size() == 0 || \
        ftp_use.ftp_addr.size() == 0 || _dma_mode_mask == 0){
        printf("%s",Use.c_str());
        exit(1);
    }
}

int main(int argc,char* argv[]){ // 如果失败只能重启使用

    std::vector<std::string> args;

    for(int i = 1 ; i < argc ; i++){
        args.push_back(std::string(argv[i]));
    }

    uint32_t  dma_addr,dma_size;
    uint8_t dma_mode;
    Ftp _ftp;
    args_parser(args,_ftp,dma_addr,dma_size,dma_mode); //获取dma的一个物理地址,在脚本中计算好,传入主程序解析使用

    char *buffer = (char*)calloc(sizeof(char)*2,dma_size); //开辟一段连续的内存空间
    _ftp.ftp_get(buffer,dma_size); //ftp 获取传输进来的 buffer, 这个buffer 为 dma 映射的区域
    Zynq7035 fpctr(COMMON_FPGA_BASEADDR,1024); //Fpga 的通用配置函数,无法同时测试收发
    Fpga* fpga_rw = &fpctr;
    uint32_t version;
    fpga_rw->read(0x0,version);
    printf("fpga version is %#x\n",version);

    fpctr.init_zynq7035(dma_mode);

    // 目前 硬件 用了 两种 不同的方案 一个 dma engine 用来 read 另一个 dma engine 用来 write
    // 只是用来测试的，所以无伤大雅

    if(dma_mode&RO_MODE){
        if(dma_mode&DIRECT_DMA_MODE){
            fpctr.read2slave(std::vector<uint32_t>());
        }else if(dma_mode&SG_DMA_MODE){
            printf("SG DMA READ MODE NONE \n");
        }
    }

    if(dma_mode&WO_MODE){
        if(dma_mode&DIRECT_DMA_MODE){
            printf("SAMPLE DMA WRITE MODE NONE \n");
        }else if(dma_mode&SG_DMA_MODE){
            fpctr.dmawrite_sg(buffer,dma_size);
        }
    }
    return 0;
}