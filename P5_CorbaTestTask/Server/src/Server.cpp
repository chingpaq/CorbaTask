#include <tao/corba.h>
#include <tao/PortableServer/PortableServer.h>
#include <orbsvcs/CosNamingC.h>

#include "EchoActivator.hpp"
#include "EchoLocator.hpp"
//#include "ComputeImpl.hpp"

#include <Logger.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <Constants.hpp>
#include <boost/thread.hpp>


//Comment line below to use ServantActivator instead of ServantLocator
#define USE_LOCATOR


CORBA::ORB_var theORB;


void orbRun()
{
	theORB->run();
}


int main(int argc, char* argv[])
{
	try
	{
		CONSOLE("Initialize ORB");

		theORB = CORBA::ORB_init(argc,argv);
		CONSOLE("Obtain RootPOA");
		CORBA::Object_var rootPOARef = theORB->resolve_initial_references("RootPOA");
		PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(rootPOARef.in());

		CONSOLE("Obtain POAManager");
		PortableServer::POAManager_var poaManager = rootPOA->the_POAManager();

		CONSOLE("Obtain NameService");
		CORBA::Object_var nameServiceRef = theORB->resolve_initial_references("NameService");
		CosNaming::NamingContext_var nameService = CosNaming::NamingContext::_narrow(nameServiceRef.in());


		//////////////////////////
		CONSOLE("Create new POA");
		CORBA::PolicyList policies;
		policies.length(2);

#ifdef USE_LOCATOR
		policies[0] = rootPOA->create_servant_retention_policy(PortableServer::NON_RETAIN);
#else
		policies[0] = rootPOA->create_servant_retention_policy(PortableServer::RETAIN);
#endif

		policies[1] = rootPOA->create_request_processing_policy(PortableServer::USE_SERVANT_MANAGER);

		PortableServer::POA_var newPOA = rootPOA->create_POA("ServantManager_POA", poaManager.in(), policies);

		//Destroy policies...
		for(CORBA::ULong i = 0; i < policies.length(); ++i)
		{
			policies[i]->destroy();
		}

		CONSOLE("Create servant manager reference");
		PortableServer::ObjectId_var servantManagerId = PortableServer::string_to_ObjectId("Compute manager");
		CORBA::Object_var servantManagerRef = newPOA->create_reference_with_id(servantManagerId.in(), "IDL:CORBATestTask/Compute:1.0");

		CONSOLE("Bind servant manager reference to NameService");
		CosNaming::Name name;
		name.length(1);
		name[0].id = constants::ECHO_SERVER.c_str();
		name[0].kind = "";

		nameService->rebind(name, servantManagerRef.in());

		CONSOLE("Set servant manager in new POA");

#ifdef USE_LOCATOR
		PortableServer::ServantManager_var echoManager = new EchoLocator();
#else
		PortableServer::ServantManager_var echoManager = new EchoActivator();
#endif

		newPOA->set_servant_manager(echoManager.in());
		//////////////////

//2nd method
//		////////////////////
//		CONSOLE("Construct servant");
//		ComputeImpl* computeImpl = new ComputeImpl();
//
//
//		CONSOLE("Activate servant in POA");
//		PortableServer::ObjectId_var computeImplId = rootPOA->activate_object(computeImpl);
//
//
//		computeImpl->_remove_ref();
//
//
//		CONSOLE("Bind servant reference to NameService");
//		CosNaming::Name name;
//		name.length(1);
//		name[0].id = "ECHO_SERVER";
//		name[0].kind = "";
//
//		CORBA::Object_var computeRef=rootPOA->servant_to_reference(computeImpl);
//		nameService->rebind(name, computeRef.in());
//
//		///////////////////




		CONSOLE("Activate POAManager");
		poaManager->activate();


		CONSOLE("Start ORB thread");
		boost::thread orbThread(orbRun);

		CONSOLE("Server READY. Press ENTER to exit");
		std::cin.get();


		CONSOLE("Shutting down...");

		CONSOLE("Unbind servant manager reference from NameService");
		nameService->unbind(name);

		sleep(1);

		CONSOLE("Shutdown ORB");
		theORB->shutdown(false);

		CONSOLE("Join ORB thread");
		orbThread.join();

		CONSOLE("Destroy ORB");
		theORB->destroy();
	}
	catch(const CORBA::Exception& e)
	{
		CONSOLE("CORBA::Exception: " << e);
	}
	catch(const std::exception& e)
	{
		CONSOLE("std::exception: " << e.what());
	}

	return 0;
}

