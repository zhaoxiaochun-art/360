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
	void closeEvent(QCloseEvent * event);
	bool eventFilter(QObject * obj, QEvent * event);
	void initUI();
	void initStatistics();
	void firstStartInit();
	void splitpixmap(QPixmap & pixmap, int xnum, int ynum);
	int showMsgBox(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);
private:
	Ui::Device360Class ui;
	bool m_bCloseSignal = false;
	bool m_bAltKeyPressed = false;
	QString AppPath;
	ProgramSet *m_ProgramDlg = nullptr;
	ResultData *m_ResultDlg = nullptr;
	DailyLog *m_DailyLogDlg = nullptr;
	int m_iShutDownPC;//0:退出程序不关机 1退出程序且立即关机 2进入主界面随后关机 3进入主界面随后不关机
	WindowOut* levelOut = nullptr;

	bool m_bFirstStartFlag = true;//第一次按启动
	QList<QPixmap> m_pixlist;//图片切割
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
