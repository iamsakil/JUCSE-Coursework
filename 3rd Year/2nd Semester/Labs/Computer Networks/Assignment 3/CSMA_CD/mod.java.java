//package kn1;

import java.lang.Thread;
import java.lang.Math;
import java.io.*;
import java.util.*;
/**
 * CSMA/CD Simulator
 * KN1 - Communication Networks 1
 * TU Darmstadt 
 * Summer 2015
 * Group: A:CSMA/CD
 * @author Pranay Sarkar
 *
 */
 
class backoffTimer {
	/**
	 *
	 * Randomly selected back-off time,
	 * Calculated according to the retransmission number
	 * random multiples by k times for k-th retransmission
	 * @param transNum  : number of retransmission
	 * @return Random multiples
	 */
	public int backoffTime(int transNum) { 
		int rndom;
		int temp;
		temp=Math.min(transNum,10);
		rndom=(int)(Math.random()*(Math.pow(2,temp)-1))+1;
		return rndom; 
	}
}

class virtualHost extends Thread {
	private int count = 0;			/**< Private integer for count for number of collisions */
	public static Integer bus = 0;		/**< status indicator of bus whether that is occupied or not 0= bus not idle, 1= sent, 2=collission*/
	private String name;			/**< Private String variable for Hostname */
	private int num;				/**< Private integer for total number of transmissions */
	private int propDelay;			/**< Private integer for sending delay */

	/**
	 * Default constructor, for hosts, running a common bus (channel)
	 * @param name: Hostname
	 * @param total: Total sending number
	 * @param propDelay: Propagation delay
	 */
	public virtualHost(String name, int total, int propDelay) { 
		this.name = name;
		num = total;
		this.propDelay = propDelay;
	}
	public void run() {
		// TODO Auto-generated method stub
		
		int time;
		//Transmission cycle starts here..
		for (int n = 1; n <= num; n++) {
			//Each host before sending sleep for random time
			//try {
			//	Thread.sleep((int) (Math.random() * propDelay) / 2); 
			//} catch (InterruptedException e) { 
			//	System.err.println("Interrupted: Interrupt exception ");
			//}
			//Starts sending output host ID starting time of transmission
			count = 0;
			//try to send: 10 times..
			while (count < 10) {
				//According to the situation of the bus, do transmission-retransmission
				//bus = 0 means:: bus is not idle
				//System.out.println("Sensing channel...");
				int flag=0,collide=0;
				//synchronized(bus){
					if(bus==0) {
						System.out.println(name+" finds channel idle");
						System.out.println(name+" transmitting "+"packet "+n);
						collide=0;
						System.out.println("Channel now busy");
						bus++;
						flag=1;
					}
				//}
				if(flag==1){
					//try{
						flag=0;
						//Thread.sleep(propDelay);
						for(float f=-10000;f<=10000;f++)
							if(bus>1) collide=1;
					//} catch (InterruptedException e) {
					//	System.err.println("Interrupted: Interrupt exception");
					//}
				}
				
				else {
					System.out.println(name+ "finds channel busy. Continue sensing...");
					continue;
				}    
				
				//try {
					for(float f=-10000;f<=10000;f++) if(bus>1) collide=1;
				//} catch (InterruptedException e) {
				//	System.err.println("Interrupted: Interrupt exception");
				//}
				
				//bus = 1 means:: bus empty, packet successfully sent to destination
				if(collide==0){
					System.out.println(name+" Packet: " +n+ " Sent successfully!");
					synchronized(bus){
						bus=0;
					}
					break;
				}
				else{
					//bus = 2 means:: collision between packets while trying to send them	
					count++;
					System.out.println(name+" Packet: " +n+" Collision "+count);
					backoffTimer timer = new backoffTimer();
					int bckof=2*propDelay*timer.backoffTime(count);
					System.out.println(name+" backing off for "+(bckof));
					synchronized(bus){
						bus=0;
					}
						//increase idle time after each failed transmission
					try {
						Thread.sleep(bckof);
					} catch (InterruptedException e) {
						System.err.println("Interrupted: Interrupt exception");
					}
					continue;
				}
				
			}
			//Retransmission failed for last 10 times? Transmission failure.
			if (count >= 10){
				System.out.println("Node " + name + " Packet: " +n+ " Transmission failure.");
			}
		}
	}	
}

public class CSMACD_Main_GroupA {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		int hostNumber;					/**< Integer containing number of hosts */
		int transNumber;				/**< Integer containing transmission number*/
		int delayTime;					/**< Integer containing propagation delay*/
		
		Scanner scan = new Scanner(System.in);
		//Number of Clients
		System.out.println("Enter the number of hosts:");
		hostNumber=scan.nextInt();
		 
		// Number of transmissions
		System.out.println("Enter the number of transmissions:(per host)");
		transNumber=scan.nextInt();
		       
		//Propagation delay
		System.out.println("Enter the propagation delay time:");
		delayTime=scan.nextInt();
		 
		//Array container of virtual hosts
		virtualHost[] virtualHosts=new virtualHost[hostNumber];
		//Assign each virtual host thread to each of the virtual hosts
		for(int j=0;j<hostNumber;j++){
			virtualHosts[j]=new virtualHost("Node_"+j,transNumber,delayTime);
		}
	 	//Starting host threads (start sending)
		for (int i = 0; i < hostNumber; i++) {
			virtualHosts[i].start();
		}
	}
}
