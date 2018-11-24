#! /bin/bash

docker rm postgresql
docker run -it --name postgresql --network host postgresql

