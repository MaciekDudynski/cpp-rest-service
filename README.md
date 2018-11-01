# cpp-rest-service
Simple REST service using cpprestsdk and mongoDB.

### Installation
Set CMAKE_INSTALL_PREFIX variable to '/opt/cpp-rest-service'.

### Run
Make a file named 'db_connection_string' containing only mongoDB connection string in $CMAKE_INSTALL_PREFIX/cfg/
And then just run cpp-rest-service executable.

### Docker
To build docker image:
1. Install project in '/opt/cpp-rest-service'.
2. Go to 'docker' directory in sources.
3. Run 'build_docker.sh'.
To start docker just run 'run_docker.sh'.
