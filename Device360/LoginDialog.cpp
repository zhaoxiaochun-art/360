#include "LoginDialog.h"
#include <QSettings>
#include <QApplication>
#include <QDir>

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QString currentPCUserName = QDir::home().dirName();
	m_autoStartPath = "C:/Users/" + currentPCUserName + "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup";

	setWindowIcon(QIcon("./dr128.ico"));//文件copy到了exe所在目录
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setWindowOpacity(0.95);//透明度
	setWindowModality(Qt::ApplicationModal);

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");
	setMaskFun(false);

	ui.label->setPixmap(QPixmap("./ico/user.ico"));
	ui.label->setScaledContents(true);
	ui.label_2->setPixmap(QPixmap("./ico/sec.ico"));
	ui.label_2->setScaledContents(true);
	ui.pB_Exit->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
	ui.pB_Login->setStyleSheet("font-size:20pt");
	ui.pB_Login->setEnabled(false);

	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text = configIniRead.value("UISetting/Style", "").toString();
	if (text == "Default Style")
	{
		ui.cB_style->setCurrentIndex(0);
	}
	else if (text == "Iron Man")
	{
		ui.cB_style->setCurrentIndex(1);
	}
	else if (text == "zxc")
	{
		ui.cB_style->setCurrentIndex(2);
	}
	else if (text == "qdh")
	{
		ui.cB_style->setCurrentIndex(3);
	}

	QString key_turnOn = configIniRead.value("UISetting/AutoRun", "").toString();
	if (key_turnOn == "1")
	{
		ui.cB_turnOn->setChecked(true);
	}
	else
	{
		ui.cB_turnOn->setChecked(false);
	}

	key_turnOff = configIniRead.value("UISetting/AutoClose", "").toString();
	if (key_turnOff == "1")
	{
		ui.cB_turnOff->setChecked(true);
	}
	else
	{
		ui.cB_turnOff->setChecked(false);
	}
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
		configIniRead.setValue("UISetting/Style", "Default Style");//写当前模板
	}
	else if (arg1 == "Iron Man")
	{
		configIniRead.setValue("UISetting/Style", "Iron Man");//写当前模板
	}
	else if (arg1 == QString::fromLocal8Bit("大话西游"))
	{
		configIniRead.setValue("UISetting/Style", "zxc");//写当前模板
	}
	else if (arg1 == QString::fromLocal8Bit("千岛湖"))
	{
		configIniRead.setValue("UISetting/Style", "qdh");//写当前模板
	}
}