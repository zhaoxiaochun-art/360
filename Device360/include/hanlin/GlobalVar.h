#pragma once
#include <string>
//���ⲿ�豸plc����������ã���vnc��basler viewer���ã�Ҳ�����Լ������ù���ϵͳ��
//�˴�����ֻ����ҵ��(�㷨�����Ӷ��޷�)��ʵ�֡�
//�������ϵͳ�Ĳ������룬ֻ���������ҵ����صĲ�����
enum ALGTYPE
{
	CAPCHECK, FRONTCHECK
};

struct struSysConfig			//����ṹ����ȫ�ֵģ����Զ���һ��ȫ�ֱ�������궨��ķ�ʽ�����Ա������ֵ
{
	int n_CamNum;				//�������
	int n_PhotoTimes;			//ÿ�����һ���޷Ϲ�����ץ�ĵ�ͼ����
	struSysConfig()
	{
		n_CamNum = 5;
		n_PhotoTimes = 3;
	}
};
struct struPlcConn
{
	char Ipadd[16];				//Plc��ip��ַ
	int port;					//�˿ں�
	int iTimeOut;				//��������|����ʱ����
	int ul;						//��������ʽ����
	struPlcConn()
	{
		strncpy_s(Ipadd, "10.86.50.210", 16);
		port = 5000;
		iTimeOut = 100;
		ul = 0;	
	}
};
struct struCamInfo				//������ӳɹ���ͼ����Ϣ���ڲ���ȡ���Ƿ�Ҫ��ǰ���ô�����
								//�㷨ģ����õ�ͼ��ROI���ã�ROI�����û���Ҫ�õ�ͼ��Ĵ�С��Ϣ
{
	int n_CamID;				//���id����Ӧ�������λ�ã�POS��������Ŀȡֵ��Χ[0,5)
	int TypeOFCamera;			//����������ͣ�Ŀǰֻ��Basler
	char c_CameraName[16];		//������к�
	struCamInfo()
	{
		n_CamID = -1;
		TypeOFCamera = 0;
		c_CameraName[0]='\0';
	}
};
struct struAlgConfig
{
	int n_CamID;				//�����id��Ӧ��
	int algtype;				//�㷨���ͣ�����ĿΪCAPCHECK
	int SaveOKorNG;				//��ͼ���á�-1��ֻ��NGͼ��0��ȫ�����棻1��ֻ��OKͼ
	char f_resultImagePath[64];	//�㷨�������ͼ��ı���·��
	struAlgConfig()
	{
		n_CamID = -1;
		algtype = CAPCHECK;
		SaveOKorNG = 0;
		f_resultImagePath[0] = '\0';
	}
};
//ͳ�ƽ��
struct StruSummary
{
	char dateTime[32];			//����ʱ��
	char batchNumber[32];		//����
	int Allnum;					//����
	int OKnum;					//�ϸ���
	int OKrate;					//�ϸ���%
	int NGStyle;				//��Ʒ�ж����� �Ƿ���Ҫ�ڴ˽ṹ�����г����е�ȱ������
	int NGnum[64];     			//�ݶ������64�ַ�Ʒ��ÿ�������������У���vector�е��������㷨��Ա��

	StruSummary()
	{
		dateTime[0] = '\0';
		batchNumber[0] = '\0';
		Allnum = 0;
		OKnum = 0;
		OKrate = 0;
		NGStyle = 0;
		NGnum[64];
	}
};
//�㷨���ؽ��
struct struAlgResult
{
	int nCamID;					//�����id��Ӧ��
	int nPhotoTimes;			//���ÿ��ѭ��ץ�ĵ�ͼ��id
	int isKick[6];				//��Ӧͼ����6�������Ƿ��޷ϣ�0-���ޣ�1-�ޡ�
	int NGType[6];				//��Ʒ���ࡣ-2Ϊ�� -1Ϊ�ϸ� 0������Ϊ��Ʒ�����
	struAlgResult()
	{
		nCamID = -1;
		nPhotoTimes = -1;
		for (int k = 0; k < 6; k++)
		{
			isKick[k] = 0;
			NGType[k] = 0;
		}
	}
};
//����UI
struct StruUi
{
	char style[16];			    //������					
	int AutoRun;				//����Կ������������� 0����
	int AutoClose;				//���������ϵͳ�رն��ػ����� 0 ����
	StruUi()
	{
		style[0] = '\0';
		AutoRun = 0;
		AutoClose = 0;
	}
};
//���ڽ���չʾ,IFrameType = 3ΪBGRͼ��IFrameType = 1Ϊ�Ҷ�ͼ��
typedef void(__stdcall *UIDisplayCb)(int nCamID, int nPhotoTimes, unsigned char* pBuf,
	int IWidth, int IHeight, int IFrameType, void* pResult);

