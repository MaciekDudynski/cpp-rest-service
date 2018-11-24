#! /bin/bash

docker rm cpp-rest-service
docker run -it --name cpp-rest-service --network host cpp-rest-service

