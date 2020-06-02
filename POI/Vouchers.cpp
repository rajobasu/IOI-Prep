/*
Go in a brute force way. Keep track of the lowest place to start for each index. Lets say we start at 2, then go to 4, then go to 6 then 8 etc. Now, if 4 and 6 are blocked, no need to keep track of where to go next. just brute, and lastly update the next free position (since its gaurenteed that all positions will be blocked). This works becoz we only scan the array once for each group size. (scanning is bounded to 1e6 and once we reach taht, we can ignore since no vouchers after 1e6). hence overall O(nlogn) as (1/1 + 1/2 + 1/3 + ...  = logn)
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
//#define mp make_pair
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 1000*1000 + 5;

bool vis[MAXN];
int lowest[MAXN];
bool voucher[MAXN];


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	FOR(i,MAXN)lowest[i] = i;
	set<ll> cst;
	int m;
	cin >> m;
	FOR(i,m){
		int a;
		cin >> a;
		voucher[a] = true;
	}
	int n;
	cin >> n;
	ll tot = 0;
	FOR(i,n){
		int a;
		cin >> a;
		int id = lowest[a];
		int ctr = 0;
		while(id < MAXN and ctr < a){
			if(!vis[id]){
				vis[id] = 1;
				if(voucher[id])cst.insert(tot + ctr+1);
				ctr++;
			}
			id += a;		
		}
		lowest[a] = id;
		tot += a;
	}
	cout << cst.size() << endl;
	for(auto e : cst){
		cout << e << endl;
	}

	return 0;
}