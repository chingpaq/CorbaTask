#include <tao/corba.h>
#include <orbsvcs/CosNamingC.h>


#include <CORBATestTask.h>
#include <Logger.hpp>

#include <vector>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/random.hpp>
#include <stdlib.h>
#include <Constants.hpp>

int count=5;
struct entries
{
	unsigned int	id;
	CORBA::String_var  operation;
	unsigned int random1;
	unsigned int random2;

};

void corbaWorkerFuncWithId(CORBATestTask::Compute_ptr server,entries the_data)
{

    boost::posix_time::seconds workTime(1);
    boost::this_thread::sleep(workTime);

    CORBATestTask::TaskData_var resultsHere;

    server->computeUsingParameters(the_data.id,the_data.random1,the_data.random2,the_data.operation,resultsHere.out());

    std::cout << std::endl << "Client worker: Received response from Server-> " << resultsHere->id << ": " <<
    		resultsHere->integer1 << " " << resultsHere->operation << " " << resultsHere->integer2 << " = " << resultsHere->results << std::endl;

}

CORBA::ORB_var theORB;


int main(int argc, char* argv[])
{
	std::cout << "main: startup" << std::endl;
	std::cout << "Please enter " << count << " operations. Select from (+ - / *)" << std::endl << std::endl;
			std::vector <entries>data_array;

			// get the inputs

	for (int i=0;i<count;i++)
				    {
						int random1 = rand()%100;
						int random2= rand() %100;

						CORBA::String_var operation;

						std::cout << std::endl << "Random numbers chosen are "<< random1 << " and " << random2 << "! Select an operation to perform on these numbers: ";

						std::string operation_as_string;
						std::cin >> operation_as_string;

						operation = CORBA::string_dup(operation_as_string.c_str());

				    	entries myData;

				    	myData.id = i+1;
				    	myData.operation = operation;
				    	myData.random1 = random1;
				    	myData.random2 = random2;

				    	data_array.push_back(myData);
				    }

	try
	{
		CONSOLE(" ");
		CONSOLE("Initialize ORB");
		theORB = CORBA::ORB_init(argc, argv);

		CONSOLE("Obtain NameService");
		CORBA::Object_var nameServiceRef = theORB->resolve_initial_references("NameService");
		CosNaming::NamingContext_var nameService = CosNaming::NamingContext::_narrow(nameServiceRef.in());

		CONSOLE("Obtain Server reference from NameService");
		CosNaming::Name name;
		name.length(1);
		name[0].id = constants::ECHO_SERVER.c_str();
		name[0].kind = "";

		CORBA::Object_var serverRef = nameService->resolve(name);
		CORBATestTask::Compute_var server = CORBATestTask::Compute::_narrow(serverRef.in());

		//fire the worker threads
		for (int i=0;i< count;i++)
		{
			boost::thread workerThread(corbaWorkerFuncWithId,server.in(),data_array[i]);
			workerThread.join();


		}


		CONSOLE("Shutdown ORB");
		theORB->shutdown(false);

		CONSOLE("Destroy ORB");
		theORB->destroy();
	}
	catch(const CORBA::Exception& e)
	{
		CONSOLE("CORBA::Exception: " << e);
	}
	std::cout << std::endl << "Thank you for trying" << std::endl;


	return 0;
}









//
//
//#include <iostream>
//#include <boost/thread.hpp>
//#include <boost/date_time.hpp>
//#include <boost/random.hpp>
//#include <boost/generator_iterator.hpp>
//
//int count=15;
//
//void workerFuncWithId(int id, int time)
//{
//    boost::posix_time::seconds workTime(time);
//
//    std::cout << "Worker " << id << "-"<< time <<": starting" << std::endl;
//
//    // Pretend to do something useful...
//    boost::this_thread::sleep(workTime);
//
//    std::cout << "Worker " << id << "-"<< time <<": finishes" << std::endl;
//
//    if (time == count-1)
//    {
//    	std::cout << "Last Worker " << id << "-"<< time << "!!! Type anything and press <Enter> to exit" << std::endl;
//    }
//
//}
//
//
//
//int main(int argc, char* argv[])
//{
//    std::cout << "main: startup" << std::endl;
//
//
//    typedef boost::mt19937 RNGType;
//
//    RNGType rng(time(0));
//    boost::uniform_int<>eight_to_thirteen(8,130);
//    boost::variate_generator< RNGType, boost::uniform_int<>>dice(rng,eight_to_thirteen);
//
//
//    for (int i=0;i<count;i++)
//    {
//    	boost::thread workerThread(workerFuncWithId,dice(),i);
//    }
//
//    std::cout << "main: waiting for thread" << std::endl;
//
//    int ching;
//    std::cin >> ching;
//
//    std::cout << "Thank you for trying" << std::endl;
//    return 0;
//}
//

