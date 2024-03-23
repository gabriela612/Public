#/bin\bash


#daca comentam linia cu break, programul citeste si reafiseaza cuvinte pana cand este introdus cuvantul ,,stop"
while true
do
	read x
	if [ $x == "stop" ]
	then
		break
	fi
	echo $x
	break
done


