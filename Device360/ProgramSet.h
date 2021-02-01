#pragma once

#include <QDialog>
#include <QMessageBox>
#include "ui_ProgramSet.h"
#include <QPropertyAnimation>
#include <QKeyEvent>

class ProgramSet : public QDialog
{
	Q_OBJECT

public:
	ProgramSet(QWidget *parent = Q_NULLPTR);
	~ProgramSet();
	void keyPressEvent(QKeyEvent *event)
	{
		switch (event->key())
		{
		case Qt::Key_Escape:
			break;
		default:
			QDialog::keyPressEvent(event);
		}
	}
	void closeEvent(QCloseEvent * event);
	bool eventFilter(QObject * obj, QEvent * event);

	void initUI();
	void initMovie();
	void initListWidgetofModel();
	int showMsgBox(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);

private:
	Ui::ProgramSet ui;
	bool m_bCloseSignal = false;
	bool m_bAltKeyPressed = false;
	QString AppPath;
	//µ¯ÌøÌØÐ§
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;

	QPropertyAnimation * animation3 = nullptr;
	QPropertyAnimation * animation4 = nullptr;
public slots: 
	void on_pB_Model_Apply_clicked();
	void on_pB_Model_Add_clicked();
	void on_pB_Model_Delete_clicked();
	void on_pB_Model_ChangeName_clicked();
	void on_pB_AlgSetting_toggled(bool checked);
	void on_cB_photoTimes_activated(const QString & arg1);
	void on_cB_freeSpace_activated(int index);
	void on_pB_brightness_toggled(bool checked);
	void on_cB_232Port_activated(int index);
	void on_pB_adjustBrightness_clicked();
	void on_cB_flash_toggled(bool checked);
	void on_pB_StartContinueGrab_toggled(bool checked);
	void on_pB_StartGrab_toggled(bool checked);
	void on_pB_Keyboard_clicked();
	void on_pB_Exit_clicked();
	void on_pb_cmdJog_clicked();
	void on_pb_cmdTestFlash0_toggled(bool checked);
	void on_pb_cmdTestFlash1_toggled(bool checked);
	void on_pb_cmdTestFlash2_toggled(bool checked);
	void on_pb_cmdTestPhoto_clicked();
	void on_pb_cmdTestFlashPhoto_clicked();
	void on_pb_cmdTestCapPhoto_clicked();
	void on_pb_cmdTestValveUp_toggled(bool checked);
	void on_pb_cmdTestValveClip_toggled(bool checked);
	void on_pb_cmdTestValveDrop_toggled(bool checked);
	void on_pb_cmdTestLampRed_toggled(bool checked);
	void on_pb_cmdTestLampYellow_toggled(bool checked);
	void on_pb_cmdTestLampGreen_toggled(bool checked);
	void on_pb_cmdTestBuzzer_toggled(bool checked);
	void on_pb_cmdTestInverter_toggled(bool checked);
	void on_pb_cmdRotateCtl_toggled(bool checked);
	void on_pb_cmdTestKick30_toggled(bool checked);
	void on_cB_debugMode_toggled(bool checked);
	void on_pb_cmdParaSave_clicked();
	void on_lE_ClipPhase1_returnPressed();
	void on_lE_ClipPhase2_returnPressed();
	void on_lE_tClip1_returnPressed();
	void on_lE_tClip2_returnPressed();
	void on_lE_UpPhase1_returnPressed();
	void on_lE_UpPhase2_returnPressed();
	void on_lE_tUp1_returnPressed();
	void on_lE_tUp2_returnPressed();
	void on_lE_DropPhase1_returnPressed();
	void on_lE_DropPhase2_returnPressed();
	void on_lE_tDrop1_returnPressed();
	void on_lE_tDrop2_returnPressed();
	void on_lE_FlashTime_returnPressed();
	void on_lE_PhotoTime_returnPressed();
	void on_lE_PhotoDelay_returnPressed();
	void on_lE_PhotoPhase_returnPressed();
	void on_lE_PhotoTimes_returnPressed();
	void on_lE_PhotoInterval_returnPressed();
	void on_lE_RejectTime_returnPressed();
	void on_lE_RejectPhase_returnPressed();
	void on_lE_DisableForceReject_returnPressed();
	void on_lE_CapCheckAlarmTime_returnPressed();
	void on_lE_RejectFallingTime_returnPressed();
	void on_lE_FeedAxisHomeOffset_returnPressed();
	void on_lE_FeedLength_returnPressed();
	void on_lE_RotateSpeed_returnPressed();
	void on_pB_changeIPPort_clicked();
	void on_pB_enPhoto_clicked();
	void on_pB_enReject_clicked();
	void on_pB_enFeed_clicked();
	void on_pB_enRotate_clicked();
	void on_lE_RunSpeed_returnPressed();
	void on_pB_ContinueKickOK_clicked();
	void on_pB_ContinueKickCancel_clicked();
	void on_pB_AddUser_clicked();
	void on_pB_Users_Delete_clicked();
	void on_cB_Users_activated(int index);

};
