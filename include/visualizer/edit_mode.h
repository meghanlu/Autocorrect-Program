#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace autocorrect {
using std::string;

namespace visualizer {

class EditMode {
public:
    void Draw() const;
    void HandleKeyDownEvent(ci::app::KeyEvent event);
    void SetTextString(string const& text_string);
    string GetTextString();

private:
    string text_string_;

};

}  // namespace autocorrect

}  // namespace naivebayes
