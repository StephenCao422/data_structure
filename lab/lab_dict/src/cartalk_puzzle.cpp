/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                                                         const string &word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    //return ret;
    ifstream wordsFile(word_list_fname);
    string word;

    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            if (word.size() >= 3) {
                string originalWord = word;
                string wordWithoutFirst = originalWord.substr(1,word.size());
                string wordWithoutSecond = originalWord.substr(0, 1) + originalWord.substr(2);

                if (d.homophones(originalWord, wordWithoutFirst) && d.homophones(originalWord, wordWithoutSecond)) {
                    ret.push_back(make_tuple(word, wordWithoutFirst, wordWithoutSecond));
                }
            }
        }
    } 
    return ret;
}
