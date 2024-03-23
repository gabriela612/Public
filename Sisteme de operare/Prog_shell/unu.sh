#\bin/bash


S=-1
for i in $*
do
	if test $S == -1 ;then
		S=0
	fi
	if [ $S != -1 ];then
		#echo "i este $i si S este $S"
		a=$S
		S=`expr $a + $i`
		#echo expresia este `expr $a + $i`
	fi
done

echo $S

