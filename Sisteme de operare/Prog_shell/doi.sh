#\bin/bash

#afiseaza numarul de linii din fisierele c din folderul dat
s=0
unu=1
for i in $1/*.c
do
	n=`cat $i | grep -E -c "[^ ]"`
	s=`expr $s + $n`
done
echo $s

# afiseaza toate fisierele care au extensia formata dintr-un caracter
#for i in $1/*.?
#do
	#echo $i
#done

