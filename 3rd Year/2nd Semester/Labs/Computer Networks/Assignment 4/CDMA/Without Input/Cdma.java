class Chips{
	int arr[];
	int len;

	Chips(int size){
        int init = 0;
		arr=new int[size];
		len=size;
		for(int i=0;i<size;i++)
			arr[i]=init;
	}

	Chips(int data[]){
		len=data.length;
		arr=new int[len];
		for(int i=0;i<len;i++)
			arr[i]=data[i];
		//System.out.println(this);
	}

	void constantMult(int cons){
		for(int i=0;i<len;i++)
			arr[i]*=cons;
	}

	void add(Chips t){
		for(int i=0;i<len;i++)
			arr[i]+=t.arr[i];
	}

	int dot(Chips t){
		int res=0;
		for(int i=0;i<t.len;i++)
			res+=arr[i]*t.arr[i];
		return res;
	}

    @Override
	public String toString(){
		String s=Integer.toString(arr[0]);
		for(int i=1;i<len;i++){
			s=s+", "+Integer.toString(arr[i]);
		}
		//System.out.println("In func "+s);;
		return s;
	}
}

public class Cdma {

	static int max(int arr[]){
		int max=arr[0];
		for(int i=1;i<arr.length;i++)
			if(arr[i]>max)
				max=arr[i];
		return max;
	}

	public static void main(String[] args) {
        //System.out.println("Hi!");
        int num = 4;
		String data[]={"100","1010","110","001"};
		
		int lendata[]=new int[num];
		for(int i=0;i<num;i++){
			System.out.println("Sender "+(char)('A'+i)+" wants to send "+data[i]);
			lendata[i]=data[i].length();
		}
		int walsh[][]=	{{1,1,1,1},
						{1,-1,1,-1},
						{1,1,-1,-1},
						{1,-1,-1,1}};
        int count = max(lendata);
		for(int i=0;i<count;i++){
			Chips channeldata=new Chips(num); // constructor to make all 0 array
            System.out.println();
            System.out.println("Sending - ");
			for(int j=0;j<4;j++){
				int currdata=0;
				if(data[j].length()>i){
					if(data[j].charAt(i)=='1')
						currdata=1;
					else
						currdata=-1;
					System.out.println("Sender "+(char)('A'+j)+" sends - "+currdata);
				}
				else
					System.out.println("Sender "+(char)('A'+j)+" is silent - 0");
				//System.out.println("Sending bit: "+currdata);
				//System.out.println(walsh[j]);
				Chips temp=new Chips(walsh[j]);   // constructor to initialise with walsh
				System.out.print("Walsh sequence: "+temp+". -> ");
				temp.constantMult(currdata);  // contant multiply
				System.out.println(temp);
				channeldata.add(temp);   // add the data to channel
				System.out.println();
			}
			System.out.println("Channel contains - "+channeldata);	// override toString
			System.out.println();
            System.out.println("Receiving - ");
            int dataBit;
			for(int j=0;j<num;j++){
				Chips temp=new Chips(walsh[j]);
				System.out.println("Walsh sequence of Sender "+(char)('A'+j)+" - "+temp);
				dataBit=channeldata.dot(temp)/num;
				
				//System.out.println("Bit sent by Sender"+(char)('A'+j)+": "+data);
				if(dataBit==0)
					System.out.println("Sender "+(char)('A'+j)+" silent");
				else if(dataBit==1)
					System.out.println("Sender "+(char)('A'+j)+" sent: 1");
				else 
					System.out.println("Sender "+(char)('A'+j)+" sent: 0");
			}
		}	
	}
}
