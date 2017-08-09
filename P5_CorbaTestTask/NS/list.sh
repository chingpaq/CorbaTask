#!/bin/bash

DIR=$(readlink -f $(dirname $0))

source ${DIR}/_name_service


if ! isNSWorking
then
	echo "NameService not running!"
	exit 1
fi

tao_nslist -ORBInitRef NameService=iiop://localhost:${NS_PORT}/NameService --ior

