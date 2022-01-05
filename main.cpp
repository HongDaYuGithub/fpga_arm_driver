#include <cstdio>
#include "zynq7035.h"
#include <string>

/* 目前使用两个调试模式 */
int main(int argc, char* argv[]) {
    Zynq7035 fpctr(COMMON_FPGA_BASEADDR,1024);
    Fpga* fpga_rw = &fpctr;
    uint32_t version;
    fpga_rw->read(0x0,version);
    printf("fpga version is %#x\n",version);

    if (argc != 1 && argv[1] != nullptr){
        if(std::string(argv[1]) == std::string("sample")){
            printf("sample dma mode\n");
            fpctr.init_sample_dma(0x500000,0x800000,0x8000); // 两个模式只能选择一种
        }else if(std::string("sg") == std::string(argv[1])){
            printf("sg dma mode\n");
            fpctr.init_sg_dma(0x500000,0x8000,0x8000); // 使用了 32kb的内存空间
        }else{
            ERROR:
            printf("Usage 5g_sg [sg / sample] \n"); // 5g_sg 信源调试模式
            exit(0);
        }
    }else if(argc == 1){
        goto ERROR;
    }

    auto fpga_test = [fpga_rw]{
        uint32_t value;
        fpga_rw->write(0x100,0x12345678);
        fpga_rw->read(0x100,value);
        printf("fpga test read && write %#x\n",value);
    };

    auto fpga_triger = [fpga_rw] {
        fpga_rw->write(0x234,0);
        fpga_rw->write(0x234,1);
        fpga_rw->write(0x234,0);
    };
    //fpga 触发使用的地址

    fpga_test();
    fpga_triger();

    fpctr.read2slave(std::vector<uint32_t>()); //占一个空位并未使用
    return 0;
}