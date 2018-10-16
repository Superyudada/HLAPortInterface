#pragma once


/*
* Agent层
* @date : 2018/09/20
* @author : jihang
*/

#include <RTI.hh>
#include <NullFederateAmbassador.hh>

class SimuFederateAgent : public NullFederateAmbassador {

	//变量定义
public:
	//当前时间
	double m_timeCurrent;
	//时间受控
	bool b_timeRegulated;
	//时间受限
	bool b_timeConstrained;
	//是否允许步进
	bool b_advancing;
	//是否声明了同步点
	bool b_announced;
	//是否准备完成
	bool b_readyToRun;

	//构造/析构
public:
	SimuFederateAgent();
	~SimuFederateAgent() throw (RTI::FederateInternalError) {}

	//时间转换私有方法定义
private:
	double convertTime(const RTI::FedTime&);

	//RTI回调函数
public:
	//联邦管理服务，14个
	virtual void synchronizationPointRegistrationSucceeded(
		const char *label)
		throw (RTI::FederateInternalError);

	virtual void synchronizationPointRegistrationFailed(
		const char *label)
		throw (RTI::FederateInternalError);

	virtual void announceSynchronizationPoint(
		const char *label, const char *tag)
		throw (RTI::FederateInternalError);

	virtual void federationSynchronized(
		const char *label)
		throw (RTI::FederateInternalError);

	virtual void initiateFederateSave(
		const char *label)
		throw (RTI::UnableToPerformSave, RTI::FederateInternalError) {};

	virtual void federationSaved()
		throw (RTI::FederateInternalError) {};

	virtual void federationNotSaved()
		throw (RTI::FederateInternalError) {};

	virtual void requestFederationRestoreSucceeded(
		const char *label)
		throw (RTI::FederateInternalError) {};

	virtual void requestFederationRestoreFailed(
		const char *label)
		throw (RTI::FederateInternalError) {};

	virtual void requestFederationRestoreFailed(
		const char *label, const char *reason)
		throw (RTI::FederateInternalError) {};

	virtual void federationRestoreBegun()
		throw (RTI::FederateInternalError) {};

	virtual void initiateFederateRestore(
		const char *label, RTI::FederateHandle handle)
		throw (RTI::SpecifiedSaveLabelDoesNotExist,
			RTI::CouldNotRestore,
			RTI::FederateInternalError) {};

	virtual void federationRestored()
		throw (RTI::FederateInternalError) {};

	virtual void federationNotRestored()
		throw (RTI::FederateInternalError) {};

	//声明管理服务，4个
	virtual void startRegistrationForObjectClass(
		RTI::ObjectClassHandle theClass)
		throw (RTI::ObjectClassNotPublished,
			RTI::FederateInternalError) {};

	virtual void stopRegistrationForObjectClass(
		RTI::ObjectClassHandle theClass)
		throw (RTI::ObjectClassNotPublished,
			RTI::FederateInternalError) {};

	virtual void turnInteractionsOn(
		RTI::InteractionClassHandle theHandle)
		throw (RTI::InteractionClassNotPublished,
			RTI::FederateInternalError) {};

	virtual void turnInteractionsOff(
		RTI::InteractionClassHandle theHandle)
		throw (RTI::InteractionClassNotPublished,
			RTI::FederateInternalError) {};

	//对象管理服务，12个
	virtual void discoverObjectInstance(
		RTI::ObjectHandle theObject,
		RTI::ObjectClassHandle theObjectClass,
		const char * theObjectName)
		throw (RTI::CouldNotDiscover,
			RTI::ObjectClassNotKnown,
			RTI::FederateInternalError);

