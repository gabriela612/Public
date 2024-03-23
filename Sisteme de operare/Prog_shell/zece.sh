

# sorteaza liniile din fisierele cu extensia .log din mai multe foldere date ca parametrii

touch rez.temp
chmod 777 rez.temp

for i in $@
do
	for j in `ls $i`
	do
		# j va avea, pe rand, toate numele de fisiere
		if [ `echo $j | grep -E -c "\.log$"` -gt 0 ]  && [ -f $j ]
		then
			# aici j are fisiere cu extensia .log
			echo $j
			cat $j | sort -f > rez.temp
			cat rez.temp > $j
		fi
	done
done

rm rez.temp
