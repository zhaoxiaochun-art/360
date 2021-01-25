#include "Device360.h"
Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	if (!dlg->verifySec())
	{
		exit(-1);
	}
	m_ProgramDlg = new ProgramSet();
	m_ResultDlg = new ResultData(); 
	m_DailyLogDlg = new DailyLog();
}
#pragma region msgbox
void Device360::on_Button_Clean_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Checkable �豸����ϵ�����ͣ��ʱ,�豸�Ͽ��ܻ��в���Ľ��ҡ�\n�ð�ť��ͣ��״̬�°���ʱ�Ὣ���Ҷ������Ʒ�С�ͬʱ���ֻ������ת��������в��á��ٴΰ��º�ֹͣ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ��๦�ܡ�"));
	}
}
void Device360::on_Button_Start_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Checkable ������⣬�ٴΰ���ֹͣ���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ���"));
	}
}
void Device360::on_Button_AlarmReset_clicked()
{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ϵͳ��������󣬵���ð�ť���й��ϸ�λ������豸����ԭ�㣬����ҪѰ��"));

}
void Device360::on_Button_CameraSet_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�򿪲������ý���"));
	m_ProgramDlg->show();
}
void Device360::on_Button_Log_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����־��ѯ����"));
	m_DailyLogDlg->show();
}

void Device360::on_Button_DataOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����ݵ�������"));
	m_ResultDlg->show();
}
void Device360::on_Button_CountReset_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ͳ��tabҳ����е��������� PLC����tabҳ����ֵ����"));

}
void Device360::on_Button_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳�ϵͳ"));
	close();
}

void Device360::on_lE_PN_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ı���������"));
}
void Device360::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ı�ϵͳ�ٶȣ�10-120rpm"));
}
#pragma endregion