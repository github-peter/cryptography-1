#ifndef AsciiByteSequence_h
#define AsciiByteSequence_h

#include <cstring> // std::strlen

#include "ByteSequence.h"
#include "ByteVector.h"

/// A sequence of ascii encoded bytes is also a ByteSequence.
class AsciiByteSequence: public ByteSequence
{
   public:
      AsciiByteSequence(const char* ascii_encoded_string)
         :ByteSequence(ByteVector(
                  ascii_encoded_string,
                  ascii_encoded_string + std::strlen(ascii_encoded_string)))
   {
   }
};
#endif
