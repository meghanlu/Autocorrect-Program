#include <catch2/catch.hpp>
#include <core/word_list.h>
#include <fstream>

using autocorrect::WordList;
using std::vector;
using std::string;
using std::unordered_map;

TEST_CASE("Test operator>>") {
    SECTION("Frequency Word List") {
        std::ifstream ifs("../../../data/testing_data/testing_word_frequencies.txt");
        WordList frequencyWordList(true, false);
        ifs >> frequencyWordList;

        vector<string> expected_word_vector = {"meghan", "test", "testing"};
        REQUIRE(frequencyWordList.GetWordVector() == expected_word_vector);

        for (size_t i = 0; i < expected_word_vector.size(); i++) {
            REQUIRE(frequencyWordList.GetWordFrequencies().
                            at(expected_word_vector.at(i))
                            == Approx(log(i + 1)));
        }
    }

    SECTION("No Frequency Word List") {
        std::ifstream ifs("../../../data/testing_data/testing_words.txt");
        WordList word_list;
        ifs >> word_list;
        vector<string> expected_word_vector = {"apple", "banana", "carrot"};
        REQUIRE(word_list.GetWordVector() == expected_word_vector);
    }
}

TEST_CASE("Test Contains Frequencies In Constructors") {
    SECTION("Empty Constructor") {
        WordList word_list;
        REQUIRE_FALSE(word_list.ContainsFrequencies());
    }

    SECTION("Vector Constructor") {
        WordList word_list(vector<string>{"zealous", "zeal", "aa", "aaa", "b"});
        REQUIRE_FALSE(word_list.ContainsFrequencies());
    }

    SECTION("Frequencies Boolean Constructor") {
        SECTION("Contains Frequencies") {
            WordList word_list(true, true);
            REQUIRE(word_list.ContainsFrequencies());
        }
        SECTION("Doesn't Contain Frequencies") {
            WordList word_list(false, true);
            REQUIRE_FALSE(word_list.ContainsFrequencies());
        }
    }
}

TEST_CASE("Test Alphabetizing") {
    WordList word_list(vector<string>{"zealous", "zeal", "aa", "aaa", "b"},
                       false);
    REQUIRE(word_list.GetWordVector() == vector<string>{"aa", "aaa", "b",
                                                         "zeal", "zealous"});

}

TEST_CASE("Test Convert String to Lowercase") {
    SECTION("Lowercase String") {
        REQUIRE(WordList::ConvertStringToLowercase("h e l lo") == "h e l lo");
    }

    SECTION("Capital String") {
        REQUIRE(WordList::ConvertStringToLowercase("HEL LO") == "hel lo");
    }

    SECTION("Mixed Case String") {
        REQUIRE(WordList::ConvertStringToLowercase("HeLlO") == "hello");
    }
}