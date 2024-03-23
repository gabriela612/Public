#/bin\bash

if [ -f $1 ]
then
	echo "fisier"
elif [ -d $1 ]
then
	echo "director"
elif [ `echo $1 | grep -E -c "^[0-9]+$"` == "0" ]
then
	echo "nu stim"
else
	echo "numar"
fi


