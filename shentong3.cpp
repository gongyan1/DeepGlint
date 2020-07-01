#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

float sum_1(float *a,int k)
{
	float sum =0;
	int i;
	for(i=0;i<k;i++)
	{
		sum = sum + *(a+i);
	}
	return sum;
}


void softmax(float *x,int k,float *result)
{
	int i;
	float zmax;
	float exp_sum;
	float exp_x[k];
	zmax = *(max_element(x,x+k));
	for(i=0;i<k;i++)
	{
		exp_x[i] = exp(*(x+i)-zmax);  
	}
	exp_sum = sum_1(exp_x,k);
	for(i=0;i<k;i++)
	{
		*(result+i) = exp_x[i]/exp_sum;
	}
}    
    

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int N,M;
	int k = 10;
	int i,j;
	
	cin >> N >> M;
	
	int X[N][1];      //  输入 X 
	float result[k];    // 存放 softmax 返回的10个值 
	float W1[M][N];
	float W2[10][M];
	float Z[10][1];
	float A[M][1];
	
	for(i=0;i<N;i++)
	{
		cin >> X[i][0];
	}
	
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			cin >> W1[i][j];
		}
	}
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<M;j++)
		{
			cin >> W2[i][j];
		}
	}
	
	int q,w,m,n,position,s;
	int P,V,old_value;
	float old_min_p,old_max_p,pp,min_p,max_p;
	int value;	
	bool mark = false;   // 判断类型是否发生变化 
	int old_max_position,old_min_position,new_max_position;
	
	
	// X 对应的结果 
	for(m=0;m<M;m++)
	{
		s=0;
		A[m][s] = 0;
		for(n=0;n<N;n++)
		{
			A[m][s]+=W1[m][n]*X[n][s];
		}
	}
	for(i=0;i<M;i++)
	{
		// relu
		A[i][0] = max(A[i][0],float(0));
	}
		// (10,M) (M,1)
		// 10,1,M
	for(m=0;m<10;m++)
	{
		s=0;
		Z[m][s] = 0;
		for(n=0;n<M;n++)
		{
			Z[m][s]+=W2[m][n]*A[n][s];
		}
	}
	softmax(&Z[0][0],k,result);
	// 概率最大值的位置就是类别所在 
	old_max_position = max_element(result,result+k)-result;
	old_min_position = min_element(result,result+k)-result;
	old_max_p = *(max_element(result,result+k));
	old_min_p = *(min_element(result,result+k));
	// 默认P V 
	P = 0;
	V = 0;
	pp = old_min_p;
	
	
	//  修改 第 i 行，每行有 -128-127的取值 
	for(i=0;i<N;i++)
	{
		// (M,N) (N,1)  
		// M,1,N
		for(j=-128;j<=127;j++)
		{
			old_value = X[i][0];
			X[i][0] = j;
			// A = W1 * X
			for(m=0;m<M;m++)
			{
				s=0;
				A[m][s] = 0;
				for(n=0;n<N;n++)
				{
					A[m][s]+=W1[m][n]*X[n][s];
				}
			}
			// A = relu(A)
			for(n=0;n<M;n++)
			{
				A[n][0] = max(A[n][0],float(0));
			}
			// (10,M) (M,1)
			// 10,1,M
            // Z = W2*A
			for(m=0;m<10;m++)
			{
				s=0;
				Z[m][s] = 0;
				for(n=0;n<M;n++)
				{
					Z[m][s]+=W2[m][n]*A[n][s];
				}
			}
			// Y = softmax(Z)
			softmax(&Z[0][0],k,result);
			// 最大值的位置 
			new_max_position = max_element(result,result+k)-result;
//			cout << "new_max_position:" << new_max_position <<endl; 
			if(new_max_position!=old_max_position)
			{
				mark=true;	
				max_p = *(max_element(result,result+k));
				// 出现更大的 概率，保存新的P，V 
				if(max_p>pp)
				{
					P = i+1;  //  存放p最大的位置
					V = j;  //  存放变化的值 
					pp = max_p;
				}
			}	
			if(!mark)
			{
				min_p = *(min_element(result,result+k));
				if(min_p<pp)
				{
					P = i+1;  //  存放p最大的位置
					V = j;  //  存放变化的值 
					pp = min_p;	
				}
			}
					
			
			X[i][0] = old_value;	
		}
	}
	cout << P <<" "<< V;
	
	
	
	
	
	// 矩阵乘法 
//	for(int m=0;m<SIZE_M;m++){
//		for(int s=0;s<SIZE_S;s++){
//			matrix_result[m][s]=0;//变量使用前记得初始化,否则结果具有不确定性
//			for(int n=0;n<SIZE_N;n++){
//				matrix_result[m][s]+=matrix_a[m][n]*matrix_b[n][s];
//			}
//		}
//	}
//	
	
	
	
	//softmax(&X[0][0],k,result);
	
	return 0;



}

