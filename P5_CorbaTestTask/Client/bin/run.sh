#!/bin/bash

DIR=$(readlink -f $(dirname $0))

source ${DIR}/../../NS/_name_service

${DIR}/Client -ORBInitRef NameService=iiop://localhost:${NS_PORT}/NameService

