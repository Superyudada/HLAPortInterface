#pragma once

/*
* 配置类
* @date : 2018/09/24
* @author : jihang
*/

#include <vector>

#include "RTI.hh"

using namespace std;

//对象类名
class ObjectNames {
public:
	string className;
	int attributeNumber;
	vector<string> attributeList;
};

//对象类句柄
class ObjectHandles {
public:
	RTI::ObjectClassHandle classHandle;
	int handleNumber;
	vector<RTI::AttributeHandle> handleList;
};