# cryptography-1
C++ types and classes useful for the Coursera course Cryptography I. The course was developed by Stanford University and given between August 8 and October 3, 2016.

* Byte: Type definition of a byte (8 bit unsigned int)
* ByteVector: Type defined as a vector of Bytes.
* ByteSequence: Base class for a sequence of bytes. Includes some useful methods for such sequences, e.g. XOR.
* AsciiByteSequence: A ByteSequence constructed from an ascii encoded string.
* HexByteSequence: A ByteSequence constructed from an hex encoded string.
