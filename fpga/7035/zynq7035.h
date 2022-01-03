//
// Created by hongyu on 2022/1/3.
//

#ifndef SINGLE_SOURCE_ZYNQ7035_H
#define SINGLE_SOURCE_ZYNQ7035_H

#include <cstdint>

class zynq7035{
    private:
        int32_t base_addr;
    public:
        void operator()(int32_t addr);
        virtual int32_t read(int32_t offset, int32_t &value);
        virtual int32_t write(int32_t offset, int32_t value);
        virtual void set_base_addr(int32_t addr);
        virtual void get_base_addr();
       ~zynq7035();
};


#endif //SINGLE_SOURCE_ZYNQ7035_H
