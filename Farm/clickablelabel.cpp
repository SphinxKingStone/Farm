#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        emit clicked();
    else if (event->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
}
