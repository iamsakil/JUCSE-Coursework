import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.*;

public class ClientHandler extends Thread{
	 DataInputStream dis;
	 DataOutputStream dos;
	 Socket s;
	 ServerData data;
	 char status='g';
	 /*public ClientHandler(Socket s,DataInputStream dis,DataOutputStream dos)
	 {
		 this.s=s;
		 this.dos=dos;
		 this.dis=dis;
	 }*/
	 public ClientHandler(Socket s,DataInputStream dis,DataOutputStream dos,ServerData data)
	 {
		 this.s=s;
		 this.dos=dos;
		 this.dis=dis;
		 this.data=data;
	 }
	 public void run()
	 {
		String send="",command="",val="",val2="";
		while(true)
		{
			try {
					dos.writeUTF("Hey,You are now connected!..");
					int sz=Integer.parseInt(dis.readUTF());
					String[] cd=new String[sz];
					for(int i=0;i<sz;i++)
					{
						cd[i]=dis.readUTF();
					}
					String[] res=new String[sz];
					int indx=0;
					for(int i=0;i<sz;)
					{
						//System.out.print("Processing:");
						if(cd[i].equals("put"))
						{
							//System.out.print(" "+cd[i]+" ");
							i++;
							//System.out.print(" "+cd[i]+" ");
							val=cd[i++];
							val2="";
							while(true)
							{
								if(cd[i].equals("get"))
									break;
								if(cd[i].equals("put"))
									break;
								if(cd[i].equals("upgrade"))
									break;
								if(cd[i].equals("degrade")) 
									break;							
								val2=val2+cd[i];
								System.out.println(val2);
								i++;
							}
							pair p=new pair(this.s,val2);
							data.setMap(val,p);
						}
						else if(cd[i].equals("get"))
						{
							//System.out.print(" "+cd[i]+" ");
							i++;
							//System.out.print(" "+cd[i]+" \n");
							val=cd[i++];
							String ans=data.getMap(val,this.status,this.s);
							res[indx++]=ans;
						}
						else if(cd[i].equals("upgrade"))
						{
							//System.out.print(" "+cd[i]+" \n");
							i++;
							upgrade();
						}
						else if(cd[i].equals("degrade"))
						{
							//System.out.print(" "+cd[i]+" \n");
							i++;
							degrade();
						}
						/*else
						{
							i++;
							System.out.println("Unknown Command");
							res[indx++]="UnknownCommand";
						}*/
					}
					dos.writeUTF(Integer.toString(indx));
					for(int i=0;i<indx;i++)
					{
						dos.writeUTF(res[i]);
					}
					System.out.println("\nClosing connection:"+s);
					this.s.close();
					break;

				} catch (IOException e) {
					e.printStackTrace();
				} 
		}
		try {
			this.s.close();
			this.dis.close();
			this.dos.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	void upgrade()
	{
		status='m';
	}
	void degrade()
	{
		status='g';
	}
}
