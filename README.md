# cryptography-1
C++ types and classes useful for the Coursera course Cryptography I. The course was developed by Stanford University and given between August 8 and October 3, 2016.

* AES: 128-bit AES encryption and decryption PRP.
* AsciiByteSequence: A ByteSequence constructed from an ascii encoded string.
* Byte: Type definition of a byte (8 bit unsigned int)
* ByteSequence: Base class for a sequence of bytes. Includes some useful methods for such sequences, e.g. XOR.
* ByteVector: Type defined as a vector of Bytes.
* CBC: A cipher block chain, uses the PRP.
* CTR: Counter mode, uses the PRP.
* HexByteSequence: A ByteSequence constructed from an hex encoded string.
* PRP: A base class for Pseudo Random Permutations.
* SHA256: A SHA-256 hashing class.
