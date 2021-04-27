#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace autocorrect {
    using std::string;
    using std::vector;

    class WordList {

    public:

        /**
         * Creates an empty Word List and
         * sets if the list needs to be alphabetized.
         */
        WordList(bool is_alphabetized);

        /**
         * Created a Word List with an a word vector and
         * if vector is alphabetized.
         */
        WordList(vector<string> const& word_vec, bool is_alphabetized);

        /**
         * Writes a file of words into a Word List object.
         */
        friend std::istream &operator>>(std::istream &is, WordList &word_list);
        vector<string> GetWordVector();

    private:
        // If word list needs to be alphabetized
        bool is_alphabetized_;
        // List of words
        vector<string> words_;

        /**
         * Alphabetize saved vector of strings.
         */
        void AlphabetizeWords();

        /**
         * Converts given string to lowercase string.
         */
        string WordList::ConvertToLowercaseString(string const& string);
    };

}  // namespace autocorrect