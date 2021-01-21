#pragma once

#include <QDialog>
#include <QMessageBox>
#include "ui_ProgramSet.h"

class ProgramSet : public QDialog
{
	Q_OBJECT

public:
	ProgramSet(QWidget *parent = Q_NULLPTR);
	~ProgramSet();

public slots: 
	void on_pB_Model_Apply_clicked();
	void on_pB_Model_Add_clicked();
	void on_pB_Model_Delete_clicked();
	void on_pB_Model_ChangeName_clicked();
	void on_pB_AlgSetting_toggled(bool checked);
	void on_pB_Model_Exit1_clicked();
	void on_cB_photoTimes_activated(const QString & arg1);
	void on_cB_freeSpace_activated(int index);
	void on_pB_brightness_toggled(bool checked);
	void on_cB_232Port_activated(int index);
	void on_pB_adjustBrightness_clicked();
	void on_cB_flash_toggled(bool checked);
	void on_pB_StartContinueGrab_toggled(bool checked);
	void on_pB_StartGrab_toggled(bool checked);
	void on_pB_Model_Exit_clicked();
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
	void on_pb_cmdTestKick30_toggled(bool checked);
	void on_cB_debugMode_toggled(bool checked);
	void on_pb_cmdParaSave_clicked();
	void on_pB_Model_Exit3_clicked();
	void on_pB_AddUser_clicked();
	void on_pB_Users_Delete_clicked();
	void on_pB_Users_Exit_clicked();

	void on_cB_Users_activated(int index);


private:
	Ui::ProgramSet ui;
};
