//
// Created by hongyu on 2022/1/3.
//
#include <string>
class ftp{
public:
    struct FileAttr{
        int32_t size;
        std::string name;
        std::string mod_date;
    };
    void config();
private:
    std::string ip_port;
    std::string get_file_name;
    std::string put_file_name;
    FileAttr file;
};

