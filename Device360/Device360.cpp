#include "Device360.h"
#include <QProcess>
#include <QSettings>
#include <Windows.h>
#include <QThread>

#ifdef _DEBUG
#pragma comment(lib,"ServiceCtrl64d.lib")
#else
#pragma comment(lib,"ServiceCtrl64.lib")
#endif

#include "JsonDll.h"
#pragma comment(lib,"JSONDLL.lib")

Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	installEventFilter(this);

	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿� 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	m_iShutDownPC = dlg->LoginDlgCloseMode(); //2��3���˳�ʱ����
	if (m_iShutDownPC==0)
	{
		exit(-1);
	}
	else if (m_iShutDownPC == 1)
	{
		QProcess pro;    //ͨ��QProcess����ִ�е���������
		QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 ��window�µĹػ����
		pro.start(cmd);    //ִ������cmd
		pro.waitForStarted();
		pro.waitForFinished();
		exit(-1);
	}

	levelOut = new WindowOut();
	levelOut->setWindowCount(0);//����������������ֹ����
	levelOut->getString(QString::fromLocal8Bit("��ϲ�����ѳɹ���½ϵͳ��"), 2000);
	levelOut->show();

	AppPath = qApp->applicationDirPath();//exe����Ŀ¼
	AppPath.replace("/", "\\");

	initUI(); 
	initStatistics();
	m_ProgramDlg = new ProgramSet();
	//m_ResultDlg = new ResultData(); 
	//m_DailyLogDlg = new DailyLog();
	initCtrl();
}
void Device360::initCtrl()
{
	m_CsCtrl = new CServiceCtrl();
	struPlcConn plcCon;
	struCamInfo camInfo[5];
	initCamera(&camInfo[0]);

	struAlgConfig algCfg;
	QString str = AppPath+"/saveImage/";
	QByteArray ba = str.toLatin1();
	char *c = ba.data();
	strcpy(algCfg.f_resultImagePath, c);

	m_CsCtrl->SysInit(&plcCon,&camInfo[0],&algCfg);
}
void Device360::initCamera(struCamInfo *TempcamInfo)
{

	string str = (AppPath + "/ModelFile/testA/cam.json").toStdString();
	JsonCommand jsc(str);
	string s[5];
	string pstr[5];
	jsc.LoopReadJson("CamInfo", "c_CameraName", s,pstr);

	
	for (int i = 0; i < 5; i++)
	{
		TempcamInfo[i].n_CamID = i;
		const char *ch = pstr[i].data();
		strcpy(TempcamInfo[i].c_CameraName, ch);
		TempcamInfo[i].TypeOFCamera = 0;
	}
}
void Device360::closeEvent(QCloseEvent *event)
{
	if (!m_bCloseSignal)
	{
		event->ignore();
		return;
	}
	m_CsCtrl->SysUnInit();
}

