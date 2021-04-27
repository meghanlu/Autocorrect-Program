#pragma once

#include <sstream>
#include "core/word_list.h"

namespace autocorrect {

    WordList::WordList(bool is_alphabetized) : is_alphabetized_(is_alphabetized){}

    WordList::WordList(bool is_alphabetized, bool contains_frequencies) :
    is_alphabetized_(is_alphabetized), contains_frequencies_(contains_frequencies){}

    WordList::WordList(vector<string> const& word_vec, bool is_alphabetized) :
                         words_(word_vec), is_alphabetized_(is_alphabetized){
        if (!is_alphabetized) AlphabetizeWords();
    }

    void WordList::AddWordVector(vector<string> const& word_vec) {
        words_ = word_vec;
        AlphabetizeWords();
    }

    vector<string> WordList::GetWordVector() const {
        return words_;
    }

    std::istream &operator>>(std::istream &is, WordList &word_list) {
        word_list.words_and_frequencies_.clear();
        word_list.words_.clear();
        size_t length_of_longest_english_word = 60;
        char line[60];
        // Loop through each line
        if (word_list.contains_frequencies_) {
            while (is.getline(line, length_of_longest_english_word)) {
                std::istringstream iss(line);
                std::string word_or_frequency;
                string word = "";
                while (iss >> word_or_frequency)
                {
                    if (word == "") {
                        word = word_or_frequency;
                        word_list.words_.push_back(word);
                    } else {
                        double frequency = log(std::stoll(word_or_frequency));
                        std::pair<std::string,double> word_freq_pair (word,frequency);
                        word_list.words_and_frequencies_.insert(word_freq_pair);
                    }
                }
            }
            word_list.AlphabetizeWords();
        } else {
            //size_t length_of_longest_english_word = 46;
            while (is.getline(line, length_of_longest_english_word)) {
                word_list.words_.push_back(line);
            }
            if (!word_list.is_alphabetized_) word_list.AlphabetizeWords();
        }
        return is;
    }

    void WordList::AlphabetizeWords() {
        auto compare_alphabetically = [this](std::string const& a, std::string const& b) {
            string lowercase_a = ConvertStringToLowercase(a);
            string lowercase_b = ConvertStringToLowercase(b);
            return lowercase_a < lowercase_b;};
        std::sort(words_.begin(), words_.end(), compare_alphabetically);
    }

    string WordList::ConvertStringToLowercase(string const& string) {
        std::string lowercase_string;
        for (char str_char : string) {
            lowercase_string += tolower(str_char);
        }
        return lowercase_string;
    }
} // namespace autocorrect