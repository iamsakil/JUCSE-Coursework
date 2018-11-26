echo "Enter the String"
read string
read t1  t2  t3  t4
for file in */
	do
		echo " No. of occurances with file name"
		grep -w -n -c -i "$string" $t1 $t2 $t3 $t4

		echo "No. Of Occurances And Corresponding Line Number In Each File" 
		grep  -w -n -i "$string" $t1 $t2 $t3 $t4 | uniq -c

		echo "Total No. of Occurances:-"
		grep -w -n -i "$string" $t1 $t2 $t3 $t4 | wc -l
	done
