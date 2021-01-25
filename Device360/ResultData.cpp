#include "ResultData.h"

ResultData::ResultData(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this); 
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}
ResultData::~ResultData()
{
}

void ResultData::on_cB_data_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于勾选以往检测到的数据信息（即上面显示的数据），配合批号、用户、日期等条件进行导出，导出格式为excel可读格式，之前为csv文件"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于取消勾选以往检测到的数据信息"));
	}
}
void ResultData::on_cB_model_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于勾选所有模板文件，配合批号、用户、日期等条件进行导出"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于取消勾选所有模板文件"));
	}
}
void ResultData::on_cB_sysLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于勾选系统日志，配合批号、用户、日期等条件进行导出"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于取消勾选系统日志"));
	}
}
void ResultData::on_cB_alarmLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于勾选报警日志，配合批号、用户、日期等条件进行导出"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于取消勾选报警日志"));
	}
}
void ResultData::on_cB_operationLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于勾选操作日志，配合批号、用户、日期等条件进行导出"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于取消勾选操作日志"));
	}
}
void ResultData::on_lE_productionNum_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("用于输入所需筛选的批号，如果输入为空，那么默认所有批号被选中"));
}
void ResultData::on_cB_LeadOut_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("筛选用户名，默认为所有均被选中"));
}
void ResultData::on_dateEdit_userDateChanged(const QDate &date)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("筛选开始日期"));
}
void ResultData::on_dateEdit_2_userDateChanged(const QDate &date)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("筛选结束日期"));
}
void ResultData::on_pB_Choose_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("选择导出的目录路径，并且在左侧lineedit中显示"));
}
void ResultData::on_pB_LeadOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("将筛选到的文件导出到目录路径"));
}
void ResultData::on_pB_LeadOutClose_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("关闭此界面"));
	close();
}
