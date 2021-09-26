#include <vector>
#include <iostream>
//#include "hdr/crypt.hpp"
#include "classBlock.h"
//#include "hdr/net.hpp"
#include <thread>
#include <fstream>
#include "classBlockChain.h"

int main()
{
    //networking for this device, start to listen on port
    //thisDev *current=new thisDev;
    //std::string PFLoc="../data/blockChain.txt";
    //std::fstream packetFile(PFLoc);

    //start blockchain
    blockChain SomeCoin;

    //block *genesisBlock=new block;
    //std::vector<block> blockChain;
    std::vector<char> test;
    std::string packet;
    //std::thread tl;

    //hardcoded first block
    //genesisBlock->genesisBlock();

    packet=SomeCoin.lastBlock().makePacket();
    std::cout<<packet<<std::endl; //test
    //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
    //packetFile<<packet<<'\n'; //make this work
    //packetFile.close();

    //adding genesisBlock to vector
    //blockChain.push_back(*genesisBlock);
    //delete genesisBlock;
    //printing block data
    SomeCoin.lastBlock().blockData();
    //std::cout<<blockChain.size()<<' '<<blockChain.max_size()<<' '<<test.max_size()<<std::endl; //vector data
    //std::cout<<sizeof(char)<<std::endl;

    //thread for listening for incoming packets
    //tl=current->acceptingThread();

    //generating blocks
    while(true)
    {
        SomeCoin.newBlock();

        packet=SomeCoin.lastBlock().makePacket();
        std::cout<<packet<<std::endl;

        //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
        //packetFile<<packet<<'\n';
        //packetFile.close();

        //current->sendingPacket(packet);

        //std::string s=blockChain.back().joinToString();
        //std::cout<<s<<std::endl; //testing

        SomeCoin.lastBlock().blockData();
    }

    return 0;
}