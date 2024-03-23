#/bin\bash

# afiseaza numarul de linii din fiecare fisier cu extensia .c din folderul dat ca si parametru in linia de comanda,
# dar verifica sa fie fisier (un folder poate avea numele ceva.c)

s=0

for i in `find -type f -wholename "$1/*.c"`
do
	n=`cat $i | grep -E -c ""`
	s=`expr $s + $n`
done
echo $s

