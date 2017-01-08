#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define max 8
int w[max], p[max];
int i,j;
int n,m;
int y[max],x[max];
int fp=-1;
int fw;

int 
create_items(){
    int i=0;
    srand(time(NULL));
    
    while(i < 4){
        i = rand() % 9;
    }
    
    printf("No of items choosen randomly between[4-8] %d\n\n", i);
    return i;
}


void
create_profit_weight(){
    int temp;
    srand(time(NULL));
    
    for(int j=0; j < n; j++){
        //generate profits
        temp =0;
        while(temp < 10){
            temp = rand() % 31;
        }
        p[j]= temp;
        
        
        //generate weights
        temp =0;
        while(temp < 5){
            temp = rand() % 21;
        }  
        w[j] = temp;
        
        printf("The (p,w) randomly generated for item: %d :(%d, %d)\n", j+1, p[j], w[j]);
    }

}

void print_items()
{
	float pft=0.0;
	float wgt=0.0;
	printf("\nItems selected into knapsack:\n");
	printf("Picked Item \tCost \tWeight");
	
	for(i=0; i<n; i++){
		if (x[i])
			printf("\n\t%d\t%d\t%d",i+1, p[i], w[i]);
	}
		
	for(i=0; i<n; i++)
		if(x[i]==1){
			wgt += (float) w[i];			
			pft += (float) p[i];
		}
		
printf("\nFinal solution total knapsack Profit: %d", (int)pft);
printf("\nFinal solution total Knapsack weight: %d", (int)wgt);
printf("\n\n");

}

float check_promising(float c_pft, float c_wgt, int k){
		int temp;
		float b = c_pft;
		float c = c_wgt;
		i =k;
		while(i<=n)	{
			c = c+w[i];
			if( c < m){
				b = b +p[i];
				temp=0;
			}
			else{
				temp =0;
				return (b+(1-(c-m)/ (float)w[i])*p[i]);
			}
		i++;		
		}
		printf("At Node: %d\n",k);
		printf("Bound: %f Weight: %f\n",b,c);
		return b;
}


void knapsack(int k,float c_pft,float c_wgt)
	{
		float temp; int a;
		if(c_wgt+w[k] <= m)
		{
			y[k] = 1;
			temp =0;
			if(k <= n){
				a =0;
				knapsack(k+1, c_pft+p[k], c_wgt+w[k]);}
				
			if(!(k != n)){
				if((c_pft+p[k]) <= fp)
					a++;
				else
				{
					fw = c_wgt+w[k];
					a=0;
					fp = c_pft+p[k];
				    j=0;
				    while(j<=k){
					 x[j] = y[j];
					 j++;}
			    }
			}
		}
		
		temp = check_promising(c_pft, c_wgt, k);
		if( temp >= fp)
		{
			y[k] = 0;
			if( k <= n){
				a=0;
				knapsack(k+1,c_pft,c_wgt);}
			a++;
			if(k == n)
				if(c_pft > fp)
				{
					a=0;
					fw = c_wgt;
					fp = c_pft;
					j=0;
					while(j<=k){
						x[j] = y[j];
						j++;}
				}
		}
	}

int 
main(void)
{

n= create_items();
create_profit_weight(); 

//int pw[3][2]={{50, 5}, {60, 10}, {140, 20}};

// total knapsack weight
for (int i=0; i<n; i++ )
    m += w[i];

m= floor(0.6 * m);
//W = 30;
printf ("Total knapsack weight :%d\n\n", m);    

knapsack(0,0.0,0.0);
print_items();

return 0;
}