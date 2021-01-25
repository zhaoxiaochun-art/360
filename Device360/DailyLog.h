#pragma once

#include <QDialog>
#include "ui_DailyLog.h"
#include <QMessageBox>

class DailyLog : public QDialog
{
	Q_OBJECT
public:
	DailyLog(QWidget *parent = Q_NULLPTR);
	~DailyLog();
private:
	Ui::DailyLog ui;
public slots:
	void on_pB_Refresh_clicked();
	void on_pB_closeLog_clicked();
	void on_cB_LogMode_activated(int index);
};
