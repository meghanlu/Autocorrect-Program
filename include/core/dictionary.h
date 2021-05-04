#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <istream>
#include <core/word_list.h>

namespace autocorrect {
    using std::string;
    using std::vector;
    using std::unordered_map;

    class Dictionary {

    public:
        Dictionary();
        Dictionary(Dictionary const &d);
        Dictionary(WordList const& word_list);

        /**
         * Returns if a given word is in the dictionary.
         */
        bool IsWordInDictionary(const string& word) const;
        double GetWordFrequency(string const& word) const;
        vector<string> GetWordVector() const;
        bool ContainsFrequencies() const {return !word_frequencies_.empty();};
        unordered_map<string, double> GetFrequencies() const;
        void AddFrequencies(unordered_map<string, double> const& frequencies);
        void AddWords(vector<string> const& words_vector_);

        void SetWordFrequencies(const unordered_map<string, double> &frequencies);

    private:
        vector<string> words_vector_;
        unordered_map<string, double> word_frequencies_;
        std::unordered_set<string> words_set_;

        /**
         * Initializes dictionary data structures.
         */
        void InitializeVariables(vector<string> const& word_list);
    };

}  // namespace autocorrect