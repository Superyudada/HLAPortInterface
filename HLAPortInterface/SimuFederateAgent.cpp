
/*
* Agent��
* @date : 2018/09/21
* @author : jihang
*/

#include "stdafx.h"

#include <iostream>

#include "fedtime.hh"

#include "SimuFederateAgent.h"
#include "HLAPortInterface.h"

using namespace std;

//ʹ��HLAPortInterfac���������յ�����Ϣ
extern CHLAPortInterface* pPortInterface;

SimuFederateAgent::SimuFederateAgent() {
	this->m_timeCurrent = 0.0;
	this->b_timeRegulated = false;
	this->b_timeConstrained = false;
	this->b_advancing = false;
	this->b_announced = false;
	this->b_readyToRun = false;
}

//ʱ��ת��
double SimuFederateAgent::convertTime(const RTI::FedTime& theTime) {
	RTIfedTime castedTime = (RTIfedTime)theTime;
	return castedTime.getTime();
}

//ͬ���ɹ�
void SimuFederateAgent::synchronizationPointRegistrationSucceeded(
	const char *label)
	throw (RTI::FederateInternalError) {
	cout << "#Agent# Successfully registered sync point: " << label << endl;
}

//ͬ��ʧ��
void SimuFederateAgent::synchronizationPointRegistrationFailed(
	const char *label)
	throw (RTI::FederateInternalError) {
	cout << "#Agent# Failed to register sync point: " << label << endl;
}

//����ͬ��
void SimuFederateAgent::announceSynchronizationPoint(
	const char *label, const char *tag)
	throw (RTI::FederateInternalError) {
	if (0 == strcmp(label, "ReadyToRun")) {
		this->b_announced = true;
	}
	cout << "#Agent# Synchronization point announced: " << label << endl;
}

//���ͬ��
void SimuFederateAgent::federationSynchronized(
	const char *label)
	throw (RTI::FederateInternalError) {
	if (0 == strcmp(label, "ReadyToRun")) {
		this->b_readyToRun = true;
	}
	cout << "#Agent# Federation Synchronized: " << label << endl;
}

//���ֶ���ʵ��
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

//���ն�����
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

//ɾ������ʵ��
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

//ɾ������ʵ��
void SimuFederateAgent::removeObjectInstance(
	RTI::ObjectHandle theObject,
	const char *theTag)
	throw (RTI::ObjectNotKnown,
		RTI::FederateInternalError) {
	cout << "#Agent# Object Removed: handle = " << theObject << endl;
}

//ʱ���ܿ�
void SimuFederateAgent::timeRegulationEnabled(
	const RTI::FedTime& theFederateTime)
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeRegulationWasNotPending,
		RTI::FederateInternalError) {
	this->b_timeRegulated = true;
	m_timeCurrent = convertTime(theFederateTime);
}

//ʱ������
void SimuFederateAgent::timeConstrainedEnabled(
	const RTI::FedTime& theFederateTime)
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeConstrainedWasNotPending,
		RTI::FederateInternalError) {
	this->b_timeConstrained = true;
	m_timeCurrent = convertTime(theFederateTime);

}

//ʱ���ƽ�
void SimuFederateAgent::timeAdvanceGrant(
	const RTI::FedTime& theTime)
	throw (RTI::InvalidFederationTime,
		RTI::TimeAdvanceWasNotInProgress,
		RTI::FederateInternalError) {
	this->b_advancing = false;
	m_timeCurrent = convertTime(theTime);
}