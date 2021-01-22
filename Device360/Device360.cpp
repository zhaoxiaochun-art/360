#include "Device360.h"
#include "LoginDialog.h"
Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//无边框 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	m_ProgramDlg = new ProgramSet();
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

}

void Device360::on_Button_DataOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开数据导出日志"));

}
void Device360::on_Button_CountReset_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("将运行统计tab页表格中的数据清零 PLC数据tab页的数值清零"));

}
void Device360::on_Button_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统"));
	close();
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