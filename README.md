# cpp-rest-service
Simple REST service using cpprestsdk and PostgreSQL.

### Installation
Set $CMAKE_INSTALL_PREFIX variable to '/opt/cpp-rest-service'.

### Run
Make a file named 'db_connection_string' containing only PostgreSQL connection string in '$CMAKE_INSTALL_PREFIX/cfg/'.
And then just run cpp-rest-service executable.
For example:
```
dbname=cpp-rest-service user=postgres
```

### Docker (not working!)
##### Program is crashing while the mongocxx::uri is being created

To build docker image:
1. Install project in '/opt/cpp-rest-service'.
2. Go to 'docker' directory in sources.
3. Run 'build_docker.sh'.

To start docker just run 'run_docker.sh'.

### PostgreSQL
1. Install with:
```bash
sudo pacman -S postgresql
```
2. Then configure with:
```bash
sudo su postgres -l
initdb --locale $LANG -E UTF8 -D '/var/lib/postgres/data/'
exit
```
3. Start and enable postgresql.service:
```bash
sudo systemctl enable postgresql.service
sudo systemctl start postgresql.service
```
4. Create DB and user:
```bash
sudo su postgres -l
createuser --interactive
createdb cpp-rest-service
exit
```
