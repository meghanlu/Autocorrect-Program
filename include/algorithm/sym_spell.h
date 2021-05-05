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
        using std::unordered_set;

        class SymSpell {

        public:
            SymSpell(size_t edit_distance = 2) : kEditDistance(edit_distance) {};

            SymSpell(Dictionary const &dictionary, size_t ed = 2);

            /**
             * Gets similar words to a given word from a given dictionary.
             */
            vector<string> GetSimilarWords(const string &word, const Dictionary &dictionary);

            void SetDictionary(Dictionary const& dictionary);

            const unordered_map<string, unordered_set<string>> GetPrecalculatedDeletes() const;

        private:
            const size_t kEditDistance = 2;
            const size_t kMaxSuggestedWords = 5;
            const size_t kPrefixLength = 7;
            unordered_map<string, unordered_set<string>> deletes_;

            /**
             * Generates all delete possibilities for a word.
             */
            //vector<string> GenerateDeletes(string const &word);

            /**
             * Generates and stores precalculated deletes for a given dictionary.
             */
            void GeneratePrecalculatedDeletes(Dictionary const &dictionary);

            static size_t GetLevenshteinDistance(const string &s1, const string &s2);

            bool IsWithinEditDistance(const string &original, const string &other, size_t edit_distance);

            void GenerateAdditionalPrecalculatedDeletes(const Dictionary &dictionary, size_t edit_distance);

            vector <string> GenerateDeletes(const Dictionary &dictionary, const string &word);

            vector <string> GenerateInputStringDeletes(const Dictionary &dict, const string &word);

            //vector <string> SortWordsByFrequency(const Dictionary &dictionary, vector <string> word_vector) const;

            vector <string> RemoveDuplicateStrings(const vector <string> &word_vector);

            void RemoveDuplicateStrings(vector <string> &word_vector);

            vector <string> SortWordsByFrequency(const Dictionary &dictionary, const vector <string> &word_vector);
        };
    } //namespace algorithm
} // namespace autocorrect