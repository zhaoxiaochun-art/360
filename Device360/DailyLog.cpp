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
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڸý���Ϊ��ģ̬��ʵʱˢ�£��˰�ť����ˢ����־��ʾ�����ݡ�"));
}
void DailyLog::on_pB_closeLog_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�رմ˽���"));
	close();
}
void DailyLog::on_cB_LogMode_activated(int index)
{

}