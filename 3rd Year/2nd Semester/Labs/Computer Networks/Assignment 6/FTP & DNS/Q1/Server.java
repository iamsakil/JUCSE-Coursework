import java.io.*;
import java.net.*;
class Server
{
	public static void main(String args[]) throws Exception
	{
		System.out.println("\nWaiting for connection\n");
		ServerSocket ss=new ServerSocket(7777);
		Socket s=ss.accept();
		System.out.println("Connected.");
		/* File Receiving starts*/
		FileInputStream fin=new FileInputStream("Send.txt");
		DataOutputStream dout=new DataOutputStream(s.getOutputStream());
		int r;
		while((r=fin.read())!=-1)
		{
			dout.write(r);
		}
		System.out.println("\nFile tranfer Completed\n");
		s.close();
		ss.close();
	}
}