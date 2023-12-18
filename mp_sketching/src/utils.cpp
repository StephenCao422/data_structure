#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <tuple>
#include "MurmurHash3.h"

std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string trim_right(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string trim_left(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string trim(const std::string & str) {
    std::string tmp = str;
    return trim_left(trim_right(str));
}

int split_string(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

std::vector<int> readFile(std::string fname){
    std::vector<int> outV;
    std::vector<std::string> totalRows;
    int rowNum = split_string(file_to_string(fname), '\n', totalRows);

    for(auto & v : totalRows){
        v = trim(v);
        outV.push_back(stoi(v));
    }
    return outV;
}

uint64_t hash_seeded(const int * key, uint64_t seed){
    uint64_t hash_otpt[2]= {0};

    MurmurHash3_x64_128(key, sizeof(int), seed, hash_otpt);
    return hash_otpt[0];
}

uint64_t hash_500(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 500);
}

uint64_t hash_1000(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 1000);
}

uint64_t hash_1(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 1);
}

uint64_t hash_2(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 2);
}

uint64_t hash_3(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 3);
}

uint64_t hash_4(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 4);
}

uint64_t hash_5(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 5);
}

uint64_t hash_6(int key){
    const int *tmp = &key;
    return hash_seeded(tmp, 6);
}

uint64_t simple(int key){
    return (uint64_t) key;
}

