/*
SOLUTION : For each query, do a O(n) deque optimised DP. main observation: if for i, j, and dp[i] = dp[j] and i<j and arr[j]> arr[i], then just kick index j. Hence, we just maintain two deques. if the smallest number in first deque (1st deque => minimum dp possibile) is greater than arr[current], then we have to make dp[currnet] = dp[minpos]+1 atleast. so add it do dq2. when dq1 is empty, just switch them. 
*/

#include <stdio.h>     
#include <stdlib.h>    
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
#define ld long double
//#define int short
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define mp make_pair
#define vv vector
#define endl '\n'


using namespace std;
int n;
const int MAXN = 1e6 + 5;
int arr[MAXN];
deque<ii> dq1,dq2;
void solve(){
	int k;
	cin >> k;
	int x;
	int ind = 0;
	dq1.clear();
	dq2.clear();
	for(int i = n-1;i >= 0;i--){
		if(i == n-1){
			// base case
			dq1.pb({arr[i],i});
			x = 0;
		}else{
			
			while(!dq1.empty() and dq1.front().ss>i+k)dq1.pop_front();
			if(dq1.empty()){
				ind++;
				swap(dq1,dq2);
				while(!dq1.empty() and dq1.front().ss>i+k)dq1.pop_front();
			}
			
			
			if(dq1.front().ff >= arr[i]){
				// the best case scenario is a jump
				while(!dq2.empty() and dq2.back().ff >= arr[i])dq2.pop_back();
				dq2.pb({arr[i],i});
				x = ind+1;
			}else{
				while(!dq1.empty() and dq1.back().ff >= arr[i])dq1.pop_back();
				dq1.pb({arr[i],i});
				x = ind;
			}	
		}
	}
	cout << x << endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	FOR(i,n)cin >> arr[i];
	int t;
	cin >> t;
	while(t--)solve();
	return 0;
}