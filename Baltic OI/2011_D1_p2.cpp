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

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 

const int INF = 1e9;
using namespace std;

const int MAXN = 204;

int main(){
	int n,m;
	cin >> n >> m;
	bool mat[n][n];
	FOR(i,n)FOR(j,n)mat[i][j] = 1;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		mat[a-1][b-1] = 0;
		mat[b-1][a-1] = 0;
	}
	int ctrtosub = 0;
	
	FOR(i,n){
		FOR(j,n){
			FOR(k,n){
				if(i >= j or j >= k)continue;
				if(mat[i][j] and mat[j][k] and mat[i][k])ctrtosub++;
			}
		}
	}
	cout << ctrtosub << endl;
    return 0;
}