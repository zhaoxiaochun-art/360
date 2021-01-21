#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_Device360.h"

class Device360 : public QMainWindow
{
    Q_OBJECT

public:
    Device360(QWidget *parent = Q_NULLPTR);

private:
    Ui::Device360Class ui;
public slots:
	void on_Button_Clean_toggled(bool checked);
	void on_Button_Exit_clicked();
	void on_Button_CountReset_clicked();
	void changeRunSpeed();
	void on_lE_PN_returnPressed();
};
