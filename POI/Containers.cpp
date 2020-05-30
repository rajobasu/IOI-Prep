/*
For every possible d, and for every one of its modulo's make a list of APs which fall under it, and do a sweepline. 

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <list>
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
#define pll pair<ll,ll>
#define il pair<int,ll>
#define vv vector
#define endl '\n'
#define num ff
#define denom ss

using namespace std;

const int MAXN = 100*100*10 + 5;
const ll INF = 1e15;

struct Data{
	int a,l,d;
	Data(int aa,int bb,int cc){
		a = aa;
		l = bb;
		d = cc;
	}
};	

/*
vector storing Li, map<modulo, list of ranges with the module>>
*/
map<int,vv<Data> > lotsofstuff[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n,k;
	cin >> n >> k;
	FOR(i,k){
		int a,l,d;
		cin >> a >> l >> d;
		a--;
		if(lotsofstuff[d].find(a%d) == lotsofstuff[d].end())
			lotsofstuff[d][a%d] = vv<Data>();
		lotsofstuff[d][a%d].pb(Data(a,l,d));
	}
	int arr[n];FOR(i,n)arr[i] = 0;
	FOR(k,n){
		for(auto e : lotsofstuff[k]){
			vv<ii> events;
			for(auto x : e.ss){
				events.pb({x.a,0});
				events.pb({x.a+(x.l-1)*x.d + x.d,1});
			}
			sort(events.begin(), events.end());
			int ctr = 0;
			FOR(i,events.size()){
				if(events[i].ss == 0)ctr++;
				else ctr--;
				
				if(i+1 < events.size() and events[i+1].ff == events[i].ff)continue;
				else 
					for(int j = events[i].ff;j < events[i+1].ff;j+=k)
						arr[j] += ctr;
			}
		}
	}

	FOR(i,n)cout << arr[i] << " ";cout << endl;
	return 0;
}