#include <catch2/catch.hpp>
#include <core/word_list.h>

using autocorrect::WordList;
using std::vector;
using std::string;

TEST_CASE("Test Constructors and Contains Frequencies") {
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
                                                        "false", "zeal", "zealous"});

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