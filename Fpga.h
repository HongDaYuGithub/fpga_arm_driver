//
// Created by hongyu on 2022/1/3.
//

#ifndef SINGLE_SOURCE_FPGA_H
#define SINGLE_SOURCE_FPGA_H
#include <cstdint>
#include <vector>

namespace FPGA_X32 {
    class Fpga {
    public:
       virtual void read(uint32_t offset, uint32_t &value) = 0;
       virtual void  write(uint32_t offset, uint32_t value) = 0;
       virtual void  set_phy_addr(uint32_t addr,int32_t size) = 0;
    };

    class FpgaDma {
    public:
        virtual void write2slave(std::vector<uint32_t> buf) = 0;
        virtual void read2slave(std::vector<uint32_t> buf) = 0;
    };
}
#endif //SINGLE_SOURCE_FPGA_H
