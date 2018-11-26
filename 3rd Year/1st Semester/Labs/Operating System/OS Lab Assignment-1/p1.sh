function recursiveCall(){
#pwd
res=${PWD##*/}
echo $res
echo "No. of files in the directory $(find . -type f | wc -l)"
echo "Files in the directory"
command=`ls -p | grep -v /`
#command=`find . -maxdepth 1 -type f`
echo $command
secondcommand=`find . -mindepth 1 -maxdepth 1 -type d`
echo "Sub-directories are"
echo $secondcommand
for d in $(find . -mindepth 1 -maxdepth 1 -type d)
		do
		cd $d
		recursiveCall "."
		cd ..
		done
}
current="."
recursiveCall $current 
