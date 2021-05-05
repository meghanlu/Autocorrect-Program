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
    vec2 right_position;
    vec2 left_position = invalid_position;
    for (size_t i = 0; i < textbox.measureGlyphs().size(); i++) {
        if (text_.at(i) == ' ') {
            if (!word.empty()) {
                right_position = textbox.measureGlyphs().at(i - 1).second
                                 + kOffset
                                 + kRightPositionOffset;

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
                                + kOffset;
            }
        }
    }
    if (!word.empty()) {
        right_position = textbox.measureGlyphs().at(
                textbox.measureGlyphs().size() - 1).second
                         + kOffset
                         + kRightPositionOffset;

        words_and_positions.push_back(std::make_pair(
                std::make_pair(word, word_first_index),
                Rectf(right_position, left_position)));
    }

    for (auto const& word_rect : words_and_positions) {
        if (corrections.find(word_rect.first.first) != corrections.end()) {
            // If the word is incorrect
            incorrect_words.insert(std::make_pair(word_rect.first,
                                                  word_rect.second));
        }
    }

}

void CorrectionMode::Draw() {
    // Draw boxes around incorrect words
    for (auto const& incorrect_word : incorrect_words) {
        ci::gl::color(ci::Color("red"));
        ci::gl::drawStrokedRect(incorrect_word.second);
    }
    // Draw correction box if there is one
    if (correction_box_.ContainsCorrections()) correction_box_.Draw();
}

bool CorrectionMode::HandleClickChanges(vec2 const& click_position) {
    if (correction_box_.ContainsCorrections()) {
        pair<string, size_t> word_to_correct =
                correction_box_.GetWordToCorrect();
        string clicked_string =
                correction_box_.GetClickedCorrection(click_position);
        if (!clicked_string.empty()) {
            text_.erase(word_to_correct.second, word_to_correct.first.size());
            text_.insert(word_to_correct.second, clicked_string);
            return true;
        }
    }
    for (auto const &incorrect_word : incorrect_words) {
        Rectf word_rect = incorrect_word.second;
        if (word_rect.getLowerRight().x <= click_position.x
            && word_rect.getLowerRight().y <= click_position.y
            && word_rect.getUpperLeft().x >= click_position.x
            && word_rect.getUpperLeft().y >= click_position.y
                ) {
            correction_box_.InitializeCorrections(incorrect_word.first,
                             corrections_.at(incorrect_word.first.first));
        }
    }
    return false;
}

}  // namespace visualizer

}  // namespace autocorrect
