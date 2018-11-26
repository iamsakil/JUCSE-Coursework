//package stopAndWaitSender;

/*
Stop and wait  protocol 
this is sender
send the packet of one character with its sequence number

 */
import java.io.*;
import java.net.*;
import java.util.*;

public class StopAndWaitSender{
	Socket sender;
	ObjectOutputStream out;
	ObjectInputStream in;
	String packet,ack,str, msg;
	StopAndWaitSender(){}
	public void run(){
		try{
			BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Waiting for Connection....");
			sender = new Socket("localhost",2004);
			out=new ObjectOutputStream(sender.getOutputStream());
			out.flush();
			in=new ObjectInputStream(sender.getInputStream());
			str=(String)in.readObject();
			System.out.println("reciver    > "+str);
			System.out.println("Enter the data to send....");
			packet=br.readLine();
			int i=0,sequence=0;
			int n=packet.length();
			Random rand = new Random();

			while(true) {
				try{
					if(i<n){
						//Text to Binary Conversion
						msg=String.valueOf(sequence);
						String dividendo=Integer.toBinaryString(packet.charAt(i)).toString();
						String divisor=new Integer(110101).toString();
						
						// Appends n-1 zeroes at end of data
						String appended_data = dividendo + appendZeros(divisor.length());
						System.out.println("appended data: "+appended_data);
						
						Modulo2BinaryDivision hel=new Modulo2BinaryDivision();
						String remainder=hel.encodeData(appended_data, divisor);
						dividendo+=remainder;
						int errorDeceision = rand.nextInt(2);
						if(errorDeceision==1) {
							//Error Injection
							System.out.println("Error injecting...");
							int randPosition = rand.nextInt(dividendo.length());
							char ch;
							if(dividendo.charAt(randPosition)=='1')	ch='0';
							else	ch='1';
							String errorDividendo = dividendo.substring(0,randPosition)+ch+dividendo.substring(randPosition+1);
							//msg+=errorDividendo;
						}
						//else	
						msg+=dividendo;
						
						int sz=msg.length();
						for(int j=sz;j<16;j++)	msg+='0';
					}
					else if(i==n){
						msg="end";out.writeObject(msg);break;
					}
					out.writeObject(msg);
					/*
                    			Changing sequence number since data sent
					 */
					sequence=(sequence==0)?1:0;
					out.flush();
					System.out.println("data sent>"+msg);
					ack=(String)in.readObject();
					System.out.println("Waiting for ack.....");

					if(ack.equals(String.valueOf(sequence))){
						i++;
						System.out.println("Receiver    >  "+" packet received");
					}
					else{      
					/* Whenever ack lost or wrong ack we change the sequence number
					 */
						System.out.println("Time out resending data....\n");
						sequence=(sequence==0)?1:0;
					}
				}catch(Exception e){}
			}
			System.out.println("All data sent. exiting.");
		}catch(Exception e){}
		finally{
			try{
				in.close();
				out.close();
				sender.close();
			}catch(Exception e){}
		}
	}
	private String appendZeros(int noOfZeros) {
		String result="";
		for(int i=1;i<noOfZeros;i++)
			result+='0';
		return result;
	}
	public static void main(String args[]){
		StopAndWaitSender s=new StopAndWaitSender();
		s.run();
	}
}
