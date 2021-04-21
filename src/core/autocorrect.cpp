#include <core/autocorrect.h>
namespace autocorrect {

    Autocorrect::Autocorrect(Dictionary const& dictionary)
                                        : dictionary_(dictionary),
                                        sym_spell(dictionary){
    }

    std::map<std::string, std::vector<std::string>> Autocorrect::GiveFeedback(string const& string) {
        std::istringstream iss(string);
        std::vector<std::string> words;
        std::map<std::string, std::vector<std::string>> suggestions;

        std::string word; // for storing each word
        while (iss >> word)
        {
            words.push_back(word);
        }

        for (std::string const& word : words) {
            if (!dictionary_.IsWordInDictionary(word)) {
                suggestions.insert(std::pair<std::string,
                                   std::vector<std::string>>(word,
                                           sym_spell.GetSimilarWords(word, dictionary_)));
            }
        }
        return suggestions;
    }


} // namespace autocorrect