#ifndef ByteSequence_h
#define ByteSequence_h

#include <algorithm> // std::fill, std::min, std::move, std::replace, std::transform
#include <cctype> // std::iscntrl
#include <iterator> // std::back_inserter, std::inserter
#include <string>

#include <boost/algorithm/hex.hpp>

#include "Byte.h"
#include "ByteVector.h"

/// A sequence of bytes is a ByteSequence.
class ByteSequence
{
   public:
      ByteSequence(ByteVector v): characters(v){}
      Byte operator[](ByteVector::size_type i) const
      {
         return characters.at(i);
      }
      Byte& operator[](ByteVector::size_type i)
      {
         return characters.at(i);
      }
      /// xor two sequences of bytes (this and s) of possibly different lengths
      ByteSequence operator^(const ByteSequence& s) const
      {
         const ByteVector::size_type N(
               std::min(characters.size(),s.characters.size()));

         ByteSequence result(N);

         std::transform( characters.begin(), characters.begin()+N,
               s.characters.begin(),
               result.characters.begin(),
               [](Byte a,Byte b)->Byte{return a^b;} );

         return result;
      }
      /// Append another sequence to this.
      void Append(ByteSequence appendix)
      {
         characters.reserve(characters.size() + appendix.characters.size() );
         std::move(
               appendix.characters.begin(),
               appendix.characters.end(),
               std::inserter(characters, characters.end()));
      }
      /// Set all bytes to the supplied byte.
      void Fill(Byte a)
      {
         std::fill(characters.begin(),characters.end(),a);
      }
      /// Replace all what's with with's.
      void Replace(Byte what, Byte with)
      {
         std::replace(characters.begin(),characters.end(),what,with);
      }
      ByteVector::size_type Size() const
      {
         return characters.size();
      }
      /// Extract part of this sequence as a new sequence.
      /// The caller is responsible for ensuring that the arguments are
      /// reasonable for this sequence.
      /// @param start The start index of the extracted sequence.
      /// @param length The length of the extracted sequence. 
      ByteSequence SubSequence(
            ByteVector::size_type start,
            ByteVector::size_type length) const
      {
         return ByteSequence(ByteVector(
                  characters.begin()+start,
                  characters.begin()+start+length));
      }
      ByteVector ToByteVector() const
      {
         return characters;
      }
      /// Convert to a hex encoded string.
      std::string ToHexString() const
      {
         std::string result;
         boost::algorithm::hex(characters, std::back_inserter(result));
         return result;
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
   protected:
      static ByteVector DecodeHexStringToByteVector(
            const char* hex_encoded_string)
      {
         ByteVector result;
         boost::algorithm::unhex(
               hex_encoded_string,
               std::back_inserter(result));
         return result;
      }
   private:
      ByteVector characters;
      ByteSequence(ByteVector::size_type size = 0):characters(size) {}
};
#endif
