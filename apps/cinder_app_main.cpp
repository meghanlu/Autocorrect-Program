#include <visualizer/autocorrect_app.h>

using autocorrect::visualizer::AutocorrectApp;

void prepareSettings(AutocorrectApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AutocorrectApp, ci::app::RendererGl, prepareSettings);
