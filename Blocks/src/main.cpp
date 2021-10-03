#include <vector>
#include <iostream>
#include <thread>
#include <fstream>
#include "classBlock.h"
#include "classBlockChain.h"
#include "cudaMiner.h"
#include "serverImplementationsP2P.h"
#include "receiverImplementationsP2P.h"

int main()
{
    //networking
    server server1;
    receiver receiver1;
    //thread to listen for incoming packets
    std::thread forServer = server1.threadForListening();

    #ifdef CUDA_MINING
        cudaMiner miner("sdfsdfsdfs");
        miner.doCuda();
    #endif
    //std::string PFLoc="../data/blockChain.txt";
    //std::fstream packetFile(PFLoc);

    //start blockchain
    blockChain UNIVERSUM;
    std::string packet;

    //make packet for sending over network
    packet=UNIVERSUM.lastBlock().makePacket();
    std::cout<<packet<<'\n'; //testing

    char* writable = new char[packet.size() + 1];
    std::copy(packet.begin(), packet.end(), writable);
    writable[packet.size()] = '\0';

    receiver1.sendingPacket("192.168.137.194", writable);

    delete[] writable;
    //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
    //packetFile<<packet<<'\n'; //make this work
    //packetFile.close();

    //printing block data
    UNIVERSUM.lastBlock().blockData();
    //std::cout<<blockChain.size()<<' '<<blockChain.max_size()<<' '<<test.max_size()<<std::endl; //vector data

    //generating blocks, improve handling
    while(true)
    {
        UNIVERSUM.newBlock();

        packet=UNIVERSUM.lastBlock().makePacket();
        std::cout<<packet<< '\n'; //testing

        char* writable = new char[packet.size() + 1];
        std::copy(packet.begin(), packet.end(), writable);
        writable[packet.size()] = '\0';

        receiver1.sendingPacket("192.168.137.194",writable);

        delete[] writable;

        //packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
        //packetFile<<packet<<'\n';
        //packetFile.close();

        //current->sendingPacket(packet);

        //std::string s=blockChain.back().joinToString();
        //std::cout<<s<<std::endl; //testing

        //print block data
        UNIVERSUM.lastBlock().blockData();
    }

    return 0;
}