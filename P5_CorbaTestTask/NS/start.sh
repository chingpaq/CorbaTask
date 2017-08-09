#!/bin/bash

DIR=$(readlink -f $(dirname $0))

source ${DIR}/_name_service


if isNSWorking
then
	echo "NameService already started!"
	exit 1
fi

echo "Starting NameService..."
nohup ${NS_COMMAND} 2>/dev/null &
sleep 0.2
rm -f nohup.out

if isNSWorking
then
	echo "NameService started in background (PID=$(pidof ${NS_EXE}))"
else
	echo "Unable to start NameService!"
	exit 1
fi


