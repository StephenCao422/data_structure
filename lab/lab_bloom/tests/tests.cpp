#include <catch2/catch_test_macros.hpp>

#include "bloom.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
//#include <algorithm>
//#include <random>

using namespace std;


TEST_CASE("test_constructor", "[weight=1]") {
    std::vector<hashFunction> hv = {easy, cpp, simple, simple2, simple3};

    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        unsigned m = (rand() % 200) +1;
        std::vector<hashFunction> tmp;
        for(auto f : hv){
            if( rand() % 2 == 1){
                tmp.push_back(f);
            }
        }

        BF user(m, tmp);
         
        REQUIRE(user.bv.size() == m);
        REQUIRE(user.hv == tmp);
    }

}

TEST_CASE("test_copy", "[weight=1]") {
    std::vector<hashFunction> hv = {easy, cpp, simple, simple2, simple3};

    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        unsigned m = (rand() % 200) + 1;
        std::vector<bool> fake_bv;
        for(unsigned j = 0; j < m; j++){
            if (rand() % 4 == 0){
                fake_bv.push_back(true);
            } else{
                fake_bv.push_back(false);
            }
        }

        std::vector<hashFunction> tmp;
        for(auto f : hv){
            if( rand() % 2 == 1){
                tmp.push_back(f);
            }
        }

        BF orig(m, tmp);
        orig.bv = fake_bv;

        BF copy(orig);
         
        REQUIRE(copy.bv.size() == orig.bv.size());
        REQUIRE(copy.bv == orig.bv);
        REQUIRE(copy.hv == orig.hv);

        for(unsigned j = 0; j < m; j++){
            if (copy.bv[j]==0){
                if (rand() % 2 == 1){
                    copy.bv[j]=1;
                }
            }
        }

        REQUIRE(copy.bv != orig.bv);
        REQUIRE(copy.hv == orig.hv);
        REQUIRE(copy.bv.size() == orig.bv.size());
    }

}

TEST_CASE("test_add", "[weight=2]") {
    int n = 5;
    int m = 20;
    int universe = 100;

    std::vector<hashFunction> hv = {simple, simple2, simple3};
    std::vector<hashFunction> hv2 = {simple, simple2};
    std::vector<hashFunction> hv3 = {cpp, simple3};

    std::vector<int> in = {83, 86, 77, 15, 93};
    std::vector<int> in2 = {89, 86, 74, 50, 35};
    
    // n = 5, m=20, universe = 100
    std::vector<bool> b1_soln = {1,0,0,0,0,0,1,0,1,0,1,0,1,1,0,0,0,0,1,1};
    std::vector<bool> b2_soln = {0,1,0,1,0,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0};
    std::vector<bool> b3_soln = {0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,1};
    std::vector<bool> b4_soln = {0,1,0,0,0,0,1,0,0,1,1,0,0,0,1,1,0,0,0,1};
    
    BF b1(m, hv2);
    BF b2(m, hv3);
    BF b3(m ,hv2);
    BF b4(m, hv3);
    for(auto b : in){
        b1.add(b);
        b2.add(b);
    }

    for(auto b : in2){
        b3.add(b);
        b4.add(b);
    }

    REQUIRE(b1.bv == b1_soln);
    REQUIRE(b2.bv == b2_soln);
    REQUIRE(b3.bv == b3_soln);
    REQUIRE(b4.bv == b4_soln);

    std::vector<int> in3 = {1, 3, 5};
    m = 10;

    std::vector<bool> b5_soln = {1,1,0,0,1,0,1,1,1,1};
    std::vector<bool> b6_soln = {1,0,0,0,1,0,1,0,1,0};
    std::vector<bool> b7_soln = {0,1,0,1,0,1,0,1,0,1};

    BF b5(m, hv);
    BF b6(m, hv2);
    BF b7(m, hv3);
    for(auto b : in3){
        b5.add(b);
        b6.add(b);
        b7.add(b);
    }

    REQUIRE(b5.bv == b5_soln);
    REQUIRE(b6.bv == b6_soln);
    REQUIRE(b7.bv == b7_soln);


}

