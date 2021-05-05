#include <visualizer/autocorrect_app.h>

namespace autocorrect {

namespace visualizer {

AutocorrectApp::AutocorrectApp() {
    std::ifstream ifs("../../../data/saved_autocorrect");
    ifs >> autocorrect_;
    ci::app::setWindowSize((int) kXWindowSize, (int) kYWindowSize);
    textBox = TextBox().font( kFont)
            .size( vec2(kXWindowSize - 5*kMargin,
                        kYWindowSize - kMargin))
            .color(ci::Color("black"))
            .backgroundColor(ci::Color("white"));
}

    void AutocorrectApp::draw() {
        ci::gl::clear(ci::Color8u(255, 246, 148));

        ci::gl::draw(ci::gl::Texture2d::create( textBox.render()),
                     kTextBoxOffset);

        if (!is_edit_mode_) correction_mode_.Draw();
    }

    void AutocorrectApp::mouseDown(ci::app::MouseEvent event) {
        if (!is_edit_mode_) {
            if (correction_mode_.HandleClickChanges(event.getPos())) {
                textBox.setText(correction_mode_.GetTextString());
                correction_mode_.SetTextAndCorrections(textBox,
                                                       autocorrect_.GetCorrections(correction_mode_.GetTextString()));
            }
        }
    }

    void AutocorrectApp::keyDown(ci::app::KeyEvent event) {
        if (event.getCode() == ci::app::KeyEvent::KEY_RETURN) {
            is_edit_mode_ = !is_edit_mode_;
            if (!is_edit_mode_) {
                correction_mode_.SetTextAndCorrections(textBox,
                                                       autocorrect_.GetCorrections(textBox.getText()));
            } else {
                editMode.SetTextString(textBox.getText());
            }
        } else if (is_edit_mode_) {
            editMode.HandleKeyDownEvent(event);
        }
    }




}  // namespace visualizer

}  // namespace autocorrect
