#include <iostream>
#include <string>
#include <sys/time.h>
#include <curl/curl.h>

#include "file_send.h"
#include "ssh_search.h"

int main()
{
    ssh_search sh;
    std::vector< std::string > send_list = sh.search_file();
    
    file_send fs;
    fs.init();

    for( int i = 0; i < send_list.size(); i++ )
    {
        fs.file_set( send_list[i] );
    }
    
    fs.send_data( "http://localhost:8080" );
}
