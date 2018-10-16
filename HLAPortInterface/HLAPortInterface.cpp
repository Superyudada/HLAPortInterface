// HLAPortInterface.cpp : 定义 DLL 应用程序的导出函数。

/*
* Interface层
* @date : 2018/09/23
* @author : jihang
*/

#include "stdafx.h"
#include "HLAPortInterface.h"

#include <iostream>

#include "fedtime.hh"

#include "SimuFederateAgent.h"

using namespace std;

//联邦大使
SimuFederateAgent *m_fedAgt;
//RTI大使
RTI::RTIambassador *m_rtiAmb;
//给联邦大使用的接口句柄
CHLAPortInterface *pPortInterface;
//联邦名
string m_federationName;
//前瞻量
double m_lookahead;

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 HLAPortInterface.h
CHLAPortInterface::CHLAPortInterface() {
	m_fedAgt = new SimuFederateAgent();
	m_rtiAmb = new RTI::RTIambassador();
	pPortInterface = this;
	m_federationName = "TempName";
}

bool CHLAPortInterface::createFederation(string fedFile, string federationName) {
	if (!federationName.empty()) {
		m_federationName = federationName;
		try {
			m_rtiAmb->createFederationExecution(federationName.c_str(), fedFile.c_str());
			cout << "#Interface# Created Federation " << m_federationName.c_str() << endl;
			return true;
		}
		catch (RTI::FederationExecutionAlreadyExists exists) {
			cout << "#Interface# Didn't create federation, it already existed." << endl;
			return false;
		}
	}
	else {
		cout << "#Interface# Federation Name Not Given." << endl;
		return false;
	}
}

long CHLAPortInterface::joinFederation(string federateName, string federationName) {
	long objectHandle = m_rtiAmb->joinFederationExecution(
		federateName.c_str(), federationName.c_str(), m_fedAgt);
	if (objectHandle != -1) {
		cout << "#Interface# Joined Federation as " << federateName.c_str() << endl;
	}
	return objectHandle;
}

bool CHLAPortInterface::resignFederation() {
	m_rtiAmb->resignFederationExecution(RTI::NO_ACTION);
	cout << "#Interface# Resigned from Federation" << endl;
	return true;
}

bool CHLAPortInterface::destroyFederation(string federationName) {
	try {
		m_rtiAmb->destroyFederationExecution(federationName.c_str());
		cout << "#Interface# Destroyed Federation" << endl;
	}
	catch (RTI::FederationExecutionDoesNotExist dne) {
		cout << "#Interface# No need to destroy federation, it doesn't exist" << endl;
	}
	catch (RTI::FederatesCurrentlyJoined fcj) {
		cout << "#Interface# Didn't destroy federation, federates still joined" << endl;
	}
	delete m_fedAgt;
	delete m_rtiAmb;
	return true;
}

ObjectHandles* CHLAPortInterface::initOneHandle(ObjectNames objectNames) {
	ObjectHandles *objectHandles = new ObjectHandles();
	if (objectNames.attributeNumber != objectNames.attributeList.size()) {
		cout << "#Interface# Initialize Handles Size Wrong" << endl;
	}
	objectHandles->classHandle =
		m_rtiAmb->getObjectClassHandle(objectNames.className.c_str());
	int i = 0;
	for (i = 0; i < objectNames.attributeNumber; ++i) {
		RTI::AttributeHandle handle = m_rtiAmb->getAttributeHandle(
			objectNames.attributeList[i].c_str(), objectHandles->classHandle);
		objectHandles->handleList.push_back(handle);
	}
	objectHandles->handleNumber = i;
	return objectHandles;
}

bool CHLAPortInterface::registerSynchronization(string label) {
	m_rtiAmb->registerFederationSynchronizationPoint(label.c_str(), "");
	while (false == m_fedAgt->b_announced) {
		m_rtiAmb->tick();
	}
	return true;
}

bool CHLAPortInterface::synchronizationAchieved(string label) {
	m_rtiAmb->synchronizationPointAchieved(label.c_str());
	cout << "#Interface# Achieved sync point: " <<
		label.c_str() << ", waiting for federation..." << endl;
	while (false == m_fedAgt->b_readyToRun) {
		m_rtiAmb->tick();
	}
	return true;
}

bool CHLAPortInterface::enableTimePolicy(double lookahead) {
	RTIfedTime federateTime = m_fedAgt->m_timeCurrent;
	m_lookahead = lookahead;
	m_rtiAmb->enableTimeRegulation(federateTime, (RTIfedTime)lookahead);
	while (false == m_fedAgt->b_timeRegulated) {
		m_rtiAmb->tick();
	}
	m_rtiAmb->enableTimeConstrained();
	while (false == m_fedAgt->b_timeConstrained) {
		m_rtiAmb->tick();
	}
	cout << "#Interface# Time Policy Enabled" << endl;
	return true;
}

bool CHLAPortInterface::publishOne(ObjectHandles* objectHandles) {
	int number = objectHandles->handleNumber;
	if (number != objectHandles->handleList.size()) {
		cout << "#Interface# Publish Size Wrong." << endl;
	}
	RTI::AttributeHandleSet *attributes =
		RTI::AttributeHandleSetFactory::create(number);
	for (int i = 0; i < number; ++i) {
		attributes->add(objectHandles->handleList[i]);
	}
	m_rtiAmb->publishObjectClass(objectHandles->classHandle, *attributes);
	delete attributes;
	return true;
}

bool CHLAPortInterface::subscribeOne(ObjectHandles* objectHandles) {
	int number = objectHandles->handleNumber;
	if (number != objectHandles->handleList.size()) {
		cout << "#Interface# Subscribe Size Wrong." << endl;
	}
	RTI::AttributeHandleSet *attributes =
		RTI::AttributeHandleSetFactory::create(number);
	for (int i = 0; i < number; ++i) {
		attributes->add(objectHandles->handleList[i]);
	}
	m_rtiAmb->subscribeObjectClassAttributes(objectHandles->classHandle, *attributes);
	delete attributes;
	return true;
}

RTI::ObjectHandle CHLAPortInterface::registerObject(string className) {
	return m_rtiAmb->registerObjectInstance(
		m_rtiAmb->getObjectClassHandle(className.c_str()));
}

bool CHLAPortInterface::sendObject(RTI::ObjectHandle objectHandle,
	RTI::AttributeHandleValuePairSet* attributes) {
	m_rtiAmb->updateAttributeValues(objectHandle, *attributes, "hi!");
	delete attributes;
	return true;
}

bool CHLAPortInterface::advanceTime(double timestep) {
	RTIfedTime newTime = (m_fedAgt->m_timeCurrent + timestep);
	m_fedAgt->b_advancing = true;
	m_rtiAmb->timeAdvanceRequest(newTime);
	cout << "Current Time : " << newTime << endl;
	while (m_fedAgt->b_advancing) {
		m_rtiAmb->tick();
	}
	return true;
}

bool CHLAPortInterface::deleteOne(RTI::ObjectHandle objectHandle) {
	m_rtiAmb->deleteObjectInstance(objectHandle, NULL);
	cout << "#Interface# Deleted Object, handle = " << objectHandle << endl;
	return true;
}

RTI::ObjectClassHandle CHLAPortInterface::getObjectClass(RTI::ObjectHandle objectHandle) {
	return m_rtiAmb->getObjectClass(objectHandle);
}