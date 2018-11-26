//Selective Repeat Client
import java.io.IOException;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;
import java.util.Scanner;

public class Client {

	public static void main(String[] args) throws UnknownHostException, IOException{
		InetAddress addr=InetAddress.getByName("localhost");
		Socket s= new Socket(addr,4500);
		Scanner sc=new Scanner(System.in);
		Scanner sc2=new Scanner(s.getInputStream());
		PrintStream p=new PrintStream(s.getOutputStream());
		p.println("Client connected");
		int row,col,i,j,flag;
		row=3;
		col=sc2.nextInt();
		int t=col/8;
		System.out.println("row:"+row+" col:"+col);
		int lengthof=(int)(col/8)*row;
		int result[]=new int[lengthof];
		int count=0;
		int arr[]=new int[col];
		for(i=0;i<col;i++)
			arr[i]=0;
		int [][] res=new int[row][col];
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				int a=sc2.nextInt();
				res[i][j]=a;
				
			}
		}
		/*for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				System.out.print(" "+res[i][j]);
				
			}
			System.out.println(" ");
		}*/
		for(i=0;i<3;i++)
		{
			for(j=0;j<t;j++)
			{
				int sum=0;
				for(int k=j*8;k<(j+1)*8;k++)
				{
					sum=2*sum+res[i][k];
				}
				result[count]=sum;
				count++;
				
			}
		}
		char []character=new char[t];
		count=0;
		for(i=0;i<3;i++)
		{
			count=0;
			for(j=0;j<t;j++)
			{
				Random randomGenerator = new Random();
				flag= randomGenerator.nextInt(1000);
				flag=flag%2;
				p.println(flag);
				if(flag==0)
				{
					char answer=(char)result[i*t+j];
					System.out.println("packet received successfully with data: "+answer);
				}
				else
				{
					char answer=(char)result[i*t+j];
					System.out.println("Damaged packet received..error..at frame: "+i+"packet: "+j+"\n");
					character[count]=answer;
					count++;
				}
				
			}
			for(int k=0;k<count;k++)
			{
		       System.out.println("Retrieving damaded packet..sending negative acknowledgement..");
		       System.out.println("Retrieved damaged packet with data: "+character[k]);
			}
		}
		System.out.println("All packets received successfully.\n");
		s.close();
		sc.close();
		sc2.close();
		p.close();

	}

}
