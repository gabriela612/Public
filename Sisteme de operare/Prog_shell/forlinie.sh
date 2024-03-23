

for i in `cat $1`
do
        echo $i unu
done
echo 11111111111111111111111

IFS=$'\n'

for i in `cat $1`
do
	echo $i doi
done

IFS=$'" " | "\n"'

echo 111111111111111111111111
a=`cat $1`
for i in $a
do
        echo $i trei
done

