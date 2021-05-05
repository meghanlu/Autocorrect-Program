#pragma once
#include "cinder/gl/gl.h"
#include <map>

namespace autocorrect {
using glm::vec2;
using std::map;

namespace visualizer {

/**
 * A box that contains a corrections for a given word.
 */
class CorrectionBox {
public:

    /**
     * Creates Correction Box with specified coordinates.
     */
    CorrectionBox(){};
    CorrectionBox(vec2 const& top_left_coordinates,
                  vec2 const& bottom_right_coordinates);

    /**
     * Initializes Correction Box variables.
     */
    void InitializeCorrections(std::pair<std::string,
                               size_t> const& word_to_correct,
                               const std::vector<std::string> &corrections);

    /**
     * Draws Correction Box.
     */
    void Draw();

    /**
     * Gets clicked correction from mouse click position (if there is one).
     * Returns empty string if no corrections were clicked.
     */
    std::string GetClickedCorrection(vec2 const& click_pos);

    /**
     * Returns if the correction box has a word to correct.
     */
    bool ContainsCorrections() {return contains_corrections_;};

    /**
     * Returns word to correct.
     */
    std::pair<std::string, size_t> GetWordToCorrect();

private:
    const std::string kNoSuggestionsMessage = "Sorry, no suggestions found.";
    const vec2 kTopLeftCoordinates = vec2(1600, 300);
    const vec2 kBottomRightCoordinates = vec2(1850, 800);
    bool contains_corrections_ = false;
    std::pair<std::string, size_t> word_to_correct_;
    map<std::string, ci::Rectf> correction_rectangles_;

    /**
     * Clears saved correction rectangles and
     * resets contains_corrections_ to false.
     */
    void ClearSavedCorrections();

};

}  // namespace visualizer

}  // namespace autocorrect
