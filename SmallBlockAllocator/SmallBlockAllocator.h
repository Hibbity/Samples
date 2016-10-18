/*
Author: Ryan Kirschman
Date: 3/30/2016

The Small Block Allocator is part of a memory management system.
Memory that is under a specific size (the block size) is designated to be allocated to a single block in the SBA.
Each SBA has a specific block size and block count.
It uses a Bitfield to keep track of which blocks are in use.
*/

#pragma once

// Forward declare the Bitfield
class Bitfield;

namespace Memory
{

	class SmallBlockAllocator
	{
	public:
		// A failsafe constructor.
		// BlockSize is how large each block is. BlockCount is how many blocks.
		static SmallBlockAllocator* Create(size_t blockSize, size_t blockCount);

		~SmallBlockAllocator();

		// Allocate to a block and Free from a Block.
		void* Alloc(size_t size);
		void Free(void* ptr);

		// Is the block that contains this pointer being used? Returns true if it does contain the ptr and is set.
		bool Contains(void* ptr);

		// How many blocks are free?
		size_t BlocksFree();

	private:
		SmallBlockAllocator(size_t blockSize, size_t blockCount, void* pBlock, Bitfield* pBitfield);

		size_t _BlockSize; // How large is each block?
		size_t _BlockCount; // How many blocks?
		void* _pBlock; // Where are the blocks located?
		Bitfield* _pBitfield; // The bitfield being used.
	};

} // End namespace Memory

#include "SmallBlockAllocator.inl"