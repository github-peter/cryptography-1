#ifndef HexText_h
#define HexText_h

#include "Text.h"

/// A sequence of hex encoded bytes is also a Text.
class HexText: public Text
{
   public:
      HexText(const char* hex_encoded_string)
         :Text(ToByteVector(hex_encoded_string))
      {
      }
};
#endif
