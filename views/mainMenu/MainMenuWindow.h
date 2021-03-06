//
// Created by Iron Tony on 20/10/2020.
//

#ifndef ATM_MAINMENUWINDOW_H
#define ATM_MAINMENUWINDOW_H

#include <QWidget>
#include "views/main/controller/ControllerLogicSettable.h"
#include "views/transaction/TransactionWindow.h"
#include "views/credit/CreditWindow.h"
#include "views/deposit/DepositWindow.h"
#include "views/payment/PaymentWindow.h"
#include "logics/managers/OperationManager.h"

namespace Ui {
    class MainMenuWindow;
}

class MainMenuWindow : public QWidget, public ControllerLogic {
Q_OBJECT

public:
    explicit MainMenuWindow(OperationManager& operationManager, QWidget* parent = nullptr);
    ~MainMenuWindow() override;

    void setController(ControllerLogicSettable* logicSettable);
    void setLogicActive();

signals:
    void signalBtnFinishClicked();

private slots:
    void onBtnBackToMainMenuClicked();

private:
    Ui::MainMenuWindow* _ui;
    ControllerLogicSettable* _logicSettable = nullptr;
    OperationManager& _operationManager;
    TransactionWindow _transactionWindow;
    CreditWindow _creditWindow;
    DepositWindow _depositWindow;
    PaymentWindow _paymentWindow;

public:
    void onBtnCancelClicked() override;
    void onBtn0Clicked() override;
    void onBtn1Clicked() override;
    void onBtn2Clicked() override;
    void onBtn3Clicked() override;
};

#endif // ATM_MAINMENUWINDOW_H
