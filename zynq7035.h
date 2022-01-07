//
// Created by hongyu on 2022/1/3.
//

#ifndef SINGLE_SOURCE_ZYNQ7035_H
#define SINGLE_SOURCE_ZYNQ7035_H

#include "Fpga.h"

using namespace FPGA_X32;

//相当于使用两个dma控制器 dma1 sg 的发送模式用于发送 dma0 sample 的接受模式 用于接受使用

enum ZynqSampleDmaReg{
    S2MM_PHY_PERE_REG= 0x40400048,
    S2MM_PERE_LENTH_REG = 0x40400058,
    MM2S_PHY_PERE_ADDR = 0x40400018,
    MM2S_PERE_LENTH_REG = 0x40400028,
    S2MM_CTR_REG= 0x40400030,
    MM2S_CTR_REG= 0x40400000,
    RESET_DMA_CHANNEL = 0x4,
    COMMON_DMAC_SET = 0x17003
};

enum ZynqSgDmaReg{
    COMMON_FPGA_BASEADDR = 0x43c10000,
    XILINX_DMA_NUM_APP_WORDS = 0x5,
    SG_S2MM_CTR_REG= 0x40410030,
    SG_RESET_DMA_CHANNEL = 0x4,
    SG_S2MM_DMCR_SET = 0x17003,             //  选中使用SG_S2MM_Cyclic 功能
    SG_S2MM_CURDESC_REG = 0x40410038,       //  SG BD phy addr with current
    SG_S2MM_TAILDESC = 0x40410040, //  SG BD phy addr with tail for example is tail
    // MM2S REG CTRL
    SG_MM2S_DMACR = 0x40410000,
    SG_MM2S_CURDESC = 0x40410004,
    SG_MM2S_TAILDESC = 0x40410010,
    SG_MM2S_DMCR_SET = 0x17013,
};

#define __ALIGNED(x) __attribute__ ((aligned (x)))

//需要使用64位的内存对齐的数据空间
struct xilinx_axidma_desc_hw{
    uint32_t next_desc;
    uint32_t next_desc_msb;
    uint32_t buf_addr;
    uint32_t buf_addr_msb;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t control;
    uint32_t status;
    uint32_t app[XILINX_DMA_NUM_APP_WORDS];
}__ALIGNED(64);

enum DMA_SG_BD_ALIGNED{
    BIT_32 = 0x20,
    BIT_64 = 0x40
};

// 最简单的版本只有一个 buffer descriptor
// 分配一个BD所使用的文件描述符

class Zynq7035:public Fpga,public FpgaDma{
    private:
        int32_t fd;
        uint32_t phy_addr;
        uint32_t* virt_addr = nullptr;
        int32_t size;
        uint32_t dma_src;
        uint32_t dma_dst;
        int32_t dma_size;
        uint32_t *virtual_dma_src = nullptr;
        uint32_t *virtual_dma_dst = nullptr;
        int32_t dma_fd;
        uint32_t *virtual_sg_desc_addr;
        uint32_t phy_sg_desc_addr;
        uint32_t phy_sg_desc_buf_addr;
        bool set_phy_flags = false; //TODO: 互斥关系操作
        bool set_dma_type = false; //TODO: 对两种的操作模式进行互斥
    public:
        Zynq7035(){}
        Zynq7035(uint32_t addr,int32_t _size);
        void init_sample_dma(uint32_t dst,uint32_t src,int32_t size);
        void init_sg_dma(uint32_t dst,uint32_t src,int32_t size);
        uint32_t* sg_bd_alloc(DMA_SG_BD_ALIGNED type);
        void operator()(uint32_t addr,int32_t _size);
        virtual void read(uint32_t offset,uint32_t &value);
        virtual void write(uint32_t offset,uint32_t value);
        virtual void set_phy_addr(uint32_t addr,int32_t _size);
        virtual void write2slave(std::vector<uint32_t> buf);
        virtual void read2slave(std::vector<uint32_t> buf);
        void dmawrite(char* buf,uint32_t length);
       ~Zynq7035();
};

#endif //SINGLE_SOURCE_ZYNQ7035_H