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
#define ll long long int
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 3*100*1000+5;//0*1000+5;

ll st[MAXN*4];
ll firstTerm[MAXN*4];
ll difference[MAXN*4];
ll lz_firstTerm[4*MAXN];
ll lz_difference[4*MAXN];

const bool DEBUG = 0;

struct SegmentTree{
	
	void push_down(int node,int ss,int se){
   		firstTerm[node] += lz_firstTerm[node];
		difference[node] += lz_difference[node];

		int mid = (ss+se)/2;

		if(ss != se){
			lz_firstTerm[2*node+1] += lz_firstTerm[node];
			lz_firstTerm[2*node+2] += lz_firstTerm[node] + lz_difference[node]*(mid+1 - ss);

			lz_difference[2*node+1] += lz_difference[node];
			lz_difference[2*node+2] += lz_difference[node];
		}

		
		ll len = se-ss+1;
		ll y = len*(2*lz_firstTerm[node] + (len-1)*lz_difference[node])/2;
		lz_firstTerm[node] = 0;
		lz_difference[node] = 0;
		st[node] += y;
	}
	void update(int node,int ss,int se,int startPoint,ll s,ll a){
		push_down(node,ss,se);
		if(se < startPoint)return;
		if(ss >= startPoint){
			lz_firstTerm[node] += s + (ss-startPoint)*a;
			lz_difference[node] += a;
			push_down(node,ss,se);
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss ,mid, startPoint,s,a);
		update(node*2+2,mid+1,se,startPoint,s,a);
		st[node] = st[node*2+1] + st[node*2+2];
	}

	ll get(int node,int ss,int se,int l,int r){
		push_down(node,ss,se);
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r){
			return st[node];
			ll len = se-ss+1;
			return len*(2*firstTerm[node] + (len-1)*difference[node])/2;
		}
		int mid = (ss+se)/2;
		return get(node*2+1,ss,mid,l,r) + get(node*2+2,mid+1,se,l,r);
	}
} segtree;	





void addAP(int x,int y,ll s,ll a){
	if(x < 0)segtree.update(0,0,MAXN,0,s + (-x*a),a);
	else segtree.update(0,0,MAXN,x,s,a);

	if(y+1 < MAXN-2)segtree.update(0,0,MAXN,y+1,-(s+a*(y+1-x)),-a);
}

ii all[MAXN];
void solve(){
	int n,m;
	cin >> n >> m;
	FOR(i,m){
		char c;
		cin >> c;
		//cout << c << endl;
		if(c == 'P'){
			int x,s,a;
			cin >> x >> s >> a;
			
			int lstPos = s/a;
			addAP(x,x+lstPos,s,-a);
			addAP(x-lstPos,x-1,s-lstPos*a,a);

			all[x] = {s,a};
		}else if(c == 'U'){
			int x;
			cin >> x;
			int s = all[x].ff;
			int a = all[x].ss;			
			int lstPos = s/a;
			addAP(x,x+lstPos,-s,+a);
			addAP(x-lstPos,x-1,-(s-lstPos*a),-a);
		}else{
			int x,y;
			cin >> x >> y;
			cout << segtree.get(0,0,MAXN,x,y)/(y-x+1) << endl;
		}
	}

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(DEBUG)test();
	if(!DEBUG)solve();
	return 0;
}