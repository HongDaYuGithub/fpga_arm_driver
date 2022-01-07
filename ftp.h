//
// Created by hongyu on 2022/1/5.
//

#ifndef SINGLE_SOURCE_FTP_H
#define SINGLE_SOURCE_FTP_H
#include "libftp/ftplib.h"
#include <string>

struct Ftp{
    std::string filename;
    std::string login_name;
    std::string login_password;
    std::string ftp_addr; // ip+port
};
int32_t ftp_get(Ftp ftp,char* buf,uint32_t& size);
#endif //SINGLE_SOURCE_FTP_H
