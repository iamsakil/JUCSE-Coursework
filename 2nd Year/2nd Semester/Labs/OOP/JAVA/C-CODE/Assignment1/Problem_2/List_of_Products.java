import java.security.SecureRandom;
import java.util.*;

public  class List_of_Products {
	
	Map<String, ArrayList<String>> map = new HashMap<String, ArrayList<String>>();
	String code;
	int quantity;
	int price;
	
	Scanner sc4 = new Scanner(System.in);
	Scanner sc5 = new Scanner(System.in);
	Scanner sc6 = new Scanner(System.in);
	Scanner sc7 = new Scanner(System.in);
	Scanner sc8 = new Scanner(System.in);
	Scanner sc9 = new Scanner(System.in);
	
	static final String AB = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	static SecureRandom rnd = new SecureRandom();

	String randomString( int len ){
	StringBuilder sb = new StringBuilder( len );
	for( int i = 0; i < len; i++ ) 
      sb.append( AB.charAt( rnd.nextInt(AB.length()) ) );
	return sb.toString();
	}
	
	public void Add_to_List(Product_Details pd)
	{
		do
		{
			code = randomString(6);
		}while(Find_key(code));
		pd.Initialize(code);
		map.put(code, pd.l1);
	}
	
	public boolean Find_key(String key)
	{
		return map.containsKey(key);
	}
	
	public void Print_all_Details()
	{
		System.out.print("\n\n\t Please input a valid Product Code: ");
		code = sc4.nextLine();
		if(Find_key(code))
		{
			System.out.print("\n\t Details of the code is here\n");
			ArrayList<String> a2 = new ArrayList<String>();
			a2 = map.get(code);
			System.out.print("\n\t Code of the Product : " + code);
			System.out.print("\n\t Name of the Product : " + a2.get(0));
			System.out.print("\n\t Price of the Product : Rs. " + a2.get(1));
			System.out.print("\n\t Quantity of the Product : " + a2.get(2));
			
		}
		else
			System.out.print("\n\t Invalid Code");
		
	}
	
	public void Issued()
	{
		System.out.print("\n\n\t Please input a valid Product Code: ");
		code = sc5.nextLine();
		System.out.print("\n\n\t Please input Quantity: ");
		quantity = sc6.nextInt();
		if(Find_key(code))
		{
			int a = Integer.parseInt(map.get(code).get(2));
			if(quantity<=a)
			{
				ArrayList<String> a2 = new ArrayList<String>();
				a2 = map.get(code);
				a2.set(2, Integer.toString(a-quantity));
				map.put(code,a2);
				System.out.print("\n\t\t\t Details of the code is here\n");
				System.out.print("\n\t Code of the Product : " + code);
				System.out.print("\n\t Name of the Product : " + a2.get(0));
				System.out.print("\n\t Price of the Product : Rs. " + a2.get(1));
				System.out.print("\n\t Remaining Quantity of the Product : " + a2.get(2));
			}
			else if(a==0)
				System.out.print("\n\t No more products can be retrived");
			else
				System.out.print("\n\t Quantity is less than Wanted");
		}
		else
			System.out.print("\n\t Invalid Code");
		
	}
	
	public void Delete_from_the_List()
	{
		System.out.print("\n\n\t Please input a valid Product Code: ");
		code = sc7.nextLine();
		if(Find_key(code))
		{
			map.remove(code);
			System.out.println("\n\t The item has been deleted from the list.");
		}
		else
			System.out.print("\n\t Invalid Code");
	}
	
	public void Update_price_of_a_particular_Item()
	{
		System.out.print("\n\n\t Please input a valid Product Code: ");
		code = sc8.nextLine();
		System.out.print("\n\n\t Please input Desired Price to change: ");
		price = sc9.nextInt();
		if(Find_key(code))
		{
			ArrayList<String> a2 = new ArrayList<String>();
			a2 = map.get(code);
			a2.set(1, Integer.toString(price));
			map.put(code,a2);
			System.out.print("\n\t\t\t Details of the code is here\n");
			System.out.print("\n\t Code of the Product : " + code);
			System.out.print("\n\t Name of the Product : " + a2.get(0));
			System.out.print("\n\t Updated Price of the Product : Rs. " + a2.get(1));
			System.out.print("\n\t Quantity of the Product : " + a2.get(2));
		}
		else
			System.out.print("\n\t Invalid Code");
	}

}
