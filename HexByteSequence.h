#ifndef HexByteSequence_h
#define HexByteSequence_h

#include "ByteSequence.h"

/// A sequence of hex encoded bytes is also a ByteSequence.
class HexByteSequence: public ByteSequence
{
   public:
      HexByteSequence(const char* hex_encoded_string)
         :ByteSequence(DecodeHexStringToByteVector(hex_encoded_string))
      {
      }
};
#endif
