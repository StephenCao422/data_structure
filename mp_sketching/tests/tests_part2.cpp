#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <filesystem>
#include "sketching.h"
#include "utils.h"

std::vector<std::vector<uint64_t>> file_to_minhash_list(std::string fname){
    std::vector<std::vector<uint64_t>> mh_list;
    std::vector<std::string> totalRows;
    int rowNum = split_string(file_to_string(fname), '\n', totalRows);

    for(auto & r : totalRows){
        r = trim(r);
        if(r.size() > 0){
            std::vector<std::string> totalCols;
            std::vector<uint64_t> mh;
            int colNum = split_string(r, ',', totalCols);
            for(auto & v : totalCols){
                v = trim(v);
                if(v.size() > 0){
                    mh.push_back(stoull(v));
                }
                
            }
            mh_list.push_back(mh);
        }
    }
    return mh_list;
}

std::tuple<int, int, int> normalizeTuple(std::tuple<int, int, int> &in){
    int first = std::get<0>(in);
    int second = std::get<1>(in);
    int third = std::get<2>(in);

    if(first > second){
        return std::make_tuple(second, first, third);
    }
    return in;
}

TEST_CASE("test_png_minhash (uniform minhash)", "[weight=5]"){
    std::vector<std::string> flist = {"../data/sixcolor_100_100/raw/0.png", "../data/sixcolor_100_100/raw/1.png", \
         "../data/sixcolor_100_100/raw/2.png", "../data/sixcolor_100_100/raw/3.png","../data/sixcolor_100_100/raw/4.png"};

    std::vector<uint64_t> expected = {29, 76, 105, 149, 178, 225};

    for(auto f : flist){
        PNG source;
        source.readFromFile(f);

        MM um(source, 1, 6, simple);

        REQUIRE(um.getMinHash(0, 0) == expected);
    }
}

TEST_CASE("test_png_minhash (black-white simple tests)", "[weight=5]"){
        std::vector<std::string> flist = {"../data/twocolor_10_10/raw/blacksquare.png","../data/twocolor_10_10/raw/whitesquare.png", \
        "../data/twocolor_10_10/raw/blacksquare2.png","../data/twocolor_10_10/raw/whitesquare2.png"};

        for(auto f : flist){
            std::string out_f = f;
            out_f.replace(out_f.find("raw"), string("raw").size(), "simple_2_2");
            out_f.replace(out_f.find("png"), string("png").size(), "csv");
            PNG source;
            source.readFromFile(f);

            unsigned numTiles = 2;
            unsigned k = 2;
            MM um(source, numTiles, k, simple);

            std::vector<std::vector<uint64_t>> emm = file_to_minhash_list(out_f);

            for(unsigned row = 0; row < numTiles; row++){
                for(unsigned col = 0; col < numTiles; col++){
                    unsigned tmp = col+row*numTiles;

                    REQUIRE(um.getMinHash(col,row) == emm[tmp]);       
                }
            }

        }
}

TEST_CASE("test_png_minhash (total random hash1 mixed sizes)", "[weight=5]"){
    std::vector<std::string> flist = {"../data/r_500_500/raw/0.png", "../data/r_500_500/raw/1.png", \
        "../data/r_500_500/raw/2.png", "../data/r_500_500/raw/3.png","../data/r_500_500/raw/4.png"};

    for(auto f : flist){
        std::string out_f = f;
        out_f.replace(out_f.find("raw"), string("raw").size(), "hash1_5_100");
        out_f.replace(out_f.find("png"), string("png").size(), "csv");
        PNG source;
        source.readFromFile(f);

        unsigned numTiles = 5;
        unsigned k = 100;
        MM um(source, numTiles, k, hash_1);

        std::vector<std::vector<uint64_t>> emm = file_to_minhash_list(out_f);

        for(unsigned row = 0; row < numTiles; row++){
            for(unsigned col = 0; col < numTiles; col++){
                unsigned tmp = col+row*numTiles;

                REQUIRE(um.getMinHash(col,row) == emm[tmp]);                      
            }
        }

    }

    /*
    for(auto f : flist){
        std::string out_f = f;
        out_f.replace(out_f.find("raw"), string("raw").size(), "hash1_50_10");
        out_f.replace(out_f.find("png"), string("png").size(), "csv");
        PNG source;
        source.readFromFile(f);

        unsigned numTiles = 50;
        unsigned k = 10;
        MM um(source, numTiles, k, hash_1);

        std::vector<std::vector<uint64_t>> emm = file_to_minhash_list(out_f);

        for(unsigned row = 0; row < numTiles; row++){
            for(unsigned col = 0; col < numTiles; col++){
                unsigned tmp = col+row*numTiles;

                REQUIRE(um.getMinHash(col,row) == emm[tmp]);                      
            }
        }

    }
    */
}

TEST_CASE("test_png_minhash (total random rectangular PNGs)", "[weight=5]"){
    std::vector<std::string> flist = {"../data/r_50_100/raw/0.png", "../data/r_50_100/raw/1.png"};

    for(auto f : flist){
        std::string out_f = f;
        out_f.replace(out_f.find("raw"), string("raw").size(), "hash1_3_13");
        out_f.replace(out_f.find("png"), string("png").size(), "csv");
        PNG source;
        source.readFromFile(f);

        unsigned numTiles = 3;
        unsigned k = 13;
        MM um(source, numTiles, k, hash_1);

        std::vector<std::vector<uint64_t>> emm = file_to_minhash_list(out_f);

        for(unsigned row = 0; row < numTiles; row++){
            for(unsigned col = 0; col < numTiles; col++){
                unsigned tmp = col+row*numTiles;

                REQUIRE(um.getMinHash(col,row) == emm[tmp]);                     
            }
        }

    }

    /*
    for(auto f : flist){
        std::string out_f = f;
        out_f.replace(out_f.find("raw"), string("raw").size(), "simple_50_2");
        out_f.replace(out_f.find("png"), string("png").size(), "csv");
        PNG source;
        source.readFromFile(f);

        unsigned numTiles = 50;
        unsigned k = 2;
        MM um(source, numTiles, k, simple);

        std::vector<std::vector<uint64_t>> emm = file_to_minhash_list(out_f);

        for(unsigned row = 0; row < numTiles; row++){
            for(unsigned col = 0; col < numTiles; col++){
                unsigned tmp = col+row*numTiles;

                REQUIRE(um.getMinHash(col,row) == emm[tmp]);                    
            }
        }

    }
    */
    
}

