#include "Device360.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>
#include <QStyleFactory>
#include "WindowOut.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSharedMemory mem("360");//以系统exe名称为参数，定义共享内存mem
	WindowOut* levelOut = new WindowOut();
	levelOut->setWindowCount(0);//动画窗弹出数，防止覆盖
	if (!mem.create(1))//创建共享内存mem，如果该共享内存已存在，则弹出提示对话框，并退出
	{
		levelOut->getString(QString::fromLocal8Bit("系统已运行一实例，请勿重复开启！"), 2000);
		levelOut->exec();
		return 0;
	}

	QApplication::setStyle(QStyleFactory::create("fusion"));//界面风格

    Device360 w;
    w.show();
    return a.exec();
}
