#include <catch2/catch.hpp>
#include <core/dictionary.h>
#include <fstream>

using autocorrect::Dictionary;
using std::vector;
using std::string;



TEST_CASE("Test Dictionary With Frequencies") {
    std::ifstream ifs("../../../data/testing_word_frequencies.txt");
    autocorrect::WordList frequencyWordList(false, true);
    ifs >> frequencyWordList;
    Dictionary freq_dict(frequencyWordList);

    SECTION("Test Contains Frequencies") {
        REQUIRE(freq_dict.ContainsFrequencies());
    }

    SECTION("Test Is Word In Dictionary") {
        SECTION("Word In Dictionary") {
            REQUIRE(freq_dict.IsWordInDictionary("test"));
        }

        SECTION("Word Not In Dictionary") {
            REQUIRE(freq_dict.IsWordInDictionary("testings"));
        }
    }
}

TEST_CASE("Test Dictionary Without Frequencies") {
    std::ifstream ifs2("../../../data/testing_words.txt");
    autocorrect::WordList word_list;
    ifs2 >> word_list;
    Dictionary dict(word_list);

    SECTION("Test Contains Frequencies") {
        REQUIRE_FALSE(word_list.ContainsFrequencies());
    }

    SECTION("Test Is Word In Dictionary") {
        SECTION("Word In Dictionary") {
            REQUIRE(dict.IsWordInDictionary("apple"));
        }

        SECTION("Word Not In Dictionary") {
            REQUIRE(dict.IsWordInDictionary("aospk"));
        }
    }
}