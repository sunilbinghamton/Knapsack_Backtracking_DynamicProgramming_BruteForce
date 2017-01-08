#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define PFT 0
#define WGT 1

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
create_profit_weight(int n, int pw[n][2]){
    int temp;
    srand(time(NULL));
    
    for(int j=0; j < n; j++){
        //generate profits
        temp =0;
        while(temp < 10){
            temp = rand() % 31;
        }
        pw[j][PFT]= temp;
        
        
        //generate weights
        temp =0;
        while(temp < 5){
            temp = rand() % 21;
        }  
        pw[j][WGT] = temp;
        
        printf("The (p,w) randomly generated for item: %d :(%d, %d)\n", j, pw[j][0], pw[j][1]);
    }

}



// Knapsack Brute force algorithm
void knapsack_bruteforce(int no_items, int pw[no_items][2], int W ){
    
    //calculate the no of subsets needed for brute force algorithm
    int no_subs = pow(2, no_items);
    int subsets[no_subs][2];
    int max_benefit=0,mb_ind, tp, tw;
    
    // Generate subsets
    for (int i=0 ; i < no_subs; i++ ){
        tp=0; tw=0;
        for(int j=0; j< no_items; j++ ){
            if(i & (1<<j)){
                tp +=pw[j][PFT];
                tw +=pw[j][WGT];
            }
        }
        //enter into subsets array
        subsets[i][PFT] =tp;
        subsets[i][WGT] =tw;
    }
    
    // print all subsets of profit/weight
    printf("Following are the subsets for this data set:\n");
    for(int i =0; i< no_subs; i++){
        printf ("Subset %d:  Profit=%d, Weight=%d\n",i+1, subsets[i][PFT], subsets[i][WGT]);
    }
    
    //Select the feasible subset with maximum profit whose weight has not exceeded knapsack weight W
    
    for(int i =0; i< no_subs; i++){
        if(subsets[i][WGT] <= W && subsets[i][PFT] > max_benefit){
            mb_ind =i;
            max_benefit = subsets[i][PFT]; // store the index to the max benefit value
        }
    }
    
    printf("Selected subset with maximum profit (P,W) : %d %d\n", subsets[mb_ind][PFT], subsets[mb_ind][WGT]);
    
}	    


int 
main(void)
{
int sel=0, no_items;
double W =0; // knapsack weight

no_items= create_items();
//no_items = 3;
int pw[no_items][2];

create_profit_weight(no_items, pw);   
//int pw[3][2]={{50, 5}, {60, 10}, {140, 20}};

// total knapsack weight
for (int i=0; i<no_items; i++ )
    W += pw[i][1]  ;

W = floor(0.6 * W);
//W = 30;
printf ("Total knapsack weight :%f\n\n", W);    

knapsack_bruteforce(no_items, pw, W); 
                
printf("\n\n");

return 0;
    
}