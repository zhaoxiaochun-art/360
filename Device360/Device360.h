#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_Device360.h"
#include "ProgramSet.h"
#include "LoginDialog.h"
#include "ResultData.h"
#include "DailyLog.h"
#include "WindowOut.h"

class Device360 : public QMainWindow
{
    Q_OBJECT

public:
    Device360(QWidget *parent = Q_NULLPTR);
	int showMsgBox(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);
private:
	Ui::Device360Class ui;
	QString AppPath;
	ProgramSet *m_ProgramDlg;
	ResultData *m_ResultDlg;
	DailyLog *m_DailyLogDlg; 
	int m_iShutDownPC;//0:�˳����򲻹ػ� 1�˳������������ػ� 2�������������ػ� 3������������󲻹ػ�
	WindowOut* levelOut = nullptr;
public slots:
	void on_Button_Clean_toggled(bool checked);
	void on_Button_Start_toggled(bool checked);
	void on_Button_AlarmReset_clicked();
	void on_Button_ParaSet_pressed();
	void on_Button_ParaSet_released();
	void on_Button_Log_clicked();
	void on_Button_DataOut_clicked();
	void on_Button_CountReset_pressed();
	void on_Button_CountReset_released();
	void on_pB_Keyboard_clicked();
	void on_Button_Exit_pressed();
	void on_Button_Exit_released();
	void on_lE_PN_returnPressed();
	void on_lE_RunSpeed_returnPressed();
};
