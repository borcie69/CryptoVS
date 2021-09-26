#include <vector>
#include <iostream>
#include <thread>
#include <fstream>
#include "classBlock.h"
#include "classBlockChain.h"

int main()
{
    //networking for this device, start to listen on port
    //thisDev *current=new thisDev;
    //std::string PFLoc="../data/blockChain.txt";
    //std::fstream packetFile(PFLoc);

    //start blockchain
    blockChain SomeCoin;
    std::string packet;
    //std::thread tl;

    //make packet for sending over network
    packet=SomeCoin.lastBlock().makePacket();
    std::cout<<packet<<'\n'; //testing
    //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
    //packetFile<<packet<<'\n'; //make this work
    //packetFile.close();

    //printing block data
    SomeCoin.lastBlock().blockData();
    //std::cout<<blockChain.size()<<' '<<blockChain.max_size()<<' '<<test.max_size()<<std::endl; //vector data
    //std::cout<<sizeof(char)<<std::endl;

    //thread for listening for incoming packets
    //tl=current->acceptingThread();

    //generating blocks, improve handling
    while(true)
    {
        SomeCoin.newBlock();

        packet=SomeCoin.lastBlock().makePacket();
        std::cout<<packet<< '\n'; //testing

        //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
        //packetFile<<packet<<'\n';
        //packetFile.close();

        //current->sendingPacket(packet);

        //std::string s=blockChain.back().joinToString();
        //std::cout<<s<<std::endl; //testing

        //print block data
        SomeCoin.lastBlock().blockData();
    }

    return 0;
}