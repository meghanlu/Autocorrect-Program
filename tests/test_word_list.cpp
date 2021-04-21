#include <catch2/catch.hpp>
#include <core/word_list.h>

using autocorrect::WordList;
using std::vector;
using std::string;

TEST_CASE("Test Alphabetizing") {
    WordList word_list(vector<string>{"zealous", "zeal", "aa", "aaa", "b"},
                                                                false);
    REQUIRE(word_list.GetWordVector() == vector<string>{"aa", "aaa", "b",
                                              "false", "zeal", "zealous"});

}