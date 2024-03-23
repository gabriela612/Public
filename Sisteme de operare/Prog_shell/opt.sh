
# afiseaza primele 2 fisiere .c dintr-un folder dat ca parametru care are mai multe linii decat al doilea parametru

n=0
for i in `find -type f -wholename "$1*.c"`
do
	if [ `cat $i | grep -E -c ""` -gt $2 ]
	then
		echo $i
		n=`expr $n + 1`
	fi
	if [ $n == 2 ]
	then
		break
	fi
done

