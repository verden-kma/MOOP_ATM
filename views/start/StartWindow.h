//
// Created by Iron Tony on 20/10/2020.
//

#ifndef ATM_STARTWINDOW_H
#define ATM_STARTWINDOW_H

#include <QWidget>
#include "views/main/controller/ControllerLogicSettable.h"
#include "views/registration/RegistrationWindow.h"
#include "views/mainMenu/MainMenuWindow.h"

namespace Ui {
    class StartWindow;
}

// TODO enter pin card number
class StartWindow : public QWidget, public ControllerLogic {
Q_OBJECT

public:
    explicit StartWindow(QWidget* parent = nullptr);
    ~StartWindow() override;

    void setController(ControllerLogicSettable* logicSettable);

private:
    Ui::StartWindow* _ui;
    ControllerLogicSettable* _logicSettable;
    RegistrationWindow _registrationWindow;
    MainMenuWindow _mainMenuWindow;

    bool checkPin();

    void onBtn0Clicked() override;
    void onBtn1Clicked() override;
    void onBtnCardClicked() override;
    void onBtnEnterClicked() override;
    void onBtnCancelClicked() override;

    int state();
};

#endif // ATM_STARTWINDOW_H
