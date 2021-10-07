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
	//winsockInit wInit;
	//server server1;

	//bool sharedForListeining=false; //shared memory between threads
	//std::thread forServer=server1.threadForListening(&sharedForListeining); //thread to listen for incoming packets

#ifdef CUDA_MINING
	cudaMiner miner("sdfsdfsdfs");
	miner.doCuda();
#endif

	//std::string PFLoc="../data/blockChain.txt";
	//std::fstream packetFile(PFLoc);

	blockChain UNIVERSUM; //start blockchain
	std::string packet;

	packet=UNIVERSUM.lastBlock().makePacket(); //make packet for sending over network
	std::cout<<packet<<'\n'; //testing

	UNIVERSUM.lastBlock().blockData(); //print block data

	//convert string to char*
	char *writable=new char[packet.size()+1];
	std::copy(packet.begin(),packet.end(),writable);
	writable[packet.size()]='\0';

	//receiver1.sendingPacket("192.168.137.194", writable);
	receiver *rec=new receiver("127.0.0.1",writable);
	delete rec;
	delete[] writable;

	//packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
	//packetFile<<packet<<'\n'; //make this work
	//packetFile.close();

	//std::cout<<blockChain.size()<<' '<<blockChain.max_size()<<' '<<test.max_size()<<std::endl; //vector data

	//generating blocks, improve handling
	while(true)
	{
		//std::cout<<sharedForListeining<<'\n';
		UNIVERSUM.newBlock();

		packet=UNIVERSUM.lastBlock().makePacket();
		std::cout<<packet<<'\n'; //testing

		UNIVERSUM.lastBlock().blockData(); //print block data

		//convert string to char*
		char *writable=new char[packet.size()+1];
		std::copy(packet.begin(),packet.end(),writable);
		writable[packet.size()]='\0';

		//receiver1.sendingPacket("192.168.137.194",writable);
		receiver *rec=new receiver("127.0.0.1",writable);
		delete rec;
		delete[] writable;

		//packetFile.open(PFLoc.c_str(),std::ios_base::app | std::ios_base::in);
		//packetFile<<packet<<'\n';
		//packetFile.close();

		//current->sendingPacket(packet);

		//std::string s=blockChain.back().joinToString();
		//std::cout<<s<<std::endl; //testing
	}

	return 0;
}