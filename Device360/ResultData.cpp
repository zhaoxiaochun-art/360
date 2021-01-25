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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڹ�ѡ������⵽��������Ϣ����������ʾ�����ݣ���������š��û������ڵ��������е�����������ʽΪexcel�ɶ���ʽ��֮ǰΪcsv�ļ�"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȡ����ѡ������⵽��������Ϣ"));
	}
}

void ResultData::on_cB_model_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڹ�ѡ����ģ���ļ���������š��û������ڵ��������е���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȡ����ѡ����ģ���ļ�"));
	}
}

void ResultData::on_cB_sysLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڹ�ѡϵͳ��־��������š��û������ڵ��������е���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȡ����ѡϵͳ��־"));
	}
}
void ResultData::on_cB_alarmLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڹ�ѡ������־��������š��û������ڵ��������е���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȡ����ѡ������־"));
	}
}
void ResultData::on_cB_operationLog_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڹ�ѡ������־��������š��û������ڵ��������е���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȡ����ѡ������־"));
	}
}

void ResultData::on_lE_productionNum_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������������ɸѡ�����ţ��������Ϊ�գ���ôĬ���������ű�ѡ��"));
}


void ResultData::on_cB_LeadOut_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ɸѡ�û�����Ĭ��Ϊ���о���ѡ��"));
}

void ResultData::on_dateEdit_userDateChanged(const QDate &date)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ɸѡ��ʼ����"));
}
void ResultData::on_dateEdit_2_userDateChanged(const QDate &date)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ɸѡ��������"));
}
void ResultData::on_pB_Choose_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ѡ�񵼳���Ŀ¼·�������������lineedit����ʾ"));
}
void ResultData::on_pB_LeadOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ɸѡ�����ļ�������Ŀ¼·��"));
}
void ResultData::on_pB_LeadOutClose_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�رմ˽���"));
	close();
}
