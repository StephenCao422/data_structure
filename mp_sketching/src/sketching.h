/**
 * @file sketching.h
 * An exploration of sketching techniques on sets and PNGs
 */

#pragma once

#include "cs225/PNG.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
#include <tuple>
#include "utils.h"


using namespace cs225;

typedef uint64_t (*hashFunction)(int); 
const uint64_t GLOBAL_MAX_INT = ~(0);

/* **************************************** Part 1: Creating MinHash Sketches **************************************** */

/**
 * Given a list of integers (possibly with repeated values) and a hash function, return a list containing the k-minimum hash values.
 * If you generate the same hash value twice, you should only track it once for the purposes of recording minima.
 * Your final return vector should be ordered from smallest to largest starting with the global min. 
 * In other words, the 1st minimum value should be stored at index 0 (and the k-th minimum at index k-1). 
 * 
 * HINT: You are free to use your previous assignments to build a way of tracking k minimum values.
 *
 * NOTE: If there arent enough unique hash values in the input set, you should use GLOBAL_MAX_INT to fill in the
 * remaining positions. This is the only allowable duplicate. 
 *  
 * @param inList A vector of integers to be run through minhash
 * @param k An unsigned integer describing the number of minima that need to be tracked (and returned)
 * @param h An hash function that takes in an integer and returns a uint64_t
 * @return A vector of uint64_t containing the k-min hash values using one hash
 */
std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h);

/**
 * Given a list of integers (possibly with repeated values) and a vector of hash functions, return the min hash value for each hash
 * The values should be stored in order corresponding to the input hash vector hv.
 * In other words, the min value of the hash at index 0 in hv should be stored at index 0 of the returning vector
 * 
 * NOTE: This is similar to k-minhash but using k hash functions instead of k min values.
 *  
 * @param inList A vector of uint64_t to be run through minhash
 * @param hv A vector of hash function that each take in an integer and returns a uint64_t
 * @return A vector of uint64_t containing the min value of k distinct hashes (order matching hv)
 */
std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv);

/**
 * Given a list of integers (possibly with repeated values), a partition number (an integer number of bits), and a hash function
 * return a list containing the min value for each partition. 
 *
 * For example, if we use one bit for our partition, we would have two partitions total corresponding to 0 / 1.
 * If we had two bits, our partitions would be 00, 01, 10, 11. 
 * If we use n bits for our partition, we would have 2^n total partitions.
 *
 * The partitions should always be based on the *highest order bits*. 
 * 
 * NOTE: These are bit encodings of real values NOT a vector<bool> or equivalent. The rightmost bit is the LOWEST order bit.
 *
 * If there are no items which hash within a partition, as a placeholder store the global maximum value at that location.
 * For your convenience, GLOBAL_MAX_INT is already defined in sketching.h
 *
 * Please also note that the 'partition' is purely conceptual for grouping and not an actual modification of the minhash values themselves.
 * The return should be the full 64-bit hash value (uint64_t), NOT a truncation of the lower order bits.
 * In other words, please do not remove the partition bits from your minhash value.
 *
 * @param inList A vector of integers to be run through minhash
 * @param part_bits An integer between 1 and 63 (inclusive) describing how many partition bits are used.
 * @param h An hash function that takes in (and returns) an integer to be used by minhash
 * @return A vector of uint64_t containing the min hash values using one hash and k partitions
 */
std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h);

/**
 * Given two minhash sketches, return the estimate of the Jaccard similarity between the two sketches.
 * This should be calculated directly as seen in lecture:
 *
 * The intersection is the numeric count of the matches between mh1 and mh2 (the order doesnt matter)!
 *
 * The union is the numeric count of the total number of unique values found when combining mh1 and mh2.
 * That is to say if |mh1|=|mh2|=4 (k=4), and they intersect with 2 items, the union total is 6.
 *
 * NOTE: In the slides we calculated Jaccard multiple ways. This is the ONLY allowed way for the assignment.
 *
 * WARNING: You MUST ignore any instances of GLOBAL_MAX_INT when computing this similarity!
 * Remember, GLOBAL_MAX_INT implies that there *wasnt* enough unique hashing items to finish the sketch.
 * This is ok but shouldnt be counted as similarity, since GLOBAL_MAX_INT doesnt correspond to a real value.
 *  
 * @param mh1 The first minhash sketch being compared
 * @param mh2 The second minhash sketch being compared
 * @return A float between 0 and 1 (inclusive) storing the estimated similarity between sketches
 */
float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2);

/**
 * Given a MinHash sketch, estimate the cardinality using the k-th minimum value.
 * Note that k is *not* the same thing as the index in your vector:
 * The 1st minimum value is the 0th index. 
 *
 * You should use the k-min value equation seen in class. However that equation was normalized for [0, 1] hashing.
 * It is up to you to figure out how to modify the equation appropriately.
 * 
 * WARNING: Your division may result in a float value. The return value MUST ROUND UP.
 * 
 * TIP: Using the required method, both k-hash and k-partition minhash are only accurate if k=1 -- why?
 * Can you think of a way to improve the accuracy of these methods using ALL hash values?
 *  
 * @param mh A *kminhash* storing k minimum hash values (generated from one hash or k hashes). 
 * @param k The value of k for our k-th minima value approach to estimating cardinality
 * @return An estimate of the total number of unique items in the hash
 */
int minhash_cardinality(std::vector<uint64_t> mh, unsigned k);

