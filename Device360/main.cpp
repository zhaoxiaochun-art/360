#include "Device360.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>
#include "WindowOut.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSharedMemory mem("360");//��ϵͳexe����Ϊ���������干���ڴ�mem
	WindowOut* levelOut = new WindowOut();
	levelOut->setWindowCount(0);//����������������ֹ����
	if (!mem.create(1))//���������ڴ�mem������ù����ڴ��Ѵ��ڣ��򵯳���ʾ�Ի��򣬲��˳�
	{
		levelOut->getString(QString::fromLocal8Bit("ϵͳ������һʵ���������ظ�������"), 2000);
		levelOut->exec();
		return 0;
	}

    Device360 w;
    w.show();
    return a.exec();
}
