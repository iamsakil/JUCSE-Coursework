/*
    Go Back N Receiver
 */
import java.io.*;
import java.util.*;

import java.net.*;
public class GoBackNReceiver{
	ServerSocket reciever;
	Socket connection=null;
	ObjectOutputStream out;
	ObjectInputStream in;
	String packet,ack,data="";
	int i=0,sequence=0;

	// create instance of Random class
	Random rand = new Random();

	//Default constructor
	GoBackNReceiver(){}

	public void run(){
		try{
			BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
			reciever = new ServerSocket(2004,10);
			System.out.println("waiting for connection...");
			connection=reciever.accept();
			sequence=0;
			System.out.println("Connection established     :");

			out=new ObjectOutputStream(connection.getOutputStream());
			out.flush();
			in=new ObjectInputStream(connection.getInputStream());
			out.writeObject("connected    .");

			try {
				packet=(String)in.readObject();
				System.out.println("The size received from Sender: "+packet);
			}catch(Exception e){}

			int slidingWindowSize=Integer.parseInt(packet);

			do{
				try{
					packet=(String)in.readObject();		boolean flag=false;
					if(packet=="end")	break;
					//String[] splited = packet.split("\\s+");
					String[] splited = packet.split("-");
					String demoData="";
					
					if(Integer.valueOf(splited[0])==sequence){
						System.out.println("Receiver side   >"+splited[1]);

						String divisor=new Integer(110101).toString();
						String extractedData = splited[1].substring(0, 7+divisor.length());		demoData=extractedData;
						System.out.println("extractedData: "+extractedData);

						String remainder=Modulo2BinaryDivision.encodeData(extractedData, divisor);
						sequence=(sequence+1)%slidingWindowSize;
						
						//Error for crc
						if(check(remainder)) {
							String integerPart=extractedData.substring(0,7);
							int messageReceivedinInteger = Integer.parseInt(integerPart, 2);
							char characterPart=(char)(messageReceivedinInteger);
							System.out.println("Message received from sender: " + characterPart);
							data+=characterPart;
						}
						else {
							System.out.println("ERROR: Message discarded by receiver");
							flag=true;
						}
						//out.writeObject(sequence);
					}
					//Error for sequence number
					else{
						System.out.println("receiver    >"+splited[1] +"   duplicate data");
						out.writeObject(sequence);
					}
					System.out.println("Total data received so far: "+data);
					
					/*
                        when i==3 then i destroy the ack
					 */
					if(i<3){
                        out.writeObject(String.valueOf(sequence));	
                        i++;
                    }else{
                    		out.writeObject(String.valueOf((sequence+1)%slidingWindowSize));	i=0;
                    }

					if(flag==true) {
						System.out.println("Retransmitted data");
						String integerPart=demoData.substring(0,7);
						int messageReceivedinInteger = Integer.parseInt(integerPart, 2);
						char characterPart=(char)(messageReceivedinInteger);
						System.out.println("Message received from sender: " + characterPart);
						data+=characterPart;
						System.out.println("Total data received so far: "+data);
					}
					flag=false;
				}catch(Exception e){}
			}while(!packet.equals("end"));
			System.out.println("Data recived="+data);
			out.writeObject("connection ended    .");
		}catch(Exception e){}
		finally{
			try{
				in.close();
				out.close();
				reciever.close();
			}catch(Exception e){}
		}
	}
	private boolean check(String remainder) {
		for(int i=0;i<remainder.length();i++)
			if(remainder.charAt(i) != '0')
				return false;
		Random rand=new Random();
		int deceision=rand.nextInt(2);
		if(deceision==1)	return true;
		else	return false;
	}
	public static void main(String args[]){
		GoBackNReceiver s=new GoBackNReceiver();
		while(true){
			s.run();
		}
	}
}