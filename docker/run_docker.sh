#! /bin/bash

docker rm cpp-rest-service
docker run -it --name cpp-rest-service --network host --expose 6502 cpp-rest-service

