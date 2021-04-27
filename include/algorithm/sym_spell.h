#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
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

            SymSpell(const Dictionary &dictionary, size_t ed);

/**
             * Gets similar words to a given word from a given dictionary.
             */
            vector<string> GetSimilarWords(const string &word, const Dictionary &dictionary);

        private:
            const size_t kEditDistance;
            const size_t kMaxSuggestedWords = 5;
            const size_t kPrefixLength = 5;
            unordered_map<string, std::unordered_set<string>> deletes_;

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