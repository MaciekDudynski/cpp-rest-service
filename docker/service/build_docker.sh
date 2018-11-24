#! /bin/bash

cp -r /opt/cpp-rest-service installed
docker build -t cpp-rest-service .
rm -r installed

