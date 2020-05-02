/*
SOLUTION:
claim : optimal [i,j] = i = {0,1,2} and j = {n-3,n-2,n-1}
proof: assume opt [i,j], see what values can be to its right and left, and show that we 
can always extend it atleast in one direction if there are >=3 stuff on both sides. 
use : casework.

*/



#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 10*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;

int sum[3][MAXN];

inline int get(int a,int b,int c){
	if(a == 0)return sum[c][b];
	return sum[c][b] -sum[c][a-1];
}

inline bool isValid(int a,int b,int c){
	if(a == 0)a = -1;
	if(b == 0)b = -2;
	if(c == 0)c = -3;
	return a!=b and b!=c and c!=a;
}
string s;
int solve(){
	int n = s.size();
	int mx = 1;
	FOR(i,n){
		FOR(j,min(i+1,3)){
			int a = get(j,i,0);
			int b = get(j,i,1);
			int c = get(j,i,2);
			if(isValid(a,b,c))mx = max(mx,i-j+1);
		}
	}
	FORE(i,n-3,n-1){
		FOR(j,i+1){
			int a = get(j,i,0);
			int b = get(j,i,1);
			int c = get(j,i,2);
			if(isValid(a,b,c))mx = max(mx,i-j+1);
		}
	}
	return mx;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	cin >> s;
	FOR(i,n)if(s[i] == 'S')s[i] = 'A';
	FOR(i,n){
		FOR(j,3)sum[j][i] = (i>0?sum[j][i-1]:0);
		sum[s[i]-'A'][i]++;
	}
	cout << solve() << endl;

	return 0;
}