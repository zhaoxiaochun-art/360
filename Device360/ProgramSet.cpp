#include "ProgramSet.h"
#include <Windows.h>
#include <QSettings>
#include <QDir>
ProgramSet::ProgramSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	installEventFilter(this);
	setWindowFlags(Qt::FramelessWindowHint);//无边框 
	setWindowModality(Qt::ApplicationModal);//设置窗体模态，要求该窗体没有父类，否则无效

	connect(ui.AlgButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {
		//if (button->objectName() == "pushButton_1")
		QString str = button->text();
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开")+str+QString::fromLocal8Bit("号相机算法设置界面"));
			}
	});
	connect(ui.KickButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {
		//if (button->objectName() == "pushButton_1")
		QString str = button->text();
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), str+QString::fromLocal8Bit("号剔废气缸动作"));
			}
	});

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");

	initUI();
	initMovie(); 
	initListWidgetofModel();
}
ProgramSet::~ProgramSet()
{
}
void ProgramSet::closeEvent(QCloseEvent *event)
{
	if (!m_bCloseSignal)
	{
		event->ignore();
		return;
	}
}
bool ProgramSet::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == this)
	{
		switch (event->type())
		{
		case QKeyEvent::KeyPress:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = true;
			break;
		}
		case QEvent::KeyRelease:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = false;
			break;
		}
		case QEvent::Close:
		{
			if (m_bAltKeyPressed)
			{//屏蔽ALT+F4
				event->ignore();
				return true;
				break;
			}
		}
		default:break;
		}
	}
	return QObject::eventFilter(obj, event);
}
void ProgramSet::initUI()
{
	ui.frame_Alg->setVisible(false);
	ui.frame_light->setVisible(false);

	ui.tabWidget->removeTab(3);
	ui.tabWidget->removeTab(3);

	ui.pB_Keyboard->setFocusPolicy(Qt::NoFocus);
	ui.pB_Keyboard->setText("");
	ui.pB_Keyboard->setStyleSheet("QPushButton{border:0px;}");
	ui.pB_Keyboard->setIcon(QPixmap(AppPath + "/ico/dr_keyboard.ico"));
	ui.pB_Keyboard->setIconSize(QSize(60, 40));

	ui.pB_Exit->setText("");
	ui.pB_Exit->setStyleSheet("QPushButton{border:0px;}");
	ui.pB_Exit->setIcon(QPixmap(AppPath + "/ico/exitgreen.png"));
	ui.pB_Exit->setIconSize(QSize(60, 54));

	QSettings readPara(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
	QString text = readPara.value("UISetting/Style", "").toString();
	QString style2 = "background-image:url(./ico/" + text + "2.png);";
	ui.lb_style2->raise();
	ui.lb_style2->setStyleSheet(style2);
	ui.lb_style2->setAttribute(Qt::WA_TransparentForMouseEvents);

	ui.lb_pic2->raise();
	ui.lb_pic2->setPixmap(QPixmap(AppPath + "/ico/dr-pharmmatch2.png"));
	ui.lb_pic2->setScaledContents(true);

	QRegExp regx("[0-9.]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_IP_2->setValidator(new QRegExpValidator(regx, this));
	QRegExp regx2("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_Port_2->setValidator(new QRegExpValidator(regx2, this));
}
void ProgramSet::initMovie()
{//创建动态对象
	{
		animation1 = new QPropertyAnimation(ui.pB_Exit, "geometry");
		//设置动画时间间隔
		animation1->setDuration(200);

		//起始位置
		animation1->setStartValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y(), ui.pB_Exit->width(), ui.pB_Exit->height()));
		//结束位置
		animation1->setEndValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y()+10, ui.pB_Exit->width(), ui.pB_Exit->height()));

		//设置弹跳曲线
		animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //创建动态对象
		animation2 = new QPropertyAnimation(ui.pB_Exit, "geometry");
		//设置动画时间间隔
		animation2->setDuration(200);

		//起始位置
		animation2->setStartValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y()+10, ui.pB_Exit->width(), ui.pB_Exit->height()));
		//结束位置
		animation2->setEndValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y(), ui.pB_Exit->width(), ui.pB_Exit->height()));

		//设置弹跳曲线
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
	{
		animation3 = new QPropertyAnimation(ui.pB_Keyboard, "geometry");
		//设置动画时间间隔
		animation3->setDuration(200);

		//起始位置
		animation3->setStartValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y(), ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));
		//结束位置
		animation3->setEndValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y() + 10, ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));

		//设置弹跳曲线
		animation3->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //创建动态对象
		animation4 = new QPropertyAnimation(ui.pB_Keyboard, "geometry");
		//设置动画时间间隔
		animation4->setDuration(200);

		//起始位置
		animation4->setStartValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y() + 10, ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));
		//结束位置
		animation4->setEndValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y(), ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));

		//设置弹跳曲线
		animation4->setEasingCurve(QEasingCurve::OutBounce);
	}
}
void ProgramSet::initListWidgetofModel()//模型listwidget初始化显示，遍历文件夹，找到模板名称并显示
{
	QSettings readDefaultModel(AppPath + "\\ModelFile\\GeneralSet.ini", QSettings::IniFormat);
	QString defaultModel = readDefaultModel.value("ModelSetting/DefaultModel", "testA").toString();
	ui.lb_DefaultName->setText(defaultModel);//更新lable 4-4
	QDir dir(AppPath + "\\ModelFile");
	if (!dir.exists())//不存在，退出
	{
		return;
	}
	dir.setFilter(QDir::Dirs);//筛选目录
	QFileInfoList list = dir.entryInfoList();//文件信息list
	int file_count = list.count();
	if (file_count <= 0)
	{
		return;
	}
	QStringList string_list;
	int i, j = 1;//j用于标记是否存在默认模板
	for (i = 0; i < file_count; i++)
	{
		QFileInfo file_info = list.at(i);
		QString folderName = file_info.fileName();
		string_list.append(folderName);
	}
	string_list.removeAt(0);//去掉.
	string_list.removeAt(0);//去掉..
	ui.listWidget->addItems(string_list);
	ui.listWidget->sortItems();
	QFont font("Arial", 24);
	ui.listWidget->setStyleSheet("QListWidget::Item:hover{background:grey; }"
	);
	int rowcount = ui.listWidget->count();
	for (int cnt = 0; cnt < rowcount; cnt++)
	{
		ui.listWidget->item(cnt)->setFont(font);
	}
	//显示模板👇👇当前应用模板
	/*for (i = 0; i < string_list.count(); i++)
	{
		if (string_list.at(i) == g_qModelName)//找到的默认模板和ini设置的一致
		{
			ui.listWidget->setCurrentRow(i);
			j = 0;//如果存在置为0
		}
	}
	if (j) {
		showWindowOut(QString::fromLocal8Bit("严重错误！不存在初始模板！"));
	}*/
}
int ProgramSet::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
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
#pragma region 模板管理
void ProgramSet::on_pB_Model_Apply_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("保存当前模板同时应用选中的模板"));
}
void ProgramSet::on_pB_Model_Add_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("添加一个模板"));
}
void ProgramSet::on_pB_Model_Delete_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("删除选中的模板（非默认和当前应用的模板）"));
}
void ProgramSet::on_pB_Model_ChangeName_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("重命名选中的模板（非默认和当前应用的模板）"));
}
void ProgramSet::on_pB_AlgSetting_toggled(bool checked)
{
	if (checked)
	{
		ui.frame_Alg->setVisible(true);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("show frame_dlg"));
	}
	else
	{
		ui.frame_Alg->setVisible(false);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("hide frame_dlg"));
	}
}

