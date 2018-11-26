import java.util.*;
public class Product {
	
	public static void main(String[] args)
	{
		List_of_Products lp = new List_of_Products();
		Scanner sc = new Scanner(System.in);
		int choice;
		do
		{
			System.out.print("\n\t\t\t\t ---- Welcome ----\n\n\t1.Add new Item\n\t2.Issue Item\n\t3.Delete Item\n\t4.Item Price Update\n\t5.Availability and Price of the item\n\t6.Exit.....->");
			choice = sc.nextInt();
			switch(choice)
				{
				
					case 1:
						Product_Details pd = new Product_Details();
						lp.Add_to_List(pd);
						break;
						
					case 2:
						lp.Issued();
						break;
					
					case 3:
						lp.Delete_from_the_List();
						break;
						
					case 4:
						lp.Update_price_of_a_particular_Item();
						break;
						
					case 5:
						lp.Print_all_Details();
						break;
						
					case 6:
						System.out.print("\n\t Thank you.");
						System.exit(0);
						
					default:
						System.out.print("\n\t Invalid Input.");
						break;
						
				}
			}while(true);
		
	}
	
}
