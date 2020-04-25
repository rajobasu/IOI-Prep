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

const int MAXN = 20*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;


struct SegmentTree{
	il st[4*MAXN];
	SegmentTree(){
		FOR(i,4*MAXN)st[i] = {MAXN,0};
	}

	void update(int node,int ss,int se,int i,il data){
		if(i < ss or i > se)return;
		if(ss == se){
			st[node] = data;
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,i,data);
		update(node*2+2,mid+1,se,i,data);
		if(st[node*2+1].ff < st[node*2+2].ff)st[node] = st[node*2+1];
		else if(st[node*2+1].ff > st[node*2+2].ff)st[node] = st[node*2+2];
		else st[node] = {st[node*2+1].ff,(st[node*2+1].ss + st[node*2+2].ss)%MOD};
	}

	il get(int node,int ss,int se,int l,int r){
		if(l > se or r < ss)return {MAXN,0};
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		auto a = get(node*2+1,ss,mid,l,r);
		auto b = get(node*2+2,mid+1,se,l,r);
		if(a.ff < b.ff)return a;
		if(a.ff > b.ff)return b;
		return {a.ff,(a.ss+b.ss)%MOD};
	}

} segtree;


void solve(){
	int n,m;
	cin >> n >> m;
	vv<ii> all;
	FOR(i,m){	
		int a,b;
		cin >> a >> b;
		all.pb({a,b});
	}
	sort(all.begin(), all.end());
	stack<ii> st;
	FOR(i,m){
		auto e = all[i];
		while(!st.empty() and e.ss <= st.top().ff)st.pop();
		st.push({e.ss,i});
	}
	vv<ii> xx;
	while(!st.empty()){
		xx.pb(all[st.top().ss]);st.pop();
	}
	all = xx;

	// we have reduced our list to something that is usable. 

	sort(all.begin(), all.end());
	m = all.size();
	int startPos[m];
	int endPos[m];
	ll numPos[4*m];

	//deque<int> covering;
	vv<iii> events;
	FOR(i,m){
		events.pb({all[i].ff,{1,i}});
		events.pb({all[i].ss,{0,i}});
	}

	sort(events.begin(), events.end());
	int ptr = 0;
	int prev = 0;
	int ctr = 0;
	for(auto e : events){
		if(ctr == 0){
			startPos[e.ss.ss] = ptr;
			ctr++;
		}else{
		 	if(e.ss.ff == 0){
				ctr--;
				endPos[e.ss.ss] = ptr;
			}else{
				ctr++;
				startPos[e.ss.ss] = ptr+1;
			}
			numPos[ptr] = e.ff - prev; 
			ptr++;
		}
		prev = e.ff;
	}
	vv<ii> startpoints;
	FOR(i,m)startpoints.push_back({startPos[i],i});
	sort(startpoints.begin(), startpoints.end());


	pair<ll,ll> dp[ptr];
	for(int i = ptr-1;i>=0;i--){
		int nextSegment = -1;
		auto it = lower_bound(startpoints.begin(), startpoints.end(),make_pair(i+1,-2));
		if(it != startpoints.end()){
			nextSegment = (*it).ss;
		}

		if(nextSegment == -1){
			dp[i] = {1,numPos[i]};
		}else{
			/*
			ll sum = 0;
			int mn = m+1;
			FORE(j,startPos[nextSegment],endPos[nextSegment]){
				if(dp[j].ss < mn){
					mn = dp[j].ss;
					sum = dp[j].ff;
				}else if(dp[j].ss == mn){
					sum += dp[j].ff;
					sum %= MOD;
				}
			}*/
			auto e = segtree.get(0,0,MAXN,startPos[nextSegment],endPos[nextSegment]);
			dp[i] = {1+e.ff,(numPos[i]*e.ss)%MOD};

		}
		//cout << i << " " << dp[i].ff << " " << dp[i].ss << endl;
		segtree.update(0,0,MAXN,i,dp[i]);
	}
	/*
	ll sum = 0;
	int mn = m+1;
	FORE(j,startPos[0],endPos[0]){
		if(dp[j].ss < mn){
			mn = dp[j].ss;
			sum = dp[j].ff;
		}else if(dp[j].ss == mn){
			sum += dp[j].ff;
			sum %= MOD;
		}
	}*/
	auto e = segtree.get(0,0,MAXN,startPos[0],endPos[0]);
	cout << e.ff << " " << e.ss << endl;


}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}