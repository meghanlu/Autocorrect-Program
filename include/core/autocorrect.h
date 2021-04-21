#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <sstream>
#include <core/dictionary.h>
#include <algorithm/sym_spell.h>


namespace autocorrect {
    using std::string;
    using std::vector;
    using autocorrect::algorithm::SymSpell;

    class Autocorrect {

    public:
        Autocorrect();
        Autocorrect(Dictionary const& dictionary);
        std::map<std::string, std::vector<std::string>> GiveFeedback(string const& str);

    private:
        SymSpell sym_spell;
        Dictionary dictionary_;
    };

}  // namespace naivebayes