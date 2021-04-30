#include <core/autocorrect.h>
namespace autocorrect {

    Autocorrect::Autocorrect(Dictionary const& dictionary)
                                        : dictionary_(dictionary){
        sym_spell.SetDictionary(dictionary);
    }

    std::map<std::string, std::vector<std::string>> Autocorrect::GetCorrections(string const& string) {
        std::istringstream iss(string);
        std::vector<std::string> words;
        std::map<std::string, std::vector<std::string>> suggestions;

        std::string word; // for storing each word
        while (iss >> word)
        {
            words.push_back(word);
        }

        for (std::string const& word : words) {
            if (!dictionary_.IsWordInDictionary(WordList::ConvertStringToLowercase(word))) {
                std::vector<std::string> suggested_words =
                        sym_spell.GetSimilarWords(word, dictionary_);
                suggestions.insert(std::pair<std::string,
                                   std::vector<std::string>>(word,
                                           suggested_words));
            }
        }
        return suggestions;
    }




    std::ostream &operator<<(std::ostream &os, const Autocorrect &autocorrect) {

        os.flush();
        // SAVE DICTIONARY FREQUENCY MAP
        for (auto const& word_freq_pair : autocorrect.dictionary_.GetFrequencies()) {
            os << "* " << word_freq_pair.first << " ";
            os << word_freq_pair.second << std::endl;
        }
        // SAVE SYMSPELL PRECALCULATED DELETES
        for (auto const& delete_pair : autocorrect.sym_spell.GetPrecalculatedDeletes()) {
            os << "& " << delete_pair.first << std::endl;
            for (string const& associated_string : delete_pair.second) {
                os << associated_string << std::endl;
            }
            os << "%" << std::endl;
        }
        return os;
    }

} // namespace autocorrect