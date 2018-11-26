import java.io.*;
import java.util.*;

class Tuple{
	int arr[];
	int len;

	Tuple(int cons,int size)
	{
		arr=new int[size];
		len=size;
		for(int i=0;i<size;i++)
			arr[i]=cons;
	}

	Tuple(int data[])
	{
		len=data.length;
		arr=new int[len];
		for(int i=0;i<len;i++)
			arr[i]=data[i];
		System.out.println(this);
	}

	void constMult(int cons)
	{
		for(int i=0;i<len;i++)
			arr[i]*=cons;
	}

	void add(Tuple t)
	{
		for(int i=0;i<len;i++)
			arr[i]+=t.arr[i];
	}

	int dot(Tuple t)
	{
		int res=0;
		for(int i=0;i<t.len;i++)
			res+=arr[i]*t.arr[i];
		return res;
	}

	public String toString()
	{
		String s=Integer.toString(arr[0]);
		for(int i=1;i<len;i++)
			s=s+", "+Integer.toString(arr[i]);
		return s;
	}
}
public class cdma {

	static int max(int arr[])
	{
		int max=arr[0];
		for(int i=1;i<arr.length;i++)
			if(arr[i]>max)
				max=arr[i];
		return max;
	}
	static int[][] makeWalsh(int n) 
	{
		int[][] W=new int[n][n];
		int power = 1;
		int i,j,k,l,p=0;
		W[0][0]=-1;  
		while (power < n) 
		{
		    for(i=0; i<2; i++) 
			{
				for(j=0; j<2; j++) 
				{
					if (!(i==0 && j==0)) 
					{
						for(k=0; k<power; k++) 
						{
							for(l=0; l<power; l++) 
							{
								if (i==1 && j == 1)
									W[i*power+k][j*power+l] = -W[k][l]; 
								else
									W[i*power+k][j*power+l] = W[k][l]; 
							}
						}
					}
				}
		    }
		    power *=2;
		}
		return W;
	}
	public static void main(String[] args) {
		String data[]=new String[4];
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter what SenderA sends:");
		data[0]=sc.next();
		System.out.println("Enter what SenderB sends:");
		data[1]=sc.next();
		System.out.println("Enter what SenderC sends:");
		data[2]=sc.next();
		System.out.println("Enter what SenderD sends:");
		data[3]=sc.next();
		//String data[]={"110011","1010","11010","001"};
		/*String dataA="110011";
		String dataB="1010";
		String dataC="11010";
		String dataD="001";
		*/

		int lendata[];
		lendata=new int[4];
		for(int i=0;i<4;i++){
			System.out.println("Sender"+(char)('A'+i)+" wants to send "+data[i]);
			lendata[i]=data[i].length();
		}

		/*int lendataA=dataA.length();
		int lendataB=dataB.length();
		int lendataC=dataC.length();
		int lendataD=dataD.length();

		System.out.println("SenderA wants to send "+dataA);
		System.out.println("SenderB wants to send "+dataB);
		System.out.println("SenderC wants to send "+dataC);
		System.out.println("SenderC wants to send "+dataD);
		*/
		//int walsh[][4];
		//walsh=new int[4][4];
		int walsh[][]=makeWalsh(4);
		System.out.println("Walsh Table Generated:");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(walsh[i][j]==-1)
					System.out.print(" "+walsh[i][j]);
				else
					System.out.print("  "+walsh[i][j]);
			}
			System.out.println();
		}
		for(int i=0;i<max(lendata);i++){
			Tuple channeldata=new Tuple(0,4); // constructor
			for(int j=0;j<4;j++){
				int currdata=0;
				if(data[j].length()>=(i+1)){
					if(data[j].charAt(i)=='1')
						currdata=1;
					else
						currdata=-1;
					System.out.println("Sender"+(char)('A'+j)+"\nData bit: "+currdata);
				}
				else
					System.out.println("Sender"+(char)('A'+j)+"\nData bit: No data to send(silent)");
				System.out.println("Sending bit: "+currdata);
				Tuple temp=new Tuple(walsh[j]);  
				System.out.println("Walsh sequence: "+temp);
				temp.constMult(currdata); 
				System.out.println("Contribution to channel: "+temp);
				channeldata.add(temp);   
				System.out.println();
			}
			System.out.println("Channel data: "+channeldata);	// override toString
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				System.err.println("Interrupted: Interrupt exception");
			}

			for(int j=0;j<4;j++){
				System.out.println("Receiver"+(char)('A'+j)+"\nChannel data (D): "+channeldata);
				Tuple temp=new Tuple(walsh[j]);
				System.out.println("Walsh sequence of Sender"+(char)('A'+j)+" (C): "+temp);
				int dotprod=channeldata.dot(temp);
				System.out.println("D.C = "+dotprod);
				int extracted_data=dotprod/4;
				System.out.println("Bit sent by Sender"+(char)('A'+j)+": "+extracted_data);
				if(extracted_data==0)
					System.out.println("Sender"+(char)('A'+j)+" silent");
				else if(extracted_data==1)
					System.out.println("Sender"+(char)('A'+j)+" sent data-bit: 1");
				else 
					System.out.println("Sender"+(char)('A'+j)+" sent data-bit: 0");
			}
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				System.err.println("Interrupted: Interrupt exception");
			}
		}	
	}
}
