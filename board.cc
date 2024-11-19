#include "textobserver.h"

TextObserver::TextObserver(Studio* subject, int top , int bottom , int left, int right) : 
    subject{subject}, top{top}, bottom{bottom}, left{left}, right{right} {
    subject->attach(this);
}
TextObserver::~TextObserver() {
    subject->detach(this);
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


char Studio::getState(int row, int col) const {
    return thePicture->charAt(row, col, ticks);
}