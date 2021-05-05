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

    void CorrectionBox::Draw() {
        // Draw solid box color
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidRect(ci::Rectf(kTopLeftCoordinates,
                                        kBottomRightCoordinates));
        ci::gl::color(ci::Color("black"));
        if (correction_rectangles_.empty()) {
            ci::gl::drawStrokedRect(ci::Rectf(kTopLeftCoordinates,
                                              kBottomRightCoordinates));
            ci::gl::drawStringCentered("Sorry, we could not find suggestions",
                                       ci::Rectf(kTopLeftCoordinates,
                                                 kBottomRightCoordinates).getCenter(),
                                       ci::Color("black"),
                                       ci::Font("Times New Roman", 30));
        } else {
            // Draw each individual correction box
            for (auto const& correction_rectangle : correction_rectangles_) {
                ci::gl::drawStrokedRect(correction_rectangle.second);
                ci::gl::drawStringCentered(correction_rectangle.first,
                                           correction_rectangle.second.getCenter(),
                                           ci::Color("black"),
                                           ci::Font("Times New Roman", 30));
            }
        }
        ci::gl::color(ci::Color("white"));
    }

    std::string CorrectionBox::GetClickedCorrection(vec2 const& click_position) {
        std::string clicked_string = GetClickedString(click_position);
        if (!clicked_string.empty()) ClearSavedCorrections();
        return clicked_string;
    }

    std::string CorrectionBox::GetClickedString(vec2 const& position) {
        for (auto const& correction_rectangle : correction_rectangles_) {
            if (correction_rectangle.second.contains(position)) {
                return correction_rectangle.first;
            }
        }
        return "";
    }

    void CorrectionBox::ClearSavedCorrections() {
        correction_rectangles_.clear();
        contains_corrections_ = false;
    }




}  // namespace visualizer

}  // namespace autocorrect
