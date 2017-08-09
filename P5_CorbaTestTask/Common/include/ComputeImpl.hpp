#pragma once


#include <CORBATestTask_skel.h>


class ComputeImpl:
	public POA_CORBATestTask::Compute,
	public PortableServer::RefCountServantBase
{
public:
	ComputeImpl();
	virtual ~ComputeImpl();
	virtual void computeUsingParameters (
		      ::CORBA::ULong id,
		      ::CORBA::ULong integer1,
		      ::CORBA::ULong integer2,
		      const char * operation,
		      ::CORBATestTask::TaskData_out resultsData);
};

