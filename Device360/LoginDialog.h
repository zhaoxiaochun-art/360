#pragma once

#include <QDialog>
#include "ui_LoginDialog.h"

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();

private:
	Ui::LoginDialog ui;

public slots:

	void on_pB_Exit_clicked();
	void on_pB_Login_clicked();
	void on_pB_more_clicked();
	void on_cB_style_activated(const QString & arg1);
};
