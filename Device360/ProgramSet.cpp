#include "ProgramSet.h"
#include <Windows.h>
#include <QSettings>

ProgramSet::ProgramSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	connect(ui.AlgButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {
		//if (button->objectName() == "pushButton_1")
		QString str = button->text();
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��")+str+QString::fromLocal8Bit("������㷨���ý���"));
			}
	});
	connect(ui.KickButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {
		//if (button->objectName() == "pushButton_1")
		QString str = button->text();
			{
				QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), str+QString::fromLocal8Bit("���޷����׶���"));
			}
	});

	AppPath = qApp->applicationDirPath();//exe����Ŀ¼
	AppPath.replace("/", "\\");

	initMovie(); 
	initUI();
}
ProgramSet::~ProgramSet()
{
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
}
void ProgramSet::initMovie()
{//������̬����
	{
		animation1 = new QPropertyAnimation(ui.pB_Exit, "geometry");
		//���ö���ʱ����
		animation1->setDuration(200);

		//��ʼλ��
		animation1->setStartValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y(), ui.pB_Exit->width(), ui.pB_Exit->height()));
		//����λ��
		animation1->setEndValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y()+10, ui.pB_Exit->width(), ui.pB_Exit->height()));

		//���õ�������
		animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //������̬����
		animation2 = new QPropertyAnimation(ui.pB_Exit, "geometry");
		//���ö���ʱ����
		animation2->setDuration(200);

		//��ʼλ��
		animation2->setStartValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y()+10, ui.pB_Exit->width(), ui.pB_Exit->height()));
		//����λ��
		animation2->setEndValue(QRect(ui.pB_Exit->x(), ui.pB_Exit->y(), ui.pB_Exit->width(), ui.pB_Exit->height()));

		//���õ�������
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
	{
		animation3 = new QPropertyAnimation(ui.pB_Keyboard, "geometry");
		//���ö���ʱ����
		animation3->setDuration(200);

		//��ʼλ��
		animation3->setStartValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y(), ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));
		//����λ��
		animation3->setEndValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y() + 10, ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));

		//���õ�������
		animation3->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //������̬����
		animation4 = new QPropertyAnimation(ui.pB_Keyboard, "geometry");
		//���ö���ʱ����
		animation4->setDuration(200);

		//��ʼλ��
		animation4->setStartValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y() + 10, ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));
		//����λ��
		animation4->setEndValue(QRect(ui.pB_Keyboard->x(), ui.pB_Keyboard->y(), ui.pB_Keyboard->width(), ui.pB_Keyboard->height()));

		//���õ�������
		animation4->setEasingCurve(QEasingCurve::OutBounce);
	}
}
int ProgramSet::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//ȫ������
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
#pragma region ģ�����
void ProgramSet::on_pB_Model_Apply_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���浱ǰģ��ͬʱӦ��ѡ�е�ģ��"));
}
void ProgramSet::on_pB_Model_Add_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���һ��ģ��"));
}
void ProgramSet::on_pB_Model_Delete_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ɾ��ѡ�е�ģ�壨��Ĭ�Ϻ͵�ǰӦ�õ�ģ�壩"));
}
void ProgramSet::on_pB_Model_ChangeName_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ѡ�е�ģ�壨��Ĭ�Ϻ͵�ǰӦ�õ�ģ�壩"));
}
void ProgramSet::on_pB_AlgSetting_toggled(bool checked)
{
	if (checked)
	{
		ui.frame_Alg->setVisible(true);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("show frame_dlg"));
	}
	else
	{
		ui.frame_Alg->setVisible(false);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("hide frame_dlg"));
	}
}

void ProgramSet::on_cB_photoTimes_activated(const QString &arg1)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������մ���"));
}
void ProgramSet::on_cB_freeSpace_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������С���У�С�ڵ��ڸ�ֵ��ʼɾ���洢��ͼƬ"));
}
#pragma endregion

