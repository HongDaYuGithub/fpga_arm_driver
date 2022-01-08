//
// Created by hongyu on 2022/1/3.
//

#include "ftp.h"

int32_t Ftp::ftp_get(char *buf, uint32_t size) {
    ftplib *ftp = new ftplib();
    ftp->Connect(this->ftp_addr.c_str());
    ftp->Login(this->login_name.c_str(),this->login_password.c_str());
    int32_t size_;
    ftp->Size(this->filename.c_str(),&size_,ftplib::image);
    ftphandle* romte_file = ftp->RawOpen(this->filename.c_str(),ftplib::fileread,ftplib::image);
    ftp->RawRead(buf,(int32_t)size,romte_file);
    ftp->RawClose(romte_file);
    delete ftp; //只使用一次即时回收系统资源
    return size_;                       //返回使用的ftp 客户端的大小
}