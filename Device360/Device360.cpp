#include "Device360.h"

Device360::Device360(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	QRegExp regx("[a-zA-Z0-9_]+$");//������ʽQRegExp,ֻ�����������ġ����֡���ĸ���»����Լ��ո�,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_PN->setValidator(new QRegExpValidator(regx, this));

	ui.cB_RunSpeed->setVisible(false);	
	ui.cB_RunSpeed->move(372, 7);
	connect(ui.lE_RunSpeed, SIGNAL(POPUPKEYBOARD()), this, SLOT(changeRunSpeed()));
	connect(ui.cB_RunSpeed, QOverload<const QString&>::of(&QComboBox::activated),
		[=](const QString& text) {
		QString str_Before = ui.lE_RunSpeed->text();
		if (text != QString::fromLocal8Bit("ȡ��"))
		{
			if (text == str_Before)
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ٶ�δ�仯��ʾ��"));
			}
			else if (QMessageBox::Yes == QMessageBox::question(nullptr,QString::fromLocal8Bit("ȷ�Ͽ�"),QString::fromLocal8Bit("�ı��ٶ���"),QMessageBox::Yes|QMessageBox::No))
			{
				ui.lE_RunSpeed->setText(text);
				QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����PLC��ϵͳ�����ٶȲ���ʾ"));
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�豸����ϵ�����ͣ��ʱ,�豸�Ͽ��ܻ��в���Ľ��ҡ�\n�ð�ť��ͣ��״̬�°���ʱ�Ὣ���Ҷ������Ʒ�С�ͬʱ���ֻ������ת��������в��á��ٴΰ��º�ֹͣ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ��๦�ܡ�"));
	}
}
void Device360::on_Button_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳�ϵͳ"));
	close();
}
void Device360::on_Button_CountReset_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳�ϵͳ"));
}
void Device360::changeRunSpeed()
{
	ui.lE_RunSpeed->clearFocus();
	ui.cB_RunSpeed->showPopup();
}

void Device360::on_lE_PN_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ı���������"));
}
#pragma endregion