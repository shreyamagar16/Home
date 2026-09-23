touch stud.csv
if [ ! -s stud.csv ]; then
    echo "Roll,Name,Class,Marks" >> stud.csv
fi
search(){
read -p "Enter roll no. to be searched: " search
	grep "^$search," stud.csv || echo "Student not found"
}
update(){
read -p "Enter roll no. of student to be updated: " update
	if grep -q "^$update," stud.csv; then
		read -p "Enter new roll: " roll
		read -p "Enter new name: " name
		read -p "Enter new class: " class
		read -p "Enter new marks: " marks

		sed -i "s/^$update,.*/$roll,$name,$class,$marks/" stud.csv
		echo "Updation successful"
	else
		echo "Student not found"
	fi
}
delete(){
read -p "Enter roll no. of student to be deleted: " del
	if grep -q "^$del," stud.csv; then
		sed -i "/^$del,/d" stud.csv
		echo "Deletion successful"
	else
		echo "Student not found"
	fi
}
while true; do
	echo "Enter choice from \n 1)add \n 2)display \n 3)update \n 4)delete \n 5)search \n 6)exit "
	read -p "Choice: " ch
	case $ch in

		1)read -p  "Enter Roll No.: " roll

		if 
			grep -q "^$roll" stud.csv; then
			echo "Student already exists."
		else
		
			read -p  "Enter Name: " name
			read -p  "Enter Class: " class
			read -p  "Enter Marks: " marks
			echo "$roll,$name,$class,$marks">>stud.csv
		fi		
		;;
		2)column -t -s "," stud.csv
		;;
		3)update
		;;
		4)delete
		;;
		5)search
		;;
		6)exit
		;;
		*) echo "Invalid choice"
		;;
	esac
done 