#include <catch2/catch.hpp>
#include <core/algorithm/sym_spell.h>
#include <core/word_list.h>
#include <core/dictionary.h>
#include <fstream>

using autocorrect::algorithm::SymSpell;
using autocorrect::WordList;
using autocorrect::Dictionary;
using std::vector;
using std::string;

TEST_CASE("Test Get Similar Words") {
    std::ifstream ifs("../../../data/testing_data/"
                      "testing_word_frequencies.txt");
    WordList frequencyWordList(true, false);
    ifs >> frequencyWordList;
    Dictionary dictionary(frequencyWordList);
    SymSpell sym_spell(dictionary);
    REQUIRE(sym_spell.GetSimilarWords("wis", dictionary) == vector<string>{"with"});
}

TEST_CASE("Test Get Precalculated Deletes") {
    std::ifstream ifs("../../../data/testing_data/"
                      "testing_word_frequencies.txt");
    WordList frequencyWordList(true, false);
    ifs >> frequencyWordList;
    Dictionary dictionary(frequencyWordList);
    SymSpell sym_spell;
    REQUIRE(sym_spell.GetPrecalculatedDeletes() == unordered_map<string,
            unordered_set<string>>{});

}