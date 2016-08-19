#ifndef PRP_h
#define PRP_h

#include "ByteSequence.h"
#include "ByteVector.h"

/// A pseudo random permutation, aka Block Cipher, base class.
class PRP
{
   public:
      virtual ByteSequence Decrypt( const ByteSequence& cipher ) const=0;

      virtual ByteSequence Encrypt( const ByteSequence& message ) const=0;

      virtual ByteVector::size_type GetBlockSize() const=0;
};
#endif