TEST_CASE("test_png_matchingTiles (sixcolor_100_100)", "[weight=10]"){
    std::string f0 = "../data/sixcolor_100_100/raw/0.png";
    std::string f1 = "../data/sixcolor_100_100/raw/1.png";
    std::string f2 = "../data/sixcolor_100_100/raw/2.png";
    std::string f3 = "../data/sixcolor_100_100/raw/3.png";

    PNG s0, s1, s2, s3;
    s0.readFromFile(f0);
    s1.readFromFile(f1);
    s2.readFromFile(f2);
    s3.readFromFile(f3);

    MM um0(s0, 50, 5, hash_1);
    MM um1(s1, 50, 5, hash_1);
    MM um2(s2, 50, 5, hash_1);
    MM um3(s3, 50, 5, hash_1);

    REQUIRE(um0.countMatchTiles(um1, 0.9) == 44);

    REQUIRE(um0.countMatchTiles(um3, 0.9) == 56);

    REQUIRE(um2.countMatchTiles(um3, 0.9) == 42);

    REQUIRE(um3.countMatchTiles(um2, 0.9) == 42);
}

TEST_CASE("test_png_matchingTiles (r_500_500)", "[weight=10]"){
    std::string f0 = "../data/r_500_500/raw/0.png";
    std::string f1 = "../data/r_500_500/raw/1.png";
    std::string f2 = "../data/r_500_500/raw/2.png";

    PNG s0, s1, s2;
    s0.readFromFile(f0);
    s1.readFromFile(f1);
    s2.readFromFile(f2);

    MM um0(s0, 10, 10, simple);
    MM um1(s1, 10, 10, simple);
    MM um2(s2, 10, 10, simple);

    REQUIRE(um0.countMatchTiles(um1, 0.5) == 20);

    REQUIRE(um0.countMatchTiles(um2, 0.5) == 21);

    MM alt0(s0, 20, 15,hash_1);
    MM alt1(s1, 20, 15,hash_1);
    MM alt2(s2, 20, 15,hash_1);

    REQUIRE(alt0.countMatchTiles(alt1, 0.5) == 400);

    REQUIRE(alt1.countMatchTiles(alt2, 0.8) == 175);

    REQUIRE(alt2.countMatchTiles(alt1, 0.6) == 382);
}

TEST_CASE("test_build_minhash_graph (sixcolor_100_100)", "[weight=10]"){
    std::vector<std::string> flist = {"../data/sixcolor_100_100/raw/0.png", "../data/sixcolor_100_100/raw/1.png", \
        "../data/sixcolor_100_100/raw/2.png", "../data/sixcolor_100_100/raw/3.png","../data/sixcolor_100_100/raw/4.png"};

    std::vector<std::tuple<int, int, int>> out = build_minhash_graph(flist, 50, 5, simple, 0.9);

    std::vector<std::tuple<int, int, int>> exp = {{0, 1, 44}, {0, 2, 55}, {0, 3, 56}, {0, 4, 57}, {1, 2, 66},\
     {1, 3, 68}, {1, 4, 49}, {2, 3, 42}, {2, 4, 55}, {3, 4, 48}};

    std::map<std::pair<int, int>, int> ans;
    std::map<std::pair<int, int>, bool> exists;

    for(auto t : exp){
        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        ans[tmp]=third;
        exists[tmp]=false;
    }

    for(auto t : out){
        std::tuple<int, int, int> nt = normalizeTuple(t);

        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        REQUIRE(ans.count(tmp)==1);

        REQUIRE(ans.at(tmp)==third);

        exists[tmp]=true;
    }

    for(auto t : exp){
        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        REQUIRE(exists.at(tmp)==true);
    }
}

TEST_CASE("test_build_minhash_graph (r_500_500)", "[weight=10]"){
    std::vector<std::string> flist = {"../data/r_500_500/raw/0.png", "../data/r_500_500/raw/1.png", \
         "../data/r_500_500/raw/2.png"};

    std::vector<std::tuple<int, int, int>> out = build_minhash_graph(flist, 10, 10, simple, 0.5);

    std::vector<std::tuple<int, int, int>> exp = {{0, 1, 20}, {0, 2, 21}, {1, 2, 20}};

    std::map<std::pair<int, int>, int> ans;
    std::map<std::pair<int, int>, bool> exists;

    for(auto t : exp){
        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        ans[tmp]=third;
        exists[tmp]=false;
    }

    for(auto t : out){
        std::tuple<int, int, int> nt = normalizeTuple(t);

        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        REQUIRE(ans.count(tmp)==1);

        REQUIRE(ans.at(tmp)==third);

        exists[tmp]=true;
    }

    for(auto t : exp){
        int first = std::get<0>(t);
        int second = std::get<1>(t);
        int third = std::get<2>(t);

        std::pair<int, int> tmp = std::make_pair(first, second);

        REQUIRE(exists.at(tmp)==true);
    }
}