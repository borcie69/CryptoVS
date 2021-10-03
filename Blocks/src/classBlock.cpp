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

//using cryptopp for sha256
std::string block::sha256(const std::string str)
{
    CryptoPP::HexEncoder encoder;

    std::string digest,s;

    CryptoPP::SHA256 hash;
    hash.Update((const CryptoPP::byte*)str.data(),str.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);

    encoder.Put((CryptoPP::byte*)digest.data(),digest.size());
    encoder.MessageEnd();

    CryptoPP::word64 size=encoder.MaxRetrievable();
    if(size && size<=SIZE_MAX)
    {
        s.resize(size);
        encoder.Get((CryptoPP::byte*)&s[0],s.size());
    }

    return s;
}

//CPU mining(optimize)
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
    this->hash=returnHash;
}

 //void block::genesisBlock()
 block::block()
{
    this->nonce=0;
    this->index=0;
    this->prevHash="";
    this->data="Genesis Block";
    this->dificulty=0;
    std::string s=joinToString();
    //std::cout<<s<<std::endl; testing
    this->hash=sha256(s);
    creation();
}

 block::block(unsigned long long prevIndexfpb, std::string prevHashfpb)
 {
     indexing(prevIndexfpb);
     prevHashing(prevHashfpb);
     getDificulty();
     giveData();
     mining();
 }

void block::indexing(unsigned long long prevIndex)
{
    this->index=++prevIndex;
    //std::cout<<prevIndex<<' '<<index<<std::endl; testing
}

void block::prevHashing(std::string prevPrevHash)
{
    this->prevHash=prevPrevHash;
    //std::cout<<prevHash<<std::endl; testing
}

void block::getDificulty()
{
    this->dificulty=5; //ctl
}

void block::giveData()
{
    this->data="data"; //ctl
}

//void block::createBlock(block prevBlock)
/*block::block(unsigned long long prevIndexfpb, std::string prevHashfpb)
{
    indexing(prevIndexfpb);
    prevHashing(prevHashfpb);
    getDificulty();
    giveData();
    mining();
}*/

std::string block::joinToString()
{
    std::string join;

    join=std::to_string(this->index)+","
        + this->prevHash+","
        + this->data+","
        +std::to_string(this->dificulty)+","
        +std::to_string(this->nonce);

    return join;
}

void block::blockData()
{
    std::cout<<"index: "<<this->index<<std::endl
        <<"prevHash: "<<this->prevHash<<std::endl
        <<"data: "<<this->data<<std::endl
        <<"hash: "<<this->hash<<std::endl
        <<"dificulty: "<<this->dificulty<<std::endl
        <<"nonce: "<<this->nonce<<std::endl
        <<"Time: "<<this->creationTime<<std::endl<<std::endl;
}

std::string block::makePacket()
{
    std::string result=std::to_string(this->index)+','
        +this->prevHash+','
        +this->data+','
        +std::to_string(this->dificulty)+','
        +std::to_string(this->nonce)+','
        +this->hash+','
        +this->creationTime+';';

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
        //write to erroLog
    }
    // Convert to an ASCII representation
    err=asctime_s(buf,26,&newtime);
    if(err)
    {
        //write to erroLog
    }

    std::string timeString;
    timeString=std::to_string(newtime.tm_mday)+'.'
        +std::to_string(newtime.tm_mon+1)+'.'
        +std::to_string(newtime.tm_year+1900)+':'
        +std::to_string(newtime.tm_hour)+'.'
        +std::to_string(newtime.tm_min)+'.'
        +std::to_string(newtime.tm_sec);
    //std::string tString=timeString.str();

    this->creationTime=timeString;
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

bool block::validHashCheck()
{
    std::string s=this->joinToString();

    std::string tempHash=this->sha256(s);

    if(tempHash!=this->hash)
    {
        return false;
        //write to file
    }
    else
    {
        return true;
    }
}

unsigned long long block::getIndex()
{
    return this->index;
}

std::string block::getHash()
{
    return this->hash;
}

/*block::~block()
{
    creation();
}*/