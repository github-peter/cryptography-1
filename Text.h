#ifndef Text_h
#define Text_h
#include <algorithm> // std::fill, std::min, std::transform
#include <cctype> // std::iscntrl
#include <iterator> // std::back_inserter
#include <string>

#include <boost/algorithm/hex.hpp>

#include "Byte.h"
#include "ByteVector.h"

/// A sequence of bytes is a Text.
class Text
{
   public:
      Byte operator[](ByteVector::size_type i) const
      {
         return characters.at(i);
      }
      Byte& operator[](ByteVector::size_type i)
      {
         return characters.at(i);
      }
      /// xor two strings (this and s) of possibly different lengths
      Text operator^(const Text& s) const
      {
         const ByteVector::size_type N(
               std::min(characters.size(),s.characters.size()));

         Text result(N);

         std::transform( characters.begin(), characters.begin()+N,
               s.characters.begin(),
               result.characters.begin(),
               [](Byte a,Byte b)->Byte{return a^b;} );

         return result;
      }
      ByteVector::size_type size() const
      {
         return characters.size();
      }
      /// Convert to a string with printable characters.
      /// Any non-printable character is replaced with a space.
      std::string ToString() const
      {
         std::string result(characters.size(),'\0');
         std::transform(
               characters.begin(), characters.end(),
               result.begin(),
               [](Byte a)->char{return (! std::iscntrl(a)?(char)a:' ');} );
         return result;
      }
      /// Convert to a hex encoded string.
      std::string ToHexString() const
      {
         std::string result;
         boost::algorithm::hex(characters, std::back_inserter(result));
         return result;
      }
      void ZeroAllBytes()
      {
         std::fill(characters.begin(),characters.end(),0);
      }
   protected:
      Text(ByteVector v): characters(v){}
      static ByteVector ToByteVector(const char* hex_encoded_string)
      {
         ByteVector result;
         boost::algorithm::unhex(
               hex_encoded_string,
               std::back_inserter(result));
         return result;
      }
   private:
      ByteVector characters;
      Text(ByteVector::size_type size = 0):characters(size) {}
};
#endif
