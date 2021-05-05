#pragma once
#include <iostream>
#include <core/word_list.h>
#include <core/algorithm/sym_spell.h>
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

    std::ifstream ifs("../data/testing_frequencies");
    WordList frequencyWordList(true, false);
    ifs >> frequencyWordList;

    Dictionary dictionary(frequencyWordList);
    Autocorrect autocorrect(dictionary);

    std::ofstream ofs("../data/saved_autocorrect");
    ofs << autocorrect;
    ofs.close();
    Autocorrect autocorrect_2;

    std::ifstream ifs2("../data/saved_autocorrect");
    ifs2 >> autocorrect_2;
    std::cout << "Corrections:" << std::endl;
    auto corrections = autocorrect_2.GetCorrections(
            "alforithm bana withpp pancaek");
    for (auto it = corrections.begin(); it != corrections.end(); ++it) {
        std::cout<< it->first << ": ";
        for (string const& correct_word : it->second) {
            std::cout<< correct_word << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "Done" << std::endl;
    return 0;
}