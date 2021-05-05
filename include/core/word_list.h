#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <math.h>

namespace autocorrect {
    using std::string;
    using std::vector;
    using std::unordered_map;

    class WordList {

    public:

        /**
         * Creates an empty Word List and
         * sets if the list needs to be alphabetized.
         */
        WordList(bool is_alphabetized = true);

        /**
         * Created a Word List with an a word vector and
         * if vector is alphabetized.
         */
        WordList(vector<string> const& word_vec, bool is_alphabetized = true);

        WordList(bool contains_frequencies, bool is_alphabetized);

        /**
         * Writes a file of words into a Word List object.
         */
        friend std::istream &operator>>(std::istream &is, WordList &word_list);
        vector<string> GetWordVector() const;
        void AddWordVector(const vector <string> &word_vec);
        bool ContainsFrequencies() const {return contains_frequencies_;} ;
        unordered_map<string, double> GetWordFrequencies() const {
            return words_and_frequencies_;} ;
        static string ConvertStringToLowercase(string const& string);

    private:
        bool is_alphabetized_ = false;
        vector<string> words_;
        bool contains_frequencies_ = false;
        unordered_map<string, double> words_and_frequencies_;

        /**
         * Alphabetize saved vector of strings.
         */
        void AlphabetizeWords();
    };

}  // namespace autocorrect