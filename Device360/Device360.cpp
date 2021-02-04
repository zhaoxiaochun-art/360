#include "Device360.h"
#include <QProcess>
#include <QSettings>
#include <Windows.h>
#include <QThread>

extern Device360 *w;

#ifdef _DEBUG
#pragma comment(lib,"ServiceCtrl64d.lib")
#else
#pragma comment(lib,"ServiceCtrl64.lib")
#endif

#include "JsonDll.h"
#pragma comment(lib,"JSONDLL.lib")


void MyFunTemp(int nCamID, int nPhotoTimes, unsigned char* pBuf, int IWidth, int IHeight, int IFrameType, void* pResult)
{
	w->MyFun(nCamID, nPhotoTimes, pBuf, IWidth, IHeight, IFrameType, pResult);
}

Device360::Device360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	installEventFilter(this);

	setWindowFlags(Qt::FramelessWindowHint);//无边框 

	LoginDialog* dlg = new LoginDialog(this);
	dlg->exec();
	m_iShutDownPC = dlg->LoginDlgCloseMode(); //2和3在退出时处理
	if (m_iShutDownPC == 0)
	{
		exit(-1);
	}
	else if (m_iShutDownPC == 1)
	{
		QProcess pro;    //通过QProcess类来执行第三方程序
		QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 是window下的关机命令，
		pro.start(cmd);    //执行命令cmd
		pro.waitForStarted();
		pro.waitForFinished();
		exit(-1);
	}

	levelOut = new WindowOut();
	levelOut->setWindowCount(0);//动画窗弹出数，防止覆盖
	levelOut->getString(QString::fromLocal8Bit("恭喜，您已成功登陆系统！"), 2000);
	levelOut->show();

	AppPath = qApp->applicationDirPath();//exe所在目录
	AppPath.replace("/", "\\");

	initUI(); 
	firstStartInit();
	initStatistics();
	m_ProgramDlg = new ProgramSet();
	//m_ResultDlg = new ResultData(); 
	//m_DailyLogDlg = new DailyLog();
	initCtrl();

	m_MyFunPtr = MyFunTemp;    // 函数指针初始化
	connect(this, SIGNAL(SignShowImage(int, cv::Mat, int)), this, SLOT(SLOTShowImage(int, cv::Mat, int)));//openCV有关 显示图片

	initPieChart();
}
void Device360::dataReceived(int one)
{
	data_One << one;
	//数据个数超过了最大数量，则删除所有数据，从头开始。
	while (data_One.size() > 2) {
		//data.clear();//
		data_One.removeFirst();
	}
	// 界面被隐藏后就没有必要绘制数据的曲线了
	if (isVisible()) {
		series->clear();
		//scatterSeries->clear();
		int dx = 1;// maxX / (maxSize - 1);
		for (int i = 0; i < data_One.size(); ++i) {
			series->append("", data_One.at(i));
			//scatterSeries->append(i*dx, data.at(i));
		}
	}
	slice();
}
void Device360::initPieChart()
{
	//绘制饼图
	series = new QPieSeries();
	//添加饼图切片的标签和值
	data_One << 10 << 10;
	series->append("", data_One.at(0));
	series->append("", data_One.at(1));
	float totalValue = 10 + 10;
	series->setHoleSize(0.0);//孔大小0.0-1.0
	series->setHorizontalPosition(0.5);//水平位置，默认0.5，0.0-1.0
	series->setLabelsPosition(QPieSlice::LabelInsideNormal);
	series->setLabelsVisible(true);
	series->setPieSize(0.8);//饼图尺寸，默认0.7
	series->setPieStartAngle(0);//0度为12点钟方向
	series->setVerticalPosition(0.5);
	series->setVisible(true);


	chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QString::fromLocal8Bit("运行统计饼图"));
	chart->setTheme(QChart::ChartThemeBlueCerulean);
	//chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
	chart->setBackgroundBrush(QBrush(QColor(6, 89, 128)));//设置背景色
	//chart->setDropShadowEnabled(true);//是否背景阴影
	chart->setLocalizeNumbers(true);//数字是否本地化
	chart->setTitleBrush(QBrush(QColor(255, 255, 255)));//设置标题Brush（刷子）
	chart->setTitleFont(QFont("微软雅黑", 14));//设置标题字体


	chart->legend()->setAlignment(Qt::AlignLeft);//对齐
	//chart->legend()->setLabelColor(QColor(0, 0, 0));//设置标签颜色
	chart->legend()->setVisible(true);//设置是否可视
	chart->legend()->setBorderColor(QColor(255, 255, 170, 185));//设置边框颜色
	QFont font = chart->legend()->font();
	font.setItalic(!font.italic());
	chart->legend()->setFont(font);//设置字体为斜体
	font.setPointSizeF(12);
	chart->legend()->setFont(font);//设置字体大小
	chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型

	slice();

	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	pVLayout = new QVBoxLayout(ui.frame_Pie);

	//setContentsMargins(int left, int top, int right, int bottom)
	//设置上下左右的边距分别为0
	pVLayout->setContentsMargins(0, 0, 0, 0);
	pVLayout->addWidget(chartView);
	/*ui.verticalLayout_4->addWidget(chartView); 
	ui.verticalLayout_4->setMargin(0);  //表示控件与窗体的左右边距
	ui.verticalLayout_4->setContentsMargins(0, 0, 0, 0);
	ui.verticalLayout_4->setSpacing(0); //表示各个控件之间的上下间距*/
}
void Device360::slice()
{
	//操作单个切片
	slice1 = series->slices().at(0);
	//slice1->setExploded();//切片是否与饼图分离
	slice1->setLabelVisible(false);//标签是否可视
	//slice1->setLabelColor(QColor(0, 170, 0));//设置标签颜色
	slice1->setColor(QColor(0, 170, 0));//设置颜色
	slice1->setLabel(QString("%1").arg(slice1->value())+"\n\t"+QString::number(123));
	//slice1->setLabelFont(QFont("微软雅黑"));//设置标签格式

	slice2 = series->slices().at(1);
	//slice2->setExploded();//切片是否与饼图分离
	slice2->setLabelVisible(false);
	//slice2->setLabelColor(QColor(170, 170, 0));
	slice2->setColor(QColor(170, 170, 0));
	slice2->setLabel(slice2->label() + QString("%1").arg(slice2->value()));
	//slice2->setLabelFont(QFont("微软雅黑"));
}
void Device360::initCtrl()
{
	m_CsCtrl = new CServiceCtrl();
	struPlcConn plcCon;
	struCamInfo camInfo[5];
	initCamera(&camInfo[0]);

	struAlgConfig algCfg;
	QString str = AppPath + "/saveImage/";
	QByteArray ba = str.toLatin1();
	char *c = ba.data();
	strcpy(algCfg.f_resultImagePath, c);

	m_CsCtrl->SysInit(&plcCon, &camInfo[0], &algCfg);
}
void Device360::initCamera(struCamInfo *TempcamInfo)
{

	string str = (AppPath + "/ModelFile/testA/cam.json").toStdString();
	JsonCommand jsc(str);
	string s[5];
	string pstr[5];
	jsc.LoopReadJson("CamInfo", "c_CameraName", s, pstr);


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
void Device360::MyFun(int nCamID, int nPhotoTimes, unsigned char* pBuf, int IWidth, int IHeight, int IFrameType, void* pResult)
{
	int sizetotal = IHeight * IWidth * IFrameType;
	cv::Mat matGetOnece = cv::Mat(IHeight, IWidth, IFrameType == 1 ? CV_8UC1 : CV_8UC3);
	memcpy(matGetOnece.data, pBuf, sizetotal);

	emit SignShowImage(nCamID, matGetOnece, nPhotoTimes);

	m_result = (struAlgResult*)pResult;
	for (int k = 0; k < 6; k++)
	{
		int iskk = m_result->isKick[k];
		int i = m_result->NGType[k];
		if (iskk==0)//不剔废
		{
			if (i==-1)//合格
			{
				int oldsum = ui.tableWidget_Result->item(0, 2)->text().toInt();
				ui.tableWidget_Result->item(0, 2)->setText(QString::number(++oldsum));
				int oldOK = ui.tableWidget_Result->item(1, 2)->text().toInt();
				ui.tableWidget_Result->item(1, 2)->setText(QString::number(++oldOK));
			}
		}
		else
		{

			int oldsum = ui.tableWidget_Result->item(0, 2)->text().toInt();
			ui.tableWidget_Result->item(0, 2)->setText(QString::number(++oldsum));
			int oldng = ui.tableWidget_Result->item(4 + i, 2)->text().toInt();
			if (oldng==0)
			{
				int oldtype = ui.tableWidget_Result->item(3, 2)->text().toInt();
				ui.tableWidget_Result->item(3, 2)->setText(QString::number(++oldtype));
			}
			ui.tableWidget_Result->item(4 + i, 2)->setText(QString::number(++oldng));
		}
	}
	int oldsum = ui.tableWidget_Result->item(0, 2)->text().toInt();
	int oldOK = ui.tableWidget_Result->item(1, 2)->text().toInt();
	float ft = oldOK * 100.0 / oldsum;
	ui.tableWidget_Result->item(2, 2)->setText(QString::number(ft, 'f', 2) + "%");
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
	ui.pB_Keyboard->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//文件copy到了exe所在目录
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

	QRegExp regx("[a-zA-Z0-9_]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lE_PN->setValidator(new QRegExpValidator(regx, this));

}
void Device360::initStatistics()
{
	QFont fo(QString::fromLocal8Bit("幼圆"), 20);
	ui.tableWidget_Result->setFont(fo);//设置tableWidget字体
	QStringList title;
	title << QString::fromLocal8Bit("ErrorType") << QString::fromLocal8Bit("类型") << QString::fromLocal8Bit("数量");
	ui.tableWidget_Result->setColumnCount(3);//3列
	ui.tableWidget_Result->setHorizontalHeaderLabels(title);//加表头
	ui.tableWidget_Result->setColumnHidden(0, true);//隐藏ErrorType列
	ui.tableWidget_Result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分填充表头
	ui.tableWidget_Result->verticalHeader()->setDefaultSectionSize(35);//默认行高20
	ui.tableWidget_Result->verticalHeader()->setVisible(false);//不显示行头
	int z = 0;
	ui.tableWidget_Result->insertRow(z);//加一行
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("Allnum")));//第0列，已隐藏
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("总数")));//第1列
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//第2列	

	z++;
	ui.tableWidget_Result->insertRow(z);//再加一行
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("OKnum")));//第0列，已隐藏
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("合格数")));//第1列
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//第2列	

	z++;
	ui.tableWidget_Result->insertRow(z);//再加一行
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("OKrate")));//第0列，已隐藏
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("合格率")));//第1列
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//第2列

	z++;
	ui.tableWidget_Result->insertRow(z);//再加一行
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("NGStyle")));//第0列，已隐藏
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("废品种类")));//第1列
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//第2列	
	
	for(int j=1;j<11;j++)
	{
	z++;
	ui.tableWidget_Result->insertRow(z);//再加一行
	ui.tableWidget_Result->setItem(z, 0, new QTableWidgetItem(QString::fromLocal8Bit("NG")+QString::number(j)));//第0列，已隐藏
	ui.tableWidget_Result->setItem(z, 1, new QTableWidgetItem(QString::fromLocal8Bit("废品") + QString::number(j)));//第1列
	ui.tableWidget_Result->setItem(z, 2, new QTableWidgetItem(QString::number(0)));//第2列
	}

	for (int rowcount = 0; rowcount < z + 1; rowcount++)
	{
		for (int i = 0; i < 3; i++)
		{
			ui.tableWidget_Result->item(rowcount, i)->setFlags(ui.tableWidget_Result->item(rowcount, i)->flags() & (~Qt::ItemIsEditable));//单元格不可编辑
		}
	}

}

