#pragma once

#include <QDialog>
#include "ui_ResultData.h"
#include <QMessageBox>

class ResultData : public QDialog
{
	Q_OBJECT
public:
	ResultData(QWidget *parent = Q_NULLPTR);
	~ResultData();
private:
	Ui::ResultData ui;
public slots:
	void on_cB_data_toggled(bool checked);
	void on_cB_model_toggled(bool checked);
	void on_cB_sysLog_toggled(bool checked);
	void on_cB_alarmLog_toggled(bool checked);
	void on_cB_operationLog_toggled(bool checked);
	void on_lE_productionNum_returnPressed();
	void on_cB_LeadOut_activated(int index);
	void on_dateEdit_userDateChanged(const QDate & date);
	void on_dateEdit_2_userDateChanged(const QDate & date);
	void on_pB_Choose_clicked();
	void on_pB_LeadOut_clicked();
	void on_pB_LeadOutClose_clicked();
};
