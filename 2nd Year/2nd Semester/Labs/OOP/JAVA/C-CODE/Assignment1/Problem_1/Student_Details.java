import java.util.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.text.*;

public class Student_Details {
	
	String name;
	int roll_no;
	String Stream;
	String Admission_Date;
	float cgpa=0;
	ArrayList <String> Subjects = new ArrayList<String>(5);
	ArrayList<Integer> Marks = new ArrayList<Integer>(5);
	ArrayList<Object> Stu_Details = new ArrayList<Object>();
	
	BufferedReader inp = new BufferedReader (new InputStreamReader(System.in));
	Scanner sc1 = new Scanner(System.in);
	Scanner sc2 = new Scanner(System.in);
	Scanner sc3 = new Scanner(System.in);
	Scanner sc4 = new Scanner(System.in);
	Scanner sc5 = new Scanner(System.in);
	Scanner sc6 = new Scanner(System.in);
	Scanner sc7 = new Scanner(System.in);
	
	public ArrayList<Object> Initialization(int roll,String s1) throws Exception
	{
		System.out.print("\n\t Please input the Name of the Student : ");
		name = inp.readLine();
		
		Date dNow = new Date( );
	    SimpleDateFormat ft = new SimpleDateFormat ("E dd.MM.yyyy 'at' hh:mm:ss a zzz");
	    Admission_Date = ft.format(dNow);
		
		System.out.println("\n\t Date and time of the admission of the Student: "+ Admission_Date);
		
		Stream = s1;
		roll_no = roll;
		
		System.out.println("\n\t The Roll_No of the Student is : " + roll);
		if(Stream.compareToIgnoreCase("Science")==0)
		{
			Science sc1 = new Science();
			Subjects=sc1.Initialize(Subjects);
		}
		
		else if(Stream.compareToIgnoreCase("Arts")==0)
		{
			Arts a1 = new Arts();
			Subjects=a1.Initialize(Subjects);
		}
		
		else if(Stream.compareToIgnoreCase("Commerce")==0)
		{
			Commerce c1 = new Commerce();
			Subjects=c1.Initialize(Subjects);
		}
		
		System.out.print("\n\t Please input the Marks for " +  Subjects.get(0) + ": ");
		Marks.add(sc3.nextInt());
		
		System.out.print("\n\t Please input the Marks for " +  Subjects.get(1) + ": ");
		Marks.add(sc4.nextInt());
	
		System.out.print("\n\t Please input the Marks for " +  Subjects.get(2) + ": ");
		Marks.add(sc5.nextInt());
		
		System.out.print("\n\t Please input the Marks for " +  Subjects.get(3) + ": ");
		Marks.add(sc6.nextInt());
		
		System.out.print("\n\t Please input the Marks for " +  Subjects.get(4) + ": ");
		Marks.add(sc7.nextInt());
		
		for(int i=0;i<5;i++)
			cgpa+=Marks.get(i);
		
		cgpa/=50.0;
		
		Stu_Details.add(name);
		Stu_Details.add(roll_no);
		Stu_Details.add(Stream);
		Stu_Details.add(Admission_Date);
		Stu_Details.add(Subjects);
		Stu_Details.add(Marks);
		Stu_Details.add(cgpa);
		
		return Stu_Details;
		
	}

}