void Device360::firstStartInit()
{
	ui.lb_Picture->setVisible(false);

	QPixmap pix(AppPath + "/ico/dr-pharmmatch.png");//
	splitpixmap(pix, 3, 5);//切图
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
				font.setFamily("宋体");
				font.setItalic(true);
				painter.setFont(font);
				painter.drawText(10, 5, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("相机位置: ") + QString::number(i) + "\n" + QString::fromLocal8Bit("照片序号: ") + QString::number(z));//0
				painter.end();
				label->setPixmap(mp);//改切割图片
				//label->setPixmap(m_pixlist.at(i + z * 5));//改切割图片
				label->setScaledContents(true);
				ui.gridLayout->addWidget(label, i, z, 1, 1);
			}

		}
	}
}
void Device360::splitpixmap(QPixmap& pixmap, int xnum, int ynum)//切图
{
	for (int x = 0; x < xnum; ++x) {
		for (int y = 0; y < ynum; ++y) {
			m_pixlist << pixmap.copy(x * (pixmap.width() / xnum), y * (pixmap.height() / ynum),
				pixmap.width() / xnum - 9, pixmap.height() / ynum - 9);
		}
	}
}
int Device360::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("Checkable 设备因故障导致在停机时,设备上可能还有残余的胶囊。\n该按钮在停机状态下按下时会将胶囊都排入废品盒。同时滚轮会持续旋转，方便进行擦拭。再次按下后停止。"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("停止清洁功能。"));
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

		m_CsCtrl->SysStartWork(m_MyFunPtr);
		static int i = 200000;
		i += 2;
		dataReceived(i);
		/*unsigned char *buff = new unsigned char[3499200];

		struAlgResult *finalresult = new struAlgResult();
		finalresult->isKick[0] = 1;
		finalresult->isKick[1] = 1;
		finalresult->isKick[2] = 1;
		finalresult->isKick[3] = 0;
		finalresult->isKick[4] = 0;
		finalresult->NGType[0] = 0;
		finalresult->NGType[1] = 1;
		finalresult->NGType[2] = 2;
		finalresult->NGType[3] = -1;//合格
		finalresult->NGType[4] = -2;//空
		static int kk = -2;
		if (kk == 5) kk = -2;
		finalresult->NGType[5] = kk;
		if (kk>=0)
		{
			finalresult->isKick[5] = 1;
		}
		else
		{
			finalresult->isKick[5] = 0;
		}
		kk++;

		void* pResult = finalresult;
		MyFunTemp(0, 0, buff, 1080, 1080, 3, pResult);*/
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
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("系统故障清除后，点击该按钮进行故障复位，如果设备不在原点，还需要寻参"));

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
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开日志查询界面"));
	m_DailyLogDlg->show();
}
void Device360::on_Button_DataOut_clicked()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("打开数据导出界面"));
	m_ResultDlg->show();
}