#pragma region �������
void ProgramSet::on_pB_brightness_toggled(bool checked)
{
	if (checked)
	{
		ui.frame_light->setVisible(true);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("show frame_light"));
	}
	else
	{
		ui.frame_light->setVisible(false);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("hide frame_light"));
	}
}
void ProgramSet::on_cB_232Port_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ù�Դ���������ں�"));
}
void ProgramSet::on_pB_adjustBrightness_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ù�Դ�����ȣ�ֵ0-255"));
}
void ProgramSet::on_cB_flash_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����й�Դ"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ر����й�Դ"));
	}
}
void ProgramSet::on_pB_StartContinueGrab_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Checkable ���ϲ���ʾѡ�����ʵʱ�ɼ�����ͼ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ����"));
	}
}
void ProgramSet::on_pB_StartGrab_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ɼ����ԣ���ת��ѡ��ʱ������ɼ�Ƶ�ʸ������õ�֡�ʽ��вɼ���������ѡ��ʱ���ɼ�������Զ�����һ��������ͼѡ������ڴ�ͼĿ¼testsaveĿ¼���򲻴�ͼ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ�ɼ�����"));
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
	if (QMessageBox::Yes == showMsgBox("�˳���ʾ", "�Ƿ�ȷ���˳��������ý��棿", "ȷ��", "ȡ��"))
	{
		close();
	}
}
#pragma endregion

#pragma region PLC����
void ProgramSet::on_pb_cmdJog_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�豸�㶯���У�ǰ���lineedit��ʾ��ǰ�豸��������λ��0-360�㣬�������ʾ��ǰ����������״̬����Ҫ��ͼ"));
}
void ProgramSet::on_pb_cmdTestFlash0_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ1��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ1��"));
	}
}
void ProgramSet::on_pb_cmdTestFlash1_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ2��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ2��"));
	}
}
void ProgramSet::on_pb_cmdTestFlash2_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ3��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��Դ3��"));
	}
}
void ProgramSet::on_pb_cmdTestPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������"));
}
void ProgramSet::on_pb_cmdTestFlashPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������+����"));
}
void ProgramSet::on_pb_cmdTestCapPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����������գ�������ת�н��ж�����գ����մ����������й�"));
}
void ProgramSet::on_pb_cmdTestValveUp_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��������̧��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ������������"));
	}
}
void ProgramSet::on_pb_cmdTestValveClip_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �����������"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ������������"));
	}
}
void ProgramSet::on_pb_cmdTestValveDrop_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ������������"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��������̧��"));
	}
}
void ProgramSet::on_pb_cmdTestLampRed_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �����"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �����"));
	}
}
void ProgramSet::on_pb_cmdTestLampYellow_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �Ƶ���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �Ƶ���"));
	}
}
void ProgramSet::on_pb_cmdTestLampGreen_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �̵���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable �̵���"));
	}
}
void ProgramSet::on_pb_cmdTestBuzzer_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ��������"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ������ͣ"));
	}
}
void ProgramSet::on_pb_cmdTestInverter_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ©���������"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ©�����ֹͣ"));
	}
}
void ProgramSet::on_pb_cmdRotateCtl_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ת�ҵ������"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ת�ҵ��ֹͣ"));
	}
}
void ProgramSet::on_pb_cmdTestKick30_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ȫ������������̫�󣬸ð�ť���ܽ���ȡ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("checkable ȫ������������̫�󣬸ð�ť���ܽ���ȡ��"));
	}
}
void ProgramSet::on_cB_debugMode_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ض��������������ô����󣬽���ȡ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ض��������������ô����󣬽���ȡ��"));
	}
}
void ProgramSet::on_pb_cmdParaSave_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���浱ǰ��ʾ������PLC�ĵ��籣������"));
}

