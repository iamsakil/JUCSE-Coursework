import java.io.*;
import java.util.*;
import java.util.Map.Entry;

public class All_Student_Records {
	
	String Stream;
	int Roll,code,i=0;
	BufferedReader inp = new BufferedReader (new InputStreamReader(System.in));
	Map<Integer, ArrayList<Object>> map_Science = new HashMap<Integer, ArrayList<Object>>();
	Map<Integer, ArrayList<Object>> map_Arts = new HashMap<Integer, ArrayList<Object>>();
	Map<Integer, ArrayList<Object>> map_Commerce = new HashMap<Integer, ArrayList<Object>>();
	
	public void Taking_Admission() throws Exception
	{
		System.out.print("\n\t Please input the Stream of the Student : ");
		
		Stream = inp.readLine();
		
	
		Student_Details sd1 = new Student_Details();
		int year = Calendar.getInstance().get(Calendar.YEAR);
		
		code = get_code(Stream);
		Roll = Roll_No_Generation(code,year);
		sd1.Stu_Details=sd1.Initialization(Roll,Stream);
		
		if(code==7)
			map_Science.put(Roll, sd1.Stu_Details);
		else if(code==8)
			map_Commerce.put(Roll, sd1.Stu_Details);
		else
			map_Arts.put(Roll, sd1.Stu_Details);
	}
	
	public int get_code(String Stream)
	{
		if(Stream.compareToIgnoreCase("Science")==0)
			 return 7;
		else if(Stream.compareToIgnoreCase("Arts")==0)
			 return 9;
		else
			return 8;
		
	}
	
	public int Roll_No_Generation(int code_of_Steram,int year)
	{
		int upto;
		if(code_of_Steram==7)
			upto = map_Science.size()+1;
		else if(code_of_Steram==8)
			upto = map_Commerce.size()+1;
		else
			upto = map_Arts.size()+1;
		
		return year*10000+(code_of_Steram)*100+upto;
	}
	
	
	@SuppressWarnings("unchecked")
	public void Display_Details() throws Exception
	{
		System.out.print("\n\t Please input the roll_no : ");
		Roll = Integer.parseInt(inp.readLine());
		code = (Roll/100)%100;
		int R = code;
		code = Roll;
		ArrayList <String> s1 = new ArrayList <String>();
		ArrayList <Integer> s2 = new ArrayList <Integer>();
		
		if(R==7)
		{
			System.out.print("\n\t Name of the Student : "+ map_Science.get(code).get(0));
			System.out.print("\n\t The Roll_No of the Student is : " + map_Science.get(code).get(1));
			System.out.print("\n\t The Stream of the Student : " + map_Science.get(code).get(2));
			System.out.print("\n\t Date and time of the admission of the Student: " + map_Science.get(code).get(3));
			System.out.println("\n\n");
			s1 = ((ArrayList <String>)map_Science.get(code).get(4));
			s2 = ((ArrayList <Integer>)map_Science.get(code).get(5));
			System.out.print("\n\t The Marks for " +  s1.get(0) + ": " + s2.get(0));
			System.out.print("\n\t The Marks for " +  s1.get(1) + ": " + s2.get(1));
			System.out.print("\n\t The Marks for " +  s1.get(2) + ": " + s2.get(2));
			System.out.print("\n\t The Marks for " +  s1.get(3) + ": " + s2.get(3));
			System.out.print("\n\t The Marks for " +  s1.get(4) + ": " + s2.get(4));
			System.out.println("\n\n So the cgpa of the Student is: " + map_Science.get(code).get(6));
		}
		
		else if(R==8)
		{
			System.out.print("\n\t Name of the Student : "+ map_Commerce.get(code).get(0));
			System.out.print("\n\t The Roll_No of the Student is : " + map_Commerce.get(code).get(1));
			System.out.print("\n\t The Stream of the Student : " + map_Commerce.get(code).get(2));
			System.out.print("\n\t Date and time of the admission of the Student: " + map_Commerce.get(code).get(3));
			System.out.println("\n\n");
			s1 = ((ArrayList <String>)map_Commerce.get(code).get(4));
			s2 = ((ArrayList <Integer>)map_Commerce.get(code).get(5));
			System.out.print("\n\t The Marks for " +  s1.get(0) + ": " + s2.get(0));
			System.out.print("\n\t The Marks for " +  s1.get(1) + ": " + s2.get(1));
			System.out.print("\n\t The Marks for " +  s1.get(2) + ": " + s2.get(2));
			System.out.print("\n\t The Marks for " +  s1.get(3) + ": " + s2.get(3));
			System.out.print("\n\t The Marks for " +  s1.get(4) + ": " + s2.get(4));
			System.out.println("\n\n So the cgpa of the Student is: " + map_Commerce.get(code).get(6));
		}
		
		else 
		{
			System.out.print("\n\t Name of the Student : "+ map_Arts.get(code).get(0));
			System.out.print("\n\t The Roll_No of the Student is : " + map_Arts.get(code).get(1));
			System.out.print("\n\t The Stream of the Student : " + map_Arts.get(code).get(2));
			System.out.print("\n\t Date and time of the admission of the Student: " + map_Arts.get(code).get(3));
			System.out.println("\n\n");
			s1 = ((ArrayList <String>)map_Arts.get(code).get(4));
			s2 = ((ArrayList <Integer>)map_Arts.get(code).get(5));
			System.out.print("\n\t The Marks for " +  s1.get(0) + ": " + s2.get(0));
			System.out.print("\n\t The Marks for " +  s1.get(1) + ": " + s2.get(1));
			System.out.print("\n\t The Marks for " +  s1.get(2) + ": " + s2.get(2));
			System.out.print("\n\t The Marks for " +  s1.get(3) + ": " + s2.get(3));
			System.out.print("\n\t The Marks for " +  s1.get(4) + ": " + s2.get(4));
			System.out.println("\n\n So the cgpa of the Student is: " + map_Arts.get(code).get(6));
		}
		
	}
	
