#pragma once
#include <string>
//对外部设备plc和相机的设置，有vnc和basler viewer可用，也可以自己做配置管理系统。
//此处我们只关心业务(算法分析从而剔废)的实现。
//所以软件系统的参数导入，只考虑与软件业务相关的参数。
enum ALGTYPE
{
	CAPCHECK, FRONTCHECK
};

struct struSysConfig			//这个结构体是全局的，可以定义一个全局变量，或宏定义的方式给其成员变量赋值
{
	int n_CamNum;				//相机数量
	int n_PhotoTimes;			//每个相机一次剔废过程内抓拍的图像数
	struSysConfig()
	{
		n_CamNum = 5;
		n_PhotoTimes = 3;
	}
};
struct struPlcConn
{
	char Ipadd[16];				//Plc的ip地址
	int port;					//端口号
	int iTimeOut;				//心跳发送|接收时间间隔
	int ul;						//非阻塞方式连接
	struPlcConn()
	{
		strncpy_s(Ipadd, "10.86.50.210", 16);
		port = 5000;
		iTimeOut = 100;
		ul = 0;	
	}
};
struct struCamInfo				//相机连接成功后，图像信息可内部获取，是否要提前设置待定。
								//算法模块会用到图像ROI设置，ROI的设置会需要用到图像的大小信息
{
	int n_CamID;				//相机id，对应了相机的位置（POS），本项目取值范围[0,5)
	int TypeOFCamera;			//相机厂商类型，目前只有Basler
	char c_CameraName[16];		//相机序列号
	struCamInfo()
	{
		n_CamID = -1;
		TypeOFCamera = 0;
		c_CameraName[0]='\0';
	}
};
struct struAlgConfig
{
	int n_CamID;				//与相机id对应。
	int algtype;				//算法类型，本项目为CAPCHECK
	int SaveOKorNG;				//存图设置。-1：只存NG图，0：全部保存；1：只存OK图
	char f_resultImagePath[64];	//算法分析结果图像的保存路径
	struAlgConfig()
	{
		n_CamID = -1;
		algtype = CAPCHECK;
		SaveOKorNG = 0;
		f_resultImagePath[0] = '\0';
	}
};
//统计结果
struct StruSummary
{
	char dateTime[32];			//日期时间
	char batchNumber[32];		//批号
	int Allnum;					//总数
	int OKnum;					//合格数
	int OKrate;					//合格率%
	int NGStyle;				//废品有多少种 是否需要在此结构体罗列出所有的缺陷类型
	int NGnum[64];     			//暂定最多有64种废品，每种数量放入其中，在vector中的排序由算法人员定

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
//算法返回结果
struct struAlgResult
{
	int nCamID;					//与相机id对应。
	int nPhotoTimes;			//相机每次循环抓拍的图像id
	int isKick[6];				//对应图像中6个胶囊是否剔废：0-不剔，1-剔。
	int NGType[6];				//废品种类。
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
//界面UI
struct StruUi
{
	char style[16];			    //界面风格					
	int AutoRun;				//随电脑开机自启动功能 0不随
	int AutoClose;				//电脑随软件系统关闭而关机功能 0 不随
	StruUi()
	{
		style[0] = '\0';
		AutoRun = 0;
		AutoClose = 0;
	}
};
//用于界面展示,IFrameType = 3为BGR图像，IFrameType = 1为灰度图像
typedef void(__stdcall *UIDisplayCb)(int nCamID, int nPhotoTimes, unsigned char* pBuf,
	int IWidth, int IHeight, int IFrameType, void* pResult);

