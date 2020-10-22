//
// Created by Iron Tony on 21/10/2020.
//

#include "Clock.h"
#include "views/clock/setdialog/SetDialog.h"
#include <QTimer>

Clock::Clock(QWidget* parent) : QLCDNumber(parent) {
    setSegmentStyle(Filled);
    setDigitCount(18);

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::showDateTime);
    timer->start(1000);

    showDateTime();
}

void Clock::showDateTime() {
    if (_custom != nullptr) {
        *_custom = _custom->addSecs(1);
        displayTime(*_custom);
    } else {
        displayTime(QDateTime::currentDateTime());
    }
}

void Clock::mouseDoubleClickEvent(QMouseEvent* event) {
    SetDialog dialog;
    dialog.setModal(true);
    int result = dialog.exec();
    delete _custom;
    _custom = nullptr;
    if (result == 1) {
        _custom = new QDateTime(dialog.getDate(), dialog.getTime());
    }
}

void Clock::displayTime(const QDateTime& datetime) {
    QString text = datetime.toString("hh:mm:ss  dd-MM-yy");
    if ((datetime.time().second() % 2) == 0) {
        text[2] = ' ';
        text[5] = ' ';
    }
    display(text);
}