void ProgramSet::on_cB_photoTimes_activated(const QString &arg1)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置拍照次数"));
}
void ProgramSet::on_cB_freeSpace_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置最小空闲，小于等于该值开始删除存储的图片"));
}
#pragma endregion

#pragma region 相机参数
void ProgramSet::on_pB_brightness_toggled(bool checked)
{
	if (checked)
	{
		ui.frame_light->setVisible(true);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("show frame_light"));
	}
	else
	{
		ui.frame_light->setVisible(false);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("hide frame_light"));
	}
}
void ProgramSet::on_cB_232Port_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置光源控制器串口号"));
}
void ProgramSet::on_pB_adjustBrightness_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置光源的亮度，值0-255"));
}
void ProgramSet::on_cB_flash_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开所有光源"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("关闭所有光源"));
	}
}
void ProgramSet::on_pB_StartContinueGrab_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("Checkable 在上侧显示选中相机实时采集到的图像"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止调试"));
	}
}
void ProgramSet::on_pB_StartGrab_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("采集测试：当转囊选中时，相机采集频率根据设置的帧率进行采集。当下料选中时，采集程序和自动程序一样。当存图选中与否，在存图目录testsave目录会存或不存图。"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止采集测试"));
	}
}
void ProgramSet::on_pB_Keyboard_clicked()
{
	animation3->start();
	animation4->start();
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
void ProgramSet::on_pB_Exit_clicked()
{
	animation1->start();
	animation2->start();
	if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出参数设置界面？", "确认", "取消"))
	{
		m_bCloseSignal = 1;
		m_bAltKeyPressed = false;
		close();
	}
}
#pragma endregion

#pragma region PLC控制
void ProgramSet::on_pb_cmdJog_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设备点动运行，前面的lineedit显示当前设备所处的相位：0-360°，上面的显示当前所有输入点的状态，需要贴图"));
}
void ProgramSet::on_pb_cmdTestFlash0_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源1亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源1灭"));
	}
}
void ProgramSet::on_pb_cmdTestFlash1_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源2亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源2灭"));
	}
}
void ProgramSet::on_pb_cmdTestFlash2_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源3亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 光源3灭"));
	}
}
void ProgramSet::on_pb_cmdTestPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("触发拍照"));
}
void ProgramSet::on_pb_cmdTestFlashPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("触发闪光+拍照"));
}
void ProgramSet::on_pb_cmdTestCapPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("触发胶囊拍照，滚子旋转中进行多次拍照，拍照次数与设置有关"));
}
void ProgramSet::on_pb_cmdTestValveUp_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 升降气缸抬起"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 升降气缸落下"));
	}
}
void ProgramSet::on_pb_cmdTestValveClip_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 伸缩气缸伸出"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 伸缩气缸缩回"));
	}
}
void ProgramSet::on_pb_cmdTestValveDrop_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 落囊气缸落下"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 落囊气缸抬起"));
	}
}
void ProgramSet::on_pb_cmdTestLampRed_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 红灯亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 红灯灭"));
	}
}
void ProgramSet::on_pb_cmdTestLampYellow_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 黄灯亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 黄灯灭"));
	}
}
void ProgramSet::on_pb_cmdTestLampGreen_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 绿灯亮"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 绿灯灭"));
	}
}
void ProgramSet::on_pb_cmdTestBuzzer_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 蜂鸣器响"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 蜂鸣器停"));
	}
}
void ProgramSet::on_pb_cmdTestInverter_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 漏斗电机动作"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 漏斗电机停止"));
	}
}
void ProgramSet::on_pb_cmdRotateCtl_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 转囊电机动作"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 转囊电机停止"));
	}
}
void ProgramSet::on_pb_cmdTestKick30_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 全部动作，动静太大，该按钮功能建议取消"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("checkable 全部动作，动静太大，该按钮功能建议取消"));
	}
}
void ProgramSet::on_cB_debugMode_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("气缸来回动作。辅助功能用处不大，建议取消"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("气缸来回动作。辅助功能用处不大，建议取消"));
	}
}
void ProgramSet::on_pb_cmdParaSave_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("保存当前显示数据至PLC的掉电保存区中"));
}

