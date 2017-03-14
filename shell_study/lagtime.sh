#!/bin/sh

## 時間間隔の計算
start=$(date "+%s")
echo "start = $start"

#do something
sleep 2

now=$(date "+%s")
echo "now = $now"

lagtime=$((now-start))
echo "lagtime = $lagtime seconds."