/**
 * Given two raw datasets containing a vector of integers, compute the exact Jaccard similarity between datasets.
 * Your similarity metric must ignore duplicates present in the dataset when computing the relevant cardinalities.
 * In other words, treat your input as two sets and do a set comparison.
 *  
 * @param raw1 The first dataset being compared
 * @param raw2 The second dataset being compared
 * @return A float between 0 and 1 (inclusive) storing the actual similarity between datasets
 */
float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2);

/**
 * Given a raw dataset containing a vector of integers, compute the exact cardinality of this set.
 * Your cardinality should be a precise measure of the number of unique values in the dataset.
 *  
 * @param raw A dataset of possibly repeating integers 
 * @return The exact count of unique items in the dataset
 */
int exact_cardinality(std::vector<int> raw);

/* **************************************** Part 2: Applying MinHash to PNGs **************************************** */

/**
 * The MinHash Matrix (MM) class converts PNGs into an indexable matrix of MinHash sketches
 * It is built using BWPixels already implemented for you (treat pixels as luminance).
 * For this implementation, use ONLY the bottom-k MinHash approach.
 */
class MM
{
    public:
        /**
        * Constructor converts a PNG into a collection of MinHash sketches.
        * It is up to you to determine *how* your collection is stored. 
        * The autograder will only check that every MinHash sketch (when accessed) is correct
        *
        * @param input The PNG image to be sketched
        * @param numTiles A vector containing a list of hash functions to use in the BF
        * @param k An unsigned integer describing the number of minima that need to be tracked (and returned)
        * @param h An hash function that takes in an integer and returns an uint64_t
        */
        MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h);

        /**
        * Accessor function that returns the MinHash sketch for a specific tile using (width, height) coordinates.
        * REMEMBER: (0, 0) is the TOP LEFT coordinate in a PNG.
        * Width increases from left to right.
        * Height increases from top to bottom.
        *
        * The tests here will require that both your constructor and your accessor are correct.
        * You are encouraged to test them separately by creating your own tests based on your implementation strategy.
        *
        * @param width An unsigned integer corresponding to the x (or width) dimension
        * @param height An unsigned integer corresponding to the y (or height) dimension
        */
        std::vector<uint64_t> getMinHash(unsigned width, unsigned height) const;

        /**
        * Comparison function that returns the number of paired tiles that are above a provided threshold of similarity.
        * Each tile should be compared using MinHash Jaccard with its direct opposite (matching width, height in tile space)
        * You may assume that this function is only run on MM that have the same total numTiles.
        *
        * So I have two MM each with four tiles, this will output a number from 0 to 4 corresponding to how many coordinate matching 
        * pairs are at or above the threshold.
        *
        * Given:
        *
        * A | B      E | F
        * -----      -----
        * C | D      G | H
        *
        * Return, with (X ~ Y) implying a MinHash Jaccard comparison above threshold:
        *
        * (A ~ E) + (B ~ F) + (C ~ G) + (D ~ H)
        *
        *
        * OBSERVE: One of the powerful things about this approach is the *scale* of the image doesnt matter!
        * The number of pixels in each tile is lost when the transformation occurs so theoretically the same image
        * resized will have a near perfect or identical match.
        *
        * @param other The MinHash Matrix (with the same number of tiles) being compared against
        * @param threshold A float value between 0 and 1. A 'match' between tiles must be equal to or greater than this value.
        */
        int countMatchTiles(const MM & other, float threshold) const;


    private:
        // Your implementation here -- only the functions above will be tested
        //std::vector<std::vector<uint64_t>> minHashTiles;
        std::vector<std::vector<std::vector<uint64_t>>> minHashTiles; 
        unsigned tileWidth, tileHeight; 
        //unsigned numTilesX, numTilesY;

        //std::vector<int> extractTileData(const PNG &input, unsigned startX, unsigned startY, unsigned endX, unsigned endY) const;


};

/* *** Part 3: Creating a Graph from MinHash Lists overlap *** */

/**
 * Given a list of PNGs as a vector of files, perform an all-pairs comparison and store the results as a weighted edge list graph
 * The vertices of your graphs are files and the edge weight between each is the number of matching tiles between them
 * Your graph will always be an undirected weighted complete graph (with no self-edges).
 * 
 * NOTE: Because file locations are a pain to autograde (and store), the 'edge list' output is a vector of INTEGERS not strings. 
 * Accordingly each file needs to be represented by an integer. To do this, assign a numeric value based on the index in the input list
 *
 * So the first file in `flist` will have the label '0' (regardless of what the string really is)
 *
 * Each tuple should be organized by giving the two vertices first and then the weight between them.
 * Ex: If file 0 and file 1 have a countMatchTiles output of 5, this would be {0, 1, 5}.
 * Depending on your strategy, you may also output {1, 0, 5}
 *
 * You should NEVER output something like {0, 0, 1}!
 *  
 * @param flist A vector storing a collection of files to be processed into MinHashes and compared
 * @param numTiles A vector containing a list of hash functions to use in the BF
 * @param k An unsigned integer describing the number of minima that need to be tracked (and returned)
 * @param h An hash function that takes in an integer and returns an uint64_t
 * @param threshold A float value between 0 and 1. A 'match' between tiles must be equal to or greater than this value.
 * @return A vector of size 3 integer tuples defining an edge list. 
 */
std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold);

