cmake_minimum_required(VERSION 3.18)
#配置cmake使用的版本号
project(single_source)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-static -DNOSSL")
add_executable(single_source main.cpp libftp/ftplib.cpp libftp/ftplib.h fpga/Fpga.cpp fpga/Fpga.h fpga/7035/zynq7035.cpp fpga/7035/zynq7035.h ftp.cpp)