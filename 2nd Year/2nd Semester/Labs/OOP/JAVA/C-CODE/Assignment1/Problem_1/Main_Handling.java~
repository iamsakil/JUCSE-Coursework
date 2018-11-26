import java.util.*;
public class Main_Handling {

	
	public static void main(String[] args) throws Exception {
		
		
		int mb = 1024*1024;
		Runtime runtime = Runtime.getRuntime();
		
		All_Student_Records asr= new All_Student_Records();
		int choice;
		Scanner sc = new Scanner(System.in);
		do
		{
			System.out.println("\n\t\t\t --Welcome--\n\n\t Please enter your choice\n\t1.Admission\n\t2.Mark_sheet_display\n\t3.Display the no of students till now\n\t4.Sort Student of a Particular Stream\n\t5.Delete a Student\n\t6.Exit.....-->");
			choice = sc.nextInt();
			
			switch(choice)		/*switch case for different operation related to STUDENT class for it's details*/
			{
				case 1:
						asr.Taking_Admission();
						break;
					
				case 2:
						asr.Display_Details();
						break;
					
				case 3:
						System.out.println("\n\n So the total no of students till now :" + asr.total_no_of_Students());
						break;
					
				case 4: 
						asr.Sort_Students_of_a_particular_Stream();
						break;
				
				case 5:
						System.out.print("\n\t Total Memory now :" + runtime.totalMemory() + "\n");
						asr.Delete_Student();
						System.out.print("\n\t Total Memory :" + (runtime.totalMemory()-runtime.freeMemory()));
						break;
				
				case 6:
						System.out.println("\n\t Thank You");
						System.exit(0);
						break;
				
				default:
						System.out.println("\n\t Wrong entry.");
						break;
			}
			
		}while(true);
	}

}
