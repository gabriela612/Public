


for i in `find -L $1`
do
	if [ -e $i ]
	then
		echo $i
	fi
done


echo 11111111111111111111111111

for i in `find $1`
do
        if [ -h $i ]
        then
                echo $i
        fi
done
