#include "sketching.h"

#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_map>
#include <cmath>

using namespace cs225;
using namespace std;

std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h){
    std::vector<uint64_t> hashValues;

    for (int num : inList) {
        uint64_t hashed = h(num);
        hashValues.push_back(hashed);
        //std::cout << "hashed value for " << num << ": " << hashed << std::endl;

    }

    std::sort(hashValues.begin(), hashValues.end());

    auto last = std::unique(hashValues.begin(), hashValues.end());
    hashValues.erase(last, hashValues.end());

    if (hashValues.size() > k) {
        hashValues.resize(k);
    } else {
        while (hashValues.size() < k) {
            hashValues.push_back(GLOBAL_MAX_INT);
        }
    }

    return hashValues;
}

std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv){
    
    std::vector<uint64_t> minValues(hv.size(), std::numeric_limits<uint64_t>::max());

    for (int num : inList) {
        for (size_t i = 0; i < hv.size(); ++i) {
            uint64_t hashed = hv[i](num);
            if (hashed < minValues[i]) {
                minValues[i] = hashed;
            }
        }
    }

    return minValues;
}

std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h){
    const int num_partitions = std::pow(2, part_bits);
    std::unordered_map<int, uint64_t> minHashes;

    for (int num : inList) {
        uint64_t hashed = h(num);
        int partition = hashed >> (64 - part_bits); 

        if (minHashes.find(partition) == minHashes.end() || hashed < minHashes[partition]) {
            minHashes[partition] = hashed;
        }
    }

    std::vector<uint64_t> result(num_partitions, GLOBAL_MAX_INT);
    for (const auto& pair : minHashes) {
        result[pair.first] = pair.second;
    }

    return result;
}


float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2){
    // size_t intersection = 0;
    // size_t unionCount = 0;
    // std::set<uint64_t> unionSet(mh1.begin(), mh1.end());

    // for (size_t i=0; i < mh2.size(); i++){
    //     if (unionSet.find(mh2[i]) != unionSet.end() && mh2[i] != GLOBAL_MAX_INT) {
    //         intersection++;
    //     } 
    //     unionSet.insert(mh2[i]);
    // }

    // unionCount = unionSet.size();

    // if (unionCount == 0) return 0.0f;
    // return static_cast<float>(intersection) / static_cast<float>(unionCount);
    size_t intersection = 0;
    std::set<uint64_t> unionSet;

    for (size_t i = 0; i < mh1.size(); ++i) {
        if (mh1[i] != GLOBAL_MAX_INT) {
            unionSet.insert(mh1[i]);
        }
    }

    for (size_t i = 0; i < mh2.size(); ++i) {
        if (mh2[i] != GLOBAL_MAX_INT) {
            if (unionSet.find(mh2[i]) != unionSet.end()) {
                intersection++;
            }
            unionSet.insert(mh2[i]);
        }
    }

    size_t unionCount = unionSet.size();
    if (unionCount == 0) return 0.0f;
    return static_cast<float>(intersection) / static_cast<float>(unionCount);

}




int minhash_cardinality(std::vector<uint64_t> mh, unsigned k){
    if (mh.empty() || k == 0 || mh[k - 1] == GLOBAL_MAX_INT) {
        return 0;
    }
    double largestSample = static_cast<double>(GLOBAL_MAX_INT);

    double cardinalityEstimate = (static_cast<double>(k) / mh[k - 1]) * largestSample - 1;
    return static_cast<int>(std::ceil(cardinalityEstimate));
}



float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2){
    std::set<int> set1(raw1.begin(), raw1.end());
    std::set<int> set2(raw2.begin(), raw2.end());

    std::vector<int> intersection;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersection));

    size_t unionSize = set1.size() + set2.size() - intersection.size();

    if (unionSize == 0) return 0.0f;
    return static_cast<float>(intersection.size()) / unionSize;
}


int exact_cardinality(std::vector<int> raw){
    std::set<int> uniqueElements(raw.begin(), raw.end());
    return uniqueElements.size();
}



