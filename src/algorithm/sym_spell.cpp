#include <algorithm/sym_spell.h>
namespace autocorrect {
namespace algorithm {
    SymSpell::SymSpell(Dictionary const& dictionary) {
        GeneratePrecalculatedDeletes(dictionary);
    }

    SymSpell::SymSpell(Dictionary const& dictionary, size_t prefix_length)
                    : dictionary_(dictionary), prefix_length_(prefix_length){
        GeneratePrecalculatedDeletes();
    }

    void SymSpell::GeneratePrecalculatedDeletes(Dictionary const &dictionary) {
        for (string const &word : dictionary.GetWordVector()) {
            for (string const &delete_string : GenerateDeletes(word)) {
                auto delete_string_itr = deletes_.find(delete_string);
                if (delete_string_itr == deletes_.end()) {
                    deletes_.insert({delete_string, vector<string>{word}});
                    //deletes_.insert(std::make_pair<string>(delete_string ,vector<string>{word}));
                } else {
                    // TODO: sort suggested word vector by frequency count!!
                    delete_string_itr->second.push_back(word);
                }
            }
        }

    }

    vector<string> SymSpell::GetSimilarWords(const string &word,
                                             const autocorrect::Dictionary &dictionary) {
        vector<string> words_to_return;
        vector<string> input_deletes = GenerateDeletes(word);
        for (const auto &it : deletes_) {
            if (it.first == word) {
                words_to_return.insert(words_to_return.end(), it.second.begin(),
                                       it.second.end());
            }
        }
        for (const string &input_delete : input_deletes) {
            if (dictionary.IsWordInDictionary(input_delete)) {
                words_to_return.push_back(input_delete);
            }
            for (const auto &it : deletes_) {
                if (it.first == input_delete) {
                    words_to_return.insert(words_to_return.end(), it.second.begin(),
                                           it.second.end());
                }
            }
        }
        //delete(dictionary entry,p1)==delete(input entry,p2) (TRANSPOSES/REPLACES)
        return words_to_return;
    }


    vector<string> SymSpell::GenerateDeletes(string const &word) {
        vector<std::pair<string, string>> string_splits;
        size_t prefix_length = (word.size() > prefix_length_) ? prefix_length_ : word.size();
        for (size_t i = 0; i < prefix_length; i++) {
            string_splits.push_back(std::make_pair(word.substr(0, i),
                                                   word.substr(i, word.size() - i)));

        }
        vector<string> delete_vector;
        for (std::pair<string, string> const &split_pair : string_splits) {
            string delete_string = split_pair.first +
                                   split_pair.second.substr(1, split_pair.second.size() - 1);
            delete_vector.push_back(delete_string);
        }
        return delete_vector;
    }
} //namespace algorithm
} // namespace autocorrect