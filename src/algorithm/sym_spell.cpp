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