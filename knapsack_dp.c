#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define PFT 0
#define WGT 1
#define MAX_WEIGHT 200


int max_weight =0;
int chosen_items[MAX_WEIGHT][MAX_WEIGHT] = {0};

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

// Knapsack Dynamic Programming refined approach

int 
max(int val1, int val2) {
int max_val;

max_val = (val1 > val2)? val1 : val2;
return max_val; 
}

int
knapsack_dynamic(int items, int pw[items][2], int W){
    int max_benefit, prev_max_benefit, benefit1, benefit2, weight1, weight2 ;
    
    // mark flags for chosen items if its the only item to be chosen
    if (items == 1){
        if (pw[items-1][0] <= W){
            chosen_items[items-1][W]=1;
            //return pw[items-1][0];
        }
        else{
            chosen_items[items-1][W]= -1;
            //return 0;
        }
    }

    if (items == 0)
       return 0;
        
    if (W == 0)
       return 0;
 

    if (pw[items-1][WGT] > W){
        // Continue with knapsack without the current items weight as it exceeds Knapsack weight W 
        return knapsack_dynamic(items-1, pw, W);   
    }
    
 

    else {
        //Calculate the benefit of current item profit and the previous row max profit without including current items weight
        benefit1 = pw[items-1][PFT] + knapsack_dynamic(items-1, pw, W-pw[items-1][WGT]);
        //printf("Visiting item: %d, Weight: %d, Profit : %d\n",items, pw[items-1][WGT], pw[items-1][PFT]); 

        //Calculate the maximum benefit of previous row
        //printf("Visiting item: %d, Weight: %d, Profit : %d\n",items, pw[items-1][WGT], pw[items-1][PFT]);       
        benefit2 = knapsack_dynamic(items-1, pw, W);
        printf("Visiting item: %d, Weight: %d, Profit : %d\n",items, pw[items-1][WGT], pw[items-1][PFT]); 

        // Calculate the maximum benefit
        max_benefit = max(benefit1, benefit2);
        printf("Current Maximum Benefit %d\n\n", max_benefit);
            
        // Mark flags for chosen items    
        if (benefit1 > benefit2)
            chosen_items[items-1][W] = 1;
                
        else
            chosen_items[items-1][W] = -1;
    }
            
    return max_benefit; 

}

void print_chosenitems(int item, int pw[item][2], int size){
    int w_items =0;
    int p_items =0;
    while (item >= 0){
        if (chosen_items[item-1][size] == 1){
            w_items+= pw[item-1][WGT];
            p_items+= pw[item-1][PFT];
            printf("Item %d,\t weight :%d\t profit : %d\n",item, pw[item-1][WGT], pw[item-1][PFT]);
            size -= pw[item-1][WGT];
            item--;            
        }
        else
            item--;
        
    }

    printf("Total Weight of selected items using dynamic approach :%d\n", w_items);
    printf("Total Profit of selected items using dynamic approach :%d\n", p_items);
}


int 
main(void)
{
int sel=0, no_items;
double W =0; // knapsack weight
int max_benefit;

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

max_benefit = knapsack_dynamic(no_items, pw, W);
printf("Max profit using dynamic approach :%d\n\n", max_benefit);
printf("The following items were picked into the knapsack\n");
print_chosenitems(no_items, pw, W);

printf("\n\n");
return 0;
    
}