// std::vector<int> MM::extractTileData(const PNG &input, unsigned startX, unsigned startY, unsigned endX, unsigned endY) const {
//     std::vector<int> tileData;
//     for (unsigned x = startX; x < endX && x < input.width(); x++) {
//         for (unsigned y = startY; y < endY && y < input.height(); y++) {
//             BWPixel pixel = input.getPixel(x, y);
//             int bwValue = static_cast<int>(pixel.l * 255);
//             tileData.push_back(bwValue);
//             //std::cout << "Pixel value at (" << x << "," << y << "): " << bwValue << std::endl;
//         }
//     }
//     return tileData;
// }


MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h){
    
    tileWidth = tileHeight = numTiles;
    unsigned weight_ = std::ceil(static_cast<float>(input.width()) / numTiles);
    unsigned height_ = std::ceil(static_cast<float>(input.height()) / numTiles);

    minHashTiles.resize(numTiles);

    for (unsigned i = 0; i < numTiles; i++) {
        minHashTiles[i].resize(numTiles);

        for (unsigned j = 0; j < numTiles; j++) {
            std::vector<int> temp;

            for (unsigned x = 0; x < weight_; x++) {
                for (unsigned y = 0; y < height_; y++) {

                    if (i * weight_ + x < input.width() && j * height_ + y < input.height()) {
                        temp.push_back(static_cast<int>(input.getPixel(i * weight_ + x, j * height_ + y).l * 255));
                    }
                    
                }
            }
            minHashTiles[i][j] = kminhash(temp, k, h);
        }
    }



    // unsigned tilesPerSide = std::ceil(std::sqrt(numTiles));

    // unsigned tileWidth = std::ceil((float)input.width() / tilesPerSide);
    // unsigned tileHeight = std::ceil((float)input.height() / tilesPerSide);

    // minHashTiles.resize(tilesPerSide, std::vector<std::vector<uint64_t>>(tilesPerSide));

    // for(unsigned tx = 0; tx < tilesPerSide; tx++) {
    //     for(unsigned ty = 0; ty < tilesPerSide; ty++) {
    //         std::vector<int> c; // Vector to hold the pixel data for one tile

    //         // Collect pixel data for the current tile
    //         for(unsigned x = 0; x < tileWidth; x++) {
    //             for (unsigned y = 0; y < tileHeight; y++) {
    //                 unsigned globalX = tx * tileWidth + x;
    //                 unsigned globalY = ty * tileHeight + y;

    //                 // Check if the pixel is within the bounds of the image
    //                 if(globalX < input.width() && globalY < input.height()) {
    //                     c.push_back(static_cast<int>(255 * input.getPixel(globalX, globalY).l));
    //                 }
    //             }
    //         }

    //         // Compute the MinHash for the current tile
    //         std::vector<uint64_t> minHash = kminhash(c, k, h);

    //         // Store the MinHash in the appropriate tile position
    //         minHashTiles[tx][ty] = minHash;
    //     }
    // }
}

std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const{
    // unsigned index = (height / tileHeight) * numTilesX + (width / tileWidth);

    // if (index < mv.size()) {
    //     return minHashTiles[index];
    // }
    // return std::vector<uint64_t>();
    return minHashTiles[width][height];
}


int MM::countMatchTiles(const MM & other, float threshold) const{
    int matchCount = 0;

    for (size_t i = 0; i < minHashTiles.size(); i++) {
        for (size_t j = 0; j < minHashTiles[0].size(); j++) {
            float jaccardIndex = minhash_jaccard(minHashTiles[i][j], other.minHashTiles[i][j]);

            if (jaccardIndex >= threshold) {
                matchCount++;
            }
        }
    }

    return matchCount;
}


std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, 
                                                            unsigned k, hashFunction h, float threshold)
{
    std::vector<MM> mms;
    for (const auto& file : flist) {
        cs225::PNG png;
        if (!png.readFromFile(file)) {
            continue;
        }
        mms.emplace_back(png, numTiles, k, h);
    }

    std::vector<std::tuple<int, int, int>> edges;
    for (size_t i = 0; i < mms.size(); i++) {
        for (size_t j = i + 1; j < mms.size(); j++) {
            int matchCount = mms[i].countMatchTiles(mms[j], threshold);
            if (matchCount > 0) {
                edges.emplace_back(i, j, matchCount);
            }
        }
    }
    
    return edges;
}