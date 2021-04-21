#include <core/dictionary.h>

namespace autocorrect {

    bool Dictionary::IsWordInDictionary(string const& word) const {
        return !(words_set_.find(word) == words_set_.end());
    }

    void Dictionary::InitializeVariables(vector<string>  const& word_vector) {
        word_vector_ = word_vector;
        for (string const& word : word_vector) {
            words_set_.insert(word);
        }

    }
} // namespace autocorrect