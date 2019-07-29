#include <vector>
#include <iostream>
#include <string>

#ifndef PW_LIST_GENERATE
#define PW_LIST_GENERATE

class pw_list_generate
{
 private:

    struct pw_data
    {
        std::string pasword;
        int limit;
    };

    struct pw_generate_data
    {
        std::string pasword;
        std::vector< int > use_count;
    };


    std::vector< int > limit_count;
    std::vector< std::string > word_list;
    std::vector< std::string > pw_list;
    std::vector< pw_data > use_list;

    std::vector< std::string > name_generate( std::string name );
    void next_generate( std::vector< pw_generate_data > & data );
    
 public:
    void word_set( std::string word, int use_value );
    void word_show(); 
    bool pw_genarate( int pw_size );
    
};

#endif
