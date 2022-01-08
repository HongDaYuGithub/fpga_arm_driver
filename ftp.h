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
    Ftp(){}
    Ftp(std::string f,std::string ln,std::string lp,std::string fa):filename(f), \
    login_name(ln),login_password(lp),ftp_addr(fa){}
    int32_t ftp_get(char* buf,uint32_t size); //ftp 下载功能
};
#endif //SINGLE_SOURCE_FTP_H
