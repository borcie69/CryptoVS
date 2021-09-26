#ifndef CLASS_BLOCK_CHAIN_HPP
#define CLASS_BLOCK_CHAIN_HPP

#include <vector>
#include "classBlock.h"

class blockChain
{
    std::vector<block> allBlocks;

public:
    blockChain();
    block lastBlock();
    void newBlock();
};

//continue

#endif