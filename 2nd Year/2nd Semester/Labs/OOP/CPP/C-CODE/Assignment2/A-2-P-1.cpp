#include <iostream>
#include <cstdlib>
#include<ctime>

using namespace std;
class coin{
	private:
		int x,i=0,count = 0;
	public:
		void flip(){
			srand(time(NULL));			//seed a different value at each run
			while(count<3)
			{
				x= rand()%2;			//generate 0 or 1 randomly
				i++;					//increment toss count
				if(x==0)
				{
					cout<<"heads\n";
					count++;			//increment heads count
				}else
				{
					cout<<"tails\n";
					count=0;			//reset heads count
				}
			}
		cout<<"\n\n It took "<<i<<" coinflips to get three consecutive heads\n";
		}	
};
int main()
{
	coin sample;
	sample.flip();
	return 0;

}
