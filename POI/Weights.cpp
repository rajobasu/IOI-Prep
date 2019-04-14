/*
SOLUTION : in sorted order, we will always be able to put some prefix into the buckets given. so binsrch on 
this number, and check if it can be placed. This checking can be done greedily. Code should be readable.
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
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 1000*1000+1;


bool check(vi con,vi ele){
	priority_queue<int,vi, less<int> > pq;
    for(auto e:con)pq.push(e);

    sort(ele.begin(), ele.end(),greater<int>());
	//cout << "Sta" << endl;
	for(auto e:ele){
		if(pq.empty())return false;
		int f = pq.top();pq.pop();
		if(f < e)return false;
		if(f-e > 0)pq.push(f-e);
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin >> n >> m;
    vi con(n);
    vi elem(m);
    vi tmp;

    for(auto& e:con)cin>>e;
    for(auto& e:elem)cin >> e;
    sort(elem.begin(), elem.end(),greater<int>());
	int lo = 0;int hi = m-1;
	int best = m;

	while(lo <= hi){
		int mid = (lo+hi)/2;
		tmp.clear();
		FORE(j,mid,m-1){
			tmp.pb(elem[j]);
		}
		if(check(con,tmp)){
			best = min(best, mid);
			hi = mid-1;
		}else{
			lo = mid+1;
		}

	}
	cout << m -best << endl;

	return 0;
}
