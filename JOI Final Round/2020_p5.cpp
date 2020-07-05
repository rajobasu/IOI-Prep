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
//#define int ll
//#define int short
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define iiii pair<iii,int>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
//#define mp make_pair
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 200*1000 + 5;
const int MAXT = 263*1000;

struct FenwickTree{
	ll BITree[MAXN];
	ll getSum(int index) { 
	    ll sum = 0;
	    index = index + 1; 
	    while (index>0){ 
	        sum += BITree[index]; 
	        index -= index & (-index); 
	    } 
	    return sum; 
	} 
	void updateBIT(int index, ll val) { 
	    index = index + 1; 
	  	while (index <= MAXN){ 
	    	BITree[index] += val; 
		    index += index & (-index); 
	    } 
	} 
	void update(int a,int b,int c,int d,ll val){
		updateBIT(d,val - get(a,b,c,d,d));
	}
	ll get(int a,int b,int c,int l,int r){
		ll cost = getSum(r);
		if(l != 0)cost -= getSum(l-1);
		return cost;
	}
};


/*
stage 1: still growing towards left. : sum of elements*time
stage 2(a): end growing and stabilise: sum of elementrange.
stage 2(b): grow and decay, hence no change: sum of element range 
stage 3: just decay: sum(elementrange) - sum(element size)*time
stage 4: dead. We dont really need to keep track of this.

// lets see how we can better the implementation. We have a period when there is a growth
and then we have a period where there is a decay. Stage 2(a/b) can be calculated in terms of those. 
stage 4 is bleh, just kick it out. 
growth_end(i) = time when growth stops. 
decay_start(i) = time when decay starts. 
dead(i) = when we dont need to consider it. 

for every viable i, ans is Arr[i]*(min(growth_end(i),t) - max(0,t-decay_start(i)))
=> Arr[i]*(min(growth_end(i),t)) - Arr[i]*(max(0,t-decay_start(i)));
*/
int D = 0;
int n;
struct Event{
	// =1 means growth_end(i) has been reached, and it wont grow anymore;
	// =2 means decay has been started.
	// type3 = ded.
	int type; 
	int time;
	int item;
	Event(int a,int b,int c){
		type = a;
		time = b;
		item = c;
	} 
};	


int prev_greater[MAXN];
int next_greater[MAXN];
ll arr[MAXN];

void generateGreaters(int n){
	stack<int> st1;
	stack<int> st2;
	FOR(i,n){
		while(!st1.empty() and arr[st1.top()] < arr[i])st1.pop();
		if(st1.empty())prev_greater[i] = -3*n;
		else prev_greater[i] = st1.top();
		st1.push(i);

		while(!st2.empty() and arr[st2.top()] <= arr[n-i-1])st2.pop();
		if(st2.empty())next_greater[n-i-1] = n;
		else next_greater[n-i-1] = st2.top();
		st2.push(n-i-1);
	}
}

vv<Event> eventlist;
void formEventList(int n){
	FOR(i,n){
		int delta1 = next_greater[i] - i;
		eventlist.pb(Event(1,delta1,i));

		int delta2 = i - prev_greater[i];
		delta2--;
		eventlist.pb(Event(2,delta2,i));

		eventlist.pb(Event(3,delta2+delta1,i));
	}
	sort(eventlist.begin(), eventlist.end(),[&](Event e1,Event e2){
		if(e1.time == e2.time)return e1.type < e2.type;
		return e1.time < e2.time;
	});
}

FenwickTree fenwick_expansion;// for expansion
FenwickTree fenwick_stable;// when no expansion
FenwickTree fenwick_decay;// when there is decay
FenwickTree fenwick_decay_helper; // basically decay is like Arr[i]*(t-somevalue), and Arr[i]*somevalue is determined by this array.

const int LOGN = 18;
ll sparseTable[LOGN][MAXN];

void generateSparseTable(){
	FOR(i,n)sparseTable[0][i] = prev_greater[i];
	FORE(i,1,LOGN-1){
		FOR(j,n){
			int p = sparseTable[i-1][j];
			if(p < 0 )sparseTable[i][j] = p;
			else sparseTable[i][j] = sparseTable[i-1][p];
		}
	}
}

ll getAnsForPrefix(int x,int t){
	ll cost = 0;
	int xcp = x;

	// here we are essentially finding the element presiding over the last element. 
	for(int goUp = LOGN-1;goUp >= 0;goUp--){
		if(sparseTable[goUp][x] >= 0 and xcp-sparseTable[goUp][x] <= t){
			x = sparseTable[goUp][x];
		}
	}


	cost += fenwick_expansion.get(0,0,n,0,x)*(t+1);// the expansion
	cost += fenwick_stable.get(0,0,n,0,x);
	cost -= fenwick_decay.get(0,0,n,0,x)*(t) - fenwick_decay_helper.get(0,0,n,0,x);
	cost -= (arr[x])*(min(max(0,t-(xcp-x)),(next_greater[x]-xcp-1)));
	return cost;
}


signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> n >> q;
	FOR(i,n)cin >> arr[i];
	iiii queries[q];
	FOR(i,q){
		int a,b,c;
		cin >> a >> b >> c;
		b--;c--;
		queries[i] = {{a,{b,c}},i};
	}
	sort(queries,queries+q);

	generateGreaters(n);
	formEventList(n);
	generateSparseTable();

	reverse(eventlist.begin(), eventlist.end()); // since we take elements from back

	FOR(i,n)fenwick_expansion.update(0,0,n,i,arr[i]);
	ll ans[q];
	for(auto f : queries){
		auto e = f.ff;
		int t = e.ff;
		int a = e.ss.ff;int b = e.ss.ss;
		// at time t, in range a to b;
		while(!eventlist.empty() and eventlist.back().time <= t){
			// we have got more events to process yay !!
			Event e = eventlist.back();eventlist.pop_back();
			int i = e.item;
			if(e.type == 1){
				fenwick_expansion.update(0,0,n,i,0);
				fenwick_stable.update(0,0,n,i,arr[i]*e.time);
			}else if(e.type == 2){
				fenwick_decay.update(0,0,n,i,arr[i]);
				fenwick_decay_helper.update(0,0,n,i,arr[i]*e.time);
			}else{
				fenwick_stable.update(0,0,n,i,0);
				fenwick_decay_helper.update(0,0,n,i,0);
				fenwick_decay.update(0,0,n,i,0);
			}
		}

		ll cost = getAnsForPrefix(b,t);
		if(a != 0)cost -= getAnsForPrefix(a-1,t);
		ans[f.ss] = cost;
	}
	FOR(i,q){
		cout << ans[i] << endl;
	}

	return 0;
}

