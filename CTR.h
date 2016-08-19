#ifndef CTR_h
#define CTR_h

#include <memory>
#include <sstream>

#include "AsciiByteSequence.h"
#include "ByteSequence.h"
#include "HexByteSequence.h"
#include "PRP.h"

#include <boost/multiprecision/cpp_int.hpp>

/// Counter mode.
class CTR
{
   public:
      CTR(std::unique_ptr<PRP> Prp)
         :prp(std::move(Prp))
      {
      }
      ByteSequence Decrypt( const ByteSequence& cipher ) const
      {
         const auto BlockSize( prp->GetBlockSize() );

         const ByteSequence IV(cipher.SubSequence(0,BlockSize));
         const boost::multiprecision::uint128_t iv("0x"+IV.ToHexString());

         AsciiByteSequence m("");
         unsigned int ctr(0);
         for( auto i(BlockSize); i < cipher.Size(); i += BlockSize, ++ctr )
         {
            const ByteSequence cSub(cipher.SubSequence(i,BlockSize));
            std::ostringstream oss;
            oss << std::hex << (iv+ctr);
            const HexByteSequence in(oss.str().c_str());
            // Observe that the CTR uses encryption for decryption.
            m.Append( cSub ^ prp->Encrypt(in) );
         }
         return m;
      }
   private:
      std::unique_ptr<PRP> prp;
};
#endif
