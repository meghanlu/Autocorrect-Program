#include <algorithm/sym_spell.h>
namespace autocorrect {
    namespace algorithm {

        SymSpell::SymSpell(const Dictionary &dictionary, size_t ed) :
                kEditDistance(ed) {
            SetDictionary(dictionary);
        }

        void SymSpell::SetDictionary(Dictionary const& dictionary) {
            GeneratePrecalculatedDeletes(dictionary);
        }

        void SymSpell::GeneratePrecalculatedDeletes(Dictionary const &dictionary) {
            deletes_.clear();
            for (string const &word : dictionary.GetWordVector()) {
                for (string const &delete_string : GenerateDeletes(dictionary, word)) {
                    auto delete_string_itr = deletes_.find(delete_string);
                    if (delete_string_itr == deletes_.end()) {
                        deletes_.insert({delete_string, unordered_set<string>{word}});
                    } else {
                        // TODO: sort suggested word vector by frequency count!!
                        delete_string_itr->second.insert(word);
                    }
                }
            }
            //GenerateAdditionalPrecalculatedDeletes(dictionary, kEditDistance);
        }

        void SymSpell::GenerateAdditionalPrecalculatedDeletes(Dictionary const& dictionary,
                                                              size_t edit_distance) {
            if (edit_distance <= 1) return;
            for (const auto &it : deletes_) {
                for (string const& delete_string : GenerateDeletes(dictionary, it.first)) {
                    auto delete_string_itr = deletes_.find(delete_string);
                    if (delete_string_itr == deletes_.end()) {
                        deletes_.insert({delete_string, it.second});
                    } else {
                        for (string const& word: it.second) {
                            delete_string_itr->second.insert(word);
                        }
                    }
                }
            }
            GenerateAdditionalPrecalculatedDeletes(dictionary, edit_distance - 1);
        }

//    void SymSpell::GeneratePrecalculatedDeletes(vector<string> const& words,
//                                           size_t remaining_edit_distance) {
//        if (remaining_edit_distance <= 0) return;
//        for (string const &word : words) {
//            if (word.size() > 1) {
//                vector<string> delete_vector = GenerateDeletes(word);
//                for (string const &delete_string : delete_vector) {
//                    auto delete_string_itr = deletes_.find(delete_string);
//                    if (delete_string_itr == deletes_.end()) {
//                        deletes_.insert({delete_string, unordered_set<string>{word}});
//                    } else {
//                        delete_string_itr->second.insert(word);
//                    }
//                }
////                GeneratePrecalculatedDeletes(delete_vector,
////                                             remaining_edit_distance - 1);
//            }
////            vector<string> delete_vector = GenerateDeletes(word);
////            if (remaining_edit_distance > 1) {
////                GeneratePrecalculatedDeletes(delete_vector,
////                                             remaining_edit_distance - 1);
////            }
////            for (string const &delete_string : delete_vector) {
////                auto delete_string_itr = deletes_.find(delete_string);
////                if (delete_string_itr == deletes_.end()) {
////                    deletes_.insert({delete_string, unordered_set<string>{word}});
////                } else {
////                    delete_string_itr->second.insert(word);
////                }
////            }
//        }
//
//    }


        vector<string> SymSpell::GetSimilarWords(const string &word,
                                                 const Dictionary &dictionary) {
            vector<string> words_to_return;
            vector<string> input_deletes = GenerateInputStringDeletes(dictionary, word);
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
                    if (it.first == input_delete
                        && IsWithinEditDistance(it.first, input_delete, kEditDistance)) {
                        words_to_return.insert(words_to_return.end(), it.second.begin(),
                                               it.second.end());
                    }
                }
            }
            std::unordered_set<string> s(words_to_return.begin(), words_to_return.end());
            words_to_return.assign(s.begin(), s.end());

            if (dictionary.ContainsFrequencies()) {
                words_to_return = SortWordsByFrequency(dictionary,
                                                       words_to_return);
            }

            return words_to_return;
        }

        vector<string> SymSpell::SortWordsByFrequency(Dictionary const& dictionary,
                                                      vector<string> word_vector) {
            vector<std::pair<double, string>> frequencies;
            vector<string> sorted_words;
            for (string const& s : word_vector) {
                frequencies.push_back(std::make_pair(dictionary.GetWordFrequency(s), s));
            }

            auto compare_by_frequency = [](std::pair<double, string>& a,
                                           std::pair<double, string>& b) {
                return a.first > b.first;};

            std::sort(frequencies.begin(), frequencies.end(),
                      compare_by_frequency);

            for(auto const& freq_word_pair : frequencies) {
                sorted_words.push_back(freq_word_pair.second);
                if (sorted_words.size() >= kMaxSuggestedWords) break;
            }
            return sorted_words;
        }

        vector<string> SymSpell::GenerateDeletes(Dictionary const& dictionary, string const &word) {
            vector<std::pair<string, string>> string_splits;
            size_t prefix_length = (word.size() > kPrefixLength) ? kPrefixLength : word.size();
            for (size_t i = 0; i < prefix_length; i++) {
                string_splits.push_back(std::make_pair(word.substr(0, i),
                                                       word.substr(i, word.size() - i)));

            }
            vector<string> delete_vector;
            for (std::pair<string, string> const &split_pair : string_splits) {
                string delete_string = split_pair.first +
                                       split_pair.second.substr(1, split_pair.second.size() - 1);
                //if (!dictionary.IsWordInDictionary(delete_string))
                delete_vector.push_back(delete_string);
            }
            return delete_vector;
        }

        vector<string> SymSpell::GenerateInputStringDeletes(Dictionary const& dict,
                                                            const string &word) {
            vector<string> input_deletes = GenerateDeletes(dict, word);
            unordered_set<string> deletes_set(input_deletes.begin(),
                                              input_deletes.end());

            for (size_t ed = 1; ed < kEditDistance; ed++) {
                for (const string &input_delete : input_deletes) {
                    for (string const& del : GenerateDeletes(dict, word)) {
                        deletes_set.insert(del);
                    }
                }
                input_deletes.assign(deletes_set.begin(), deletes_set.end());
            }

            return input_deletes;
        }

        bool SymSpell::IsWithinEditDistance(const string &original,
                                            const string &other, size_t edit_distance) {
            return GetLevenshteinDistance(original, other) <= edit_distance;
        }

        size_t SymSpell::GetLevenshteinDistance(const string &s1, const string &s2)
        {
            const size_t m(s1.size()), n(s2.size());

            if( m==0 ) return n;
            if( n==0 ) return m;

            size_t *costs = new size_t[n + 1];

            for( size_t k=0; k<=n; k++ ) costs[k] = k;

            size_t i = 0;
            for (char const &c1 : s1)
            {
                costs[0] = i+1;
                size_t corner { i }, j { 0 };
                for (char const &c2 : s2)
                {
                    size_t upper { costs[j+1] };
                    if( c1 == c2 ) costs[j+1] = corner;
                    else {
                        size_t t(upper<corner? upper: corner);
                        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
                    }

                    corner = upper;
                    j++;
                }
                i++;
            }
            size_t result = costs[n];
            delete[] costs;
            return result;
        }


    } //namespace algorithm
} // namespace autocorrect