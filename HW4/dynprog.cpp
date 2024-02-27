#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
    int var1, var2,var3;
    for (int i = 0; i <= n; i++)  
    {  
        for (int j = 0; j <=m ; j++) {
			if (i == 0 || j == 0)  
                P[i][j]=H[i][j] = 0;  
        }          
    }  
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) 
        {
            char X_char = X[i - 1];
            char Y_char = Y[j - 1];

            int diag = H[i - 1][j - 1] + (X_char == Y_char ? 2 : -1);
            int up = H[i - 1][j] - 1;
            int left = H[i][j - 1] - 1;

            H[i][j] = (diag >= up && diag >= left) ? diag : (up >= left ? up : left);

            P[i][j] = (H[i][j] == diag) ? 'd' : ((H[i][j] == up) ? 'u' : 'l');
        }
    }
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
	const char EMPTY = '-';
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            H[i][j] = 0;
            P[i][j] = EMPTY;
        }
    }
    
    memoized_SW_AUX(X, Y, P, H, n, m);
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
	if (m == 0 || n == 0) 
        return 0; 

    if (H[n][m] != 0) 
        return H[n][m];

    int var1 = (X[n - 1] == Y[m - 1]) ? memoized_SW_AUX(X, Y, P, H, n - 1, m - 1) + 2 : memoized_SW_AUX(X, Y, P, H, n - 1, m - 1) - 1;
    int var2 = memoized_SW_AUX(X, Y, P, H, n - 1, m) - 1;
    int var3 = memoized_SW_AUX(X, Y, P, H, n, m - 1) - 1;

    H[n][m] = (var1 >= var2 && var1 >= var3) ? var1 : ((var2 >= var1 && var2 >= var3) ? var2 : var3);
    
    P[n][m] = (H[n][m] == var1) ? 'd' : ((H[n][m] == var2) ? 'u' : 'l');

    return H[n][m];
}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
	if (m < 0 || n < 0) {
        return;
    }

    char currentChar = X[n - 1]; // Calculate X[n-1] once

    if (P[n][m] == 'd') {
        print_Seq_Align_X(X, P, n - 1, m - 1);
        cout << currentChar << endl;
    } else if (P[n][m] == 'l') {
        print_Seq_Align_X(X, P, n, m - 1);
        cout << "-" << endl;
    } else if (P[n][m] == 'u') {
        print_Seq_Align_X(X, P, n - 1, m);
        cout << currentChar << endl;
    }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
	if (m < 0 || n < 0) {
        return;
    }

    char currentChar = Y[m - 1]; // Calculate Y[m-1] once

    if (P[n][m] == 'd') {
        print_Seq_Align_Y(Y, P, n - 1, m - 1);
        cout << currentChar << endl;
    } else if (P[n][m] == 'l') {
        print_Seq_Align_Y(Y, P, n, m - 1);
        cout << currentChar << endl;
    } else if (P[n][m] == 'u') {
        print_Seq_Align_Y(Y, P, n - 1, m);
        cout << "-" << endl;
    }
}
