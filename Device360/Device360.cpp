#include "Device360.h"
#include <QProcess>
#include <QSettings>
#include <Windows.h>
#include <QThread>

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

	levelOut = new WindowOut();
	levelOut->setWindowCount(0);//动画窗弹出数，防止覆盖
	levelOut->getString(QString::fromLocal8Bit("恭喜，您已成功登陆系统！"), 2000);
	levelOut->show();

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");
	QSettings readPara(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text = readPara.value("UISetting/Style", "").toString();
	QString style1 ="background-image:url(./ico/"+text+".png);";
	ui.lb_style->raise();
	ui.lb_style->setStyleSheet(style1);
	ui.lb_style->setAttribute(Qt::WA_TransparentForMouseEvents);

	ui.lb_Picture->setPixmap(QPixmap(AppPath + "/ico/dr-pharmmatch.png"));
	ui.lb_Picture->setScaledContents(true);

	ui.pB_Keyboard->setFocusPolicy(Qt::NoFocus);
	ui.pB_Keyboard->setFlat(true);
	ui.pB_Keyboard->setIconSize(QSize(35, 35));
	ui.pB_Keyboard->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//文件copy到了exe所在目录
	ui.pB_Keyboard->setText("");

	ui.Button_Start->setText("");
	ui.Button_Start->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/start.png"));
	ui.Button_Start->setIconSize(QSize(280, 129));

	ui.Button_ParaSet->setText("");
	ui.Button_ParaSet->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraSet.png"));
	ui.Button_ParaSet->setIconSize(QSize(280, 129));

	ui.Button_CountReset->setText("");
	ui.Button_CountReset->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset.png"));
	ui.Button_CountReset->setIconSize(QSize(280, 129));


	ui.Button_Exit->setText("");
	ui.Button_Exit->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit.png"));
	ui.Button_Exit->setIconSize(QSize(280, 129));




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
		ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/stop.png"));
		ui.Button_ParaSet->setEnabled(false);
		ui.Button_CountReset->setEnabled(false);
		ui.Button_Exit->setEnabled(false);
		ui.lE_PN->setEnabled(false);
	}
	else
	{
		ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/start.png"));
		ui.Button_ParaSet->setEnabled(true);
		ui.Button_CountReset->setEnabled(true);
		ui.Button_Exit->setEnabled(true);
		ui.lE_PN->setEnabled(true);
	}
}
void Device360::on_Button_AlarmReset_clicked()
{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("系统故障清除后，点击该按钮进行故障复位，如果设备不在原点，还需要寻参"));

}

void Device360::on_Button_ParaSet_pressed()
{
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraset2.png"));
}
void Device360::on_Button_ParaSet_released()
{
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraset.png"));
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

void Device360::on_Button_CountReset_pressed()
{
	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset2.png"));
}

void Device360::on_Button_CountReset_released()
{

	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset.png"));
}

void Device360::on_pB_Keyboard_clicked()
{
	PVOID OldValue = nullptr;
	BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
	QString csProcess = "C:\\Windows\\System32\\osk.exe";
	QString params = "";
	ShellExecute(nullptr, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), nullptr, SW_SHOWNORMAL);
	if (bRet)
	{
		Wow64RevertWow64FsRedirection(OldValue);
	}
}

void Device360::on_Button_Exit_pressed()
{
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit2.png"));
}
void Device360::on_Button_Exit_released()
{
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit.png"));
	if (m_iShutDownPC == 2)
	{
		if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出系统？", "确认", "取消"))
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

	}
	else
	{
		if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出系统？", "确认", "取消"))
		{
			close();
		}
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