void ProgramSet::on_lE_ClipPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置夹紧气缸动作相位 0-360"));
}
void ProgramSet::on_lE_ClipPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置夹紧气缸释放相位 0-360"));
}
void ProgramSet::on_lE_tClip1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置夹紧气缸动作延迟，单位ms"));
}
void ProgramSet::on_lE_tClip2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置夹紧气缸释放延迟，单位ms"));
}
void ProgramSet::on_lE_UpPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置抬升气缸动作相位 0-360"));
}
void ProgramSet::on_lE_UpPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置抬升气缸释放相位 0-360"));
}
void ProgramSet::on_lE_tUp1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置抬升气缸动作延迟，单位ms"));
}
void ProgramSet::on_lE_tUp2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置抬升气缸释放延迟，单位ms"));
}
void ProgramSet::on_lE_DropPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置落料气缸动作相位 0-360"));
}
void ProgramSet::on_lE_DropPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置落料气缸释放相位 0-360"));
}
void ProgramSet::on_lE_tDrop1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置落料气缸动作延迟，单位ms"));
}
void ProgramSet::on_lE_tDrop2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置落料气缸释放延迟，单位ms"));
}
void ProgramSet::on_lE_FlashTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置闪光持续的时间，单位ms"));
}
void ProgramSet::on_lE_PhotoTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置拍照触发的高电平持续时间，单位ms"));
}
void ProgramSet::on_lE_PhotoDelay_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置闪光打开多久以后开始拍照，单位ms"));
}
void ProgramSet::on_lE_PhotoPhase_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置闪光拍照的相位时机，0-360"));
}
void ProgramSet::on_lE_PhotoTimes_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("每次滚轮转一圈执行几次拍照"));
}
void ProgramSet::on_lE_PhotoInterval_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("每次滚轮转多少度执行一次拍照，注意一般不是120°，因为胶囊的角速度会大很多"));
}
void ProgramSet::on_lE_RejectTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("剔废气缸动作后，隔多久复位，单位ms"));
}
void ProgramSet::on_lE_RejectPhase_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("剔废动作相位，0-360"));
}
void ProgramSet::on_lE_DisableForceReject_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("0开启强制剔废，1关闭强制剔废"));
}
void ProgramSet::on_lE_CapCheckAlarmTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("剔废胶囊下落的时间过去后未检测到信号，则报警，报警持续的时间。单位ms"));
}
void ProgramSet::on_lE_RejectFallingTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("剔废胶囊下落的时间ms，暂时没用"));
}
void ProgramSet::on_lE_FeedAxisHomeOffset_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("送进寻参偏移，设备寻参以后要继续执行的偏移量，单位0.01°"));
}
void ProgramSet::on_lE_FeedLength_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("送进最大长度，单位0.01mm"));
}
void ProgramSet::on_lE_RotateSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("旋转轴的最大速度，RPM"));
}
void ProgramSet::on_pB_changeIPPort_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置PLC IP地址和端口号，一般情况下第一次设置一次之后就不用再变化了，且默认IP：10.86.50.210，默认port：5000"));
}
void ProgramSet::on_pB_enPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("使能拍照功能"));
}
void ProgramSet::on_pB_enReject_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("使能剔废功能"));
}
void ProgramSet::on_pB_enFeed_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("使能料斗功能"));
}
void ProgramSet::on_pB_enRotate_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("使能转囊功能"));
}
void ProgramSet::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置系统运行速度，0-120单位：次每分钟"));
}
void ProgramSet::on_pB_ContinueKickOK_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("设置连剔报警开关及数量、连剔停机开关及数量，停机数要大于报警数。连剔是由于外界条件变化导致的连续剔废。"));
}
void ProgramSet::on_pB_ContinueKickCancel_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("恢复连剔报警开关及数量、连剔停机开关及数量的默认值。"));
}
#pragma endregion

#pragma region 用户管理
void ProgramSet::on_pB_AddUser_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("添加自定义用户"));
}
void ProgramSet::on_pB_Users_Delete_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("删除自定义用户"));
}

void ProgramSet::on_cB_Users_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("根据该combobox在权限描述中说明"));
}
#pragma endregion