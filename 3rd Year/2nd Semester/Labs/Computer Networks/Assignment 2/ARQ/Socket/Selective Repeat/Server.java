//Selective Repeat Server
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
public class Server {

	public static void main(String[] args) throws UnknownHostException,IOException {
		int no_of_packets,no_of_frames,t,i,j,temp,count=0,k,count1=0;
		 ServerSocket s1= new ServerSocket(4500);
		 String ans;
		@SuppressWarnings("resource")
		Socket s=new Socket();
		s=s1.accept();
		Scanner sc=new Scanner(System.in);
		Scanner sc1=new Scanner(s.getInputStream());
		PrintStream p=new PrintStream(s.getOutputStream());
		ans=sc1.nextLine();
		System.out.println(ans);
		/*System.out.println("Enter no of packets to be sent:");
		no_of_packets=sc.nextInt();
		System.out.println("Enter no of frames to be sent:");
		no_of_frames=sc.nextInt();*/
		File f=new File("Arq.txt");
		if(!f.exists()) 
			{
				f.createNewFile();
				FileOutputStream fos=new FileOutputStream(f);
				DataOutputStream dos=new DataOutputStream(fos);
				dos.writeUTF("Hello_world_Madame");
			}
		FileInputStream fis=new FileInputStream(f);
		DataInputStream dis=new DataInputStream(fis);
		String text=dis.readUTF();
		//System.out.println(text);
		int len=text.length();
		no_of_packets=len;
		no_of_frames=3;
		t=(int)(no_of_packets/no_of_frames);
		p.println(8*t);
		/*int [][] ar=new int[no_of_frames][t];
		count=1;
		for(i=0;i<no_of_frames;i++)
		{
			for(j=0;j<t;j++)
			{
				ar[i][j]=count;
				count++;
			}
		}*/
		char ar[][]=new char[3][8*t];
		String sarray[]=new String[len];
		for(i=0;i<len;i++)
		{
			sarray[i]="";
		}
		int binary[]=new int[8];
		for(i=0;i<8;i++)
			binary[i]=0;
		for(i=0;i<len;i++)
		{
			int tempo=(int)(text.charAt(i));
			j=0;
			while(tempo>0)
			{
				binary[j]=tempo%2;
				tempo=tempo/2;
				j++;
			}
			for(j=7;j>=0;j--)
				sarray[i]=sarray[i]+binary[j];
			
		}
		for(i=0;i<3;i++)
		{
			k=0;
			for(j=i*t;j<(i+1)*t;j++)
			{

				for(count=0;count<8;count++)
				{
					 ar[i][k]=sarray[j].charAt(count);
					// System.out.println("k:"+k+" ar[i][k]:"+ar[i][k]);
					 k++;
					
				}
			}

		}
		/*for(i=0;i<no_of_frames;i++)
		{
			for(j=0;j<8*t;j++)
			{
				System.out.print(ar[i][j]+" ");
			}
			System.out.println("");
		}*/
		for(i=0;i<3;i++)
		{
			for(j=0;j<8*t;j++)
			{
				if(ar[i][j]=='0')
				p.println(0);
				if(ar[i][j]=='1')
					p.println(1);
			}
		}
		for(i=0;i<no_of_frames;i++)
		{
			for(j=0;j<t;j++)
			{
				temp=sc1.nextInt();
				if(temp==0)
					System.out.println("Acknowledgement received for packet :"+j+"frame:"+i+"\n");
				else
				{
					System.out.println("negetive Acknowledgement received for packet:"+j+"frame:"+i+" resending packet\n");
				}
			}
		}
		System.out.println("All packets sent successfully..\n");
		sc.close();
		sc1.close();
		p.close();
		s1.close();
		s.close();
	}

}
