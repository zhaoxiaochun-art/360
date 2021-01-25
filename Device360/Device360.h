#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_Device360.h"
#include "ProgramSet.h"
#include "LoginDialog.h"
#include "ResultData.h"

class Device360 : public QMainWindow
{
    Q_OBJECT

public:
    Device360(QWidget *parent = Q_NULLPTR);

private:
	Ui::Device360Class ui;
	ProgramSet *m_ProgramDlg;
	ResultData *m_ResultDlg;
public slots:
	void on_Button_Clean_toggled(bool checked);
	void on_Button_Start_toggled(bool checked);
	void on_Button_AlarmReset_clicked();
	void on_Button_CameraSet_clicked();
	void on_Button_Log_clicked();
	void on_Button_DataOut_clicked();
	void on_Button_CountReset_clicked();
	void on_Button_Exit_clicked();
	void on_lE_PN_returnPressed();
	void on_lE_RunSpeed_returnPressed();
};
