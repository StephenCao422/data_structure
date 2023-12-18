#include <iostream>
#include "cs225/PNG.h"
#include "sketching.h"
#include "MurmurHash3.h"
#include "utils.h"
#include <filesystem>

using namespace cs225;

int main() {
    std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};

    // *** Part 1 ***

    std::string fname = "../data/universe_100/raw/dataset_0.txt";

    std::vector<int> input = readFile(fname);

    std::vector<uint64_t> kmin = kminhash(input, 8, hash_1); // Check against "../data/universe_100/kminhash_8/dataset_0.txt"

    std::vector<uint64_t> khash = khash_minhash(input, hv); // Check against "../data/universe_100/khash_8/dataset_0.txt"

    std::vector<uint64_t> kpart = kpartition_minhash(input, 3, hash_1); // Check against "../data/universe_100/kpart_8/dataset_0.txt"

    int ec = exact_cardinality(input); // 35

    // Only the bottom-k minhash can meaningfully do k-th minimum value. Why?
    // (K-partition can do something else if we are clever, but this assignment doesnt require it)
    int kmin_card = minhash_cardinality(kmin, 8); // 33
    int khash_card = minhash_cardinality(khash, 1); // 155
    int kpart_card = minhash_cardinality(kpart, 1); // 155

    std::string fname2 = "../data/universe_100/raw/dataset_1.txt";

    std::vector<int> input2 = readFile(fname2);

    std::vector<uint64_t> kmin2 = kminhash(input2, 8, hash_1); // Check against "../data/universe_100/kminhash_8/dataset_1.txt"

    std::vector<uint64_t> khash2 = khash_minhash(input2, hv); // Check against "../data/universe_100/khash_8/dataset_1.txt"

    std::vector<uint64_t> kpart2 = kpartition_minhash(input2, 3, hash_1); // Check against "../data/universe_100/kpart_8/dataset_1.txt"

    float ej = exact_jaccard(input, input2); // 0.295082

    float kmin_j = minhash_jaccard(kmin, kmin2); // 0.230769
    float khash_j = minhash_jaccard(khash, khash2); // 0.142857
    float kpart_j = minhash_jaccard(kpart, kpart2); // 0.066667

    // *** Part 2 ***

    // std::string png_file = "../data/sixcolor_100_100/raw/0.png";
    // PNG source;
    // source.readFromFile(png_file);

    // MM um(source, 1, 6, simple); // Should produce one minHash for the entire file

    // std::vector<uint64_t> minhash = um.getMinHash(0, 0); // {29, 76, 105, 149, 178, 225};

    // std::string p1 = "../data/twocolor_10_10/raw/blacksquare.png";
    // std::string p2 = "../data/twocolor_10_10/raw/whitesquare.png";
    // PNG s1, s2;
    // s1.readFromFile(p1);
    // s2.readFromFile(p2);

    // // The 'simple' hash is great for debugging!
    // MM um1(s1, 2, 2, simple);
    // MM um2(s2, 2, 2, simple);

    // minhash = um1.getMinHash(0, 0); // Check '../twocolor_10_10/simple_2_2/'! 
    // minhash = um2.getMinHash(1, 1); // Check '../twocolor_10_10/simple_2_2/'! 

    // um1.countMatchTiles(um2, 0.5); // Should be 0 -- GLOBAL_MAX_INT doesnt count!
    // um1.countMatchTiles(um1, 1); // Should be 4 -- The total number of tiles in a 2x2 image is 4 and the images are the same!

    // // *** Part 3 ***

    // std::vector<std::string> flist = {"../data/r_500_500/raw/0.png", "../data/r_500_500/raw/1.png", \
    //      "../data/r_500_500/raw/2.png"};

    // // Should output at least three 'edge tuples' with the values below:
    // std::vector<std::tuple<int, int, int>> out = build_minhash_graph(flist, 10, 10, simple, 0.5); // {{0, 1, 20}, {0, 2, 21}, {1, 2, 20}}
    
}