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
void LoginDialog::initUI()
{
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
		if (key_turnOff == "1")
		{ 
			if (QMessageBox::Yes== showMsgBox("关机提示", "是否确认关机？", "确认", "取消"))
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
	else
	{
		ui.lE_Password->clear();
	}
}
void LoginDialog::on_pB_Login_clicked()
{
	if (ui.lE_Password->text()=="1111")
	{
		if (key_turnOff == "1")
		{
			m_iCloseMode = 2;
		}
		else
		{
			m_iCloseMode = 3;
		}
		close();
	}
	else
	{
		showMsgBox("提示", "默认密码为：1111","我知道了", "");
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
void LoginDialog::on_cB_turnOn_toggled(bool checked)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	if (checked)
	{
		configIniRead.setValue("UISetting/AutoRun", 1);//写当前模板
		copyDirectoryFiles(AppPath + "/startup", m_autoStartPath, true);
	}
	else
	{
		configIniRead.setValue("UISetting/AutoRun", 0);//写当前模板
		deleteDir(m_autoStartPath);
	}
}
void LoginDialog::on_cB_turnOff_toggled(bool checked)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	if (checked)
	{
		key_turnOff = "1";
		configIniRead.setValue("UISetting/AutoClose", 1);//写当前模板
	}
	else
	{
		key_turnOff = "0";
		configIniRead.setValue("UISetting/AutoClose", 0);//写当前模板
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