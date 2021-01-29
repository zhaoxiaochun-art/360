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
	initUI();

	connect(ui.numButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {ui.lE_Password->setText(ui.lE_Password->text() += button->text()); });
	initMovie();
	animation1->start();
	cowTimer->start(1000);
}
LoginDialog::~LoginDialog()
{
}
void LoginDialog::initMovie()
{//创建动态对象
	{
		animation1 = new QPropertyAnimation(this, "geometry");
		//设置动画时间间隔
		animation1->setDuration(1000);

		//起始位置
		animation1->setStartValue(QRect((768 - 423) / 2, (1366 - 760) / 2 + 500, width(), height()));
		//结束位置
		animation1->setEndValue(QRect((768 - 423) / 2, (1366 - 760) / 2, width(), height()));

		//设置弹跳曲线
		animation1->setEasingCurve(QEasingCurve::OutElastic);
	}
	{
		animation2 = new QPropertyAnimation(this, "geometry");
		//设置动画时间间隔
		animation2->setDuration(500);

		//起始位置
		animation2->setStartValue(QRect((768 - 423) / 2, (1366 - 760) / 2, width(), height()));
		//结束位置
		animation2->setEndValue(QRect((768 - 423) / 2, (1366 - 760) / 2 + 500, width(), height()));

		//设置弹跳曲线
		animation2->setEasingCurve(QEasingCurve::OutElastic);
	}
	aniTimer = new QTimer();
	connect(aniTimer, SIGNAL(timeout()), this, SLOT(closeThis()));
	cowTimer = new QTimer();
	connect(cowTimer, SIGNAL(timeout()), this, SLOT(showCow()));
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
void LoginDialog::initUI()
{
	ui.label->setPixmap(QPixmap("./ico/user.ico"));
	ui.label->setScaledContents(true);
	ui.label_2->setPixmap(QPixmap("./ico/sec.ico"));
	ui.label_2->setScaledContents(true);
	ui.pB_Exit->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
	ui.pB_Login->setStyleSheet("font-size:20pt");
	ui.pB_Login->setEnabled(false);

	QSettings configIniRead(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
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

	ui.cB_turnOn->setFixedSize(163, 29);
	ui.cB_turnOn->setStyleSheet("QPushButton{border:0px;}");
	ui.cB_turnOn->setIconSize(QSize(163, 29));
	QString key_turnOn = configIniRead.value("UISetting/AutoRun", "").toString();
	if (key_turnOn == "1")
	{
		ui.cB_turnOn->setChecked(true);
		ui.cB_turnOn->setIcon(QPixmap(AppPath + "/ico/startup1.png"));
	}
	else
	{
		ui.cB_turnOn->setChecked(false);
		ui.cB_turnOn->setIcon(QPixmap(AppPath + "/ico/startup2.png"));
	}

	ui.cB_turnOff->setFixedSize(163, 29);
	ui.cB_turnOff->setStyleSheet("QPushButton{border:0px;}");
	ui.cB_turnOff->setIconSize(QSize(163, 29));
	key_turnOff = configIniRead.value("UISetting/AutoClose", "").toString();
	if (key_turnOff == "1")
	{
		ui.cB_turnOff->setChecked(true);
		ui.cB_turnOff->setIcon(QPixmap(AppPath + "/ico/shutdown1.png"));
	}
	else
	{
		ui.cB_turnOff->setChecked(false);
		ui.cB_turnOff->setIcon(QPixmap(AppPath + "/ico/shutdown2.png"));
	}

	lb_pic15 = new QLabel(this);
	lb_pic15->resize(this->size());
	lb_pic15->move(0, 0);
	lb_pic15->setPixmap(QPixmap(AppPath + "/ico/newyear15.png"));
	lb_pic15->setScaledContents(true);
	lb_pic15->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic15->setVisible(false);

	lb_pic20 = new QLabel(this);
	lb_pic20->resize(this->size());
	lb_pic20->move(0, 0);
	lb_pic20->setPixmap(QPixmap(AppPath + "/ico/newyear20.png"));
	lb_pic20->setScaledContents(true);
	lb_pic20->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic20->setVisible(false);

	lb_pic30 = new QLabel(this);
	lb_pic30->resize(this->size());
	lb_pic30->move(0, 0);
	lb_pic30->setPixmap(QPixmap(AppPath + "/ico/newyear30.png"));
	lb_pic30->setScaledContents(true);
	lb_pic30->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic30->setVisible(false);

	lb_pic40 = new QLabel(this);
	lb_pic40->resize(this->size());
	lb_pic40->move(0, 0);
	lb_pic40->setPixmap(QPixmap(AppPath + "/ico/newyear40.png"));
	lb_pic40->setScaledContents(true);
	lb_pic40->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic40->setVisible(false);

	lb_pic50 = new QLabel(this);
	lb_pic50->resize(this->size());
	lb_pic50->move(0, 0);
	lb_pic50->setPixmap(QPixmap(AppPath + "/ico/newyear50.png"));
	lb_pic50->setScaledContents(true);
	lb_pic50->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic50->setVisible(false);

	lb_pic60 = new QLabel(this);
	lb_pic60->resize(this->size());
	lb_pic60->move(0, 0);
	lb_pic60->setPixmap(QPixmap(AppPath + "/ico/newyear60.png"));
	lb_pic60->setScaledContents(true);
	lb_pic60->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic60->setVisible(false);

	lb_pic70 = new QLabel(this);
	lb_pic70->resize(this->size());
	lb_pic70->move(0, 0);
	lb_pic70->setPixmap(QPixmap(AppPath + "/ico/newyear70.png"));
	lb_pic70->setScaledContents(true);
	lb_pic70->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic70->setVisible(false);

	lb_pic80 = new QLabel(this);
	lb_pic80->resize(this->size());
	lb_pic80->move(0, 0);
	lb_pic80->setPixmap(QPixmap(AppPath + "/ico/newyear80.png"));
	lb_pic80->setScaledContents(true);
	lb_pic80->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic80->setVisible(false);

	lb_pic90 = new QLabel(this);
	lb_pic90->resize(this->size());
	lb_pic90->move(0, 0);
	lb_pic90->setPixmap(QPixmap(AppPath + "/ico/newyear90.png"));
	lb_pic90->setScaledContents(true);
	lb_pic90->setAttribute(Qt::WA_TransparentForMouseEvents);
	lb_pic90->setVisible(false);

	lb_pic100 = new QLabel(this);
	lb_pic100->resize(this->size());
	lb_pic100->move(0, 0);
	lb_pic100->setPixmap(QPixmap(AppPath + "/ico/newyear100.png"));
	lb_pic100->setScaledContents(true);
	lb_pic100->setAttribute(Qt::WA_TransparentForMouseEvents);

}
int LoginDialog::LoginDlgCloseMode()
{
	return m_iCloseMode;
}
bool LoginDialog::copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	if (!targetDir.exists()) {    /**< 如果目标目录不存在,则进行创建 */
		if (!targetDir.mkpath(targetDir.absolutePath()))
		{
			return false;
		}
	}
	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;
		if (fileInfo.isDir()) {    /**< 当为目录时,递归的进行copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else {            /**< 当允许覆盖操作时,将旧文件进行删除操作 */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}
			/// 进行文件copy
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))) {
				return false;
			}
		}
	}
	return true;
}
bool LoginDialog::deleteDir(const QString& path)//eg：deleteDir(AppPath + "/DefaultModel");//删除文件夹/目录功能
{
	if (path.isEmpty()) {
		return false;
	}
	QDir dir(path);
	if (!dir.exists()) {
		return true;
	}
	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
	QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
	foreach(QFileInfo file, fileList) { //遍历文件信息
		if (file.isFile()) { // 是文件，删除
			file.dir().remove(file.fileName());
		}
		else { // 递归删除
			deleteDir(file.absoluteFilePath());
		}
	}
	return dir.rmpath(dir.absolutePath()); // 删除文件夹
}
int LoginDialog::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
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

