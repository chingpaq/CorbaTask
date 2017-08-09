#pragma once


#include <tao/PortableServer/ServantActivatorC.h>


class EchoActivator:
	public PortableServer::ServantActivator
{
public:
	EchoActivator();
	virtual ~EchoActivator();

	virtual PortableServer::Servant incarnate(	const PortableServer::ObjectId& oid,
												PortableServer::POA_ptr adapter);
	virtual void etherealize(	const PortableServer::ObjectId& oid,
								PortableServer::POA_ptr adapter,
								PortableServer::Servant serv,
								CORBA::Boolean cleanup_in_progress,
								CORBA::Boolean remaining_activations);

};

