echo "enter filename"
read fname
sed -i -e 's/This is my program/This is copied program/g' $fname