void LoginDialog::on_pB_Exit_clicked()
{
	if (ui.pB_Exit->text() == QString::fromLocal8Bit("退出"))
	{
		if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出系统？", "确认", "取消"))
		{
			if (key_turnOff == "1")
			{
				if (QMessageBox::Yes == showMsgBox("关机提示", "是否确认关机？", "确认", "取消"))
				{
					m_iCloseMode = 1;
				}
				else
				{
					m_iCloseMode = 0;
				}
			}
			else
			{
				m_iCloseMode = 0;
			}
			close();
		}
	}
	else
	{
		ui.lE_Password->clear();
	}
}
void LoginDialog::on_pB_Login_clicked()
{
	if (ui.lE_Password->text() == "1111")
	{
		if (key_turnOff == "1")
		{
			m_iCloseMode = 2;
		}
		else
		{
			m_iCloseMode = 3;
		}
		animation2->start();
		aniTimer->start(50);
	}
	else
	{
		showMsgBox("提示", "默认密码为：1111", "我知道了", "");
	}
}
void LoginDialog::on_cB_style_activated(const QString &arg1)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
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
void LoginDialog::on_cB_turnOn_toggled(bool checked)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
	if (checked)
	{
		configIniRead.setValue("UISetting/AutoRun", 1);//写当前模板
		copyDirectoryFiles(AppPath + "/startup", m_autoStartPath, true);
		ui.cB_turnOn->setIcon(QPixmap(AppPath + "/ico/startup1.png"));
	}
	else
	{
		configIniRead.setValue("UISetting/AutoRun", 0);//写当前模板
		deleteDir(m_autoStartPath);
		ui.cB_turnOn->setIcon(QPixmap(AppPath + "/ico/startup2.png"));
	}
}
void LoginDialog::on_cB_turnOff_toggled(bool checked)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
	if (checked)
	{
		key_turnOff = "1";
		configIniRead.setValue("UISetting/AutoClose", 1);//写当前模板
		ui.cB_turnOff->setIcon(QPixmap(AppPath + "/ico/shutdown1.png"));
	}
	else
	{
		key_turnOff = "0";
		configIniRead.setValue("UISetting/AutoClose", 0);//写当前模板
		ui.cB_turnOff->setIcon(QPixmap(AppPath + "/ico/shutdown2.png"));
	}
}

