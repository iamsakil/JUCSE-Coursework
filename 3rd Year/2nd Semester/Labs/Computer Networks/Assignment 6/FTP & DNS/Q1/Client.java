import java.io.*;
import java.net.*;
public class Client {

	public static void main(String[] args) throws Exception
	{
			Socket s=null;
			int delay=0;
			while (true) {
		      try {
		       s=new Socket("127.0.0.1",7777);
		       if (s != null) { break; }
		       }
		      catch (IOException e) {
		      	delay++;
		      	System.out.println("\nWaiting for connection with Server. Time passed "+Integer.toString(delay)+" seconds.");
		      	Thread.sleep(1000); }
		    }
			if(s.isConnected())
			{
				System.out.println("\nConnected to server\n");
			}
			FileOutputStream fout= new FileOutputStream("Received.txt");
			DataInputStream din=new DataInputStream(s.getInputStream());
			int r;
			while((r=din.read())!=-1)
			{
				fout.write((char)r);
			}
			s.close();
			System.out.println("\nFile Sent.\n");
	}

}