bool Device360::eventFilter(QObject* obj, QEvent* event)
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
			{//����ALT+F4
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
void Device360::initUI()
{
	QSettings readPara(AppPath + "\\ModelFile\\testA\\ProgramSet.ini", QSettings::IniFormat);
	QString text = readPara.value("UISetting/Style", "").toString();
	QString style1 = "background-image:url(./ico/" + text + ".png);";
	ui.lb_style->raise();
	ui.lb_style->setStyleSheet(style1);
	ui.lb_style->setAttribute(Qt::WA_TransparentForMouseEvents);

	ui.lb_Picture->setPixmap(QPixmap(AppPath + "/ico/dr-pharmmatch.png"));
	ui.lb_Picture->setScaledContents(true);

	ui.pB_Keyboard->setFocusPolicy(Qt::NoFocus);
	ui.pB_Keyboard->setFlat(true);
	ui.pB_Keyboard->setIconSize(QSize(35, 35));
	ui.pB_Keyboard->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//�ļ�copy����exe����Ŀ¼
	ui.pB_Keyboard->setText("");

	ui.Button_Start->setText("");
	ui.Button_Start->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/start.png"));
	ui.Button_Start->setIconSize(QSize(280, 129));

	ui.Button_ParaSet->setText("");
	ui.Button_ParaSet->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraSet.png"));
	ui.Button_ParaSet->setIconSize(QSize(280, 129));

	ui.Button_CountReset->setText("");
	ui.Button_CountReset->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset.png"));
	ui.Button_CountReset->setIconSize(QSize(280, 129));

	ui.Button_Exit->setText("");
	ui.Button_Exit->setStyleSheet("QPushButton{border:0px;}");
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit.png"));
	ui.Button_Exit->setIconSize(QSize(280, 129));

	ui.tabWidget->removeTab(1);

	QRegExp regx("[a-zA-Z0-9_]+$");//������ʽQRegExp,ֻ�����������ġ����֡���ĸ���»����Լ��ո�,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_PN->setValidator(new QRegExpValidator(regx, this));
	
}
void Device360::initStatistics()
{
	QFont fo(QString::fromLocal8Bit("��Բ"), 20);
	ui.tableWidget_Result->setFont(fo);//����tableWidget����
	QStringList title;
	title << QString::fromLocal8Bit("ErrorType") << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("����");
	ui.tableWidget_Result->setColumnCount(3);//3��
	ui.tableWidget_Result->setHorizontalHeaderLabels(title);//�ӱ�ͷ
	ui.tableWidget_Result->setColumnHidden(0, true);//����ErrorType��
	ui.tableWidget_Result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//��������ͷ
	ui.tableWidget_Result->verticalHeader()->setDefaultSectionSize(35);//Ĭ���и�20
	ui.tableWidget_Result->verticalHeader()->setVisible(false);//����ʾ��ͷ
	int z = 0;
	ui.tableWidget_Result->insertRow(z);//��һ��
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("Allnum")));//��0�У�������
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("����")));//��1��
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//��2��	

	z++;
	ui.tableWidget_Result->insertRow(z);//�ټ�һ��
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("OKnum")));//��0�У�������
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("�ϸ���")));//��1��
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//��2��	

	z++;
	ui.tableWidget_Result->insertRow(z);//�ټ�һ��
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("OKrate")));//��0�У�������
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("�ϸ���")));//��1��
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//��2��

	z++;
	ui.tableWidget_Result->insertRow(z);//�ټ�һ��
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("NGStyle")));//��0�У�������
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("��Ʒ����")));//��1��
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//��2��
	for (int rowcount = 0; rowcount < z+1; rowcount++)
	{
		for (int i = 0; i < 3; i++)
		{
			ui.tableWidget_Result->item(rowcount, i)->setFlags(ui.tableWidget_Result->item(rowcount, i)->flags() & (~Qt::ItemIsEditable));//��Ԫ�񲻿ɱ༭
		}
	}

}

void Device360::firstStartInit()
{
	ui.lb_Picture->setVisible(false);
	m_bFirstStartFlag = false;

	QPixmap pix(AppPath + "/ico/dr-pharmmatch.png");//
	splitpixmap(pix, 3, 5);//��ͼ
	for (int i = 0; i < 5; i++)
	{
		for (int z = 0; z < 3; z++)
		{
			if (nullptr == this->findChild<QLabel*>("LabelShow" + QString::number(i) + "_" + QString::number(z)))
			{
				QLabel* label = new QLabel(this);
				label->setObjectName(QString::fromUtf8("LabelShow") + QString::number(i) + "_" + QString::number(z));
				label->setFrameShape(QFrame::Box);
				label->setLineWidth(1);

				QPixmap mp = m_pixlist.at(i + z * 5);
				QPainter painter;
				painter.begin(&mp);	
				painter.setRenderHint(QPainter::Antialiasing, true);
				QFont font;
				font.setPointSize(15);
				font.setFamily("����");
				font.setItalic(true);
				painter.setFont(font);
				painter.drawText(10, 5, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("���λ��: ")+QString::number(i)+"\n"+QString::fromLocal8Bit("��Ƭ���: ")+QString::number(z));//0
				painter.end();
				label->setPixmap(mp);//���и�ͼƬ
				//label->setPixmap(m_pixlist.at(i + z * 5));//���и�ͼƬ
				label->setScaledContents(true);
				ui.gridLayout->addWidget(label, i, z, 1, 1);
			}

		}
	}
}
void Device360::splitpixmap(QPixmap& pixmap, int xnum, int ynum)//��ͼ
{
	for (int x = 0; x < xnum; ++x) {
		for (int y = 0; y < ynum; ++y) {
			m_pixlist << pixmap.copy(x * (pixmap.width() / xnum), y * (pixmap.height() / ynum),
				pixmap.width() / xnum - 9, pixmap.height() / ynum - 9);
		}
	}
}
int Device360::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//ȫ������
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
#pragma region msgbox

