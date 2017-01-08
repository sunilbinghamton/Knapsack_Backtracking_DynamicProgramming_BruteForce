all: 
	gcc -std=c99 knapsack_bruteforce.c -o kbf -lm
	gcc -std=c99 knapsack_dp.c -o kdp -lm
	gcc -std=c99 knapsack_backtracking.c -o kbt -lm 

clean:
	rm kbf kbt kdp

