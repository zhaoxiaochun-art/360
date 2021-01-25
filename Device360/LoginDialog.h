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
	bool verifySec();
private:
	Ui::LoginDialog ui;
	bool m_bSec = false;
public slots:
	void on_pB_Exit_clicked();
	void on_pB_Login_clicked();
	void on_pB_more_clicked();
	void on_cB_style_activated(const QString & arg1);
};
