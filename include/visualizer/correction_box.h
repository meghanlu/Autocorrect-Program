#pragma once
#include "cinder/gl/gl.h"
#include <map>

namespace autocorrect {
using glm::vec2;
using std::map;

namespace visualizer {

class CorrectionBox {
public:
    CorrectionBox(){};
    CorrectionBox(vec2 const& top_left_coordinates,
                  vec2 const& bottom_right_coordinates);

    /**
     *
     */
    void InitializeCorrections(std::pair<std::string, size_t> const& word_to_correct,
                               const std::vector<std::string> &corrections);
    void Draw();
    std::string GetClickedCorrection(vec2 const& click_pos);
    bool ContainsCorrections() {return contains_corrections_;};
    std::pair<std::string, size_t> GetWordToCorrect();

private:
    bool contains_corrections_ = false;
    std::pair<std::string, size_t> word_to_correct_;
    map<std::string, ci::Rectf> correction_rectangles_;
    const vec2 kTopLeftCoordinates = vec2(1600, 300);
    const vec2 kBottomRightCoordinates = vec2(1850, 800);
    std::string GetClickedString(vec2 const& click_pos);

    void ClearSavedCorrections();

};

}  // namespace visualizer

}  // namespace autocorrect
