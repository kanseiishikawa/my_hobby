#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include <queue>

#include "ssh_search.h"

std::string
ssh_search::replaceOtherStr(std::string &replacedStr, std::string from, std::string to)
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
ssh_search::command_result( std::string command )
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

std::string
ssh_search::ssh_path_search()
{
    std::string ls = "ls -F -a ";
    std::string file_check = "| grep -v /";
    std::string dir_check = " | grep /";

    std::string ssh_path;
    std::vector< std::string > instance;
    std::queue< std::string > ssh_search;
    
    std::string home_path;
    std::string current_path;

    instance = command_result( "echo $HOME" );

    if( instance.empty() )
    {
        return ssh_path;
    }

    home_path = instance.front() + "/";
    current_path = home_path;

    bool finish = false;

    while( !finish )
    {
        instance = command_result( ls + current_path + dir_check );
        //std::cout<< "----> " << current_path << "\n";

        for( int i = 0; i < instance.size(); i++ )
        {
            if( instance[i] == "ssh/" || instance[i] == ".ssh/" )
            {
                finish = true;
                ssh_path = current_path + instance[i];
                break;
            }
            else if( instance[i] != "./" && instance[i] != "../" )
            {
                ssh_search.push( current_path + instance[i] );
            }            
        }
        
        if( ssh_search.empty() )
        {
            finish = true;
        }
        else
        {
            current_path = ssh_search.front();
            ssh_search.pop();
        }
    }

    return ssh_path;
}

std::vector< std::string >
ssh_search::search_file()
{
    std::vector< std::string > result;
    std::vector< std::string > instance;
    std::queue< std::string > search;

    std::string ssh_path = ssh_path_search();

    if( ssh_path.empty() )
    {
        return result;
    }

    std::string ls = "ls -F -a ";
    std::string file_check = "| grep -v /";
    std::string dir_check = " | grep /";

    std::string home_path = ssh_path;
    std::string current_path = home_path;

    bool finish = false;

    while( !finish )
    {
        instance = command_result( ls + current_path + file_check );

        for( int i = 0; i < instance.size(); i++ )
        {
            result.push_back( current_path + instance[i] );
        }

        instance = command_result( ls + current_path + dir_check );
        
        for( int i = 0; i < instance.size(); i++ )
        {
            if( instance[i] != "./" && instance[i] != "../" )
            {
                search.push( current_path + instance[i] );
            }                      
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

