//
// Created by hongyu on 2022/1/3.
//

#ifndef SINGLE_SOURCE_FPGA_H
#define SINGLE_SOURCE_FPGA_H

template<class T>
class Fpga {
    T read(T offset, T &value) = 0;
    T write(T offset, T &value) = 0;
    void set_base_addr(T addr) = 0;
    void get_base_addr() = 0;
};

class FpgaDma {
    void write2slave(char *buf) = 0;
    void read2slave(char *buf) = 0;
    void reset() = 0;
    void config() = 0;
};
#endif //SINGLE_SOURCE_FPGA_H
