#include <iostream>
#include "config.h"
#include "libftp/ftplib.h"

using namespace std;

int main() {
    ftplib *ftp = new ftplib();
    ftp->Connect("192.168.1.5");
    ftp->Login("admin","admin");
    int file_size;
    ftp->Size("bin.txt",&file_size,ftplib::image);
    ftphandle* romte_file = ftp->RawOpen("bin.txt",ftplib::fileread,ftplib::image);
    char *buf = new char(file_size);
    cout << "romte file size: " << file_size << endl;
    ftp->RawRead(buf,file_size,romte_file);
    sleep(3);
    cout << buf << endl;
    return 0;
}