void ProgramSet::on_lE_ClipPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���üн����׶�����λ 0-360"));
}
void ProgramSet::on_lE_ClipPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���üн������ͷ���λ 0-360"));
}
void ProgramSet::on_lE_tClip1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���üн����׶����ӳ٣���λms"));
}
void ProgramSet::on_lE_tClip2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���üн������ͷ��ӳ٣���λms"));
}
void ProgramSet::on_lE_UpPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����̧�����׶�����λ 0-360"));
}
void ProgramSet::on_lE_UpPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����̧�������ͷ���λ 0-360"));
}
void ProgramSet::on_lE_tUp1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����̧�����׶����ӳ٣���λms"));
}
void ProgramSet::on_lE_tUp2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����̧�������ͷ��ӳ٣���λms"));
}
void ProgramSet::on_lE_DropPhase1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����������׶�����λ 0-360"));
}
void ProgramSet::on_lE_DropPhase2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������������ͷ���λ 0-360"));
}
void ProgramSet::on_lE_tDrop1_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����������׶����ӳ٣���λms"));
}
void ProgramSet::on_lE_tDrop2_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������������ͷ��ӳ٣���λms"));
}
void ProgramSet::on_lE_FlashTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������������ʱ�䣬��λms"));
}
void ProgramSet::on_lE_PhotoTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������մ����ĸߵ�ƽ����ʱ�䣬��λms"));
}
void ProgramSet::on_lE_PhotoDelay_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������򿪶���Ժ�ʼ���գ���λms"));
}
void ProgramSet::on_lE_PhotoPhase_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����������յ���λʱ����0-360"));
}
void ProgramSet::on_lE_PhotoTimes_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ÿ�ι���תһȦִ�м�������"));
}
void ProgramSet::on_lE_PhotoInterval_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ÿ�ι���ת���ٶ�ִ��һ�����գ�ע��һ�㲻��120�㣬��Ϊ���ҵĽ��ٶȻ��ܶ�"));
}
void ProgramSet::on_lE_RejectTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷����׶����󣬸���ø�λ����λms"));
}
void ProgramSet::on_lE_RejectPhase_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷϶�����λ��0-360"));
}
void ProgramSet::on_lE_DisableForceReject_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("0����ǿ���޷ϣ�1�ر�ǿ���޷�"));
}
void ProgramSet::on_lE_CapCheckAlarmTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷Ͻ��������ʱ���ȥ��δ��⵽�źţ��򱨾�������������ʱ�䡣��λms"));
}
void ProgramSet::on_lE_RejectFallingTime_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷Ͻ��������ʱ��ms����ʱû��"));
}
void ProgramSet::on_lE_FeedAxisHomeOffset_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ͽ�Ѱ��ƫ�ƣ��豸Ѱ���Ժ�Ҫ����ִ�е�ƫ��������λ0.01��"));
}
void ProgramSet::on_lE_FeedLength_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ͽ���󳤶ȣ���λ0.01mm"));
}
void ProgramSet::on_lE_RotateSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ת�������ٶȣ�RPM"));
}
void ProgramSet::on_pB_changeIPPort_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����PLC IP��ַ�Ͷ˿ںţ�һ������µ�һ������һ��֮��Ͳ����ٱ仯�ˣ���Ĭ��IP��10.86.50.210��Ĭ��port��5000"));
}
void ProgramSet::on_pB_enPhoto_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ʹ�����չ���"));
}
void ProgramSet::on_pB_enReject_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ʹ���޷Ϲ���"));
}
void ProgramSet::on_pB_enFeed_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ʹ���϶�����"));
}
void ProgramSet::on_pB_enRotate_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ʹ��ת�ҹ���"));
}
void ProgramSet::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ϵͳ�����ٶȣ�0-120��λ����ÿ����"));
}
void ProgramSet::on_pB_ContinueKickOK_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ޱ������ؼ�����������ͣ�����ؼ�������ͣ����Ҫ���ڱ�������������������������仯���µ������޷ϡ�"));
}
void ProgramSet::on_pB_ContinueKickCancel_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ָ����ޱ������ؼ�����������ͣ�����ؼ�������Ĭ��ֵ��"));
}
#pragma endregion

#pragma region �û�����
void ProgramSet::on_pB_AddUser_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����Զ����û�"));
}
void ProgramSet::on_pB_Users_Delete_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ɾ���Զ����û�"));
}

void ProgramSet::on_cB_Users_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݸ�combobox��Ȩ��������˵��"));
}
#pragma endregion