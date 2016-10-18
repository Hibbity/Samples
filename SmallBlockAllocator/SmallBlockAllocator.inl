/*
Author: Ryan Kirschman
Date: 3/30/2016

An inline file used to define my inline functions for the SmallBlockAllocator
*/

namespace Memory
{
	SmallBlockAllocator* SmallBlockAllocator::Create(size_t blockSize, size_t blockCount)
	{
		char* pBlock = reinterpret_cast<char *>(malloc(blockSize * blockCount));
		if (pBlock == nullptr)
			return nullptr;

		Bitfield* pBitfield = Bitfield::Create(blockCount);
		if (pBitfield == nullptr)
		{
			delete[] pBlock;
			return nullptr;
		}

		return new SmallBlockAllocator(blockSize, blockCount, pBlock, pBitfield);
	}

	SmallBlockAllocator::~SmallBlockAllocator()
	{
		delete _pBitfield;
	}


	void* SmallBlockAllocator::Alloc(size_t size) {
		size_t index = 0;

		if (_pBitfield->FirstFreeBit(index)) {
			_pBitfield->SetBit(index);
			return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_pBlock) + (index * _BlockSize));
		}

		return nullptr;
	}

	void SmallBlockAllocator::Free(void* ptr) {
		if (ptr < _pBlock || ptr >= _pBlock) {
			return;
		}
		if (!Contains(ptr)) {
			return;
		}

		size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_pBlock)) / _BlockSize;
		_pBitfield->FreeBit(index);
	}

	bool SmallBlockAllocator::Contains(void* ptr) {
		if (reinterpret_cast<uintptr_t>(ptr) == 0xfeeefeee) 
		{
			return false;
		}

		size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_pBlock)) / _BlockSize;

		if (index < 0 || index >= _BlockCount) 
		{
			// If our ptr is not in a block
			return false;
		}
		return _pBitfield->operator[](index);
	}

	unsigned int SmallBlockAllocator::BlocksFree() { return _pBitfield->FreeBits(); }

	SmallBlockAllocator::SmallBlockAllocator(size_t blockSize, unsigned int blockCount, void* pBlock, Bitfield* pBitfield) :
		_BlockSize(blockSize),
		_BlockCount(blockCount),
		_pBlock(pBlock),
		_pBitfield(pBitfield)
	{}
}