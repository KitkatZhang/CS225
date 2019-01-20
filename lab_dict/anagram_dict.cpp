/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
	string word;
	std::vector <string> file_data;
	if (wordsFile.is_open()) {
	    /* Reads a line from `wordsFile` into `word` until the file ends. */
	    while (getline(wordsFile, word)) {
	        //cout << word << endl;
	        file_data.push_back(word);
	    }
	}

	std::vector <char> second;
	for(auto it : file_data){
		while(!second.empty()){
			second.pop_back();
		}
		unsigned len = it.length();
		for(unsigned i = 0; i < len; i ++){
			second.push_back(it[i]);
		}
		for(unsigned i = 0; i < len; i ++){
			for(unsigned j = i; j < len; j ++){
				if(second[j] < second[i]){
					char temp = second[i];
					second[i] = second[j];
					second[j] = temp;
				}
			}
		}
		std::string key = "";
		for(auto it : second){
			key += it;
		}
		vector<string> v;
		v.push_back(key);
		dict[it] = v;
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    std::vector <char> second;
	for(auto it : words){
		while(!second.empty()){
			second.pop_back();
		}
		unsigned len = it.length();
		for(unsigned i = 0; i < len; i ++){
			second.push_back(it[i]);
		}
		for(unsigned i = 0; i < len; i ++){
			for(unsigned j = i; j < len; j ++){
				if(second[j] < second[i]){
					char temp = second[i];
					second[i] = second[j];
					second[j] = temp;
				}
			}
		}
		std::string key = "";
		for(auto it : second){
			key += it;
		}
		vector<string> v;
		v.push_back(key);
		dict[it] = v;
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */

    auto find_ = dict.find(word);
    if(find_ == dict.end()){
    	return vector<string>();
    }
    string solu = (find_->second)[0];
    vector<string> ret;
	for(auto it : dict){
		if((it.second)[0] == solu){
			ret.push_back(it.first);
		}
	}

    return ret;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::map<std::string, std::string> dict_temp;
    std::map<string, vector<string>> quick;

    vector<vector<string>> ret;
    for(auto it : dict){
    	dict_temp[it.first] = (it.second)[0];
    }

    for(auto it : dict_temp){
    	quick[it.second].push_back(it.first);
    }

    for(auto it : quick){
    	if(it.second.size() > 1){
    		ret.push_back(it.second);
    	}
    }
    return ret;
}
