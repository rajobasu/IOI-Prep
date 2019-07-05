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
#include <fstream>
#include <complex>
#include <stack>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int INF = 4e6;
const int MAXN = 3001;
const int MAXK = 100+10;

int n,m;
int dp[MAXN][MAXN][3];// 0-> none taken, 1->to the right taken,2 = to the bottom taken.
string grid[MAXN];

inline bool isRpos(int x,int y){
	if(y+2 >= m)return 0;
	return grid[x][y] == 'R' and grid[x][y+1] == 'G' and grid[x][y+2] == 'W';
}
inline bool isBpos(int x,int y){
	if(x+2 >= n)return 0;
	return grid[x][y] == 'R' and grid[x+1][y] == 'G' and grid[x+2][y] == 'W';
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	FOR(i,n)cin >> grid[i];
	FOR(diagonal,2*n-1){
		FOR(column,diagonal+1){
			int row = diagonal - column;
			if(row == n-1){
				dp[row][column][0] = 0;
				dp[row][column][1] = (isRpos(row,column))?1:-INF;
				dp[row][column][2] = -INF;
			}else if(row == n-2){
				dp[row][column][0] = //max(0,dp[row+1][column];
				dp[row][column][1] = (isRpos(row,column))?1:-INF;
				dp[row][column][2] = -INF;
			}else if(row == n-3){
				dp[row][column][0] = 0;
				dp[row][column][1] = (isRpos(row,column))?1:-INF;
				dp[row][column][2] = (isBpos(row,column))?1:-INF;
			}

		}
	}

	return 0;
}