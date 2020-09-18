#ifndef SEARCH_FILE_H
#define SEARCH_FILE_H

class search
{
 public:
    std::vector< std::string > search_file();
 private:
    std::vector< std::string > command_result( std::string command );
    std::string replaceOtherStr( std::string &replacedStr, std::string from, std::string to );
};
#endif
