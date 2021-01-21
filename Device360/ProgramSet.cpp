#include "ProgramSet.h"

ProgramSet::ProgramSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	ui.frame_Alg->setVisible(false);
	ui.frame_light->setVisible(false);

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
	
}

ProgramSet::~ProgramSet()
{
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
void ProgramSet::on_pB_Model_Exit1_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳��������ý���"));
	close();

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
void ProgramSet::on_pB_Model_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳����ý���"));
	close();
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ض������������ܼ��ߣ�����ȡ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ض������������ܼ��ߣ�����ȡ��"));
	}
}
void ProgramSet::on_pb_cmdParaSave_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���浱ǰ��ʾ������PLC�ĵ��籣������"));
}
void ProgramSet::on_pB_Model_Exit3_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳����ý���"));
	close();
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
void ProgramSet::on_pB_Users_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˳�ϵͳ����"));
	close();
}

void ProgramSet::on_cB_Users_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݸ�combobox��Ȩ��������˵��"));
}
#pragma endregion