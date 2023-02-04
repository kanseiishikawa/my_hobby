#!/bin/bash

if [ $# -ne 1 ]; then
  echo "指定された引数は$#個です。" 1>&2
  echo "実行するには1個の引数が必要です。" 1>&2
  exit 1
fi

domain=$1
domain_array=(${domain//./ })

step_server=""
ynwd="ynwd"
ynwp="ynwp"

for d in ${domain_array[@]}; do
    if [ $d = $ynwd ]; then
        step_server="login"
        break
    elif [ $d = $ynwp ]; then
        step_server="login1"
        break
    fi
done

if [ ${#step_server} -ne 0 ]; then
    ssh $step_server -t ssh $domain
else
    ssh $domain
fi