TEST_CASE("test_find (assumes add works)", "[weight=2]") {
    int n = 5;
    int m = 20;
    int universe = 100;

    std::vector<hashFunction> hv = {simple, simple2, simple3};
    std::vector<hashFunction> hv2 = {simple, simple2};
    std::vector<hashFunction> hv3 = {cpp, simple3};

    std::vector<int> in = {83, 86, 77, 15, 93};
    //std::vector<bool> expected_bv = {1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,1,1};

    std::vector<int> present = {3, 6, 9, 15, 17, 26, 35, 37, 43, 46, 49,\
     50, 53, 57, 63, 75, 77, 83, 86, 89, 90, 93};

    std::vector<int> absent = {0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 13, 14,\
     16, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34,\
      36, 38, 39, 40, 41, 42, 44, 45, 47, 48, 51, 52, 54, 55, 56, 58, 59,\
       60, 61, 62, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 76, 78, 79,\
        80, 81, 82, 84, 85, 87, 88, 91, 92, 94, 95, 96, 97, 98, 99};

    BF b1(m, hv);
    for(auto b : in){
        b1.add(b);
    }

    for(auto p : present){
        REQUIRE(b1.contains(p)==true);
    }

    for(auto a : absent){
        REQUIRE(b1.contains(a)==false);
    }

    in = {1, 3, 5};
    m = 10;
    //std::vector<bool> expected_bv = {1,0,0,0,1,0,1,0,1,0};

    present = {1, 3, 5, 9, 11, 13, 15, 19, 21, 23,\
     25, 29, 31, 33, 35, 39, 41, 43, 45, 49, 51,\
      53, 55, 59, 61, 63, 65, 69, 71, 73, 75, 79,\
       81, 83, 85, 89, 91, 93, 95, 99};

    absent = {0, 2, 4, 6, 7, 8, 10, 12, 14, 16,\
     17, 18, 20, 22, 24, 26, 27, 28, 30, 32, 34,\
      36, 37, 38, 40, 42, 44, 46, 47, 48, 50, 52,\
       54, 56, 57, 58, 60, 62, 64, 66, 67, 68, 70,\
        72, 74, 76, 77, 78, 80, 82, 84, 86, 87, 88,\
         90, 92, 94, 96, 97, 98};

    BF b2(m, hv2);
    for(auto b : in){
        b2.add(b);
    }

    for(auto p : present){
        REQUIRE(b2.contains(p)==true);
    }

    for(auto a : absent){
        REQUIRE(b2.contains(a)==false);
    }

    in = {89, 86, 74, 50, 35};
    m = 7;
    //std::vector<bool> expected_bv = {1,1,1,1,1,1,1};

    present = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,\
     10, 11, 12, 13, 14, 15, 16, 17, 18, 19,\
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29,\
       30, 31, 32, 33, 34, 35, 36, 37, 38, 39,\
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49,\
         50, 51, 52, 53, 54, 55, 56, 57, 58, 59,\
         60, 61, 62, 63, 64, 65, 66, 67, 68, 69,\
          70, 71, 72, 73, 74, 75, 76, 77, 78, 79,\
           80, 81, 82, 83, 84, 85, 86, 87, 88, 89,\
            90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

    absent = {};

    BF b3(m, hv3);
    for(auto b : in){
        b3.add(b);
    }

    for(auto p : present){
        REQUIRE(b3.contains(p)==true);
    }

    for(auto a : absent){
        REQUIRE(b3.contains(a)==false);
    }

}

TEST_CASE("test_union", "[weight=1]") {
    std::vector<hashFunction> hv = {easy, cpp, simple, simple2, simple3};

    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        unsigned m = rand() % 200;
        std::vector<bool> fake_bv1;
        std::vector<bool> fake_bv2;
        std::vector<bool> ans;
        for(unsigned j = 0; j < m; j++){
            bool flipbv1 = (rand() % 5 == 0);
            bool flipbv2 = (rand() % 5 == 0);
            if (flipbv1){
                fake_bv1.push_back(true);
            } else{
                fake_bv1.push_back(false);
            }

            if (flipbv2){
                fake_bv2.push_back(true);
            } else{
                fake_bv2.push_back(false);
            }

            if (flipbv1 or flipbv2){
                ans.push_back(true);
            } else{
                ans.push_back(false);
            }
        }

        BF user(m, hv);
        BF other(m, hv);
        user.bv = fake_bv1;
        other.bv = fake_bv2;

        user.bit_union(other);
         
        REQUIRE(user.bv.size() == ans.size());
        REQUIRE(user.bv == ans);
    }
}

TEST_CASE("test_intersection", "[weight=1]") {
    std::vector<hashFunction> hv = {easy, cpp, simple, simple2, simple3};

    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        unsigned m = rand() % 200;
        std::vector<bool> fake_bv1;
        std::vector<bool> fake_bv2;
        std::vector<bool> ans;
        for(unsigned j = 0; j < m; j++){
            bool flipbv1 = (rand() % 5 == 0);
            bool flipbv2 = (rand() % 5 == 0);
            if (flipbv1){
                fake_bv1.push_back(true);
            } else{
                fake_bv1.push_back(false);
            }

            if (flipbv2){
                fake_bv2.push_back(true);
            } else{
                fake_bv2.push_back(false);
            }

            if (flipbv1 and flipbv2){
                ans.push_back(true);
            } else{
                ans.push_back(false);
            }
        }

        BF user(m, hv);
        BF other(m, hv);
        user.bv = fake_bv1;
        other.bv = fake_bv2;

        user.intersect(other);
         
        REQUIRE(user.bv.size() == ans.size());
        REQUIRE(user.bv == ans);
    }

}

