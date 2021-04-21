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