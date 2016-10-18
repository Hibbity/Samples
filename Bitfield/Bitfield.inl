/*
Author: Ryan Kirschman
Date: 3/30/2016

An inline file used to define my inline functions for the Bitfield.
All of the methods for my Bitfield are inlined as they are simple functions except for the static Create methods.
*/

#define BITS_IN_BYTES 8
#define MAXUINT32_T 4294967296

inline Bitfield::Bitfield(size_t fieldSize, unsigned int* pField) :
	_FieldSize(fieldSize),
	_pField(pField),
	_FreeBits(fieldSize)
{}

inline Bitfield::~Bitfield()
{ 
	delete _pField; 
}

inline bool Bitfield::operator[](size_t index) {
	if (index < 0 || index >= _FieldSize) {
		return false;
	}

	//which index in m_pField does i_index lie
	size_t fieldNumber = index / (sizeof(int) * BITS_IN_BYTES);
	//which bit does it correspond to in m_pField[fieldNumber]
	unsigned int offset = index - (fieldNumber * sizeof(int)* BITS_IN_BYTES);

	//shift by offset and see if it's set or free
	return !!((_pField[fieldNumber]) & (1 << offset));
}

inline bool Bitfield::FirstFreeBit(size_t& o_index) {
	size_t fieldNumber = 0;

	while (fieldNumber < (_FieldSize / (sizeof(unsigned int) * BITS_IN_BYTES + 1))) {
		if (_pField[fieldNumber] == MAXUINT32_T)
		{
			fieldNumber++;
			continue;
		}
		for (size_t i = 0; i < sizeof(int); i++) {
			//check to see if we are out of range of bitfield while still in array
			if (fieldNumber * (sizeof(unsigned int) * BITS_IN_BYTES) + i >= _FieldSize)
			{
				o_index = -1;
				return false;
			}
			if (!((_pField[fieldNumber]) & (1 << i))) {
				o_index = fieldNumber * sizeof(unsigned int) * BITS_IN_BYTES + i;
				return true;
			}
		}
		o_index = -1;
		return false;
	}
	o_index = -1;
	return false;
}

inline bool Bitfield::FirstSetBit(size_t& o_index) {
	size_t fieldNumber = 0;

	while (fieldNumber < (_FieldSize / (sizeof(unsigned int) * BITS_IN_BYTES + 1))) {
		if (_pField[fieldNumber] == 0) {
			fieldNumber++;
			continue;
		}
		for (size_t i = 0; i < sizeof(int); i++) {
			//check to see if we are out of range of bitfield while still in array
			if (fieldNumber * (sizeof(unsigned int) * BITS_IN_BYTES) + i >= _FieldSize)
			{
				o_index = -1;
				return false;
			}

			if (_pField[fieldNumber] & (1 << i)) {
				o_index = fieldNumber * sizeof(unsigned int) * BITS_IN_BYTES + i;
				return true;
			}
		}
		o_index = -1;
		return false;
	}
	o_index = -1;
	return false;
}

inline void Bitfield::SetBit(size_t index) {
	size_t fieldNumber = index / (sizeof(unsigned int) * BITS_IN_BYTES);
	unsigned int offset = index - (fieldNumber * sizeof(unsigned int) * BITS_IN_BYTES);

	if (!this->operator[](index))
	{
		_pField[fieldNumber] |= (1 << offset);
		_FreeBits--;
	}
}

inline void Bitfield::FreeBit(size_t index) {
	size_t fieldNumber = index / (sizeof(unsigned int) * BITS_IN_BYTES);
	unsigned int offset = index - (fieldNumber * sizeof(unsigned int) * 8);

	if (this->operator[](index))
	{
		_pField[fieldNumber] &= ~(1 << offset);
		_FreeBits++;
	}
}

inline void Bitfield::ToggleBit(size_t index)
{
	size_t fieldNumber = index / (sizeof(unsigned int) * BITS_IN_BYTES);
	unsigned int offset = index - (fieldNumber * sizeof(unsigned int) * 8);
		
	_pField[fieldNumber] ^=  ~(1 << offset);
	_FreeBits++;
}