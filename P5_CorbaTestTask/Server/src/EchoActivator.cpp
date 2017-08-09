#include "EchoActivator.hpp"

#include <ComputeImpl.hpp>
#include <Logger.hpp>


EchoActivator::EchoActivator()
{
	CONSOLE("EchoActivator CONSTRUCTOR");
}

EchoActivator::~EchoActivator()
{
	CONSOLE("EchoActivator DESTRUCTOR");
}

PortableServer::Servant EchoActivator::incarnate(	const PortableServer::ObjectId& oid,
													PortableServer::POA_ptr adapter)
{
	CORBA::String_var objectId = PortableServer::ObjectId_to_string(oid);
	CONSOLE("EchoActivator INCARNATE, objectId=" << objectId);

	return new ComputeImpl();
}

void EchoActivator::etherealize(const PortableServer::ObjectId& oid,
								PortableServer::POA_ptr adapter,
								PortableServer::Servant serv,
								CORBA::Boolean cleanup_in_progress,
								CORBA::Boolean remaining_activations)
{
	CORBA::String_var objectId = PortableServer::ObjectId_to_string(oid);
	CONSOLE("EchoActivator ETHEREALIZE, objectId=" << objectId);

	serv->_remove_ref();
}

