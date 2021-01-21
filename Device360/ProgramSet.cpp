#include "ProgramSet.h"

ProgramSet::ProgramSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//无边框 

	ui.frame_Alg->setVisible(false);
	ui.frame_light->setVisible(false);

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
	
}

ProgramSet::~ProgramSet()
{
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
void ProgramSet::on_pB_Model_Exit1_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出参数设置界面"));
	close();

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
void ProgramSet::on_pB_Model_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出设置界面"));
	close();
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("气缸来回动作。辅助功能鸡肋，建议取消"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("气缸来回动作。辅助功能鸡肋，建议取消"));
	}
}
void ProgramSet::on_pb_cmdParaSave_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("保存当前显示数据至PLC的掉电保存区中"));
}
void ProgramSet::on_pB_Model_Exit3_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出设置界面"));
	close();
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
void ProgramSet::on_pB_Users_Exit_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("退出系统设置"));
	close();
}

void ProgramSet::on_cB_Users_activated(int index)
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("根据该combobox在权限描述中说明"));
}
#pragma endregion