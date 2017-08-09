#include <ComputeImpl.hpp>
#include "MathFactory.cpp"

#include <Logger.hpp>
#include <iostream>
#include <sstream>
#include <string>


ComputeImpl::ComputeImpl()
{
	CONSOLE("ComputeForThisImpl v");
}

ComputeImpl::~ComputeImpl()
{
	CONSOLE("ComputeForThisImpl x");
}

void ComputeImpl::computeUsingParameters (
	      ::CORBA::ULong id,
	      ::CORBA::ULong integer1,
	      ::CORBA::ULong integer2,
	      const char * operation,
	      ::CORBATestTask::TaskData_out resultsData)
{
	int random1= integer1;
	int random2= integer2;
	int results=0;
	std::string operation_normal = operation;

	if (operation_normal.compare("+")==0)
		results = Plus(random1, random2);
		//results = random1+random2;
	else if (operation_normal.compare("-")==0)
		results = Minus(random1, random2);
	else if (operation_normal.compare("*")==0)
			results = Multiply(random1, random2);
	else if (operation_normal.compare("/")==0)
		results = Divide(random1, random2);
	else
		results = 0;


	std::cout << std::endl << "Received Request from Client " << id << ": " <<
	    		random1 << " " << operation << " " << random2 << " = " << results << std::endl;

	CORBATestTask::TaskData_var resultsDataForOut = new CORBATestTask::TaskData;


	resultsDataForOut->id= id;
	resultsDataForOut->operation= operation;
	resultsDataForOut->integer1= random1;
	resultsDataForOut->integer2= random2;
	resultsDataForOut->results = results;

	resultsData = resultsDataForOut._retn();
}



