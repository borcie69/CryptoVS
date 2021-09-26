#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>

//block template
class block
{
    unsigned long long index=0;
    std::string prevHash;
    std::string data;
    int dificulty=0;
    unsigned long long nonce=0;
    std::string hash;
    std::string creationTime;

public:
    //block();
    //block(block*);
    void genesisBlock();
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

    //make packet for network
    std::string makePacket();

    //create block(join all functions)
    void createBlock(block);

    //~block();
};

#endif