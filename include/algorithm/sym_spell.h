#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <core/dictionary.h>
#include <utility>

namespace autocorrect {
namespace algorithm {
    using std::string;
    using std::vector;
    using std::unordered_map;

    class SymSpell {

    public:
        SymSpell() {};

        SymSpell(Dictionary const &dictionary);

        /**
         * Gets similar words to a given word from a given dictionary.
         */
        vector<string> GetSimilarWords(const string &word, const Dictionary &dictionary);

    private:
        size_t prefix_length_ = 7;
        unordered_map<string, vector<string>> deletes_;

        /**
         * Generates all delete possibilities for a word.
         */
        vector<string> GenerateDeletes(string const &word);

        /**
         * Generates and stores precalculated deletes for a given dictionary.
         */
        void GeneratePrecalculatedDeletes(Dictionary const &dictionary);

    };
} //namespace algorithm
} // namespace autocorrect