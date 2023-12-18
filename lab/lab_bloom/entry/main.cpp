/**
 * @file main.cpp
 * Contains code for testing different bloom filter sizes
 */

#include <iostream>
#include <sstream>
#include <string>
#include "bloom.h"

using namespace std;

int main(int argc, char** argv)
{
    std::vector<hashFunction> hv = {simple, simple2, simple3};
    std::vector<hashFunction> hv2 = {simple, simple2};
    std::vector<hashFunction> hv3 = {cpp, simple3};

    /* Part 1 Example Run */
    BF b1(7, hv);
    BF b2(7, hv);
    BF b3(7, hv);

    cout << b1 << std::endl; // 0000000

    b1.add(4);

    cout << b1 <<std::endl; // 0010001

    b2.add(2);

    cout << b2 <<std::endl; // 1100001

    b3.bit_union(b2);
    b3.bit_union(b1);

    cout << b3 << std::endl; // 1110001

    b3.intersect(b2);

    cout << b3 << std::endl; // 1100001

    b3.intersect(b1);

    cout << b3 << std::endl; // 0000001

    /* Part 2 Example Run*/
    // n = 7, m = 50, universe = 100
    // Expected Out: 0.0967742
    std::vector<int> in = {1, 3, 8, 30, 92, 50, 39};
    int m = 50;
    int universe = 100;
    std::cout << measureFPR(in, m, hv, universe) << std::endl; 

    // n=5, m=10, universe = 20
    // Expected Out: 0.4
    std::vector<int> in2 = {89, 86, 74, 50, 35};
    m = 10;
    universe = 20;
    std::cout << measureFPR(in2, m, hv, universe) << std::endl;

    /* Part 3 Example Run*/
    char tmp{ 0b11100101 };
    char tmp2{ 0b10100101 };
    char tmp3{ 0b11110111 };
    char tmp4{ 0b00000001 };
    char tmp5{ 0b11000000 };

    // Expected: 11100101 (recreate any of the above tmp variables!)
    for(int i = 0; i < 8; i++){
        std::cout << getBitFromByte(tmp,i);
    }
    std::cout << endl;

    // Expected: 110000001111011111100101 (ordered from left to right)
    std::vector<char> cv= {tmp5, tmp3, tmp};
    for(int i = 0; i < 24; i++){
        std::cout << getBitFromArray(cv, i);
    }
    std::cout << endl;

}
