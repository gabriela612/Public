

# creeaza fisiere / foldere sau ceva cu numele argumentelor, afiseaza cu ls -l, apoi le sterge

for i in $@
do
	mkdir $i
	touch $i.c
	ls -l
	rm -d $i
	rm $i.c
done


# crearea unui fisier cu numele argumentului 2 si inlocuirea acestuia cu numele argumentului 2 .c
touch $2
ls -l
mv $2 $2.c
ls -l
