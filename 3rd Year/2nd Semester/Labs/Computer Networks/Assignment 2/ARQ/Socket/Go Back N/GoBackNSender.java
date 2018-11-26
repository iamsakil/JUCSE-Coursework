/*
    Go Back N Sender
*/
import java.io.*;
import java.net.*;
import java.util.*;

public class GoBackNSender{
    Socket sender;
    ObjectOutputStream out;
    ObjectInputStream in;
    String packet,ack,str, msg;
    int n,i=0;
    GoBackNSender(){}
    public void run(){
        try{
            BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Waiting for Connection....");
            sender = new Socket("localhost",2004);
            
            out=new ObjectOutputStream(sender.getOutputStream());
            out.flush();
            in=new ObjectInputStream(sender.getInputStream());
            str=(String)in.readObject();
            System.out.println("receiver    > "+str);
            
            System.out.print("Enter the size of Sequence number field in bits: ");
            Scanner sc=new Scanner(System.in);
            int seqNoSize=sc.nextInt();
            final int slidingWindowSize=(int) Math.pow(2, seqNoSize)-1;
			Integer slid=slidingWindowSize;
			
			String sld=slid.toString();
			
			out.writeObject(sld);
            
            System.out.print("Enter the data to send: ");
            packet=br.readLine();
            n=packet.length();
			Random rand = new Random();
            
            int sf=0, sn=0, tempSn=0;
            Queue<String> q=new LinkedList<>();
			boolean requestToSend=true;
            
            do{
                try{
					if(requestToSend==true) {
						if((sn-sf) >= slidingWindowSize)	Thread.sleep(2000);
						if(i<n){
							msg=String.valueOf(sn);		//makeFrame(sn)
							
							String dividendo=Integer.toBinaryString(packet.charAt(i)).toString();
							String divisor=new Integer(110101).toString();
							
							// Appends n-1 zeroes at end of data
							String appended_data = dividendo + appendZeros(divisor.length());
							System.out.println("appended data: "+appended_data);
							
							String remainder=Modulo2BinaryDivision.encodeData(appended_data, divisor);
							dividendo+=remainder;
							String finalMsg="";
							
							int errorDeceision = rand.nextInt(2);
							if(errorDeceision==1) {
								System.out.println("Error injecting...");
								int randPosition = rand.nextInt(dividendo.length());
								char ch;
								if(dividendo.charAt(randPosition)=='1')	ch='0';
								else	ch='1';
								String errorDividendo = dividendo.substring(0,randPosition)+ch+dividendo.substring(randPosition+1);
								finalMsg+=errorDividendo;
							}
							else	finalMsg+=dividendo;
							           
							int sz=finalMsg.length();
							finalMsg=dividendo; 
							for(int j=sz;j<16;j++)	finalMsg+='0';
							
							msg+='-'+finalMsg;	//getdata()
							
							q.add(msg);		//storeFrame(sn)
							out.writeObject(msg);	//sendFrame(sn)
							tempSn=(sn+1);	//sn=sn+1
							sn = tempSn % slidingWindowSize;
							System.out.println("After sending sn: "+sn);
							
							out.flush();
							System.out.println("data sent>"+msg);
							System.out.println("waiting for ack.....");
						}
						else if(i==n){
							msg="end";out.writeObject(msg);break;
						}
						requestToSend=false;
					}
                    
                    ack=(String)in.readObject();
                    int ackNo=Integer.parseInt(ack);
					
					System.out.println("Ackno: "+ackNo+" sn: "+sn+" sf: "+sf); 
                    
                    if(((ackNo>sf) || (ackNo==0 && sf==(slidingWindowSize-1))) && (ackNo<=sn)) {	//if a valid ack
                        i++;
                        System.out.println("Receiver    >  "+" packet received");
                        while(sf < ackNo) {
                        	q.remove();
                        	sf=(sf+1)%slidingWindowSize;
							System.out.println("After ack sf: "+sf);
                        }
						if(ackNo==0 && sf==(slidingWindowSize-1)) 	sf=0;
						requestToSend=true;
                    }
                    else{      /* whenever ack lost or wrong ack we change the sequence number
                                */
                        System.out.println("Time out resending data....\n");
                        int temp=sf;
						System.out.println("Curren temp: "+temp);
                        while(temp < tempSn) {
                            msg=String.valueOf(temp)+'-';
                            
                            String dividendo=Integer.toBinaryString(packet.charAt(temp)).toString();
							String divisor=new Integer(110101).toString();
							
							// Appends n-1 zeroes at end of data
							String appended_data = dividendo + appendZeros(divisor.length());
							System.out.println("appended data: "+appended_data);
							
							String remainder=Modulo2BinaryDivision.encodeData(appended_data, divisor);
							dividendo+=remainder;
							String finalMsg=dividendo;
							
							int sz=finalMsg.length();
							for(int j=sz;j<16;j++)	finalMsg+='0';
							
							msg+=finalMsg;
							out.writeObject(msg);	//sendFrame(sn)
							System.out.println("data sent>"+msg);
                            temp++;
                        }
						requestToSend=false;
                    }
                }catch(Exception e){}
            }while(i<n+1);
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
        GoBackNSender s=new GoBackNSender();
            s.run();
    }
}