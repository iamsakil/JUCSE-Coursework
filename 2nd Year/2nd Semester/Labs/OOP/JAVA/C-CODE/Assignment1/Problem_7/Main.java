

public class Main{
	public static void main(String args[]) throws Exception	{
		DirFile d = new DirFile();
		if(args.length == 0)
			d.sortByName();
		else if(args.length == 1) {
			if(args[0].compareToIgnoreCase("-d") == 0)
				d.sortByDate();
			else if(args[0].compareToIgnoreCase("-s") == 0)
				d.sortBySize();
			else System.out.println("-->SORRY, YOUR INVOKATION DOES NOT MATCHES WITH ANYTHING");
		}
		else
			System.out.println("-->SORRY, YOUR INVOKATION DOES NOT MATCHES WITH ANYTHING");
	}
}
