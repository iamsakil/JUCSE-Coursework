import java.util.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
public class Client {
	public static void main(String[] args) throws IOException{
	       try
	        {
	            Scanner scn = new Scanner(System.in);
	            InetAddress ip = InetAddress.getByName("localhost");
	            System.out.println(ip);
	            String res="localhost/"+args[0];
	            System.out.println(args[0]);
	            System.out.println(args[1]);
	            if(!res.equals(""+ip)|| !args[1].equals("3900"))
	            {
	            	throw new Exception("Error");
	            }
	            Socket s = new Socket(ip, 3900);
	            DataInputStream dis = new DataInputStream(s.getInputStream());
	            DataOutputStream dos = new DataOutputStream(s.getOutputStream());
	            System.out.println("Server:"+dis.readUTF());
	            int sz=args.length;
	            int x=sz-2;
	            dos.writeUTF(Integer.toString(x));
	            for(int i=2;i<sz;i++)
	            {
	            	dos.writeUTF(args[i]);
	            }
	            sz=Integer.parseInt(dis.readUTF());
	            String[] output=new String[sz];
	            for(int i=0;i<sz;i++)
	            {
	            	output[i]=dis.readUTF();
	            	if (!output[i].trim().equals("")) {
	            		System.out.println(output[i]);
	            	}
	            	else {
	            		System.out.println("<blank>");
	            	}
	            }
	            // Scanner sc=new Scanner(System.in);
	            // String end=sc.nextLine();
	            scn.close();
	            dis.close();
	            dos.close();
	        }catch(Exception e){
	        	System.out.println("Some error occurred!!!!!..");
	            //e.printStackTrace();
	        }
	}

}
