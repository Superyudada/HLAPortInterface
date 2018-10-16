// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HLAPORTINTERFACE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HLAPORTINTERFACE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

/*
* Interface层
* @date : 2018/09/22
* @author : jihang
*/

#include "config.h"

using namespace std;

#ifdef HLAPORTINTERFACE_EXPORTS
#define HLAPORTINTERFACE_API __declspec(dllexport)
#else
#define HLAPORTINTERFACE_API __declspec(dllimport)
#endif

// 此类是从 HLAPortInterface.dll 导出的
class HLAPORTINTERFACE_API CHLAPortInterface {
public:
	//构造/析构
public:
	CHLAPortInterface();
	virtual ~CHLAPortInterface() {};

	//状态
public:
	bool isPause;
	bool isEnd;

	//接口方法
public:
	//创建联邦
	bool createFederation(string fedFile, string federationName);
	//加入联邦，返回联邦成员ID，失败返回-1，默认加入fed文件中定义的联邦名称
	long joinFederation(string federateName, string federationName = "");
	//退出联邦
	bool resignFederation();
	//撤销联邦，默认销毁fed文件中定义的联邦名称
	bool destroyFederation(string federationName = "");
	//初始化句柄，目前仅限对象类，仅限一条
	ObjectHandles* initOneHandle(ObjectNames);
	//注册联邦同步点
	bool registerSynchronization(string label);
	//运行到同步点
	bool synchronizationAchieved(string label);
	//设置时间策略
	bool enableTimePolicy(double lookahead);
	//发布对象类，目前仅限对象类，仅限一条
	bool publishOne(ObjectHandles*);
	//订阅对象类，目前仅限对象类，仅限一条
	bool subscribeOne(ObjectHandles*);
	//注册对象类
	RTI::ObjectHandle registerObject(string className);
	//发送对象类，目前仅限对象类
	bool sendObject(RTI::ObjectHandle, RTI::AttributeHandleValuePairSet*);
	//接收对象类,目前仅限对象类
	virtual void processData(RTI::ObjectHandle,
		const RTI::AttributeHandleValuePairSet&, const char*) = 0;
	//时间步进
	bool advanceTime(double timestep);
	//删除对象类，目前仅限对象类
	bool deleteOne(RTI::ObjectHandle);
	//通过类句柄定位对象类
	RTI::ObjectClassHandle getObjectClass(RTI::ObjectHandle objectHandle);
};
