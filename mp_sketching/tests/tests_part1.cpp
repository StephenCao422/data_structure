#include <catch2/catch_test_macros.hpp>


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <filesystem>
#include "sketching.h"
#include "utils.h"

std::vector<uint64_t> file_to_minhash(std::string fname){
    std::vector<uint64_t> mh;
    std::vector<std::string> totalRows;
    int rowNum = split_string(file_to_string(fname), '\n', totalRows);

    std::string r = totalRows[0];
    r = trim(r);
    if(r.size() > 0){
        std::vector<std::string> totalCols;
        int colNum = split_string(r, ',', totalCols);
        for(auto & v : totalCols){
            v = trim(v);
            if(v.size() > 0){
                mh.push_back(stoull(v));
            }
            
        }
    }
    return mh;
}

TEST_CASE("test_kminhash", "[weight=5]") {
    std::string dirpath = "../data/universe_100/raw/";
    std::vector<std::string> filenames;
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};
    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kminhash_8");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = kminhash(input, 8, hash_1);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }

    dirpath = "../data/universe_10000/raw/";
    filenames.clear();
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kminhash_256");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = kminhash(input, 256, hash_1);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }

    std::vector test = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<uint64_t> out = kminhash(test, 5, hash_2);
    std::vector<uint64_t> exp = file_to_minhash("../data/misc/kminhash_hash2_5.csv");


    REQUIRE(out.size() == exp.size());

    for(unsigned i = 0; i < exp.size(); i++){
        REQUIRE(out[i] == exp[i]);
    }

    out = kminhash(test, 3, hash_500);
    exp = file_to_minhash("../data/misc/kminhash_hash500_3.csv");

    REQUIRE(out.size() == exp.size());

    for(unsigned i = 0; i < exp.size(); i++){
        REQUIRE(out[i] == exp[i]);
    }

}

TEST_CASE("test_khash", "[weight=5]") {
    std::string dirpath = "../data/universe_100/raw/";
    std::vector<std::string> filenames;
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};
    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "khash_8");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = khash_minhash(input, hv);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }

    dirpath = "../data/universe_10000/raw/";
    filenames.clear();
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "khash_8");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = khash_minhash(input, hv);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }
}

TEST_CASE("test_kpartition", "[weight=5]") {
    std::string dirpath = "../data/universe_100/raw/";
    std::vector<std::string> filenames;
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};
    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kpart_3");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = kpartition_minhash(input, 3, hash_1);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }

    dirpath = "../data/universe_10000/raw/";
    filenames.clear();
    for (const auto & entry : std::filesystem::directory_iterator(dirpath)){
        std::string fname = entry.path();
        if(fname.find("dataset") != std::string::npos){
            filenames.push_back( fname );
        }
    }

    for(auto f : filenames){
        std::string kminhash_f = f;

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kpart_8");

        std::vector<int> input = readFile(f);

        std::vector<uint64_t> user_kmin = kpartition_minhash(input, 8, hash_1);

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);

        REQUIRE(user_kmin.size() == expected_kmin.size());

        for(unsigned i = 0; i < expected_kmin.size(); i++){
            REQUIRE(user_kmin[i] == expected_kmin[i]);
        }
    }

    std::vector t = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<uint64_t> out = kpartition_minhash(t, 3, hash_2);
    std::vector<uint64_t> exp = file_to_minhash("../data/misc/kpart_hash2_3.csv");


    REQUIRE(out.size() == exp.size());

    for(unsigned i = 0; i < exp.size(); i++){
        REQUIRE(out[i] == exp[i]);
    }

    out = kpartition_minhash(t, 3, hash_500);
    exp = file_to_minhash("../data/misc/kpart_hash500_3.csv");

    REQUIRE(out.size() == exp.size());

    for(unsigned i = 0; i < exp.size(); i++){
        REQUIRE(out[i] == exp[i]);
    }
}

