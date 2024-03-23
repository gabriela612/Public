


read a
while [ $a != "stop" ]
do
	#w=`who`
	aw=`awk '{print $1}' a.txt`
	for i in $aw
	do
		if [ $i == $a ]
		then
			echo $a
		fi
	done
	if [ -f $a ]
	then
		touch s.sup
		cat $a | grep -E -v "\<Ana\>" > s.sup
		cat s.sup > $a
		rm s.sup
	fi
	read a
done






