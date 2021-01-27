#include "DailyLog.h"
#include <QSettings>
#include <QApplication>
DailyLog::DailyLog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}
DailyLog::~DailyLog()
{
}

void DailyLog::on_pB_Refresh_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("由于该界面为非模态非实时刷新，此按钮用于刷新日志显示的内容。"));
}
void DailyLog::on_pB_closeLog_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("关闭此界面"));
	close();
}
void DailyLog::on_cB_LogMode_activated(int index)
{

}