import java.io.*;
import java.net.*;

class UDPserver
{
	public static DatagramSocket ds;
	public static byte buffer[]=new byte[1024];
	public static int clientport=7777,serverport=8888;

	public static void main(String args[])throws Exception
	{
		ds=new DatagramSocket(clientport);
		System.out.println("press ctrl+c to quit the program");
		BufferedReader dis=new BufferedReader(new InputStreamReader(System.in));
		InetAddress ia=InetAddress.getLocalHost();

		while(true)
		{
			DatagramPacket p=new DatagramPacket(buffer,buffer.length);
			ds.receive(p);
			String psx=new String(p.getData(),0,p.getLength());
			System.out.println("Client:" + psx);
			InetAddress ib=InetAddress.getByName(psx);
			System.out.println("Server output:"+ib);
			String str=dis.readLine();
			if(str.equals("end"))
				break;
			buffer=str.getBytes();
			ds.send(new DatagramPacket(buffer,str.length(),ia,serverport));
		}
	}
}