#/bin\bash

# verifica daca un fisier exista si daca exista, verifica si daca se poate scrie sau nu in el
if [ `find $1 2>./gunoi` ]
then
	echo exista
	if [ `cat $1 2>./gunoi` ]
	then
		echo se poate citi
	else
		echo nu se poate citi
	fi
else
	echo nu exista
fi



