/**
SOLUTION : consider dp[a][i][j] = starting at row i and ending at row j, where middle element is on obdiagonal.
and length of sequence be 2*a+1. columns can be derived from the constraints. calculate this in N^3 time.
Complexity: N^3
*/



#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const int INF = 1000000000;
const int MAXN = 501;
ll dp[2][MAXN][MAXN];

#define cin fin
#define cout fout

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("palpath.in");
	fout.open("palpath.out");


	int n;
	cin >> n;
	string grid[n];
	FOR(i,n)cin >> grid[i];

	FOR(i,n)dp[0][i][i] = 1;
	FOR(stepsctr,n){
		FOR(row1,n){
			FOR(row2,n){
				int steps = 2*stepsctr+1;
				if(row2 < row1)continue;
                int rr = row2 - row1 + 1;
                if(rr > steps)continue;
                int cc = steps - rr;
				int midi = n-1-(row1+row2)/2;
				int col1 = midi - (cc+1)/2;
				int col2 = midi + (cc)/2;
				//cout << "steps : " << steps << " -? " << row1 << " " << col1 << " " << row2 << " " << col2 << endl;
				if(col1 < 0 or col1 >=n or col2 < 0 or col2 >= n)continue;
				if(grid[row1][col1] != grid[row2][col2])continue;
				//cout << "lala" << endl;
				dp[1][row1][row2] = (dp[0][row1][row2-1] + dp[0][row1][row2] + dp[0][row1+1][row2] + dp[0][row1+1][row2-1])%MOD;

			}
		}/*
		cout << "MATRIX STATE : " <<endl;
		FOR(i,n){
			FOR(j,n)cout << dp[1][i][j] << " ";
			cout << endl;
		}*/
		FOR(i,n)FOR(j,n)dp[0][i][j] = dp[1][i][j];
		FOR(i,n)FOR(j,n)dp[1][i][j] = 0;
	}
	cout << dp[0][0][n-1] << endl;


	return 0;
}