	public int total_no_of_Students()
	{
		return map_Science.size()+map_Arts.size()+map_Commerce.size();
	}
	
	@SuppressWarnings("unchecked")
	public void Sort_Students_of_a_particular_Stream() throws Exception
	{
		i=0;
		ArrayList <String> s1 = new ArrayList <String>();
		ArrayList <Integer> s2 = new ArrayList <Integer>();
		System.out.print("\n\t Please input the Stream : ");
		Stream = inp.readLine();
		code = get_code(Stream);
		Map<Integer, ArrayList<Object>> m1 = new HashMap<Integer, ArrayList<Object>>();
		if(code == 7)
			m1 = sortByValues(map_Science);
		else if (code == 8)
			m1 = sortByValues(map_Commerce);
		else
			m1 = sortByValues(map_Arts);
		


		for (Map.Entry<Integer, ArrayList<Object>> entry : m1.entrySet()) {
			i++;
			ArrayList<Object> value = entry.getValue();
			System.out.print("\n\t " + i +">" + "Name of the Student : "+ value.get(0));
			System.out.print("\n\t The Roll_No of the Student is : " + value.get(1));
			System.out.print("\n\t The Stream of the Student : " + value.get(2));
			System.out.print("\n\t Date and time of the admission of the Student: " + value.get(3));
			System.out.println("\n\n");
			s1 = (ArrayList <String>)value.get(4);
			s2 = (ArrayList <Integer>)value.get(5);
			System.out.print("\n\t The Marks for " +  s1.get(0) + ": " + s2.get(0));
			System.out.print("\n\t The Marks for " +  s1.get(1) + ": " + s2.get(1));
			System.out.print("\n\t The Marks for " +  s1.get(2) + ": " + s2.get(2));
			System.out.print("\n\t The Marks for " +  s1.get(3) + ": " + s2.get(3));
			System.out.print("\n\t The Marks for " +  s1.get(4) + ": " + s2.get(4));
			System.out.println("\n\n So the cgpa of the Student is: " + value.get(6));
		}


	}
	
	public void Delete_Student() throws Exception
	{
		System.out.print("\n\t Please input the roll_no : ");
		Roll = Integer.parseInt(inp.readLine());
		code = (Roll/100)%100;
		For_Counter();
		
		if(code==7)
			map_Science.remove(Roll);
		else if(code==8)
			map_Commerce.remove(Roll);
		else
			map_Arts.remove(Roll);
		
	}
	
	public void For_Counter()
	{
		
	}
	
	private static Map<Integer, ArrayList<Object>> sortByValues(Map<Integer, ArrayList<Object>> map) { 
		Set<Entry<Integer, ArrayList<Object>>> set = map.entrySet();
		List<Entry<Integer, ArrayList<Object>>> list = new ArrayList<Entry<Integer, ArrayList<Object>>>(set);
	      
		Collections.sort( list, new Comparator<Map.Entry<Integer, ArrayList<Object>>>()
        {
            public int compare( Map.Entry<Integer, ArrayList<Object>> o1, Map.Entry<Integer, ArrayList<Object>> o2 )
            {
                return ((Float) o2.getValue().get(6)).compareTo( (Float) o1.getValue().get(6) );
            }
			
        } );
	       return map;
	  }
	

}