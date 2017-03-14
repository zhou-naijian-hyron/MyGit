#!/bin/sh

start=$(date "+%s")
echo "start = $start"

## 時間間隔の計算
getNowtime()
{
	nowtime=$(date "+%s")
	lagtime=$((nowtime - start))
	echo "nowtime = $nowtime, lagtime = $lagtime"
	if [ $lagtime -ge 30 ]; then
		exit 1
	fi
}

## 毎２秒に、echoで出力
while true
do
	echo "111111111"
	sleep 2
	getNowtime
done
