#include <core/dictionary.h>
#include <iostream>

namespace autocorrect {

    Dictionary::Dictionary(){
        InitializeVariables(vector<string>{});
    }
    Dictionary::Dictionary(Dictionary const &d){
        word_vector_ = d.word_vector_;
        words_set_ = d.words_set_;
        word_frequencies_ = d.word_frequencies_;
    }

    Dictionary::Dictionary(WordList const& word_list) {
        if (word_list.ContainsFrequencies()) {
            word_frequencies_ = word_list.GetWordFrequencies();
        }
        InitializeVariables(word_list.GetWordVector());
    }

    bool Dictionary::IsWordInDictionary(string const& word) const {
        return !(words_set_.find(word) == words_set_.end());
    }

    void Dictionary::InitializeVariables(vector<string>  const& word_vector) {
        word_vector_ = word_vector;
        for (string const& word : word_vector) {
            words_set_.insert(word);
        }
    }

    vector<string> Dictionary::GetWordVector() const {
        return word_vector_;
    }

    double Dictionary::GetWordFrequency(const string &word) const {
        auto it = word_frequencies_.find(word);
        if (it == word_frequencies_.end()) {
            throw "" + word + " is not in word list...";
        } else {
            return it->second;
        }
    }

} // namespace autocorrect