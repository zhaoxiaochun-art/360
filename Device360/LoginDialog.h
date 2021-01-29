#pragma once

#include <QDialog>
#include "ui_LoginDialog.h"
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QTimer>

class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();
	void initMovie();
	void setMaskFun(bool);
	void initUI();
	int LoginDlgCloseMode();
	bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist);
	bool deleteDir(const QString& path);//eg：deleteDir(AppPath + "/DefaultModel");
	int showMsgBox(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);
private:
	Ui::LoginDialog ui;
	QPropertyAnimation *animation1 = nullptr;
	QPropertyAnimation *animation2 = nullptr;
	QTimer *aniTimer = nullptr;
	QTimer * cowTimer = nullptr;
	QLabel *lb_pic = nullptr;
	QLabel *lb_pic2 = nullptr;
	bool m_bSec = false;
	QString AppPath;
	QString m_autoStartPath; 
	QString key_turnOff;
	int m_iCloseMode;//0:退出程序不关机 1退出程序且立即关机 2进入主界面随后关机 3进入主界面随后不关机
public slots:
	void on_pB_Exit_clicked();
	void on_pB_Login_clicked();
	void on_cB_style_activated(const QString & arg1);
	void on_cB_turnOn_toggled(bool checked);
	void on_cB_turnOff_toggled(bool checked);
	void on_lE_Password_textChanged(const QString & arg1);
	void closeThis();
	void showCow();
};