TEST_CASE("test_exact_cardinality", "[weight=2]"){
    std::vector<std::string> flist = {"../data/universe_100/raw/dataset_0.txt", "../data/universe_100/raw/dataset_1.txt",\
     "../data/universe_100/raw/dataset_10.txt", "../data/universe_100/raw/dataset_11.txt", "../data/universe_100/raw/dataset_12.txt",\
     "../data/universe_100/raw/dataset_13.txt", "../data/universe_100/raw/dataset_14.txt", "../data/universe_100/raw/dataset_15.txt", \
     "../data/universe_100/raw/dataset_16.txt", "../data/universe_100/raw/dataset_17.txt", "../data/universe_100/raw/dataset_18.txt",\
      "../data/universe_100/raw/dataset_19.txt", "../data/universe_100/raw/dataset_2.txt", "../data/universe_100/raw/dataset_3.txt",\
       "../data/universe_100/raw/dataset_4.txt", "../data/universe_100/raw/dataset_5.txt", "../data/universe_100/raw/dataset_6.txt",\
        "../data/universe_100/raw/dataset_7.txt", "../data/universe_100/raw/dataset_8.txt", "../data/universe_100/raw/dataset_9.txt"};

    std::vector<int> ec_list = {35, 44, 55, 57, 38, 62, 32, 34, 60, 50, 47, 56, 40, 73, 42, 32, 59, 43, 40, 36};

    for(unsigned i = 0; i < flist.size(); i++){
        std::vector<int> input = readFile(flist[i]);
        int ec = exact_cardinality(input);

        REQUIRE(ec == ec_list[i]);
    }
}

TEST_CASE("test_minhash_cardinality", "[weight=5]"){
    std::vector<std::string> flist = {"../data/universe_100/raw/dataset_0.txt", "../data/universe_100/raw/dataset_1.txt",\
     "../data/universe_100/raw/dataset_10.txt", "../data/universe_100/raw/dataset_11.txt", "../data/universe_100/raw/dataset_12.txt",\
     "../data/universe_100/raw/dataset_13.txt", "../data/universe_100/raw/dataset_14.txt", "../data/universe_100/raw/dataset_15.txt", \
     "../data/universe_100/raw/dataset_16.txt", "../data/universe_100/raw/dataset_17.txt", "../data/universe_100/raw/dataset_18.txt",\
      "../data/universe_100/raw/dataset_19.txt", "../data/universe_100/raw/dataset_2.txt", "../data/universe_100/raw/dataset_3.txt",\
       "../data/universe_100/raw/dataset_4.txt", "../data/universe_100/raw/dataset_5.txt", "../data/universe_100/raw/dataset_6.txt",\
        "../data/universe_100/raw/dataset_7.txt", "../data/universe_100/raw/dataset_8.txt", "../data/universe_100/raw/dataset_9.txt"};

    std::vector<int> kmin_list = {33, 36, 47, 38, 38, 50, 25, 25, 38, 50, 36, 55, 34, 50, 33, 25, 43, 38, 25, 34};
    std::vector<int> khash_list = {155, 80, 155, 22, 80, 155, 155, 31, 80, 31, 80, 155, 155, 155, 155, 80, 155, 155, 31, 80};
    std::vector<int> kpart_list = {155, 80, 155, 22, 80, 155, 155, 31, 80, 31, 80, 155, 155, 155, 155, 80, 155, 155, 31, 80};

    for(unsigned i = 0; i < flist.size(); i++){
        std::string kminhash_f = flist[i];
        std::string khash_min_f = flist[i];
        std::string kpart_f = flist[i];

        kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kminhash_8");
        khash_min_f.replace(khash_min_f.find("raw"), string("raw").size(), "khash_8");
        kpart_f.replace(kpart_f.find("raw"), string("raw").size(), "kpart_3");

        std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);
        std::vector<uint64_t> expected_khash = file_to_minhash(khash_min_f);
        std::vector<uint64_t> expected_kpart = file_to_minhash(kpart_f);

        int kmin_ec = minhash_cardinality(expected_kmin, 8);
        int khash_ec = minhash_cardinality(expected_khash, 1);
        int kpart_ec = minhash_cardinality(expected_kpart, 1);

        REQUIRE(kmin_ec == kmin_list[i]);
        REQUIRE(khash_ec == khash_list[i]);
        REQUIRE(kpart_ec == kpart_list[i]);
    }
}

TEST_CASE("test_exact_jaccard", "[weight=3]"){
    std::vector<std::string> flist = {"../data/universe_100/raw/dataset_0.txt", "../data/universe_100/raw/dataset_1.txt", \
         "../data/universe_100/raw/dataset_2.txt", "../data/universe_100/raw/dataset_3.txt","../data/universe_100/raw/dataset_4.txt"};

        std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};
        std::vector<float> ec_list = {1.000000, 0.295082, 0.271186, 0.301205, 0.262295, 0.295082, 1.000000,\
         0.200000, 0.444444, 0.283582, 0.271186, 0.200000, 1.000000, 0.329412, 0.242424, 0.301205, 0.444444, 0.329412,\
          1.000000, 0.369048, 0.262295, 0.283582, 0.242424, 0.369048, 1.000000};

        unsigned count = 0;
        float delta = 0.0001;

        for(auto f : flist){

            std::vector<int> input = readFile(f);
            for( auto f2 : flist){
                std::vector<int> input2 = readFile(f2);
                float user_ej = exact_jaccard(input, input2);
                float expected_ej = ec_list[count];
                REQUIRE(0 <= user_ej);
                REQUIRE(1 >= user_ej);

                REQUIRE(expected_ej + delta >= user_ej);
                REQUIRE(expected_ej - delta <= user_ej);

                count++;
            }
        }
}

