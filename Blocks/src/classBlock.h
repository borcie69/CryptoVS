#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>

//block template
class block
{
    unsigned long long index=0;
    std::string prevHash;
    std::string data;
    int dificulty;
    unsigned long long nonce=0;
    std::string hash;
    std::string creationTime;

public:
    //used just for genesis block
    block();
    //used for all other blocks
    block(unsigned long long,std::string);
    //indexing
    void indexing(unsigned long long);
    //previous hash
    void prevHashing(std::string);
    //dificulty of mining
    void getDificulty();
    //give block data
    void giveData();
    //join block data to string
    std::string joinToString();
    //output block data
    void blockData();
    //sha256
    std::string sha256(const std::string);
    //mining
    void mining();
    //time of creation
    void creation();
    //check hash
    bool validHashCheck();
    //make packet for network
    std::string makePacket();
    //create block(join all functions)
    unsigned long long getIndex();
    std::string getHash();

    //~block();
};

#endif