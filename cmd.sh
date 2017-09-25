#!/bin/bash

#ipArr=("100.109.100.188")
ipArr=("101.109.100.188" "101.109.100.187")
while true
do
	echo  -n "请您老人家输入要执行的命令: "
	read cmd
	break
	if [ $cmd ]
		then
		echo  "开始执行命令 : $cmd "
	fi
done

#首先本地执行一次，expect的缺点在于无法与本地交互

eval $cmd


password="l"
# 跟远程交互，
for ip in ${ipArr[@]}
do
     expect <<EOF
			spawn ssh root@$ip $cmd
			expect  {
				"root@$ip's password:" {
					send "$password\r"
				}
			}
			set timeout 300
			send "exit"
			expect eof
EOF
# EOF 一定要挨着行开始,否则会有语法错误
echo ""

done
