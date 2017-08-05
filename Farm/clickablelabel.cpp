#include "clickablelabel.h"
#include <QDebug>

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

bool can_del = false;

void ClickableLabel::enterEvent(QEvent *)
{
    can_del = true;
    emit entered();
}

void ClickableLabel::leaveEvent(QEvent *)
{
    if (can_del)
    {
        emit left();
        can_del = false;
    }
}
