#include <cstdio>
#include "zynq7035.h"
#include <string>
#include "ftp.h"

void init_dma(){
    //    Zynq7035 fpctr(COMMON_FPGA_BASEADDR,1024);
//    Fpga* fpga_rw = &fpctr;
//    uint32_t version;
//    fpga_rw->read(0x0,version);
//    printf("fpga version is %#x\n",version);
//
//
//    fpctr.init_sg_dma(0x500000,0x800000,buffer_ssg_size+0x40);   // 初始化 sg 的 dma 模式
//    fpctr.dmawrite(buffer_ssg,buffer_ssg_size);               // 从内存向dma发送数据
}

int main(){ // 如果失败只能重启使用
    ftplib *ftp = new ftplib();
    ftp->Connect("192.168.1.33");
    ftp->Login("admin","admin");
    int file_size;
    ftp->Size("sg.txt",&file_size,ftplib::image);
    ftphandle* romte_file = ftp->RawOpen("sg.txt",ftplib::fileread,ftplib::image);
    char *buf =(char*)calloc(file_size,1);
    ftp->RawRead(buf,file_size,romte_file);


    Zynq7035 fpctr(COMMON_FPGA_BASEADDR,1024);
    Fpga* fpga_rw = &fpctr;
    uint32_t version;
    fpga_rw->read(0x0,version);
    printf("fpga version is %#x\n",version);


    fpctr.init_sg_dma(0x500000,0x800000,file_size+0x40);   // 初始化 sg 的 dma 模式
    fpctr.dmawrite(buf,file_size);
    return 0;
}