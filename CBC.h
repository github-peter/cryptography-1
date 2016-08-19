#ifndef CBC_h
#define CBC_h

#include <memory>

#include "AsciiByteSequence.h"
#include "ByteSequence.h"
#include "PRP.h"

/// Cipher Block Chain
class CBC
{
   public:
      CBC(std::unique_ptr<PRP> Prp)
         :prp(std::move(Prp))
      {
      }
      ByteSequence Decrypt( const ByteSequence& cipher ) const
      {
         const auto BlockSize( prp->GetBlockSize() );

         const ByteSequence IV(cipher.SubSequence(0,BlockSize));

         ByteSequence carry(IV);

         AsciiByteSequence m("");
         for( auto i(BlockSize); i < cipher.Size(); i += BlockSize )
         {
            const ByteSequence cSub(cipher.SubSequence(i,BlockSize));
            m.Append( carry ^ prp->Decrypt(cSub) );
            carry = cSub;
         }

         // Unpad the message.
         m.EraseFromEnd( m[m.Size()-1] );

         return m;
      }
   private:
      std::unique_ptr<PRP> prp;
};
#endif
