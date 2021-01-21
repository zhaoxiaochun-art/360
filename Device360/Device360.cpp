#include "Device360.h"

Device360::Device360(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
	setWindowFlags(Qt::FramelessWindowHint);//无边框 

	QRegExp regx("[a-zA-Z0-9_]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_PN->setValidator(new QRegExpValidator(regx, this));

	ui.cB_RunSpeed->setVisible(false);	
	ui.cB_RunSpeed->move(372, 7);
	connect(ui.lE_RunSpeed, SIGNAL(POPUPKEYBOARD()), this, SLOT(changeRunSpeed()));
	connect(ui.cB_RunSpeed, QOverload<const QString&>::of(&QComboBox::activated),
		[=](const QString& text) {
		QString str_Before = ui.lE_RunSpeed->text();
		if (text != QString::fromLocal8Bit("取消"))
		{
			if (text == str_Before)
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("速度未变化提示。"));
			}
			else if (QMessageBox::Yes == QMessageBox::question(nullptr,QString::fromLocal8Bit("确认框"),QString::fromLocal8Bit("改变速度吗？"),QMessageBox::Yes|QMessageBox::No))
			{
				ui.lE_RunSpeed->setText(text);
				QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置PLC的系统运行速度并显示"));
			}
		}
		else
		{
			ui.lE_RunSpeed->setText(str_Before);
		}
	});
}

#pragma region msgbox
void Device360::on_Button_Clean_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设备因故障导致在停机时,设备上可能还有残余的胶囊。\n该按钮在停机状态下按下时会将胶囊都排入废品盒。同时滚轮会持续旋转，方便进行擦拭。再次按下后停止。"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止清洁功能。"));
	}
}
void Device360::on_Button_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统"));
	close();
}
void Device360::on_Button_CountReset_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统"));
}
void Device360::changeRunSpeed()
{
	ui.lE_RunSpeed->clearFocus();
	ui.cB_RunSpeed->showPopup();
}

void Device360::on_lE_PN_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变生产批号"));
}
#pragma endregion