#pragma once

#ifdef JSONDLL_EXPORTS
#define JSONDLL_API __declspec(dllexport)
#else
#define JSONDLL_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <json.h>
#include <cassert>
#include <errno.h>
#include <string.h>
#include "GlobalVar.h"
using namespace std;
// 此类是从 dll 导出的
class JSONDLL_API JsonCommand {
public:
	Json::Value root;
	struCamInfo SCI;
	string ReadJsonFromFile(string RootNode, string SonNode, string DefaultValue);
	string ReadJsonFromFile(string RootNode, string DefaultValue);
	int ReadJsonFromFile(string RootNode, string SonNode, int DefaultValue);
	int ReadJsonFromFile(string RootNode, int DefaultValue);
	void ReadJsonFromFile(char *param, string value);
	int *LoopReadJson(string RootNode, string SonNode, int DefaultValue[]);
	string *LoopReadJson(string RootNode, string SonNode, string DefaultValue[],string *p);
	Json::Value WriteFileJson(string RootNode, string SonNode, string Value);
	Json::Value WriteFileJson(string RootNode, string SonNode, int Value);
	Json::Value WriteFileJson(string RootNode, string Value);
	Json::Value WriteFileJson(string RootNode, int Value);
	void SaveFileJson(string FileName);
	void InitRead();
	void InitWrite();
	JsonCommand(string FileName);
	~JsonCommand();
	// TODO: 在此处添加方法。
};