void Device360::on_Button_Clean_toggled(bool checked)
{
	if (checked)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Checkable �豸����ϵ�����ͣ��ʱ,�豸�Ͽ��ܻ��в���Ľ��ҡ�\n�ð�ť��ͣ��״̬�°���ʱ�Ὣ���Ҷ������Ʒ�С�ͬʱ���ֻ������ת��������в��á��ٴΰ��º�ֹͣ��"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֹͣ��๦�ܡ�"));
	}
}
void Device360::on_Button_Start_toggled(bool checked)
{
	if (checked)
	{
		ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/stop.png"));
		ui.Button_ParaSet->setEnabled(false);
		ui.Button_CountReset->setEnabled(false);
		ui.Button_Exit->setEnabled(false);
		ui.lE_PN->setEnabled(false);
		//if (m_bFirstStartFlag)
		//{
		//	firstStartInit();
		//}
		//m_CsCtrl->SysStartWork();
	}
	else
	{
		ui.Button_Start->setIcon(QPixmap(AppPath + "/ico/start.png"));
		ui.Button_ParaSet->setEnabled(true);
		ui.Button_CountReset->setEnabled(true);
		ui.Button_Exit->setEnabled(true);
		ui.lE_PN->setEnabled(true);
		m_CsCtrl->SysStopWork();
	}
}
void Device360::on_Button_AlarmReset_clicked()
{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ϵͳ��������󣬵���ð�ť���й��ϸ�λ������豸����ԭ�㣬����ҪѰ��"));

}

void Device360::on_Button_ParaSet_pressed()
{
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraset2.png"));
}
void Device360::on_Button_ParaSet_released()
{
	ui.Button_ParaSet->setIcon(QPixmap(AppPath + "/ico/paraset.png"));
	m_ProgramDlg->show();
}
void Device360::on_Button_Log_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����־��ѯ����"));
	m_DailyLogDlg->show();
}
void Device360::on_Button_DataOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����ݵ�������"));
	m_ResultDlg->show();
}

void Device360::on_Button_CountReset_pressed()
{
	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset2.png"));
}

void Device360::on_Button_CountReset_released()
{

	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset.png"));
}

void Device360::on_pB_Keyboard_clicked()
{
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

void Device360::on_Button_Exit_pressed()
{
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit2.png"));
}
void Device360::on_Button_Exit_released()
{
	ui.Button_Exit->setIcon(QPixmap(AppPath + "/ico/exit.png"));
	if (m_iShutDownPC == 2)
	{
		if (QMessageBox::Yes == showMsgBox("�˳���ʾ", "�Ƿ�ȷ���˳�ϵͳ��", "ȷ��", "ȡ��"))
		{
			if (QMessageBox::Yes == showMsgBox("�ػ���ʾ", "�Ƿ�ȷ�Ϲػ���", "ȷ��", "ȡ��"))
			{
				QProcess pro;    //ͨ��QProcess����ִ�е���������
				QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 ��window�µĹػ����
				pro.start(cmd);    //ִ������cmd
				pro.waitForStarted();
				pro.waitForFinished();
				exit(-1);
			}
			else
			{
				m_bCloseSignal = true;
				m_bAltKeyPressed = false;
				close();
			}
		}

	}
	else
	{
		if (QMessageBox::Yes == showMsgBox("�˳���ʾ", "�Ƿ�ȷ���˳�ϵͳ��", "ȷ��", "ȡ��"))
		{
			m_bCloseSignal = true;
			m_bAltKeyPressed = false;
			close();
		}
	}
	
}
void Device360::on_lE_PN_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ı���������"));
}
void Device360::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ı�ϵͳ�ٶȣ�10-120rpm"));
}
#pragma endregion