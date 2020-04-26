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

const int MAXN = 10*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;

int f[MAXN];
vi all[MAXN];
int main(){
	//precalc();
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,s;
	cin >> n >> s;

	int arr[n];
	FOR(i,n)cin >> arr[i];
	FOR(i,n)arr[i]++;
	FOR(i,n)arr[i] %= s;
	FOR(i,n)all[arr[i]].pb(i);
	FOR(i,n)f[arr[i]]++;

	priority_queue<ii, vv<ii>, less<ii> > pq;

	FOR(i,s)if(i > 0 and f[i] > 0)pq.push({f[i],i});
	vi order;
	FOR(i,f[0])order.pb(0);
	int sum = -1;
	int ctr = 0;
	while(!pq.empty()){
		auto e = pq.top();pq.pop();
		int toAdd = 0;
		if((e.ss + sum)%s == s-2){
			if(!pq.empty()){
				auto e2 = pq.top();pq.pop();
				toAdd = e2.ss;
				if(e2.ff > 1)pq.push({e2.ff-1,e2.ss});
				pq.push(e);
			}else {
				if(e.ff > 1)pq.push({e.ff-1,e.ss});
				toAdd = e.ss;
			}
		}else{
			if(e.ff > 1)pq.push({e.ff-1,e.ss});
			toAdd = e.ss;
		}
		sum += toAdd;
		order.pb(toAdd);
		sum %= s;
		if(!pq.empty() and sum == s-2){
			ctr++;
			sum++;
		}
	}
	//cout << ctr << endl;
	
	cout << ctr << endl;
	for(auto e : order){
		cout << all[e].back()+1 << " ";
		all[e].pop_back();
	}
	cout << endl;


	return 0;
}