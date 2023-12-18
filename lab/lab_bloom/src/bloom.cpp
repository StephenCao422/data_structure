/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "bloom.h"
#include <iostream>
using namespace std;

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here 
    bv.resize(size, false);
    hv = hashList;
}

BF::BF(const BF& other){
    // Your code here 
    bv = other.bv;
    hv = other.hv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){

    // Your code here 
    for (auto& hashFunc : hv) {
        int hashValue = hashFunc(key);
        hashValue %= bv.size();
        bv[hashValue] = true;
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    //return false;
    for (auto& hashFunc : hv) {
        int hashValue = hashFunc(key);

        hashValue %= bv.size();

        if (!bv[hashValue]) {
            return false;
        }
    }

    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    if (bv.size() != other.bv.size()) {
        throw std::invalid_argument("Bloom Filters sizes do not match");
    }

    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] || other.bv[i];
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    if (bv.size() != other.bv.size()) {
        throw std::invalid_argument("Bloom Filters sizes do not match");
    }

    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] && other.bv[i];
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here

    BF bloomFilter(size, hashList);

    for (int key : inList) {
        bloomFilter.add(key);
    }

    int falsePositives = 0;
    for (unsigned i = 0; i < max; ++i) {
        if (std::find(inList.begin(), inList.end(), i) == inList.end() && bloomFilter.contains(i)) {
            falsePositives++;
        }
    }

    return static_cast<float>(falsePositives) / (max - inList.size());

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    // int charIndex = index / 8;
    // int bitPosition = index % 8;
    // return (bv[charIndex] >> bitPosition) & 1;
    int charIndex = index / 8;
    int bitPosition = index % 8;
    return (bv[charIndex] >> (7 - bitPosition)) & 1;
}

bool getBitFromByte(char in, int index){
    // Your code here
    // char maskedBit = in >> index;
    // return maskedBit & 1;
    return (in >> (7 - index)) & 1;

}