TEST_CASE("test_minhash_jaccard", "[weight=5]"){
    std::vector<std::string> flist = {"../data/universe_100/raw/dataset_0.txt", "../data/universe_100/raw/dataset_1.txt", \
         "../data/universe_100/raw/dataset_2.txt", "../data/universe_100/raw/dataset_3.txt","../data/universe_100/raw/dataset_4.txt"};

        std::vector<hashFunction> hv = {hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_500, hash_1000};
        std::vector<float> kmin_list = {1.000000, 0.230769, 0.230769, 0.230769, 0.230769, 0.230769, 1.000000,\
         0.066667, 0.333333, 0.230769, 0.230769, 0.066667, 1.000000, 0.333333, 0.230769, 0.230769, 0.333333,\
          0.333333, 1.000000, 0.230769, 0.230769, 0.230769, 0.230769, 0.230769, 1.000000};
        std::vector<float> khash_list = {1.000000, 0.142857, 0.333333, 0.333333, 0.454545, 0.142857, 1.000000,\
         0.066667, 0.454545, 0.230769, 0.333333, 0.066667, 1.000000, 0.230769, 0.230769, 0.333333, 0.454545, 0.230769,\
          1.000000, 0.454545, 0.454545, 0.230769, 0.230769, 0.454545, 1.000000};
        std::vector<float> kpart_list = {1.000000, 0.066667, 0.066667, 0.230769, 0.142857, 0.066667, 1.000000,\
         0.066667, 0.142857, 0.333333, 0.066667, 0.066667, 1.000000, 0.333333, 0.142857, 0.230769, 0.142857, 0.333333,\
          1.000000, 0.333333, 0.142857, 0.333333, 0.142857, 0.333333, 1.000000};

        unsigned count = 0;
        float delta = 0.0001;

        for(auto f : flist){
            std::string kminhash_f = f;
            std::string khash_min_f = f;
            std::string kpart_f = f;

            kminhash_f.replace(kminhash_f.find("raw"), string("raw").size(), "kminhash_8");
            khash_min_f.replace(khash_min_f.find("raw"), string("raw").size(), "khash_8");
            kpart_f.replace(kpart_f.find("raw"), string("raw").size(), "kpart_3");

            std::vector<uint64_t> expected_kmin = file_to_minhash(kminhash_f);
            std::vector<uint64_t> expected_khash = file_to_minhash(khash_min_f);
            std::vector<uint64_t> expected_kpart = file_to_minhash(kpart_f);

            for( auto f2 : flist){
                std::string kminhash_f2 = f2;
                std::string khash_min_f2 = f2;
                std::string kpart_f2 = f2;
                kminhash_f2.replace(kminhash_f2.find("raw"), string("raw").size(), "kminhash_8");
                khash_min_f2.replace(khash_min_f2.find("raw"), string("raw").size(), "khash_8");
                kpart_f2.replace(kpart_f2.find("raw"), string("raw").size(), "kpart_3");

                std::vector<uint64_t> expected_kmin2 = file_to_minhash(kminhash_f2);
                std::vector<uint64_t> expected_khash2 = file_to_minhash(khash_min_f2);
                std::vector<uint64_t> expected_kpart2 = file_to_minhash(kpart_f2);

                float user_kmin_j = minhash_jaccard(expected_kmin, expected_kmin2);
                float user_khash_j = minhash_jaccard(expected_khash, expected_khash2);
                float user_kpart_j = minhash_jaccard(expected_kpart, expected_kpart2);

                float expected = kmin_list[count];
                REQUIRE(0 <= user_kmin_j);
                REQUIRE(1 >= user_kmin_j);

                REQUIRE(expected + delta >= user_kmin_j);
                REQUIRE(expected - delta <= user_kmin_j);

                expected = khash_list[count];
                REQUIRE(0 <= user_khash_j);
                REQUIRE(1 >= user_khash_j);

                REQUIRE(expected + delta >= user_khash_j);
                REQUIRE(expected - delta <= user_khash_j);

                expected = kpart_list[count];
                REQUIRE(0 <= user_kpart_j);
                REQUIRE(1 >= user_kpart_j);

                REQUIRE(expected + delta >= user_kpart_j);
                REQUIRE(expected - delta <= user_kpart_j);

                count++;
            }
        }
}

