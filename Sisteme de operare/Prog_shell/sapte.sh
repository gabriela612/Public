
# gasiti toate fisierele din folderul dat ca prim argument in linia de comanda care au lungime mai mare decat al doilea argument din linia de comanda


find $1 -type f | while read i
do
	#echo $i
	size=`ls -l $i | awk '{print $5}'`
	if [ $size -gt $2 ]
	then
		echo $i
	fi
done