	virtual void reflectAttributeValues(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleValuePairSet& theAttributes,
		const RTI::FedTime& theTime,
		const char *theTag,
		RTI::EventRetractionHandle theHandle)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateOwnsAttributes,
			RTI::InvalidFederationTime,
			RTI::FederateInternalError) {};

	virtual void reflectAttributeValues(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleValuePairSet& theAttributes,
		const char *theTag)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateOwnsAttributes,
			RTI::FederateInternalError);

	virtual void receiveInteraction(
		RTI::InteractionClassHandle theInteraction,
		const RTI::ParameterHandleValuePairSet& theParameters,
		const RTI::FedTime& theTime,
		const char *theTag,
		RTI::EventRetractionHandle theHandle)
		throw (RTI::InteractionClassNotKnown,
			RTI::InteractionParameterNotKnown,
			RTI::InvalidFederationTime,
			RTI::FederateInternalError) {};

	virtual void receiveInteraction(
		RTI::InteractionClassHandle theInteraction,
		const RTI::ParameterHandleValuePairSet& theParameters,
		const char *theTag)
		throw (RTI::InteractionClassNotKnown,
			RTI::InteractionParameterNotKnown,
			RTI::FederateInternalError) {};

	virtual void removeObjectInstance(
		RTI::ObjectHandle theObject,
		const RTI::FedTime& theTime,
		const char *theTag,
		RTI::EventRetractionHandle theHandle)
		throw (RTI::ObjectNotKnown,
			RTI::InvalidFederationTime,
			RTI::FederateInternalError);

	virtual void removeObjectInstance(
		RTI::ObjectHandle theObject,
		const char *theTag)
		throw (RTI::ObjectNotKnown,
			RTI::FederateInternalError);

	virtual void attributesInScope(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateInternalError) {};

	virtual void attributesOutOfScope(
		RTI::ObjectHandle heObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateInternalError) {};

	virtual void provideAttributeValueUpdate(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeNotOwned,
			RTI::FederateInternalError) {};

	virtual void turnUpdatesOnForObjectInstance(
		RTI::ObjectHandle heObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotOwned,
			RTI::FederateInternalError) {};

	virtual void turnUpdatesOffForObjectInstance(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotOwned,
			RTI::FederateInternalError) {};

	//所有权管理服务，9个
	virtual void requestAttributeOwnershipAssumption(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& offeredAttributes,
		const char *theTag)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeAlreadyOwned,
			RTI::AttributeNotPublished,
			RTI::FederateInternalError) {};

	virtual void attributeOwnershipDivestitureNotification(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& releasedAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeNotOwned,
			RTI::AttributeDivestitureWasNotRequested,
			RTI::FederateInternalError) {};

	virtual void attributeOwnershipAcquisitionNotification(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& securedAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeAcquisitionWasNotRequested,
			RTI::AttributeAlreadyOwned,
			RTI::AttributeNotPublished,
			RTI::FederateInternalError) {};

	virtual void attributeOwnershipUnavailable(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeAlreadyOwned,
			RTI::AttributeAcquisitionWasNotRequested,
			RTI::FederateInternalError) {};

	virtual void requestAttributeOwnershipRelease(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& candidateAttributes,
		const char *theTag)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeNotOwned,
			RTI::FederateInternalError) {};

	virtual void confirmAttributeOwnershipAcquisitionCancellation(
		RTI::ObjectHandle theObject,
		const RTI::AttributeHandleSet& theAttributes)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::AttributeAlreadyOwned,
			RTI::AttributeAcquisitionWasNotCanceled,
			RTI::FederateInternalError) {};

	virtual void informAttributeOwnership(
		RTI::ObjectHandle theObject,
		RTI::AttributeHandle theAttribute,
		RTI::FederateHandle theOwner)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateInternalError) {};

	virtual void attributeIsNotOwned(
		RTI::ObjectHandle theObject,
		RTI::AttributeHandle theAttribute)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateInternalError) {};

	virtual void attributeOwnedByRTI(
		RTI::ObjectHandle theObject,
		RTI::AttributeHandle theAttribute)
		throw (RTI::ObjectNotKnown,
			RTI::AttributeNotKnown,
			RTI::FederateInternalError) {};

	//时间管理服务，4个
	virtual void timeRegulationEnabled(
		const RTI::FedTime& theFederateTime)
		throw (RTI::InvalidFederationTime,
			RTI::EnableTimeRegulationWasNotPending,
			RTI::FederateInternalError);

	virtual void timeConstrainedEnabled(
		const RTI::FedTime& theFederateTime)
		throw (RTI::InvalidFederationTime,
			RTI::EnableTimeConstrainedWasNotPending,
			RTI::FederateInternalError);

	virtual void timeAdvanceGrant(
		const RTI::FedTime& theTime)
		throw (RTI::InvalidFederationTime,
			RTI::TimeAdvanceWasNotInProgress,
			RTI::FederateInternalError);

	virtual void requestRetraction(
		RTI::EventRetractionHandle theHandle)
		throw (RTI::EventNotKnown,
			RTI::FederateInternalError) {};
};