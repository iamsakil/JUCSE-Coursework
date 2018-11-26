clear
function prime_check(){
	echo -n "Enter a number: "
	read num
	i=2
	#calc=$(echo "sqrt ($num)" | bc -l)
	#float=$calc
	#int=${float%.*}
	while [ $i -lt $num ]
	do
	  if [ `expr $num % $i` -eq 0 ]
	  then
	      echo "$num is not a prime number"
	      echo "Since it is divisible by $i"
	      exit
	  fi
	  i=`expr $i + 1`
	done

	echo "$num is a prime number "
}

prime_check
