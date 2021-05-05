#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include <map>
#include <utility>
#include <visualizer/correction_box.h>
#include <regex>
#include "cinder/Area.h"

namespace autocorrect {
using glm::vec2;
using ci::TextBox;
using std::string;
using std::vector;
using std::pair;
using ci::Rectf;
namespace visualizer {

/**
 * When in correction mode, user can see incorrect words and click with mouse
 * to change them to correct suggestions.
 */
class CorrectionMode {
public:
    CorrectionMode(){};

    /**
     * Handles mouse click events by the given mouse position.
     * Changes correction box or text string based on where is clicked.
     */
    bool HandleClickChanges(vec2 const& click_position);

    /**
     * Draws red boxes on incorrect words and draws correction box
     * if red box was clicked.
     */
    void Draw();

    /**
     * Initializes variables.
     */
    void SetTextAndCorrections(const TextBox &textbox,
                          map<string, vector<string>> const& corrections);

    /**
     * Gets saved text string.
     */
    string GetTextString(){return text_;};

private:
    const vec2 kOffset = vec2(50, 50);
    const vec2 kRightPositionOffset = vec2(20, 32);
    map<string, vector<string>> corrections_;
    map<pair<string, size_t>, Rectf> incorrect_words;
    string text_;
    CorrectionBox correction_box_;
};

}  // namespace visualizer

}  // namespace autocorrect
