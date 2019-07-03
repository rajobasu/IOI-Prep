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

const int INF = 1e9;
const int MAXN = 1e5;
const int MAXK = 100+10;

int main(){
	int n,k;
	cin >> n >> k;
	vi all;
	FOR(i,n){
		int a;cin >> a;
		all.pb(a);
	}
	sort(all.begin(), all.end());
	//int tot = all.back() - all.front() + 1;
	vi diff;
	FORE(i,1,n-1){
		diff.pb(all[i]-all[i-1] - 1);
	}
	sort(diff.begin(), diff.end());
	int tot = n;
	FOR(j,n-k){
		tot += diff[j];
	}
	cout << tot << endl;
	return 0;
}