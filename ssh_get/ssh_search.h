#ifndef SSH_SEARCH_H
#define SSH_SEARCH_H

class ssh_search
{
 public:
    std::vector< std::string > search_file();
 private:

    std::vector< std::string > command_result( std::string command );
    std::string replaceOtherStr( std::string &replacedStr, std::string from, std::string to );
    std::string ssh_path_search();
};
#endif
