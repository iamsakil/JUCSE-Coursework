#include <bits/stdc++.h>

using namespace std;
 
int main()
{
    int i,j,k,l;
     
    //Get Frame
    char str[256];
	string t="";
	char tmp[8];

  	cout << "\n Enter the name of an existing text file: ";
  	cin.get (str,256);    // get c-string

  	ifstream file(str);     // open file

	if(file.is_open())
	{
		char ch;
	  	while (file.get(ch))          // loop getting single characters
	    {
			itoa(ch,tmp, 2);
			t+=tmp;
	    	cout<<"\n "<<ch<<" ==> "<<tmp<<endl;
		}
		cout<<"\n Complete message in binary: "<<t<<endl;
	
	  	file.close();                // close file
	}
	else
	{
		cout<<"\n No such file exists"<<endl;
		return 0;
	}
	
  	int fs = t.length();
  	int f[fs];
  	
  	for(i=0;i<fs;i++)
    {
        if(t[i]=='0')
        {
        	f[i]=0;
		}
		else
		{
			f[i]=1;
		}
    }
    
    cout<<"\n Frame: ";
    for(i=0;i<fs;i++)
    {
        cout<<f[i];
    }
    
    //Get Generator
    int gs;
    string gstr;
    
    cout<<"\n Enter Generator:";
    cin>>gstr;
    gs=gstr.length();
    int g[gs];
    
    for(i=0;i<gs;i++)
    {
        if(gstr[i]=='0')
        {
        	g[i]=0;
		}
		else
		{
			g[i]=1;
		}
    }
 
    cout<<"\n SENDER SIDE:\n";
    cout<<"\n Frame: ";
    for(i=0;i<fs;i++)
    {
        cout<<f[i];
    }
    cout<<"\n Generator :";
    for(i=0;i<gs;i++)
    {
        cout<<g[i];
    }
 
    //Append 0's
    int rs=gs-1;
    cout<<"\n\n Number of 0's to be appended: "<<rs;
    for (i=fs;i<fs+rs;i++)
    {
        f[i]=0;
    }
 
    int temp[fs+rs];
    for(i=0;i<fs+rs;i++)
    {
        temp[i]=f[i];
    }
 
    cout<<"\n Message after appending 0's :";
    for(i=0; i<fs+rs;i++)
    {
        cout<<temp[i];
    }
 
    //Division
    for(i=0;i<fs;i++)
    {
        j=0;
        k=i;
        if(i==fs)
        	break;
        //check whether it is divisible or not
        if (temp[k]>=g[j])
        {
            for(j=0,k=i;j<gs;j++,k++)
            {
                if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
                {
                    temp[k]=0;
                }
                else
                {
                    temp[k]=1;
                }
            }
        }
    }
 
    //CRC
    int crc[rs];
    for(i=0,j=fs;i<rs;i++,j++)
    {
        crc[i]=temp[j];
    }
 
    cout<<"\n\n CRC bits: ";
    for(i=0;i<rs;i++)
    {
        cout<<crc[i];
    }
 
    cout<<"\n Transmitted Frame: ";
    int tf[fs+rs];
    for(i=0;i<fs;i++)
    {
        tf[i]=f[i];
    }
    for(i=fs,j=0;i<fs+rs;i++,j++)
    {
        tf[i]=crc[j];
    }
    for(i=0;i<fs+rs;i++)
    {
        cout<<tf[i];
    }
    
    //----------------------------------------------------------------------------------------------------------------------
    ofstream inter("INTERMEDIATE.txt");
    if(inter.is_open())
    {
    	for(i=0;i<fs+rs;i++)
	    {
	        inter<<tf[i];
	    }
	    inter.close();
	}
	else
	{
		cout<<"\n Unable to open INTERMEDIATE.txt\n";
		return 0;
	}
    //--------------------------------------
    cout<<"\n\n The frame is being transmitted now....";
    cout<<"\n If you want to put error in the data, do it now in INTERMEDIATE.txt";
    return 0;
}
