#include "Device360.h"
#include <QProcess>
#include <QSettings>

Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//无边框 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	m_iShutDownPC = dlg->LoginDlgCloseMode(); //2和3在退出时处理
	if (m_iShutDownPC==0)
	{
		exit(-1);
	}
	else if (m_iShutDownPC == 1)
	{
		QProcess pro;    //通过QProcess类来执行第三方程序
		QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 是window下的关机命令，
		pro.start(cmd);    //执行命令cmd
		pro.waitForStarted();
		pro.waitForFinished();
		exit(-1);
	}

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");
	QSettings readPara(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text = readPara.value("UISetting/Style", "").toString();
	QString style1 ="background-image:url(./ico/"+text+".png);";
	ui.lb_style->raise();
	ui.lb_style->setStyleSheet(style1);
	ui.lb_style->setAttribute(Qt::WA_TransparentForMouseEvents);

	ui.lb_Picture->setPixmap(QPixmap("./ico/dr-pharm.png"));
	ui.lb_Picture->setScaledContents(true);

	ui.tabWidget->removeTab(1);
	m_ProgramDlg = new ProgramSet();
	//m_ResultDlg = new ResultData(); 
	//m_DailyLogDlg = new DailyLog();
}
int Device360::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("Checkable 设备因故障导致在停机时,设备上可能还有残余的胶囊。\n该按钮在停机状态下按下时会将胶囊都排入废品盒。同时滚轮会持续旋转，方便进行擦拭。再次按下后停止。"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止清洁功能。"));
	}
}
void Device360::on_Button_Start_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("Checkable 启动检测，再次按下停止检测"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止检测"));
	}
}
void Device360::on_Button_AlarmReset_clicked()
{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("系统故障清除后，点击该按钮进行故障复位，如果设备不在原点，还需要寻参"));

}
void Device360::on_Button_CameraSet_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开参数设置界面"));
	m_ProgramDlg->show();
}
void Device360::on_Button_Log_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开日志查询界面"));
	m_DailyLogDlg->show();
}
void Device360::on_Button_DataOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开数据导出界面"));
	m_ResultDlg->show();
}
void Device360::on_Button_CountReset_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("将运行统计tab页表格中的数据清零 PLC数据tab页的数值清零"));

}
void Device360::on_Button_Exit_clicked()
{
	if (m_iShutDownPC == 2)
	{
		if (QMessageBox::Yes == showMsgBox("关机提示", "是否确认关机？", "确认", "取消"))
		{
			QProcess pro;    //通过QProcess类来执行第三方程序
			QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 是window下的关机命令，
			pro.start(cmd);    //执行命令cmd
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
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变生产批号"));
}
void Device360::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变系统速度：10-120rpm"));
}
#pragma endregion