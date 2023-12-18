/**
 * @file utils.h
 * Support functions that the autograder will have access to
 * You should not modify this file (it wont be included in your submission)
 */

#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>

/**
* Takes a filename and reads in all the text from the file
* Newline characters are also just characters in ASCII
* 
* @param filename The name of the file that will fill the string
* @return A string containing the whole text of the given file
*/
std::string file_to_string(const std::string & filename);

/**
* Functions for the removal of whitespace to the left or right of a string (or both)
*
* @param str The string being processed
* @return The processed string
*/
std::string trim_right(const std::string & str);
std::string trim_left(const std::string & str);
std::string trim(const std::string & str);

/**
* Given a string and character, split the string by the character and store in a vector
* A 'split' string treats the character as a breakpoint and creates a separate item
* in the output vector for each substring. 
* 
* NOTE: The separator character is not included in the substrings.
* 
* The total number of substrings created (the length of fields) is returned 
*  
* @param str1 The string being split
* @param sep The separator character
* @param fields The string vector storing all substrings created by the split
* @return The number of substrings created
*/
int split_string(const std::string & str1, char sep, std::vector<std::string> &fields);

/**
 * Given a filename to a line-separated text file, create a vector of integers where each row
 * in the text file is an entry in the vector. You may assume the text file contains only numbers.
 * 
 * Your vector should match the exact structure of the input file -- so the first row of the file
 * should correspond to the 0th index of the vector.
 *  
 * @param filename The filename of the text file. 
 * @return A vector of integers whose order matches the input file
 */
std::vector<int> readFile(std::string fname);

/**
* Built using MurmurHash3
* A generalizable hash function that can be passed different seed inputs. 
* Will likely be good (but not great) since using only 64-bits of a 128-bit hash.
*
* @param key The integer being hashed
* @param seed The uint64_t defining the seed of the hash.
* @return A uint64_t hash encoding of the key. 
*/
uint64_t hash_seeded(const int * key, uint64_t seed);

/**
* Built using MurmurHash3
* Specific hash functions that can be used without specifying seeds
* The autograder will be built around these to limit the args that need to be passed.
* Ex: You should expect hash functions to take in one arg (an int) and return a hash value.
*
* @param key The integer being hashed
* @return A uint64_t hash encoding of the key. 
*/
uint64_t hash_1(int key);
uint64_t hash_2(int key);
uint64_t hash_3(int key);
uint64_t hash_4(int key);
uint64_t hash_5(int key);
uint64_t hash_6(int key);
uint64_t hash_500(int key);
uint64_t hash_1000(int key);
uint64_t simple(int key);

