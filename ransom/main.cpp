#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

#include "RSA.h"
#include "ende_code_file.h"
#include "search_file.h"

int main()
{
    search s;
    std::vector< std::string >list = s.search_file();
    
    RSA rsa;
    RSA::code_key ck = rsa.key_generate( 1000 );
    
    for( int i = 0; i < list.size(); i++ )
    {
        //code().encode_file( list[i], ck.public_key_1, ck.public_key_2 );
        code().decode_file( list[i], 1370393, 2991119 );
    }

    //code().encode_file( "test.JPG", ck.public_key_1, ck.public_key_2 );
    //code().decode_file( "test.JPG", 637397, 2390891 );
    //code().decode_file( "test.JPG", ck.secret_key, ck.public_key_2 );

    std::cout<< "公開鍵1 " << ck.public_key_1 <<"\n";
    std::cout<< "公開鍵2 " << ck.public_key_2 <<"\n";
    std::cout<< "秘密鍵 " << ck.secret_key <<"\n";

}
