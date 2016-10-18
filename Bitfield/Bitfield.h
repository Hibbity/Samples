/*
Author: Ryan Kirschman
Date: 3/30/2016

The Bitfield is used to store multiple true/false values in one piece of data.
While the bool data type is 1 byte, it can only hold 1 true/false value. 
In reality, it only needs 1 bit. 
A bitfield is good to use when you need to store many booleans at once.
*/

#pragma once

class Bitfield
{
public:
	// Static failsafe constructors used to create a Bitfield. Will return NULL if no memory is available.
	// fieldSize is how many bits are needed for our field.
	static inline Bitfield* Create(const size_t fieldSize);

	// This is used if a location has already been assigned for the pointer.
	// This pointer is then updated once we've allocated the memory needed.
	// This should only be used when we know for certain there is enough memory, such as the initialization of a memory manager.
	static inline Bitfield* Create(const size_t fieldSize, void*& io_pField);

	inline ~Bitfield();

	// Getters
	const size_t FieldSize() const { return _FieldSize; }
	const size_t FreeBits() const { return _FreeBits; }

	// Overload operator [] to return true/false if bit is set/free.
	inline bool operator[](size_t index);

	// Accessors
	inline bool FirstFreeBit(size_t& o_index); // Finds the first free bit. Returns false if no bit is free.
	inline bool FirstSetBit(size_t& o_index); // Finds the first set bit. Returns false if no bit is set.
	inline void SetBit(size_t i_index); // Sets a bit to 1.
	inline void FreeBit(size_t i_index); // Sets a bit to 0.
	inline void ToggleBit(size_t i_index); // Sets a bit to 1 if 0 and 0 if 1.

private:
	// A private constructor is used
	inline Bitfield(const size_t fieldSize, unsigned int* pField);

	size_t _FreeBits; // The number of bits free in our bitfield.
	size_t _FieldSize; // The number of bits in our bitfield.
	unsigned int* _pField; // The location of the bitfield itself.
};

#include "Bitfield.inl"
