#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

#include "pw_list_generate.h"

void
pw_list_generate::word_set( std::string word,
                            int use_value )
{
    word_list.push_back( word );

    std::vector< std::string > instance = name_generate( word );

    int use_size = use_value;
    
    for( std::string word : instance )
    {
        pw_data pd;
        pd.pasword = word;
        pd.limit = use_size;
        use_list.push_back( pd );
    }
}

void
pw_list_generate::word_show()
{
    for( std::string word : word_list )
    {
        std::cout<< word <<"\n";
    }
}

bool
pw_list_generate::pw_genarate( int pw_size )
{
    int size = static_cast< int >( use_list.size() );

    if( size == 0 )
    {
        return false;
    }
    
    std::vector< pw_generate_data > pw_data_list;
    std::vector< int > count_list;

    for( pw_data & pd: use_list )
    {
        count_list.push_back( 0 );
    }

    int use_size = static_cast< int >( use_list.size() );

    for( int i = 0; i < use_size; i++ )
    {
        pw_generate_data pwd;
        pwd.pasword = use_list[i].pasword;
        pwd.use_count = count_list;
        pwd.use_count[i] = 1;
        pw_data_list.push_back( pwd );
        pw_list.push_back( pwd.pasword );
    }

    for( int i = 0; i < pw_size - 1; i++ )
    {
        next_generate( pw_data_list );
    }

    for( std::string & paswaord : pw_list )
    {
        std::cout<< paswaord <<"\n";
    }
}

void
pw_list_generate::next_generate( std::vector< pw_generate_data > & data )
{
    std::vector< pw_generate_data > next_data;
    int size = static_cast< int >( use_list.size() );

    for( pw_generate_data & p : data )
    {
        for( int i = 0; i < size; i++ )
        {
            pw_generate_data pwgd = p;

            if( pwgd.use_count[i] < use_list[i].limit )
            {
                pwgd.pasword += use_list[i].pasword;
                pwgd.use_count[i] += 1;
                next_data.push_back( pwgd );
                pw_list.push_back( pwgd.pasword );
            }
        }
    }

    data = next_data;
}

std::vector< std::string >
pw_list_generate::name_generate( std::string name )
{
    std::vector< std::string > list;
    std::string pw_c = "";

    int size = static_cast< int >( name.size() );

    for( int i = 0; i < size; i++ )
    {
        if( name.c_str()[i] == 'a'
            || name.c_str()[i] == 'b'
            || name.c_str()[i] == 'c'
            || name.c_str()[i] == 'd'
            || name.c_str()[i] == 'e' )
        {
            pw_c += name.c_str()[i];
            list.push_back( pw_c );
            pw_c = "";
        }
        else if( name.c_str()[i] == 'n' )
        {
            if( i != size - 1
                && name.c_str()[i+1] != 'a'
                && name.c_str()[i+1] != 'b'
                && name.c_str()[i+1] != 'c'
                && name.c_str()[i+1] != 'd'
                && name.c_str()[i+1] != 'e')
            {
                pw_c += name.c_str()[i];
                list.push_back( pw_c );
                pw_c = "";
            }
            else
            {
                pw_c += name.c_str()[i];
            }
        }
        else
        {
            pw_c += name.c_str()[i];
        }
    }

    if( pw_c != "" )
    {
        list.push_back( pw_c );
    }

    return list;
}

