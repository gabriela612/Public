


for i in `find -type f -wholename "$i*"`
do
	if [ -w $i ]
	then
		echo $i
	fi
done


