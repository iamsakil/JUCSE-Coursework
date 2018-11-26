//package stopAndWaitSender;

/*
Stop and wait  protocol
this is reciever
send the packet of one character with its sequence number

 */
import java.io.*;
import java.net.*;
import java.util.Random;
public class StopAndWaitReceiver{
	ServerSocket reciever;
	Socket connection=null;
	ObjectOutputStream out;
	ObjectInputStream in;
	String packet,ack,data="";
	int i=0,sequence=0;
	StopAndWaitReceiver(){}
	public void run(){
		try{
			BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
			reciever = new ServerSocket(2004,10);
			System.out.println("Waiting for connection...");
			connection=reciever.accept();
			sequence=0;
			System.out.println("Connection established     :");

			out=new ObjectOutputStream(connection.getOutputStream());
			out.flush();
			in=new ObjectInputStream(connection.getInputStream());
			out.writeObject("Connected    .");
			do{
				try{
					String demoData="";
					packet=(String)in.readObject();		boolean flag=false;
					if(packet == "end")	break;
					if(Integer.valueOf(packet.substring(0,1))==sequence){
						System.out.println("Receiver side   >"+packet);
						
						String divisor=new Integer(110101).toString();
						String extractedData = packet.substring(1, 7+divisor.length());		demoData=extractedData;
						System.out.println("extractedData: "+extractedData);
						
						Modulo2BinaryDivision hel=new Modulo2BinaryDivision();
						String remainder=hel.encodeData(extractedData, divisor);
						
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
						sequence=(sequence==0)?1:0;
						System.out.println("Message received so far: "+data);
					}else{
						System.out.println("\nReceiver side    >"+packet +"   duplicate data\n");
					}
					/*
                    			when i==3 then i destroy the ack
					 */
					if(i<3){
						out.writeObject(String.valueOf(sequence));i++;
					}else{
						out.writeObject(String.valueOf((sequence+1)%2));i=0;
					}
					if(flag==true) {
						System.out.println("Retransmitted data");
						String integerPart=demoData.substring(0,7);
						int messageReceivedinInteger = Integer.parseInt(integerPart, 2);
						char characterPart=(char)(messageReceivedinInteger);
						System.out.println("Message received from sender: " + characterPart);
						data+=characterPart;
						System.out.println("Message received so far: "+data);
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
	//Check if remainder is zero
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
		StopAndWaitReceiver s=new StopAndWaitReceiver();
		while(true){
			s.run();
		}
	}
}
