#pragma once
#ifndef SVC_CTRL_H
#define SVC_CTRL_H

#if defined(SVC_CTRL_LIBRARY)
#  define SVC_CTRL_EXPORT __declspec(dllexport)
#else
#  define SVC_CTRL_EXPORT __declspec(dllimport)
#endif

#include "GlobalVar.h"

class SVC_CTRL_EXPORT CServiceCtrl
{
public:
	int SysInit(struPlcConn* p_stru_PlcConn, struCamInfo* pCamInfo, struAlgConfig *ptrAlgConfig);
	int SysStartWork(UIDisplayCb DisplayCbFun);
	int SysStopWork();
	int SysUnInit();
};
#endif

