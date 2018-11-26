

import java.lang.Thread;
import java.lang.Math;
import java.io.*;
import java.util.*;

class backoffTimer {
	
	public int backoffTime(int transNum) { 
		int rndom;
		int temp;
		temp=Math.min(transNum,10);
		rndom=(int)(Math.random()*(Math.pow(2,temp)-1))+1;
		return rndom; 
	}
}

class Sender extends Thread {
	private int count = 0;			
	public static Integer bus = 0;	
	private String name;			
	private int num;				
	private int propDelay;			

	public Sender(String name, int total, int propDelay) { 
		this.name = name;
		num = total;
		this.propDelay = propDelay;
	}
	public void run() {
		
		int time;
		for (int n = 1; n <= num; n++) {
			
			count = 0;
			while (count < 10) {
				//System.out.println("Sensing channel...");
				int collide=0;
				if(bus==0) {
					bus++;
					System.out.println(name+" finds channel idle\n"+name+" transmitting "+"packet "+n+"\nChannel now busy");
					collide=0;
					for(float f=-10000;f<=10000;f++)
						if(bus>1) 
							collide=1;
					//} catch (InterruptedException e) {
					//	System.err.println("Interrupted: Interrupt exception");
					//}
				}
				else {
					System.out.println(name+ " finds channel busy. Continue sensing...");
					continue;
				}    
				
				//try {
				for(float f=-10000;f<=10000;f++) 
					if(bus>1) 
						collide=bus;
				//} catch (InterruptedException e) {
				//	System.err.println("Interrupted: Interrupt exception");
				//}
				
				
				
				if(collide==0){
					System.out.println(name+" Packet: " +n+ " Sent successfully!");
					bus--;
					break;
				}
				else{
					count++;
					System.out.println(name+" Packet: " +n+" Collision "+count);
					backoffTimer timer = new backoffTimer();
					int bckof=2*propDelay*timer.backoffTime(count);
					System.out.println(name+" backing off for "+(bckof));
					collide=0;
					synchronized(bus){
						bus=0;
					}
					try {
						Thread.sleep(bckof);
					} catch (InterruptedException e) {
						System.err.println("Interrupted: Interrupt exception");
					}
					continue;
				}
				
			}
			if (count >= 10){
				System.out.println("Node " + name + " Packet: " +n+ " Transmission failure.");
			}
		}
	}	
}

public class CSMACD {
	public static void main(String[] args) {
		
		int nodeNumber;					
		int transNumber;				
		int delayTime;					
		
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter the number of Servers:");
		nodeNumber=scan.nextInt();
		 
		System.out.println("Enter the number of transmissions:(per node)");
		transNumber=scan.nextInt();
		       
		System.out.println("Enter the propagation delay time:");
		delayTime=scan.nextInt();
		 
		Sender[] Senders=new Sender[nodeNumber];
		for(int j=0;j<nodeNumber;j++){
			Senders[j]=new Sender("Node_"+j,transNumber,delayTime);
		}
		for (int i = 0; i < nodeNumber; i++) {
			Senders[i].start();
		}
	}
}
