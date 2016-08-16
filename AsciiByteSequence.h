#ifndef AsciiText_h
#define AsciiText_h

#include <cstring> // std::strlen

#include "ByteVector.h"
#include "Text.h"

/// A sequence of ascii encoded bytes is also a Text.
class AsciiText: public Text
{
   public:
      AsciiText(const char* ascii_encoded_string)
         :Text(ByteVector(
                  ascii_encoded_string,
                  ascii_encoded_string + std::strlen(ascii_encoded_string)))
   {
   }
};
#endif
