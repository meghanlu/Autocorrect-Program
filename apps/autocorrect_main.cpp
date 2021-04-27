#pragma once
#include <iostream>
#include <core/word_list.h>
#include <algorithm/sym_spell.h>
#include <core/dictionary.h>
#include <core/autocorrect.h>
#include <fstream>

using std::vector;
using std::string;
using autocorrect::WordList;
using autocorrect::Dictionary;
using autocorrect::algorithm::SymSpell;
using autocorrect::Autocorrect;


int main() {
//    autocorrect::WordList word_list(vector<string>{"Zealous", "false",
//                                                   "zeal", "aa", "aAa", "B"},
//                                                                false);
//    vector<string> alphabetical{"aa", "aaa", "b", "false", "zeal", "zealous"};
//    auto a2 = word_list.GetWordVector();
//    for (size_t i = 0; i < alphabetical.size(); i++) {
//        std::cout<< alphabetical[i] << " = " << a2[i] << std::endl;
//    }

    // Parses training images from a file to a vector of images
    std::ifstream ifs("../data/testing_words.txt");
    WordList all_words(true);
    ifs >> all_words;
    ifs.close();
    Dictionary dict(all_words);
    Autocorrect varname(dict);
    //SymSpell sym_spell(dictionary);
//    for (string const& suggestion : sym_spell.GetSimilarWords("aaa")) {
//        std::cout<< suggestion << std::endl;
//    }

    std::cout << "Done" << std::endl;
    return 0;
}