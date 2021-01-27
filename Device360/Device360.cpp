#include "Device360.h"
#include <QProcess>
#include <QSettings>

Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	m_iShutDownPC = dlg->LoginDlgCloseMode(); //2��3���˳�ʱ����
	if (m_iShutDownPC==0)
	{
		exit(-1);
	}
	else if (m_iShutDownPC == 1)
	{
		QProcess pro;    //ͨ��QProcess����ִ�е���������
		QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 ��window�µĹػ����
		pro.start(cmd);    //ִ������cmd
		pro.waitForStarted();
		pro.waitForFinished();
		exit(-1);
	}

	AppPath = qApp->applicationDirPath();//exe����Ŀ¼
	AppPath.replace("/", "\\");
	QSettings readPara(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text = readPara.value("UISetting/Style", "").toString();
	QString style1 ="background-image:url(./ico/"+text+".png);";
	ui.lb_style->raise();
	ui.lb_style->setStyleSheet(style1);
	ui.lb_style->setAttribute(Qt::WA_TransparentForMouseEvents);

	m_ProgramDlg = new ProgramSet();
	//m_ResultDlg = new ResultData(); 
	//m_DailyLogDlg = new DailyLog();
}
int Device360::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//ȫ������
{
	if (QString::fromLocal8Bit(button2Str) == "")
	{
		QMessageBox msg(QMessageBox::Information, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Ok);
		msg.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit(button1Str));
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
		return msg.exec();
	}
	else
	{
		QMessageBox msg(QMessageBox::Question, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Yes | QMessageBox::No);
		msg.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit(button1Str));
		msg.setButtonText(QMessageBox::No, QString::fromLocal8Bit(button2Str));
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
		return msg.exec();
	}
	//  QMessageBox::NoIcon
	//	QMessageBox::Question
	//	QMessageBox::Information
	//	QMessageBox::Warning
	//	QMessageBox::Critical
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
	if (m_iShutDownPC == 2)
	{
		if (QMessageBox::Yes == showMsgBox("�ػ���ʾ", "�Ƿ�ȷ�Ϲػ���", "ȷ��", "ȡ��"))
		{
			QProcess pro;    //ͨ��QProcess����ִ�е���������
			QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 ��window�µĹػ����
			pro.start(cmd);    //ִ������cmd
			pro.waitForStarted();
			pro.waitForFinished();
			exit(-1);
		}
		else
		{
			close();
		}

	}
	else
	{ 
		close();
	}
	
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