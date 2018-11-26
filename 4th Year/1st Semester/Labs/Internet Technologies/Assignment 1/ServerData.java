import java.net.Socket;
import java.util.*;

public class ServerData {
	public HashMap<String,pair> map=new HashMap<>();
	void setMap(String s,pair p)
	{
		map.put(s,p);
	}
	String getMap(String str,char access,Socket s)
	{
		if(map.containsKey(str))
		{
			pair p=map.get(str);
			if(p.s==s)
			{
				return p.value;
			}
			else if(access=='m')
			{
				return p.value;
			}
			else return "";
		}
		else return "";
	}
	
}
