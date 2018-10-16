
/*
* Agent层
* @date : 2018/09/21
* @author : jihang
*/

#include "stdafx.h"

#include <iostream>

#include "fedtime.hh"

#include "SimuFederateAgent.h"
#include "HLAPortInterface.h"

using namespace std;

//使用HLAPortInterfac句柄处理接收到的消息
extern CHLAPortInterface* pPortInterface;

SimuFederateAgent::SimuFederateAgent() {
	this->m_timeCurrent = 0.0;
	this->b_timeRegulated = false;
	this->b_timeConstrained = false;
	this->b_advancing = false;
	this->b_announced = false;
	this->b_readyToRun = false;
}

//时间转换
double SimuFederateAgent::convertTime(const RTI::FedTime& theTime) {
	RTIfedTime castedTime = (RTIfedTime)theTime;
	return castedTime.getTime();
}

//同步成功
void SimuFederateAgent::synchronizationPointRegistrationSucceeded(
	const char *label)
	throw (RTI::FederateInternalError) {
	cout << "#Agent# Successfully registered sync point: " << label << endl;
}

//同步失败
void SimuFederateAgent::synchronizationPointRegistrationFailed(
	const char *label)
	throw (RTI::FederateInternalError) {
	cout << "#Agent# Failed to register sync point: " << label << endl;
}

//声明同步
void SimuFederateAgent::announceSynchronizationPoint(
	const char *label, const char *tag)
	throw (RTI::FederateInternalError) {
	if (0 == strcmp(label, "ReadyToRun")) {
		this->b_announced = true;
	}
	cout << "#Agent# Synchronization point announced: " << label << endl;
}

//完成同步
void SimuFederateAgent::federationSynchronized(
	const char *label)
	throw (RTI::FederateInternalError) {
	if (0 == strcmp(label, "ReadyToRun")) {
		this->b_readyToRun = true;
	}
	cout << "#Agent# Federation Synchronized: " << label << endl;
}

//发现对象实例
void SimuFederateAgent::discoverObjectInstance(
	RTI::ObjectHandle theObject,
	RTI::ObjectClassHandle theObjectClass,
	const char * theObjectName)
	throw (RTI::CouldNotDiscover,
		RTI::ObjectClassNotKnown,
		RTI::FederateInternalError) {
	cout << "#Agent# Discoverd Object: handle = " << theObject <<
		". classHandle = " << theObjectClass << ". name = " << theObjectName << endl;
}

//接收对象类
void SimuFederateAgent::reflectAttributeValues(
	RTI::ObjectHandle theObject,
	const RTI::AttributeHandleValuePairSet& theAttributes,
	const char *theTag)
	throw (RTI::ObjectNotKnown,
		RTI::AttributeNotKnown,
		RTI::FederateOwnsAttributes,
		RTI::FederateInternalError) {
	pPortInterface->processData(theObject, theAttributes, theTag);
}

//删除对象实例
void SimuFederateAgent::removeObjectInstance(
	RTI::ObjectHandle theObject,
	const RTI::FedTime& theTime,
	const char *theTag,
	RTI::EventRetractionHandle theHandle)
	throw (RTI::ObjectNotKnown,
		RTI::InvalidFederationTime,
		RTI::FederateInternalError) {
	cout << "#Agent# Object Removed: handle = " << theObject << endl;
}

//删除对象实例
void SimuFederateAgent::removeObjectInstance(
	RTI::ObjectHandle theObject,
	const char *theTag)
	throw (RTI::ObjectNotKnown,
		RTI::FederateInternalError) {
	cout << "#Agent# Object Removed: handle = " << theObject << endl;
}

//时间受控
void SimuFederateAgent::timeRegulationEnabled(
	const RTI::FedTime& theFederateTime)
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeRegulationWasNotPending,
		RTI::FederateInternalError) {
	this->b_timeRegulated = true;
	m_timeCurrent = convertTime(theFederateTime);
}

//时间受限
void SimuFederateAgent::timeConstrainedEnabled(
	const RTI::FedTime& theFederateTime)
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeConstrainedWasNotPending,
		RTI::FederateInternalError) {
	this->b_timeConstrained = true;
	m_timeCurrent = convertTime(theFederateTime);

}

//时间推进
void SimuFederateAgent::timeAdvanceGrant(
	const RTI::FedTime& theTime)
	throw (RTI::InvalidFederationTime,
		RTI::TimeAdvanceWasNotInProgress,
		RTI::FederateInternalError) {
	this->b_advancing = false;
	m_timeCurrent = convertTime(theTime);
}