void Device360::on_Button_CountReset_pressed()
{
	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset2.png"));
}

void Device360::on_Button_CountReset_released()
{

	ui.Button_CountReset->setIcon(QPixmap(AppPath + "/ico/countReset.png"));	
	for (int i = 0; i < ui.tableWidget_Result->rowCount(); i++)//遍历没有，增加新行赋值1
	{
		ui.tableWidget_Result->setItem(i, 2, new QTableWidgetItem(QString::number(0)));
	}
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
		if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出系统？", "确认", "取消"))
		{
			if (QMessageBox::Yes == showMsgBox("关机提示", "是否确认关机？", "确认", "取消"))
			{
				QProcess pro;    //通过QProcess类来执行第三方程序
				QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 是window下的关机命令，
				pro.start(cmd);    //执行命令cmd
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
		if (QMessageBox::Yes == showMsgBox("退出提示", "是否确认退出系统？", "确认", "取消"))
		{
			m_bCloseSignal = true;
			m_bAltKeyPressed = false;
			close();
		}
	}

}
void Device360::on_lE_PN_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变生产批号"));
}
void Device360::on_lE_RunSpeed_returnPressed()
{
	QMessageBox::about(nullptr, QString::fromLocal8Bit("功能"), QString::fromLocal8Bit("改变系统速度：10-120rpm"));
}
#pragma endregion

void Device360::SLOTShowImage(int pos, cv::Mat img, int checktimes)
{
	QLabel* label = this->findChild<QLabel*>("LabelShow" + QString::number(pos) + "_" + QString::number(checktimes % 3));

	int zz = label->frameWidth();
	QSize ss = label->size();
	ss.setWidth(ss.width() - zz * 2);
	ss.setHeight(ss.height() - zz * 2);
	cv::Mat imgsend;
	if (img.channels() == 1)
	{
		cv::cvtColor(img, imgsend, cv::COLOR_GRAY2BGR);
	}
	else if (img.channels() == 3)
	{
		cv::cvtColor(img, imgsend, cv::COLOR_BGR2RGB);
	}
	cv::resize(imgsend, imgsend, cv::Size(ss.width(), ss.height()));
	QImage disImage = QImage((const unsigned char*)(imgsend.data), imgsend.cols, imgsend.rows, imgsend.step, QImage::Format_RGB888);
	label->setPixmap(QPixmap::fromImage(disImage));
}