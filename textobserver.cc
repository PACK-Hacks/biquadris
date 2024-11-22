#include "textobserver.h"

TextObserver::TextObserver(Display* subject, int top, int bottom, int left, int right) 
    :subject{subject}, top{top}, bottom{bottom}, left{left}, right{right} {
        subject->attach(this);
}
void TextObserver::notify() {
    out << '+';
    for (int j = left; j <= right; ++j) out << '-';
    out << '+' << std::endl;

    for (int i = top; i <= bottom; ++i) {
        out << '|';
        for (int j = left; j <= right; ++j) {
            out << subject->getState(i, j);
        }
        out << '|' << std::endl;
    }
    out << '+';
    for (int j = left; j <= right; ++j) out << '-';
    out << '+' << std::endl;
}

// memeory deltion is delegated to Observer
TextObserver::~TextObserver() {
    subject->detach(this);
}
