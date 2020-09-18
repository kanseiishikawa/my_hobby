#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include <queue>

#include "search_file.h"

std::string
search::replaceOtherStr(std::string &replacedStr, std::string from, std::string to)
{
    const unsigned int pos = replacedStr.find( from );
    const int len = from.length();
 
    if( pos == std::string::npos || from.empty() )
    {
        return replacedStr;
    }
 
    return replacedStr.replace( pos, len, to );
}

std::vector< std::string >
search::command_result( std::string command )
{
    std::vector< std::string > result;
    char word[256];
    std::string instance;

    FILE* fp = popen( command.c_str(), "r");
    
    if( fp )
    {    
        while( fgets( word, 256, fp ) != NULL )
        {
            instance = word;
            replaceOtherStr( instance, "\n", "" );
            result.push_back( instance );
        }
    }

    return result;
}

std::vector< std::string >
search::search_file()
{
    std::vector< std::string > result;
    std::vector< std::string > instance;
    std::queue< std::string > search;
    
    std::string ls = "ls -F ";
    std::string file_check = "| grep -v /";
    std::string dir_check = " | grep /";
    
    std::string home_path;
    std::string current_path;
    
    instance = command_result( "echo $HOME" );

    if( instance.empty() )
    {
        return result;
    }
    
    home_path = instance.front() + "/Desktop/";
    current_path = home_path;

    bool finish = false;

    while( !finish )
    {
        instance = command_result( ls + current_path + file_check );

        for( int i = 0; i < instance.size(); i++ )
        {
            result.push_back( current_path + instance[i] );
        }

        instance = command_result( ls + current_path + dir_check );
        //std::cout<< "----> " << current_path << "\n";

        for( int i = 0; i < instance.size(); i++ )
        {
            if( i == 0 )
            {
                //std::cout<< "---> " << instance[i] <<"\n";
            }

            search.push( current_path + instance[i] );
        }
        
        if( search.empty() )
        {
            finish = true;
        }
        else
        {
            current_path = search.front();
            search.pop();
        }
    }

    return result;
}

