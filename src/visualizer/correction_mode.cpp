#include <visualizer/correction_mode.h>

namespace autocorrect {

namespace visualizer {

    void CorrectionMode::SetTextAndCorrections(const TextBox &textbox,
                                               map<string, vector<string>> const& corrections) {
        incorrect_words.clear();
        corrections_ = corrections;
        text_ = textbox.getText();

        vector<pair<pair<string, size_t>, Rectf>> words_and_positions;
        string word = "";
        size_t word_first_index;
        vec2 invalid_position = vec2(-1, -1);
        vec2 right_position = vec2(-1, -1);
        vec2 left_position = vec2(-1, -1);
        for (size_t i = 0; i < textbox.measureGlyphs().size(); i++) {
            if (text_.at(i) == ' ') {
                if (!word.empty()) {
                    right_position = textbox.measureGlyphs().at(i - 1).second
                                     + vec2(50, 50)
                                     + vec2(20, 32);

                    words_and_positions.push_back(std::make_pair(
                            std::make_pair(word, word_first_index),
                            Rectf(right_position, left_position)));

                    left_position = vec2(-1, -1);
                    word = "";
                }
            } else {
                word += text_.at(i);
                if (left_position == invalid_position) {
                    word_first_index = i;
                    left_position = textbox.measureGlyphs()[i].second
                                    + vec2(50, 50);
                }
            }
        }
        if (!word.empty()) {
            right_position = textbox.measureGlyphs().at(
                    textbox.measureGlyphs().size() - 1).second
                             + vec2(50, 50)
                             + vec2(25, 32);

            words_and_positions.push_back(std::make_pair(
                    std::make_pair(word, word_first_index),
                    Rectf(right_position, left_position)));
        }

        for (auto const& word_rect : words_and_positions) {
            if (corrections.find(word_rect.first.first) != corrections.end()) {
                // If the word is incorrect
                incorrect_words.insert(std::make_pair(word_rect.first, word_rect.second));
            }
        }

    }


}  // namespace visualizer

}  // namespace autocorrect
