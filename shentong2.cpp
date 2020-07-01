#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
	int w,h,s,t,k,P,Q,xmax,ymax,m;
	cin >> w >> h >> s >> t >> k >> P >> Q;
	int X[k],Y[k],W[k],H[k];
	int count = 0;
	int i,j;
	int x_i,y_j;
	int anchor_x_min,anchor_x_max,anchor_y_min,anchor_y_max;
	int bbox_x_max,bbox_y_max;
	x_i = floor(float(P-w)/float(s));
	y_j = floor(float(Q-h)/float(t));
	for(i=0;i<k;i++)
	{
		cin >> X[i] >> Y[i] >> W[i] >> H[i];
	}
	
	for(i=0;i<=x_i;i++)
	{
		for(j=0;j<=y_j;j++)
		{
			anchor_x_min = s*i;
			anchor_y_min = t*j;
			anchor_x_max = s*i+w;
			anchor_y_max = t*j+h;
			for(m=0;m<k;m++)
			{
				bbox_x_max = X[m]+W[m];
				bbox_y_max = Y[m]+H[m];
				if(X[m]>x_i*s+w)
				{
					continue;
				}
				if(Y[m]>y_j*t+h)
				{
					continue;
				}
				if(bbox_x_max>x_i*s+w)
				{
					bbox_x_max = x_i*s+w;
				}
				if(bbox_y_max>y_j*t+h)
				{
					bbox_y_max = y_j*t+h;
				}
				
				
				if(X[m]>=anchor_x_max||anchor_y_max<=Y[m]||bbox_x_max<=anchor_x_min||bbox_y_max<=anchor_y_min)
				{
					continue;
				}
				else
				{
//					cout << "count++";
					count++;
					break;
				}	
			}
			
			
		}
	}
	cout <<count;
	
	
	
	return 0;	
} 
