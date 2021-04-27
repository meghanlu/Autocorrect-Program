#pragma once
#include "core/word_list.h"

namespace autocorrect {

    WordList::WordList(bool is_alphabetized) : is_alphabetized_(is_alphabetized){}

    WordList::WordList(vector<string> const& word_vec, bool is_alphabetized) :
                         words_(word_vec), is_alphabetized_(is_alphabetized){
        AlphabetizeWords();
    }

    vector<string> WordList::GetWordVector() {
        return words_;
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

    void WordList::AlphabetizeWords() {
        if (is_alphabetized_) return;
        auto compare_alphabetically = [this](std::string a, std::string b) {
            string lowercase_a = ConvertToLowercaseString(a);
            string lowercase_b = ConvertToLowercaseString(b);
            return lowercase_a < lowercase_b;};
        std::sort(words_.begin(), words_.end(), compare_alphabetically);
    }

    string WordList::ConvertToLowercaseString(string const& string) {
        std::string lowercase_string;
        for (char str_char : string) {
            lowercase_string += tolower(str_char);
        }
        return lowercase_string;
    }


} // namespace autocorrect