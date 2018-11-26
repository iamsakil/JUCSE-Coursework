import java.io.*;
import java.util.*;
import java.lang.*;

class Tuple{
	int a[];
	int l;
	Tuple(int s){
		a=new int[s];
		l=s;
	}
	Tuple(int d[]){
		l=d.length;
		a=new int[l];
		for(int i=0;i<l;i++)
			a[i]=d[i];
	}
	void constMult(int cons){
		for(int i=0;i<l;i++)
			a[i]*=cons;
	}
	void add(Tuple t){
		for(int i=0;i<l;i++)
			a[i]+=t.a[i];
	}
	int dot(Tuple t){
		int r=0;
		for(int i=0;i<t.l;i++)
			r+=a[i]*t.a[i];
		return r;
	}
	@Override
	public String toString(){
		String s=Integer.toString(a[0]);
		for(int i=1;i<l;i++){
			s=s+", "+Integer.toString(a[i]);
		}
		return s;
	}
}
public class WW {

	static int max(int a[]){
		int m=a[a.length-1];
		for(int i=a.length-2;i>=0;i--)
			if(a[i]>m)
				m=a[i];
		return m;
	}
	static int[][] makeWalsh(int n) {
		  int[][] W=new int[n][n];
		  int pow = 1;
		  int i,j,k,l,p=0;
		  W[0][0]=-1;

		  while (pow < n) {
		    for(i=0; i<2; i++) {
		      for(j=0; j<2; j++) {
			if (!(i==0 && j==0)) {
			  for(k=0; k<pow; k++) {
			    for(l=0; l<pow; l++) {
			      if (i==1 && j == 1) {
				W[i*pow+k][j*pow+l] = -W[k][l]; 
			      }
			      else {
				W[i*pow+k][j*pow+l] = W[k][l]; 
			      }
			    }
			  }
			}
		      }
		    }
		    pow *=2;
		  }
		  return W;
	}
	static boolean isPow2(int n) {
		if(n<1) 
			return false;
		else if(n==1)
			return true;
		while(n>1) 
		{
			if (n%2==1) 
				return false;
			n=n/2;
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter number of Senders(and Receivers)(power of 2):");
		int n=sc.nextInt();
		if(!isPow2(n))
		{
			System.out.println(n+" is not power of 2");
			System.exit(1);
		}
		String d[]=new String[n];
		for(int i=0;i<n;i++)
		{
			System.out.print("Enter what Sender"+(char)('A'+i)+" sends:");
			d[i]=sc.next();
		}
		int len_d[];
		len_d=new int[n];
		for(int i=0;i<n;i++)
			len_d[i]=d[i].length();
		int walsh[][]=makeWalsh(4);
		System.out.println("Walsh Table Generated:");
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(walsh[i][j]==-1)
					System.out.print(" "+walsh[i][j]);
				else
					System.out.print("  "+walsh[i][j]);
			}
			System.out.println();
		}

		for(int i=0;i<max(len_d);i++){
			System.out.println();
			//System.out.println();
			Tuple ch_d=new Tuple(n);
			for(int j=0;j<n;j++){
				int send=0;
				if(d[j].length()>=(i+1))
				{
					if(d[j].charAt(i)=='1')
						send=1;
					else
						send=-1;
					System.out.println("Sender"+(char)('A'+j)+"\nData bit: "+d[j].charAt(i));
				}
				else
					System.out.println("Sender"+(char)('A'+j)+"\nData bit: No data to send(silent)");
				System.out.println("Sending bit(s): "+send);
				Tuple temp=new Tuple(walsh[j]);  
				System.out.println("Walsh sequence(w): "+temp);
				temp.constMult(send);
				System.out.println("s.w: "+temp);
				ch_d.add(temp);  
				//System.out.println();
			}
			System.out.println();
			System.out.println("Channel data: "+ch_d);	
			System.out.println();
			for(int j=0;j<n;j++){
				//System.out.println();
				System.out.println("Receiver"+(char)('A'+j)+"\nChannel d (D): "+ch_d);
				Tuple temp=new Tuple(walsh[j]);
				System.out.println("Walsh sequence of Sender"+(char)('A'+j)+" (C): "+temp);
				int dotprod=ch_d.dot(temp);
				System.out.println("D.C = "+dotprod);
				int extracted_d=dotprod/4;
				System.out.println("Bit received by Receiver"+(char)('A'+j)+": "+extracted_d);
				if(extracted_d==0)
					System.out.println("No data received by Receiver"+(char)('A'+j));
				else if(extracted_d==1)
					System.out.println("Receiver"+(char)('A'+j)+" received data-bit: 1");
				else 
					System.out.println("Receiver"+(char)('A'+j)+" received data-bit: 0");
			}			
		}	
	}
}