void LoginDialog::on_lE_Password_textChanged(const QString &arg1)
{
	int i = arg1.length();
	if (i > 0)
	{
		ui.pB_Exit->setText(QString::fromLocal8Bit("清空"));
	}
	if (i == 0)
	{
		ui.pB_Exit->setText(QString::fromLocal8Bit("退出"));
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:20pt");
	}
	else if (i == 1)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:23pt");
	}
	else if (i == 2)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:26pt");
	}
	else if (i == 3)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:29pt");
	}
	else
	{
		ui.pB_Login->setEnabled(true);
		ui.pB_Login->setStyleSheet("background-color: rgba(0, 170, 0, 125);font-size:29pt");
	}
}
void LoginDialog::closeThis()
{
	close();
}

void LoginDialog::showCow()
{
	cowTimer->stop();
	int i = 100;
	if (m_iValue == 0)
	{
		lb_pic100->setVisible(false);
		lb_pic90->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 1)
	{
		lb_pic90->setVisible(false);
		lb_pic80->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 2)
	{
		lb_pic80->setVisible(false);
		lb_pic70->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 3)
	{
		lb_pic70->setVisible(false);
		lb_pic60->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 4)
	{
		lb_pic60->setVisible(false);
		lb_pic50->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 5)
	{
		lb_pic50->setVisible(false);
		lb_pic40->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 6)
	{
		lb_pic40->setVisible(false);
		lb_pic30->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 7)
	{
		lb_pic30->setVisible(false);
		lb_pic20->setVisible(true);
		cowTimer->start(i);
	}
	else if (m_iValue == 8)
	{
		lb_pic20->setVisible(false);
		lb_pic15->setVisible(true);
	}
	m_iValue++;
}