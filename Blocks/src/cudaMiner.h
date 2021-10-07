//for start just CUDA
//#define CUDA_MINING //for testing(after testing mining should be defined by user)
#ifdef CUDA_MINING //for turning miner on and off

#ifndef CUDA_MINER_H
#define CUDA_MINER_H

#include <iostream>
#include <string>


class cudaMiner
{
	std::string toMine;
	std::string finishedHash;

public:
	cudaMiner(std::string);
	void doCuda();
};


#endif //CUDA_MINER_H
#endif //CUDA_MINING