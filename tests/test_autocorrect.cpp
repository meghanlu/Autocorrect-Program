#include <catch2/catch.hpp>
#include <core/autocorrect.h>
#include <core/word_list.h>
#include <core/dictionary.h>
#include <fstream>

using autocorrect::algorithm::SymSpell;
using autocorrect::WordList;
using autocorrect::Dictionary;
using autocorrect::Autocorrect;
using std::vector;
using std::string;

TEST_CASE("Test operators") {
    std::ifstream ifs("../../../data/testing_data/"
                      "testing_word_frequencies.txt");
    WordList frequencyWordList(true, false);
    ifs >> frequencyWordList;
    Dictionary dictionary(frequencyWordList);
    Autocorrect autocorrect(dictionary);
    SECTION("Test operator<<") {
        std::ofstream ofs("../data/saved_autocorrect");
        ofs << autocorrect;
        ofs.close();
    }
    SECTION("Test operator>>") {
        Autocorrect autocorrect_2;
        std::ifstream ifs2("../data/saved_autocorrect");
        ifs2 >> autocorrect_2;

        string get_corrections = "hello with wish";
        REQUIRE(autocorrect.GetCorrections(get_corrections)
                        == autocorrect_2.GetCorrections(get_corrections));
    }
}