#include "EchoLocator.hpp"

#include <ComputeImpl.hpp>
#include <Logger.hpp>


EchoLocator::EchoLocator()
{
	CONSOLE("EchoLocator CONSTRUCTOR");
}

EchoLocator::~EchoLocator()
{
	CONSOLE("EchoLocator DESTRUCTOR");
}

PortableServer::Servant EchoLocator::preinvoke(	const PortableServer::ObjectId& oid,
												PortableServer::POA_ptr adapter,
												const char* operation,
												PortableServer::ServantLocator::Cookie& the_cookie)
{
	CORBA::String_var objectId = PortableServer::ObjectId_to_string(oid);
	CONSOLE("EchoLocator PREINVOKE, objectId=" << objectId);

	return new ComputeImpl();
}

void EchoLocator::postinvoke(	const PortableServer::ObjectId& oid,
								PortableServer::POA_ptr adapter,
								const char* operation,
								PortableServer::ServantLocator::Cookie the_cookie,
								PortableServer::Servant the_servant)
{
	CORBA::String_var objectId = PortableServer::ObjectId_to_string(oid);
	CONSOLE("EchoLocator POSTINVOKE, objectId=" << objectId);

	the_servant->_remove_ref();
}

