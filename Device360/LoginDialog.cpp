#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.cB_style->setVisible(false);
	ui.cB_turnOn->setVisible(false);
	ui.cB_turnOff->setVisible(false);

	setMaskFun(false);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->setWindowOpacity(0.95);//透明度
	this->setWindowModality(Qt::ApplicationModal);
	ui.label->setPixmap(QPixmap("./ico/user.ico"));
	ui.label->setScaledContents(true);
	ui.label_2->setPixmap(QPixmap("./ico/sec.ico"));
	ui.label_2->setScaledContents(true);
	ui.pB_Exit->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
	ui.pB_Login->setStyleSheet("font-size:20pt");

	connect(ui.numButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {ui.lE_Password->setText(ui.lE_Password->text() += button->text()); });
}
LoginDialog::~LoginDialog()
{
}

void LoginDialog::setMaskFun(bool b)
{
	if (b)
	{
		ui.pB_more->setText(QString::fromLocal8Bit("︽"));
		this->resize(QSize(400, 780));
	}
	else
	{
		ui.pB_more->setText(QString::fromLocal8Bit("︾"));
		this->resize(QSize(400, 710));
	}
	//设置窗口圆角
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 5, 5);
	setMask(bmp);
	//👆👆👆

}
bool LoginDialog::verifySec()
{
	return m_bSec;
}
void LoginDialog::on_pB_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统，如果退出时关机选项选中，那么也会同时关机"));
	m_bSec = false;
	close();
}
void LoginDialog::on_pB_Login_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("如果密码与用户匹配登录系统，不匹配则提示错误重新输入。"));
	m_bSec = true;
	close();
}
void LoginDialog::on_pB_more_clicked()
{
	if (ui.pB_more->text() == QString::fromLocal8Bit("︾"))
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开隐藏项"));
		setMaskFun(true);
		ui.cB_style->setVisible(true);
		ui.cB_turnOn->setVisible(true);
		ui.cB_turnOff->setVisible(true);
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("关闭隐藏项"));
		setMaskFun(false);
		//👆👆👆
		ui.cB_style->setVisible(false);
		ui.cB_turnOn->setVisible(false);
		ui.cB_turnOff->setVisible(false);
	}
}
void LoginDialog::on_cB_style_activated(const QString &arg1)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变进入系统后的界面风格"));
}