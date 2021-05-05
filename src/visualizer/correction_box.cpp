#include <visualizer/correction_box.h>

namespace autocorrect {


namespace visualizer {

CorrectionBox::CorrectionBox(vec2 const& top_left_coordinates,
                             vec2 const& bottom_right_coordinates)
                             : kTopLeftCoordinates(top_left_coordinates),
                             kBottomRightCoordinates(bottom_right_coordinates){
}

void CorrectionBox::InitializeCorrections(std::pair<std::string, size_t> const& word_to_correct,
                                          std::vector<std::string> const& corrections) {
    ClearSavedCorrections();
    float y_increment = (kBottomRightCoordinates.y - kTopLeftCoordinates.y)
                        /corrections.size();
    for (size_t i = 0; i < corrections.size(); i++) {
        ci::Rectf rectangle = ci::Rectf(vec2(kTopLeftCoordinates.x,
                                             kTopLeftCoordinates.y +
                                             i * y_increment),
                                        vec2(kBottomRightCoordinates.x,
                                             kTopLeftCoordinates.y +
                                             (i + 1) * y_increment));
        std::string correction = corrections.at(i);
        correction_rectangles_.insert(std::make_pair(correction, rectangle));
    }
    word_to_correct_ = word_to_correct;
    contains_corrections_ = true;
}


}  // namespace visualizer

}  // namespace autocorrect
