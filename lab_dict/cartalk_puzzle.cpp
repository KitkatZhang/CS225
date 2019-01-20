/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

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
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
	string word;
	std::vector <string> file_data;
	if (wordsFile.is_open()) {
	    /* Reads a line from `wordsFile` into `word` until the file ends. */
	    while (getline(wordsFile, word)) {
	        //cout << word << endl;
	        file_data.push_back(word);
	    }
	}

	for(auto it : file_data){
		std::string miss_first = it;
		std::string miss_second = it;
		if(it.length() <= 2){
			continue;
		}

		int len_first = it.length() - 1;
		int len_second = it.length() - 2;
		miss_first = it.substr(1, len_first);
		miss_second = it[0] + it.substr(2, len_second);

		bool judge1 = d.homophones(it, miss_first);
		bool judge2 = d.homophones(miss_first, miss_second);
		bool judge = judge1 && judge2;

		if(judge){
			auto re = std::make_tuple(it, miss_first, miss_second);
			ret.push_back(re);
		}

	}
    return ret;
}
