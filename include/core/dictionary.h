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
        Dictionary(WordList word_list);

        /**
         * Returns if a given word is in the dictionary.
         */
        bool IsWordInDictionary(const string& word) const;
        vector<string> GetWordVector() const;

    private:
        std::unordered_set<string> words_set_;
        vector<string> word_vector_;
        //unordered_map<char, vector<string>> words_by_first_letter_;

        /**
         * Initializes dictionary data structures.
         */
        void InitializeVariables(vector<string> const& word_list);

    };

}  // namespace autocorrect