#!/bin/bash

DIR=$(readlink -f $(dirname $0))

source ${DIR}/_name_service


if ! isNSWorking
then
	echo "NameService not running!"
	exit 1
fi

echo "Stopping NameService..."
kill $(pidof ${NS_EXE})
echo "NameService stopped"

