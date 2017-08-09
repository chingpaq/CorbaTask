#pragma once


#include <tao/PortableServer/ServantLocatorC.h>


class EchoLocator:
	public PortableServer::ServantLocator
{
public:
	EchoLocator();
	virtual ~EchoLocator();

	virtual PortableServer::Servant preinvoke(	const PortableServer::ObjectId& oid,
												PortableServer::POA_ptr adapter,
												const char* operation,
												PortableServer::ServantLocator::Cookie& the_cookie);
	virtual void postinvoke(const PortableServer::ObjectId& oid,
							PortableServer::POA_ptr adapter,
							const char* operation,
							PortableServer::ServantLocator::Cookie the_cookie,
							PortableServer::Servant the_servant);

};

