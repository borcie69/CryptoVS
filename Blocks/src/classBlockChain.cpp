#include "classBlockChain.h"

blockChain::blockChain()
{
    block *genesis=new block;

    genesis->genesisBlock();

    allBlocks.push_back(*genesis);

    delete genesis;
}

block blockChain::lastBlock()
{
    return allBlocks.back();
}

void blockChain::newBlock()
{
    block *newBl=new block;

    newBl->createBlock(lastBlock());

    allBlocks.push_back(*newBl);

    delete newBl;
}