#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// z = 1
int putong(int d,int p)
{
	d = d + p;
	return d;
}
	
// z = 2
int beizeng(int d,int p)
{
	d = d * p;
	return d;
}	
	
// z = 3
int juji(int d,int p)
{
	d = ceil(d/p);
	return d;
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int d=1;
    int k,i;
    int a[1000],b[1000];
    cin >> k;
    for(i=0;i<k;i++)
    {
    	cin >> a[i] >> b[i];
	}
	for(i=0;i<k;i++)
	{
		if(a[i]==1)
		{
			d = putong(d,b[i]);
		}
		if(a[i]==2)
		{
			d = beizeng(d,b[i]);
		}
		if(a[i]==3)
		{
			d = juji(d,b[i]);
		}		
	}
	cout <<  d; 
    return 0;
}

