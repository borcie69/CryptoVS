#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include "cryptopp/base32.h"
#include "classBlock.h"

std::string block::sha256(const std::string str)
{
    CryptoPP::HexEncoder encoder;

    std::string digest,s;

    CryptoPP::SHA256 hash;
    hash.Update((const CryptoPP::byte*)str.data(),str.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);

    encoder.Put((CryptoPP::byte *)digest.data(),digest.size());
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        s.resize(size);
        encoder.Get((CryptoPP::byte*)&s[0],s.size());
    }

    return s;
}

void block::mining()
{
    std::string hashFirst,validHash,returnHash,s,temp;
    s=joinToString();

    temp=sha256(s);
    //std::cout<<temp<<'\n';

    //if first hash is valid
    for(int a=0;a<dificulty;a++)
    {
        hashFirst+=temp[a];
        validHash+="0";
    }

    while(hashFirst!=validHash)
    {
        nonce++;

        s=joinToString(); //first check hash...
        returnHash=sha256(s); //make hash private

        hashFirst="";
        for(int a=0;a<dificulty;a++)
        {
            hashFirst+=returnHash[a];
        }
    }
    creation();
    hash=returnHash;
}

 void block::genesisBlock()
{
    nonce=0;
    index=0;
    prevHash="";
    data="Genesis Block";
    dificulty=0;
    std::string s=joinToString();
    //std::cout<<s<<std::endl; testing
    hash=sha256(s);
    creation();
}

void block::indexing(unsigned long long prevIndex)
{
    index=++prevIndex;
    //std::cout<<prevIndex<<' '<<index<<std::endl; testing
}

void block::prevHashing(std::string prevPrevHash)
{
    prevHash=prevPrevHash;
    //std::cout<<prevHash<<std::endl; testing
}

void block::getDificulty()
{
    dificulty=4; //ctl
}

void block::giveData()
{
    data="data"; //ctl
}

void block::createBlock(block prevBlock)
{
    indexing(prevBlock.index);
    prevHashing(prevBlock.hash);
    getDificulty();
    giveData();
    mining();
}

std::string block::joinToString()
{
    std::string join;

    join=std::to_string(index)+","
        +prevHash+","
        +data+","
        +std::to_string(dificulty)+","
        +std::to_string(nonce);

    return join;
}

void block::blockData()
{
    std::cout<<"index: "<<index<<std::endl
        <<"prevHash: "<<prevHash<<std::endl
        <<"data: "<<data<<std::endl
        <<"hash: "<<hash<<std::endl
        <<"dificulty: "<<dificulty<<std::endl
        <<"nonce: "<<nonce<<std::endl
        <<"Time: "<<creationTime<<std::endl<<std::endl;
}

std::string block::makePacket()
{
    std::string result=std::to_string(index)+','
        +prevHash+','
        +data+','
        +std::to_string(dificulty)+','
        +std::to_string(nonce)+','
        +hash+','
        +creationTime+';';

    //int sizeOfData=result.size()*sizeof(std::string);

    //result=std::to_string(sizeOfData)+','+result;

    return result;
}

//time of block creation (format dd.mm.yyyy:hh.minmin.ss)
void block::creation()
{
    tm newtime;
    __int64 ltime;
    char buf[26];
    errno_t err;
    _time64(&ltime);
    err=_gmtime64_s(&newtime,&ltime);
    if(err)
    {
        std::cerr<<"Invalid Argument to _gmtime64_s.\n";
    }
    // Convert to an ASCII representation
    err=asctime_s(buf,26,&newtime);
    if(err)
    {
        std::cerr<<"Invalid Argument to asctime_s.\n";
    }

    std::string timeString;
    timeString=std::to_string(newtime.tm_mday)+'.'
        +std::to_string(newtime.tm_mon+1)+'.'
        +std::to_string(newtime.tm_year+1900)+':'
        +std::to_string(newtime.tm_hour)+'.'
        +std::to_string(newtime.tm_min)+'.'
        +std::to_string(newtime.tm_sec);
    //std::string tString=timeString.str();

    creationTime=timeString;
}

/*void block::createBlock(block *prevBlock)
{
    /*std::cout<<prevBlock.index<<" "<<prevBlock.prevHash<<" "<<prevBlock.dificulty<<" "<<prevBlock.data<<
    " "<<prevBlock.nonce<<" "<<prevBlock.hash<<" "<<prevBlock.creationTime<<std::endl; //testing
    indexing(prevBlock->index);
    prevHashing(prevBlock->hash);
    getDificulty();
    giveData();
    mining();
}*/

/*block::~block()
{
    creation();
}*/