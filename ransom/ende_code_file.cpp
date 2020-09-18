#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "RSA.h"
#include "ende_code_file.h"

bool
code::encode_file( std::string file_name, long p_key1, long p_key2)//ファイルを暗号化する
{
    std::vector< char > word_list = encode_file_read( file_name );
    std::vector< int > en_word_list;

    //暗号化
    for( char c : word_list )
    {
        en_word_list.push_back( RSA().powmod( c, p_key1, p_key2) );
    }
    
    encode_file_write( file_name, en_word_list );
    
    return true;
}

bool
code::decode_file( std::string file_name, long s_key, long p_key)//ファイルを復号する
{
    std::vector< int > word_value = decode_file_read( file_name );//暗号化された数値を読み込む
                    
    std::vector< char > write_word = msg_decode( word_value, s_key, p_key );//復号
    
    decode_file_write( file_name, write_word );

    return true;
}

//decodeの時に使うファイル書き込み
void
code::decode_file_write( std::string file_name, std::vector< char > word )
{
    std::ofstream ofs( file_name );

    for( int i = 0; i < word.size(); i++ )
    {
        ofs << word[i];
    }
    
    ofs.close();
}

//encodeの時に使うファイル書き込み
void
code::encode_file_write( std::string file_name, std::vector< int > word_list )
{
    std::ofstream ofs( file_name );
    
    for( int word_value : word_list )
    {
        ofs << word_value << " ";
    }

    ofs.close();
}

//decodeのときのファイル読み込み
std::vector< int >
code::decode_file_read( std::string file_name )
{
    std::ifstream ifs( file_name );
    std::string str;
    std::vector< int > word_list;
    int s;

    if( !ifs.fail() )
    {        
        while( ifs >> s )
        {
            word_list.push_back( s );
        }
    }

    ifs.close();
    return word_list;
    
}

std::vector< char >
code::encode_file_read( std::string file_name )
{
    std::ifstream ifs( file_name );
    std::string str;
    char c;
    std::vector< char > word_list;

    if( !ifs.fail() )
    {
        while( ifs.get( c ) )
        {
            word_list.push_back( c );
        }
    }

    
    ifs.close();
    
    return word_list;
}

std::vector< int >
code::msg_encode( const char *word, int p_key1, int p_key2 )
{
    std::vector< int > en_value;

    for( int i = 0; i < sizeof( word ); i++ )
    {
        en_value.push_back( RSA().powmod( word[i], p_key1, p_key2) );
    }

    return en_value;
}

std::vector< char >
code::msg_decode( std::vector< int > &word_value, long s_key, long p_key )
{
    std::vector< char > c_word;
    
    for( int i = 0; i < word_value.size(); i++ )
    {
        int word = RSA().powmod( word_value[i], s_key, p_key);
        c_word.push_back( word );
    }
    
    return c_word;
}
