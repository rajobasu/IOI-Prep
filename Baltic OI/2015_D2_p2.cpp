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
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

const int INF = 1e9+10;
using namespace std;
const int MAXN = 1000*100*2+10;
const int MAXVAL = 1e9+10;


inline int modVal(int v,int n){
	if(v < 0)return v+2*n;
	else if(v >= 2*n)return v-2*n;
	else return n;
}

int main(){
	int n;
	cin >> n;
	int arr[3*n];
	FOR(i,n){
		cin >> arr[i];
		arr[i+n] = arr[i];
		arr[i+2*n] = arr[i];
	}
	//FOR(i,3*n)cout << arr[i] << " ";cout << endl;
	
	int k = (n+1)/2;
	int sum = 0;
	int sumst[3*n];
	FOR(i,k){
		sum += arr[i];
	}
	sumst[0] = sum;
	FORE(i,k,3*n-1){
		sum += arr[i]-arr[i-k];
		sumst[i-k+1] = sum; 
	}

	int mx = 0;
	//FOR(i,3*n)cout << arr[i] << " ";cout << endl;
	//FOR(i,3*n)cout << sumst[i] << " ";cout << endl;
	deque<ii> dq;
	FORE(j,0-k+1,0-1){
		ii e = {sumst[j+n],j+n};
		while(!dq.empty() and dq.front().ff >= e.ff)dq.pop_front();
		dq.push_front(e);
	}
	FOR(i,n){
		int mn = INF;
		ii e = {sumst[i+n],i+n};
		while(!dq.empty() and dq.front().ff >= e.ff)dq.pop_front();
		dq.push_front(e);
		/*	
		FORE(j,i-k+1,i){
			//int jj = modVal(j,n);
			mn = min(mn,sumst[j+n]);
		}
		*/
		//for(auto ee:dq)cout << ee.ff << ":" << ee.ss-n << "  ";cout << endl;
		mn = min(mn,dq.back().ff);
		while(!dq.empty() and dq.back().ss-n <= i-k+1)dq.pop_back();
		mx = max(mx,mn);
	}
	cout << mx << endl;

	return 0;
}