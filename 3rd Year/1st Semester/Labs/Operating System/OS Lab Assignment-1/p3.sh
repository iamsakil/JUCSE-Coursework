read -p "Enter the name of the file:" text
if [ -f $text ]
then
echo "No. of lines in the file="
wc -l < $text
else
echo "The file name you entered doesn't exist!!!"
fi
