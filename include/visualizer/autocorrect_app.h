#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include <fstream>

#include <core/autocorrect.h>
#include <visualizer/correction_box.h>
#include <visualizer/correction_mode.h>
#include <visualizer/edit_mode.h>

namespace autocorrect {

using ci::TextBox;
using glm::vec2;

namespace visualizer {

class AutocorrectApp : public ci::app::App {
public:
    AutocorrectApp();

    AutocorrectApp(Autocorrect autocorrect);


    void update() override;
    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;



private:
//    string* text_string;
    const double kXWindowSize = 1920;
    const double kYWindowSize = 1106;
    const double kMargin = 100;
    const vec2 kTextBoxOffset = vec2(50, 50);
    const ci::Font kFont = ci::Font( "Times New Roman", 36 );

    bool is_edit_mode_ = true;
    TextBox textBox;
    Autocorrect autocorrect_;
    CorrectionMode correction_mode_;
    EditMode editMode;
};

}  // namespace visualizer

}  // namespace autocorrect
