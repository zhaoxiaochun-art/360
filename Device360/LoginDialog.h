#pragma once

#include <QDialog>
#include "ui_LoginDialog.h"
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QButtonGroup>

class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();
	void setMaskFun(bool);
	bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist);
	bool deleteDir(const QString& path);//eg£ºdeleteDir(AppPath + "/DefaultModel");
private:
	Ui::LoginDialog ui;
	bool m_bSec = false;
	QString AppPath;
	QString m_autoStartPath; 
	QString key_turnOff;
public slots:
	void on_pB_Exit_clicked();
	void on_pB_Login_clicked();
	void on_cB_style_activated(const QString & arg1);
	void on_cB_turnOn_toggled(bool checked);
	void on_cB_turnOff_toggled(bool checked);
	void on_lE_Password_textChanged(const QString & arg1);
};
