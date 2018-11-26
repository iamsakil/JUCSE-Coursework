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
	public static int bus = 0;		/**< status indicator of bus whether that is occupied or not 0= bus not idle, 1= sent, 2=collission*/
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
			try {
				Thread.sleep((int) (Math.random() * propDelay) / 2); 
			} catch (InterruptedException e) { 
				System.err.println("Interrupted: Interrupt exception ");
			}
			//Starts sending output host ID starting time of transmission
			count = 0;
			//try to send: 10 times..
			while (count < 10) {
				//According to the situation of the bus, do transmission-retransmission
				//bus = 0 means:: bus is not idle
				if(bus==0) {
					try {
						Thread.sleep(propDelay);
					} catch (InterruptedException e) {
						System.err.println("Interrupted: Interrupt exception");
					}
					bus++;       
				}
				else {
					//System.out.println("Shared bus is non-idle");
					continue;
				}    
				
				try {
					Thread.sleep(propDelay);
				} catch (InterruptedException e) {
					System.err.println("Interrupted: Interrupt exception");
				}
				
				//bus = 1 means:: bus empty, packet successfully sent to destination
				if(bus==1) {
					System.out.println("Host["+name+"]Packet " +n+ " Sent successfully!");
					bus=0;
					break;
				}
				
				//bus = 2 means:: collision between packets while trying to sent them
				if(bus==2) {
					count++;
					System.out.println("Host computer["+name+"]Packet " +count+ " Collision!");
					bus=0;
					//increase idle time after each failed transmission
					try {
						backoffTimer timer = new backoffTimer();
						Thread.sleep(2*propDelay*timer.backoffTime(count));
					} catch (InterruptedException e) {
						System.err.println("Interrupted: Interrupt exception");
					}
					continue;
				}
			}
			//Retransmission failed for last 10 times? Transmission failure.
			if (count >= 10){
				System.out.println("Host computer[" + name + "]Packet " +n+ " transmission failure.");
			}
		}
	}
}

public class CSMA {
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
