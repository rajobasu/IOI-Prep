#include <bits/stdc++.h>

#define ll long long int
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define vi vector<int>
#define ii pair<int,int>
#define ff first
#define ss second
#define pb push_back

//#include "game.h"

using namespace std;

const int INF = 1e9;
const int MAXN = 1e5+3;

struct Node{
	int left;
	int right;
	ll val;
	int activeValues;
	void init(int left1,int right1,ll val1,int active){
		left = left1;
		right = right1;
		val = val1;
		activeValues = active;
	}

};
Node B[100*100*10*20];
int PTR = 0;
int get(){
	B[PTR].init(-1,-1,-1,0);
	return PTR++;
}

struct SegmentTree{
	int head;
	vector<int> versions;
	SegmentTree(){
		head = -1;
	}
	void init(){
		versions.clear();
		PTR = 0;
	}
	int update(int node,int ss,int se,int i,int val){
		if(i > se or i < ss)return node;
		//if(node == -1)node = get();
		if(ss == se){
			int nd = get();
			B[nd].init(-1,-1,val,1);
			return nd;
		}
		int mid = (ss+se)/2;
		int lft = update(node!=-1?B[node].left:-1,ss,mid,i,val);
		int rgt = update(node!=-1?B[node].right:-1,mid+1,se,i,val);
		int nd = get();
		B[nd].init(lft,rgt,B[lft].val + B[rgt].val,B[lft].activeValues + B[rgt].activeValues);
		return nd;
	}
	ll ans(int node1,int node2,int ss,int se,int k){
		int x3 = (node2 ==-1)?0:B[node2].activeValues;
		int y3 = (node1 ==-1)?0:B[node1].activeValues;


		//cout <<"duh" << endl;
		int x = (node2 ==-1 or B[node2].right == -1)?0:B[B[node2].right].activeValues;
		int y = (node1 ==-1 or B[node1].right == -1)?0:B[B[node1].right].activeValues;
		//cout << ss << " " << se << " " << x << " " << y << endl;
		if(ss == se){
			

			if(k >= (x3-y3)){
				ll x2 = (node2 ==-1)?0:B[node2].val;
				ll y2 = (node1 ==-1)?0:B[node1].val;
				return x2-y2;	
			}
			return 0;
		}
		//cout << "bleh" << endl;
		int mid = (ss+se)/2;
		if(x-y == k){
			ll x2 = (node2 ==-1 or B[node2].right == -1)?0:B[B[node2].right].val;
			ll y2 = (node1 ==-1 or B[node1].right == -1)?0:B[B[node1].right].val;

			return x2-y2;
		}else if(x-y > k){
			return ans(node1!=-1?B[node1].right:-1,node2!=-1?B[node2].right:-1,mid+1,se,k);
		}else{
			ll x2 = (node2 ==-1 or B[node2].right == -1)?0:B[B[node2].right].val;
			ll y2 = (node1 ==-1 or B[node1].right == -1)?0:B[B[node1].right].val;
			return (x2-y2) + ans(node1!=-1?B[node1].left:-1,node2!=-1?B[node2].left:-1,ss,mid,k-(x-y)); 
		}
	}
	void update(int pos,ll val){
		//cout << pos << " " << val ;
		if(versions.empty()){
			versions.pb(update(-1,0,MAXN,pos,val));
		}else{
			//int x = versions.pop_back();
			versions.pb(update(versions.back(),0,MAXN,pos,val));
		}
		//cout << " :: " << B[versions.back()].val << " " << B[versions.back()].activeValues << endl;
	}
	ll query(int l,int r,int k){
		if(l == 0){
			return ans(-1,versions[r],0,MAXN,k);
		}else{
			return ans(versions[l-1],versions[r],0,MAXN,k);
		}
	}
};



int n;
int start;
int d;
ll arr[MAXN];
vector<ii> pos;
SegmentTree st;

ll cost(int l,int r,int k){
	vi all;
	FORE(i,l,r)all.pb(arr[i]);
	sort(all.begin(), all.end());
	reverse(all.begin(), all.end());
	ll sum = 0;
	FOR(i,min(k,(int)all.size())){
		sum += all[i];
	}
	return sum;
}

ll cost2(int l,int r,int k){
	return st.query(l,r,k);
}

void preprocess(){
	if(!pos.empty())pos.clear();
	FOR(i,n){
		pos.pb({arr[i],i});
	}
	sort(pos.begin(), pos.end());
	// we have now a mapped value
	// now we create the segment tree;
	st.init();
	PTR = 0;
	ii upd[n];
	FOR(i,n){
		upd[pos[i].ss] = {pos[i].ff,i};
	}


	FOR(i,n){
		st.update(upd[i].ss,upd[i].ff);
	}

	//cout << endl;
	//cout << st.query(1,4,2) << endl;
}	

ll dp[MAXN];

void recurse(int l,int r,int il,int ir){
	int mid = (l+r)/2;
	ll best = 0;
	int bestind = 0;
	FORE(i,il,ir){
		int left = d - abs(start-mid) - abs(mid-i);
		
		ll res;
		if(left <= 0){
			res = 0;
		}else{
			res = cost2(i,mid,left);
		}
		if(res >= best){
			best = res;
			bestind = i;
		}
	}

	dp[mid] = best;
	if(l == r)return;
	recurse(l,mid,il,bestind);
	recurse(mid+1,r,bestind,ir);
}


ll getBest(){
	preprocess();
	recurse(start,n-1,0,start);

	//return 0;
	//cout << "pr" << endl;
	ll mx = 0;

	FOR(i,n){
		if(i < start)continue;
		mx = max(mx,dp[i]);
		continue;
		FOR(j,n){
			if(j < start)continue;
			int left = d - abs(start-i) - abs(j-i);
			if(left <= 0)continue;
			mx = max(mx,cost2(i,j,left));
		}
	}
	return mx;
}


ll findMaxAttraction(int n, int start, int d,int attraction[]){
	::n = n;
	::start = start;
	::d = d;
	FOR(i,n)arr[i] = attraction[i];

	ll mx = getBest();
	reverse(arr,arr+n);
	::start = n-start-1;
	mx = max(mx,getBest());

	return mx;
}

int main1(){
	int n = 5;
	int d = 7;
	int start = 2;
	int attraction[5] = {10,2,20,30,1};
	cout << findMaxAttraction(n,start,d,attraction) << endl;
	return 0;
}