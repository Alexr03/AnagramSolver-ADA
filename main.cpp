#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

void allCombinations(string word, int startIndex, int endIndex, vector<string> *collection);

string convertToLowerCase(string word) {
    std::for_each(word.begin(), word.end(), [](char &c) {
        c = ::tolower(c);
    });

    return word;
}

std::string &trim(std::string &str, const std::string &chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars));
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

vector<string> generateDictionary() {
    vector<string> dictionary;
    std::ifstream englishDictionary("words_alpha.txt");

    for (std::string line; getline(englishDictionary, line);) {
        dictionary.push_back(trim(line));
    }

    return dictionary;
}

vector<string> Split(const string &str, int splitLength) {
    int NumSubstrings = str.length() / splitLength;
    vector<std::string> ret;

    for (auto i = 0; i < NumSubstrings; i++) {
        ret.push_back(str.substr(i * splitLength, splitLength));
    }
    if (str.length() % splitLength != 0) {
        ret.push_back(str.substr(splitLength * NumSubstrings));
    }

    return ret;
}

int main() {
    int minimumCharacters = 3;

    vector<string> englishWords = generateDictionary();
    string word;
    std::vector<string> possibleAnagrams;
    cout << "Please enter a word: ";
    cin >> word;

    for (int i = minimumCharacters; i <= word.size(); i++) {
        vector<string> splittedString = Split(word, i);
        for (string v : splittedString) {
            if (v.size() >= minimumCharacters) {
                allCombinations(convertToLowerCase(v), 0, v.size() - 1, &possibleAnagrams);
            }
        }
    }

    cout << "Possible anagrams:" << endl;
    for (const auto &anagram : possibleAnagrams) {
        bool conta = find(englishWords.begin(), englishWords.end(), anagram) != englishWords.end();
        if (conta) {
            cout << anagram << endl;
        }
    }

    cout << "FINISHED";
    return 0;
}

void allCombinations(string word, int startIndex, int endIndex, vector<string> *collection) {
    if (find(collection->begin(), collection->end(), word) == collection->end()) {
        if (startIndex == endIndex) {
            cout << word << endl;
            collection->push_back(word);
        }
    }

    for (int i = startIndex; i <= endIndex; i++) {
        swap(word[startIndex], word[i]);
        allCombinations(word, startIndex + 1, endIndex, collection);
        swap(word[startIndex], word[i]);
    }
}