import java.util.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
public class Server {
	public static void main(String[] args) throws IOException {
		ServerSocket ss=null;
		ServerData data=new ServerData();
		try {
			ss=new ServerSocket(3900);
		} catch (IOException e) {
			e.printStackTrace();
		}
		while(true)
		{
			System.out.println(".......Server Running.......");
			Socket s=null;
			try {
				s=ss.accept();
				System.out.println("\nA new Client Connected: "+s);
	            DataInputStream dis = new DataInputStream(s.getInputStream());
	            DataOutputStream dos = new DataOutputStream(s.getOutputStream());
	            Thread t=new ClientHandler(s,dis,dos,data);
				t.start();
			} catch (IOException e) {
				e.printStackTrace();
				s.close();
			}
		}

	}

}
