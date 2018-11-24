#! /bin/bash

if [ -z "$(ls -A /var/lib/postgres/data)" ]; then
   initdb --locale en_US.UTF-8 -E UTF8 -D '/var/lib/postgres/data'
fi
systemctl start postgresql
bash

