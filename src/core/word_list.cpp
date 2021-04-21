#pragma once
#include "core/word_list.h"

namespace autocorrect {

    WordList::WordList(bool is_alphabetized) : is_alphabetized_(is_alphabetized){}

    WordList::WordList(vector<string> const& word_vec, bool is_alphabetized) :
                         words_(word_vec), is_alphabetized_(is_alphabetized){
        AlphabetizeWords();
    }

    std::istream &operator>>(std::istream &is, WordList &word_list) {
        // Clear previous word list
        word_list.words_.clear();
        size_t length_of_longest_english_word = 200;
        char word[200];
        // Loop through each line
        while (is.getline(word, length_of_longest_english_word)) {
            word_list.words_.push_back(word);
        }
        word_list.AlphabetizeWords();
        return is;
    }



    string WordList::ConvertToLowercaseString(string const& string) {
        std::string lowercase_string;
        for (char str_char : string) {
            lowercase_string += tolower(str_char);
        }
        return lowercase_string;
    }


} // namespace autocorrect