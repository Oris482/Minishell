#!/bin/bash
RED='\033[0;31m'
NC='\033[0m'
NAME="minishell"
TTY="/dev/tty"$(ps u | grep -E '[.]/'${NAME} | awk 'END {print $7}')
while :
do
	PID=$(ps u | grep -E '[.]/'${NAME} | awk '{print $2}' | xargs echo )
	IFS=' ' read -r -a pids <<< "${PID}"
	for pid in "${pids[@]}"
	do
		echo -e "${RED}PID : ${pid}${NC}   TTY : ${TTY}"
		leaks ${pid} | grep Process
	done
	echo "============================================================"
	sleep 1
done
