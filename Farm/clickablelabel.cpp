#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        emit clicked();
    //убрал баг при котором после клика на виджет дальнейшим кликам было не важно, где курсор, все равно тригеррилось нажатие на виджет (пкм + qmenu)
    else if ((event->button() == Qt::RightButton) && (this->rect().contains(event->pos())))
    {
        emit rightClicked();
    }
}
