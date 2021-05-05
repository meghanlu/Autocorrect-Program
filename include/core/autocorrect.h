#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm/sym_spell.h>
#include <core/dictionary.h>



namespace autocorrect {
    using std::string;
    using std::vector;

    class Autocorrect {

    public:
        Autocorrect() {};
        Autocorrect(Dictionary const& dictionary);

        /**
         * Encodes and saves an autocorrect model to a file.
         */
        friend std::ostream &operator<<(std::ostream &os, const Autocorrect &autocorrect);

        /**
         * Loads an autocorrect model from an encoded file.
         */
        friend std::istream &operator>>(std::istream &is, Autocorrect &autocorrect);

        /**
         * Gives a map with words that are incorrect and a vector of possible corrections.
         */
        std::map<std::string, std::vector<std::string>> GetCorrections(string const& str);

    private:
        autocorrect::algorithm::SymSpell sym_spell;
        Dictionary dictionary_;
    };

}  // namespace naivebayes