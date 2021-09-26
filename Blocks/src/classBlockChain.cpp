#include <iostream>
#include "classBlockChain.h"

blockChain::blockChain()
{
    block *genesis=new block;

    //genesis->genesisBlock();

    if (genesis->validHashCheck())
    {
        allBlocks.push_back(*genesis);
    }

    delete genesis;
}

block blockChain::lastBlock()
{
    return allBlocks.back();
}

void blockChain::newBlock()
{
    block *newBl=new block(lastBlock().getIndex(),lastBlock().getHash());

    //newBl->createBlock(lastBlock());

    if (newBl->validHashCheck())
    {
        allBlocks.push_back(*newBl);
    }

    delete newBl;
}