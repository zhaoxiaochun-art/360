#include "LoginDialog.h"
#include <QSettings>
#include <QApplication>

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->setWindowOpacity(0.95);//透明度
	this->setWindowModality(Qt::ApplicationModal);

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");
	setMaskFun(false);

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

void LoginDialog::on_pB_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统，如果退出时关机选项选中，那么也会同时关机"));
	close();
}
void LoginDialog::on_pB_Login_clicked()
{
	if (ui.lE_Password->text()=="1111")
	{
		close();
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("密码为1111"));

	}
}
void LoginDialog::on_cB_style_activated(const QString &arg1)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	if (arg1 == QString::fromLocal8Bit("默认风格"))
	{
		configIniRead.setValue("ProgramSetting/Style", "Default Style");//写当前模板
	}
	else if (arg1 == "Iron Man")
	{
		configIniRead.setValue("ProgramSetting/Style", "Iron Man");//写当前模板
	}
	else if (arg1 == QString::fromLocal8Bit("大话西游"))
	{
		configIniRead.setValue("ProgramSetting/Style", "zxc");//写当前模板
	}
	else if (arg1 == QString::fromLocal8Bit("千岛湖"))
	{
		configIniRead.setValue("ProgramSetting/Style", "qdh");//写当前模板
	}
}