TEST_CASE("test_fpr", "[weight=2]") {
    float delta = 0.001;

    std::vector<hashFunction> hv = {simple, simple2, simple3};
    std::vector<hashFunction> hv2 = {simple, simple2};
    std::vector<hashFunction> hv3 = {cpp, simple3};
    std::vector<int> in = {1, 3, 8, 30, 92, 50, 39};
    int n = 5;
    unsigned universe = 100;

    std::vector<int> m_vector = {10, 20, 30, 50};
    std::vector<float> ans_vector = {0.795699, 0.387097, 0.354839, 0.0967742};

    for(unsigned i = 0; i < m_vector.size(); i++){
        float user = measureFPR(in, m_vector[i], hv, universe);

        REQUIRE(user - delta < ans_vector[i]);
        REQUIRE(user + delta > ans_vector[i]);
    }

    m_vector = {10, 20, 30, 100};
    ans_vector = {0.646154, 0.2, 0.107692, 0};
    in = {83, 86, 77, 15, 93};
    universe = 200;

    for(unsigned i = 0; i < m_vector.size(); i++){
        float user = measureFPR(in, m_vector[i], hv, universe);

        REQUIRE(user - delta < ans_vector[i]);
        REQUIRE(user + delta > ans_vector[i]);
    }

    m_vector = {10, 20};
    ans_vector = {0.176471, 0};
    in = {1, 3, 5};
    universe = 20;

    for(unsigned i = 0; i < m_vector.size(); i++){
        float user = measureFPR(in, m_vector[i], hv, universe);

        REQUIRE(user - delta < ans_vector[i]);
        REQUIRE(user + delta > ans_vector[i]);
    }

    ans_vector = {0.411765, 0.117647};
    for(unsigned i = 0; i < m_vector.size(); i++){
        float user = measureFPR(in, m_vector[i], hv3, universe);

        REQUIRE(user - delta < ans_vector[i]);
        REQUIRE(user + delta > ans_vector[i]);
    }


}

TEST_CASE("test_bitfrombyte", "[weight=1]") {
    std::uint8_t tmp{ 0b11100101 };
    std::vector<bool> ans = {1, 1, 1, 0, 0, 1, 0, 1};
    std::uint8_t tmp2{ 0b10100101 };
    std::vector<bool> ans2 = {1, 0, 1, 0, 0, 1, 0, 1};
    std::uint8_t tmp3{ 0b11110111 };
    std::vector<bool> ans3 = {1, 1, 1, 1, 0, 1, 1, 1};
    std::uint8_t tmp4{ 0b00000001 };
    std::vector<bool> ans4 = {0, 0, 0, 0, 0, 0, 0, 1};
    std::uint8_t tmp5{ 0b11000000 };
    std::vector<bool> ans5 = {1, 1, 0, 0, 0, 0, 0, 0};

    for(int i = 0; i < 8; i++){
        bool u1 = getBitFromByte(static_cast<char>(tmp),i);
        bool u2 = getBitFromByte(static_cast<char>(tmp2),i);
        bool u3 = getBitFromByte(static_cast<char>(tmp3),i);
        bool u4 = getBitFromByte(static_cast<char>(tmp4),i);
        bool u5 = getBitFromByte(static_cast<char>(tmp5),i);

        REQUIRE(u1 == ans[i]);
        REQUIRE(u2 == ans2[i]);
        REQUIRE(u3 == ans3[i]);
        REQUIRE(u4 == ans4[i]);
        REQUIRE(u5 == ans5[i]);
    }
}

TEST_CASE("test_bitfromarray", "[weight=1]") {
    std::uint8_t tmp{ 0b11100101 };
    std::vector<bool> ans = {1, 1, 1, 0, 0, 1, 0, 1};
    std::uint8_t tmp2{ 0b10100101 };
    std::vector<bool> ans2 = {1, 0, 1, 0, 0, 1, 0, 1};
    std::uint8_t tmp3{ 0b11110111 };
    std::vector<bool> ans3 = {1, 1, 1, 1, 0, 1, 1, 1};
    std::uint8_t tmp4{ 0b00000001 };
    std::vector<bool> ans4 = {0, 0, 0, 0, 0, 0, 0, 1};
    std::uint8_t tmp5{ 0b11000000 };
    std::vector<bool> ans5 = {1, 1, 0, 0, 0, 0, 0, 0};


    std::vector<char> q1 = {static_cast<char>(tmp2), static_cast<char>(tmp4)};
    std::vector<bool> qa1 = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1};
    for(int i = 0; i < 16; i++){
        bool user = getBitFromArray(q1,i);

        REQUIRE(user == qa1[i]);
    }

    q1 = {static_cast<char>(tmp), static_cast<char>(tmp3), static_cast<char>(tmp5)};
    qa1 = {1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

    for(int i = 0; i < 24; i++){
        bool user = getBitFromArray(q1,i);

        REQUIRE(user == qa1[i]);
    }

    q1 = {static_cast<char>(tmp4), static_cast<char>(tmp), static_cast<char>(tmp5), static_cast<char>(tmp3)};
    qa1 = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1};

    for(int i = 0; i < 32; i++){
        bool user = getBitFromArray(q1,i);

        REQUIRE(user == qa1[i]);
    }
}