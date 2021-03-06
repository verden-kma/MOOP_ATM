//
// Created by Iron Tony on 20/10/2020.
//

#include "StartWindow.h"
#include "gui/ui_startwindow.h"

enum Windows {
    START,
    INFO,
    INSERT_CARD,
    REGISTER,
    MAIN_MENU,
};

#include "views/validator/Validators.h"

StartWindow::StartWindow(QWidget* parent) :
        QWidget(parent), _ui(new Ui::StartWindow),
        _operationManager(CustomerDataManager()),
        _registrationWindow(_operationManager),
        _mainMenuWindow(_operationManager) {
    _ui->setupUi(this);

    _ui->stackedWidget->addWidget(&_registrationWindow);
    _ui->stackedWidget->addWidget(&_mainMenuWindow);

    _ui->editCardNumber->setValidator(new QRegularExpressionValidator(
            QRegularExpression(cardNumberRegex), this));
    _ui->editPin->setValidator(new QRegularExpressionValidator(
            QRegularExpression(pinRegex), this));

    connect(&_registrationWindow, &RegistrationWindow::signalBtnCancelClicked,
            this, &StartWindow::onBtnCancelClicked);
    connect(&_mainMenuWindow, &MainMenuWindow::signalBtnFinishClicked,
            this, &StartWindow::onBtnCancelClicked);
}

StartWindow::~StartWindow() {
    delete _ui;
}

void StartWindow::setController(ControllerLogicSettable* logicSettable) {
    _logicSettable = logicSettable;
    _logicSettable->setLogic(this);
    _registrationWindow.setController(logicSettable);
    _mainMenuWindow.setController(logicSettable);
}

void StartWindow::onBtn0Clicked() {
    if (state() == START) {
        _ui->stackedWidget->setCurrentIndex(INFO);
    }
}

void StartWindow::onBtn1Clicked() {
    if (state() == START) {
        _registrationWindow.setLogicActive();
        _ui->stackedWidget->setCurrentIndex(REGISTER);
    }
}

void StartWindow::onBtnCardClicked() {
    if (state() == START) {
        _ui->stackedWidget->setCurrentIndex(INSERT_CARD);
        _ui->editCardNumber->setEnabled(true);
        _pinAttempts = 3;
        _ui->editCardNumber->setText("");
        _ui->editPin->setText("");
        _ui->labelAttemptsRemaining->setText(QString::number(_pinAttempts) + " attempts remaining");
    }
}

void StartWindow::onBtnEnterClicked() {
    if (state() == INSERT_CARD) {
        if (!_ui->editCardNumber->hasAcceptableInput()) {
            QMessageBox::critical(this, "ATM", "Card Number is invalid");
            return;
        }
        if (!_ui->editPin->hasAcceptableInput()) {
            QMessageBox::critical(this, "ATM", "Pin is invalid");
            return;
        }

        QString number = _ui->editCardNumber->text();
        QString pin = _ui->editPin->text();

        try {
            if (_operationManager.authorizeCustomer(number, pin)) {
                _mainMenuWindow.setLogicActive();
                _ui->stackedWidget->setCurrentIndex(MAIN_MENU);
            } else if (--_pinAttempts == 0) {
                OperationManager::blockCustomer(number);
                QMessageBox::critical(this, "ATM", "Your card has been blocked");
                _ui->stackedWidget->setCurrentIndex(START);
            } else {
                _ui->labelAttemptsRemaining->setText(QString::number(_pinAttempts) + " attempts remaining");
                _ui->editCardNumber->setEnabled(false);
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "ATM", e.what());
            _ui->stackedWidget->setCurrentIndex(START);
        }
    }
}

void StartWindow::onBtnCancelClicked() {
    if (cardLocked()) {
        QMessageBox::critical(this, "ATM", "Card is locked. "
                                           "Please provide the correct pin");
    } else {
        _logicSettable->setLogic(this);
        _ui->stackedWidget->setCurrentIndex(START);
    }
}

int StartWindow::state() {
    return _ui->stackedWidget->currentIndex();
}

void StartWindow::setClock(Clock* clock) {
    _operationManager.setClock(clock);
}

bool StartWindow::cardLocked() const {
    return _pinAttempts != 3;
}
