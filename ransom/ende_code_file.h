#ifndef ENDE_CODE_FILE_H
#define ENDE_CODE_FILE_H

class code
{
 public:
    bool encode_file( std::string file_name, long p_key1, long p_key2);//ファイルを暗号化する
    bool decode_file( std::string file_name, long s_key, long p_key);//ファイルを復号する
 private:
    std::vector< int > msg_encode( const char *word, int p_key1, int p_key2 );
    std::vector< char > msg_decode( std::vector< int > &word_value, long s_key, long p_key );
    
    std::vector< char > encode_file_read( std::string file_name );
    std::vector< int > decode_file_read( std::string file_name );
    
    void decode_file_write( std::string file_name, std::vector< char > );
    void encode_file_write( std::string file_name, std::vector< int > word_list );

};
#endif
