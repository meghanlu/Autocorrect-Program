#include <core/dictionary.h>

namespace autocorrect {

    Dictionary::Dictionary(){
        InitializeVariables(vector<string>{});
    }
    Dictionary::Dictionary(Dictionary const &d){
        word_vector_ = d.word_vector_;
        words_set_ = d.words_set_;
    }

    Dictionary::Dictionary(WordList word_list) {
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

} // namespace autocorrect