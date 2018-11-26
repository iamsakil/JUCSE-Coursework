#include <bits/stdc++.h>

using namespace std;
 
int main()
{
    int i,j,k,l;
    int fs;
    
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
    cout<<"\n Generator :";
    for(i=0;i<gs;i++)
    {
        cout<<g[i];
    }
 
    //0's to append
    int rs=gs-1;
    
    //Counting number of characters in the file
    ifstream inter1;
	inter1.open("INTERMEDIATE.txt");
    if(inter1.is_open())
    {
    	
    	char single_char;
    	i=0;
	  	while (inter1.get(single_char))          // loop getting single characters
	    {
			i++;
		}
		fs=(i+1)-rs;
	    inter1.close();
	}
	else
	{
		cout<<"\n Unable to open INTERMEDIATE.txt\n";
		return 0;
	}
    
    int tf[fs+rs];
    
	//-----------------------------------------------------------------------------
	ifstream inter2;
	inter2.open("INTERMEDIATE.txt");
    if(inter2.is_open())
    {
    	
    	char single_char;
    	i=0;
	  	while (inter2.get(single_char))          // loop getting single characters
	    {
			tf[i]=single_char-'0';
			i++;
		}
	    inter2.close();
	}
	else
	{
		cout<<"\n Unable to open INTERMEDIATE.txt\n";
		return 0;
	}
 	//-------------------------------------------------------------------------------


    cout<<"\n Receiver side : ";
    cout<<"\n Received Frame: ";
    for(i=0;i<fs+rs;i++)
    {
        cout<<tf[i];
    }
    
    int temp[fs+rs];
    cout<<endl;
    for(i=0;i<fs+rs;i++)
    {
        temp[i]=tf[i];
    }
 
    //Division
    for(i=0;i<fs+rs;i++)
    {
        j=0;
        k=i;
        if(i==fs)
        	break;
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
 
    cout<<"\n Remainder: ";
    int rrem[rs];
    for (i=fs,j=0;i<fs+rs;i++,j++)
    {
        rrem[j]= temp[i];
    }
    for(i=0;i<rs;i++)
    {
        cout<<rrem[i];
    }
 
    int flag=0;
    for(i=0;i<rs;i++)
    {
        if(rrem[i]!=0)
        {
            flag=1;
        }
    }
 
    if(flag==0)
    {
        cout<<"\n Since Remainder Is 0 Hence Message Transmitted From Sender To Receriver Is Correct";
    }
    else
    {
        cout<<"\n Since Remainder Is Not 0 Hence Message Transmitted From Sender To Receriver Contains Error";
    }
    return 0;
}
