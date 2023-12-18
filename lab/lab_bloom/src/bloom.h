/**
 * @file bloom.h
 * Declaraction of the BF class. 
 */

#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <functional> //Needed for std::hash<>

typedef int (*hashFunction)(int); 
//using hashFunction = int(*)(int); // Equivalent definition to typdef

/**
 * The BF class implements a int --> int hash function bloom filter
 * (In other words, we will only use "hash functions" that work on integers)
 */
class BF
{
  public:
    /**
     * Constructor to create an empty bit vector of the appropriate size.
     * The constructor should store the hashList as a vector of hashFunctions
     * for use in other class methods.
     *
     * @param size The size (in bits) of the bloom filter to create
     * @param hashList A vector containing a list of hash functions to use in the BF 
     */
    BF(uint64_t size, std::vector<hashFunction> hashList);

    /**
     * Copy constructor.
     * @param other The BF to copy
     */
    BF(const BF& other);

    /**
     * Destructor; frees anything stored in heap memory by the BF
     */
    ~BF();

    /**
     * Inserts a hashable value into the BF
     * The insert should use every hash function in hashList and ignore collisions
     *
     * @param key The key to insert
     */
    void add(const int& key);

    /**
     * Checks if the bloom filter 'contains' the input key
     * The BF is probabilistic so the return value may be inaccurate.
     *
     * @param key The element to search for
     * @return True if the BF (might) contain the object, False otherwise
     */
    bool contains(const int& key) const;

    /**
     * Perform a bitwise union between two bloom filters
     *
     * `BF1.bit_union(BF2)` should store the union in BF1
     *
     * You should assume BF1 and BF2 have the same size and hashes
     *
     * @param other The BF to union
     */
    void bit_union(const BF& other);

    /**
     * Perform a bitwise intersection between two bloom 
     *
     * `BF1.intersect(BF2)` should store the intersection in BF1
     *
     * You should assume BF1 and BF2 have the same size and hashes
     *
     * @param other The BF to intersect
     */
    void intersect(const BF& other);

    std::vector<hashFunction> hv;
    std::vector<bool> bv;
};

/**
* Measures the false positive rate for a bloom filter
* The insert should use every hash function in hashList
* The calculation should query every value between 0 and max-1 (So not including max)
* HINT: The FPR is calculated using the counts of True Negatives (TN) and False Positives (FP).
*
* @param inList A vector of integers to be inserted into the bloom filter
* @param size The size (in bits) of the bloom filter to create
* @param hashList A vector containing a list of hash functions to use in the BF 
* @param max The size of the range of numbers being tested (our universe)
* @return A value between 0 and 1 (inclusive) estimating the FPR for the BF under these conditions
*/
float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max);


/**
* A bitmask-based function to get a boolean value from a character
* To be clear, the character itself isnt relevant -- its an encoding of 8 bits!
* You should assume the left-most bit is 0-indexed. In other words:
* Bit Index: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
* 
* HINT: You will have to use one or more bit operations (and, or, xor) to do this.
* @param in A character representing an eight-bit (one byte) register in the bloom filter
* @param index The register whose value we want to get in the byte
* @return The boolean value of the indexed bit
*/
bool getBitFromByte(char in, int index);

/**
* A logic-based function to find the correct byte register given an integer index in bits
* You should assume that the starting character in our vector are the bits 0-7
* In other words, our bit vector is indexed from left to right.
* NOTE: That is not a guarantee using some other forms of bit encoding!
* The use of vectors here is to make our approach system agnostic.
*
* HINT: You will have to use one or more bit operations (and, or, xor) to do this.
* @param bv A vector storing a bit vector as a collection of characters (8 bits each)
* @param index The register whose value we want to get in the vector ofbytes
* @return The boolean value of the indexed bit
*/
bool getBitFromArray(std::vector<char> bv, int index);

/* Given Functions */

 /**
   * Stream operator that allows BF to be written to standard streams
   * (like cout).
   *
   * @param out Stream to write to.
   * @param b BF to write to the stream.
   */
std::ostream & operator <<(std::ostream & out, BF const & b);
std::stringstream & operator <<(std::stringstream & out, BF const & b);


 /**
   * A series of provided hashes of various (low) quality
   * Designed more for easy calculations than good hash properties
   *
   * @param key The integer being hashed
   * @return The hash value for the integer
   */
int easy (int key);
int cpp (int key);
int simple(int key);
int simple2(int key);
int simple3(int key);