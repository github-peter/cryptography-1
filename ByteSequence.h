#ifndef ByteSequence_h
#define ByteSequence_h

#include <algorithm>
#include <cctype>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <string>

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
      /// Erase some number of bytes from the end of the sequence.
      void EraseFromEnd(const ByteVector::size_type& n)
      {
         if( n < characters.size() )
            characters.erase(
                  characters.end()-n,
                  characters.end());
         else
            characters.clear();
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
      /// If the arguments imply a range larger than the size of this sequence,
      /// then the extracted part ends when this sequence ends.
      /// @param start The start index in this sequence where the extracted
      /// sequence begins.
      /// @param length The length of the extracted sequence. 
      ByteSequence SubSequence(
            ByteVector::size_type start,
            ByteVector::size_type length) const
      {
         if( characters.size() > start+length )
            return ByteSequence(ByteVector(
                     characters.begin()+start,
                     characters.begin()+start+length));
         else
            return ByteSequence(ByteVector(
                     characters.begin()+start,
                     characters.end()));
      }
      ByteVector ToByteVector() const
      {
         return characters;
      }
      /// Convert to a hex encoded string.
      std::string ToHexString() const
      {
         std::string result;
         result.reserve( characters.size()*2 );
         for( Byte b : characters )
         {
            result.push_back( hexchars[b >> 4] );
            result.push_back( hexchars[b & 15] );
         }
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
            std::string hex_encoded_string)
      {
         const auto len(hex_encoded_string.size());
         if(len & 1)
            throw std::invalid_argument(
                  "ByteSequence::DecodeHexStringToByteVector: Argument has"
                  " odd length.");
         // Need uppercase since we look into hexchars.
         std::transform(
               hex_encoded_string.begin(),
               hex_encoded_string.end(),
               hex_encoded_string.begin(),
               std::ptr_fun<int, int>(std::toupper));

         ByteVector result;
         result.reserve(len/2);
         for( std::string::size_type i(0); i < len; i += 2 )
         {
            const char a(hex_encoded_string[i]);
            const char b(hex_encoded_string[i + 1]);
            const char* p = std::lower_bound(hexchars, hexchars + 16, a);
            const char* q = std::lower_bound(hexchars, hexchars + 16, b);
            
            if(*p != a)
               throw std::invalid_argument(
                     std::string(
                        "ByteSequence::DecodeHexStringToByteVector: The")
                     +" 1:st character '"+a+"' is not a hex digit.");

            if(*q != b)
               throw std::invalid_argument(
                     std::string(
                        "ByteSequence::DecodeHexStringToByteVector: The")
                     +" 2:nd character '"+b+"' is not a hex digit.");

            result.push_back(((p - hexchars) << 4) | (q - hexchars));
         }
         return result;
      }
   private:
      static constexpr const char* const hexchars = "0123456789ABCDEF";
      ByteVector characters;
      ByteSequence(ByteVector::size_type size = 0):characters(size) {}
};
#endif
