#pragma once

#include <QDialog>
#include "ui_LoginDialog.h"
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QTimer>
#include <QKeyEvent>

class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();
	bool eventFilter(QObject * obj, QEvent * event);
	void keyPressEvent(QKeyEvent *event)
	{
		switch (event->key())
		{
		case Qt::Key_Escape:
			break;
		default:
			QDialog::keyPressEvent(event);
		}
	}
	void initMovie();
	void setMaskFun(bool);
	void initUI();
	int LoginDlgCloseMode();
	bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist);
	bool deleteDir(const QString& path);//eg：deleteDir(AppPath + "/DefaultModel");
	int showMsgBox(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);
private:
	Ui::LoginDialog ui;
	bool m_bAltKeyPressed = false;
	QPropertyAnimation *animation1 = nullptr;
	QPropertyAnimation *animation2 = nullptr;
	QTimer * cowTimer = nullptr;
	QLabel *lb_pic15 = nullptr;
	QLabel *lb_pic20 = nullptr;
	QLabel *lb_pic30 = nullptr;
	QLabel *lb_pic40 = nullptr;
	QLabel *lb_pic50 = nullptr;
	QLabel *lb_pic60 = nullptr;
	QLabel *lb_pic70 = nullptr;
	QLabel *lb_pic80 = nullptr;
	QLabel *lb_pic90 = nullptr;
	QLabel *lb_pic100 = nullptr;
	int m_iValue = 0;
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
