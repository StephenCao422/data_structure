/**
 * @file bloom_given.cpp
 * Support functions that the autograder will have access to
 * You should not modify this file (it wont be included in your submission)
 */

 #include "bloom.h"


std::ostream & operator<<(std::ostream & out, BF const & b){
    for(unsigned i = 0; i < b.bv.size(); i++){
        out << b.bv[i];
    }

    return out;
}


// You might think this is a terrible hash function...
int easy(int key) {
    return key;
}

// But try running the C++ default hash function for int...
int cpp(int key){
    std::size_t h1 = std::hash<int>{}(key);
    return int(h1);
}

int simple(int key){
    return 5*key + 3;
}

int simple2(int key){
    return 3*key + 1;
}

int simple3(int key){
    return 2654435769*key;
}

