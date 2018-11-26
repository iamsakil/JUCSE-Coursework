class CSMA
{
	ArrayList<Thread> senders;
	ArrayList<Thread> receivers; 
	
	CSMA()
	{
		senders=new ArrayList<>(4);
		receivers=new ArrayList<>(4);
	}
	void addSender(Thread s)
	{
		senders.add(s);
	}
	void addReceiver(Thread r)
	{
		receivers.add(r);
	}
}
class Channel
{
	String message;
	int sender,receiver;
	synchronised void setStations(int s,int r,String m)
	{
		message=m;
		sender=s;
		receiver=r;
		System.out.println("Now sender "+
	}
