/*
Solution : find which all starting positions are invalid. (all of these are contiguous since we go about
a permutation since (n,a) = 1). also check for the last m-1 elements in this permutation and discard them
since they had only contributed to cyclic matchings. 

incorrect : trying to maintain the valid ranges as we go forward since it can get split into two. 
*/

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
#define pll pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

ll n;
ll a,b,p,m;

pll add(pll range,ll a,ll i = 1){
	return {((range.ff + (a*i)%n)%n+n)%n,((range.ss + (a*i)%n)%n+n)%n};
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	
	cin >> n >> a >> b >> p >> m;
	string s;
	cin >> s;

	vv<ii> events;
	ll allPresent = 0;
	FOR(i,m){
		ii range;
		if(s[i] == '0'){
			range = add({p,n-1},-a,i);
		}else{
			range = add({0,p-1},-a,i);
		}
		if(range.ss >= range.ff){
			events.pb({range.ff,0});
			events.pb({range.ss,2});
		}else{
			events.pb({0,0});
			events.pb({range.ss,2});
			events.pb({range.ff,0});
			events.pb({n-1,2});
		}
		range = add(range,-a);
	}
	ll vall = b;
	FOR(j,m-1){
		vall -= a-n;
		vall %= n;
		events.pb({vall,1});
	} 
	sort(events.begin(), events.end());
	int open = 0;
	int prev = -1;
	for(auto e : events){
		if(open == 0 and e.ff > prev)allPresent += max(0,e.ff-prev-1);
		if(e.ss == 0)open++;
		else if(e.ss == 2)open--;
		prev = e.ff;
	}
	allPresent += max(0LL,n-prev-1);
	cout << allPresent << endl;
	return 0;
}

