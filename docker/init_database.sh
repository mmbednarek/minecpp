#!/usr/bin/bash

FDB_HOST=$(host "fdb" | head -1 | awk '{print $4}')
if [ $FDB_HOST = 'found:' ]; then
    FDB_HOST='127.0.0.1'
fi

echo "docker:docker@$FDB_HOST:4500" | tee /root/clusterfile

fdbcli -C "/root/clusterfile" --exec 'configure new single ssd logs=1'
if [ $? -eq 2 ]; then
  fdbcli -C "/root/clusterfile" --exec 'configure single ssd logs=1'
fi
