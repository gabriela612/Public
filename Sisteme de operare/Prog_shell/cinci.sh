#/bin\bash

# hotaram daca ceva dat este un fisier, director, numar (daca nu este niciuna spunem ca nu stim ce e)

echo $1
if test -f $1
then
	echo "fisier"
elif test -d $1
then
	echo "director"
#a=`echo -q $1 | grep -E -c "^[0-9]+$"`
elif echo $1 | grep -E -q "^[0-9]+$"
then
	echo "numar"
else
	echo "altceva"
fi


