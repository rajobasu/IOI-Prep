/*
only looking at adjacent pair suffices.
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

const int MAXN = 200*100*10 + 5;
const ll INF = 1e15;

int sgn(ll x){
	return (x > 0) - (x < 0);
}

class cmp1{
public:
	bool operator()(const pll& d1,const pll& d2) const {
		if(d1.num == d2.num and d1.num == INF)return false;
		if(d2.num == INF)return false;
		if(d1.num == INF)return true;	
		return abs(d1.num*d2.denom) > abs(d2.num *d1.denom);
	}
};

class cmp2{
public:
	bool operator()(const pll& d1,const pll& d2) const {
		if(d1.num == d2.num and d1.num == INF)return false;
		if(d1.num == INF)return false;
		if(d2.num == INF)return true;	
		
		return abs(d1.num*d2.denom) < abs(d2.num *d1.denom);	
	}
};

pll interSectionPoint(pll p1,pll p2){
	//y = c1+m1x = c2 + m2x => m2-m1 
	if(p2.ss == p1.ss)return {INF,1};
	ll x = sgn(p1.ff-p2.ff)*sgn(p2.ss-p1.ss);
	if(x <= 0)return {INF,1};
	return {p1.ff-p2.ff,p2.ss-p1.ss};
}

multiset<pll,cmp1> startings;
multiset<pll,cmp2> endings;


void addRange(pll p1, pll p2){
	if(p1.ff < p2.ff){
		endings.insert(interSectionPoint(p1,p2));
	}
	else if(p1.ff > p2.ff){
		startings.insert(interSectionPoint(p1,p2));
	}
	else if(p1.ff == p2.ff){
		if(p1.ss <= p2.ss){
			startings.insert({0,1});
		}else{
			endings.insert({0,1});
		}
	}
}

void delRange(pll p1,pll p2){
	if(p1.ff < p2.ff){
		endings.erase(endings.find(interSectionPoint(p1,p2)));
	}
	else if(p1.ff > p2.ff){
		startings.erase(startings.find(interSectionPoint(p1,p2)));
	}
	else if(p1.ff == p2.ff){
		if(p1.ss <= p2.ss){
			startings.erase(startings.find({0,1}));
		}else{
			endings.erase(endings.find({0,1}));
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	pll points[n];
	FOR(i,n)cin >> points[i].ff >> points[i].ss;
	
	int perm[n];
	FOR(i,n)cin >> perm[i];
	FOR(i,n)perm[i]--;

	startings.insert({0,1});
	endings.insert({INF,1});
	
	FOR(i,n-1){
		auto p1 = points[perm[i]];
		auto p2 = points[perm[i+1]];
		addRange(p1,p2);
	}
	
	for(auto e : startings){
		//cout << "ST: " << e.ff << " " << e.ss << endl;
	}

	for(auto e : endings){
		//cout << "END: " << e.ff << " " << e.ss << endl;
	}
	

	pll en = *(endings.begin());
	pll st = *(startings.begin());

	

	if(en.ff == 0 or st.ff == INF or (en.num != INF and abs(st.num*en.denom) > abs(en.num*st.denom))){
		
		cout << "NIE" << endl;
	}else {
		if(en.num == INF){
			cout << "1000000000/1" << endl;

		}else{
			ll g = __gcd(abs(en.ff),abs(en.ss));	
			cout << abs(en.ff)/g << "/" << abs(en.ss)/g << endl;	
		}
		
	}

	int q;
	cin >> q;
	while(q--){
		int a,b;
		cin >> a >> b;
		a--;b--;
		int c = min(a,b);
		int d = max(a,b);
		if(c > 0)delRange(points[perm[c-1]],points[perm[c]]);
		if(d < n-1)delRange(points[perm[d]],points[perm[d+1]]);

		if(c+1 == d){
			delRange(points[perm[c]],points[perm[d]]);
			swap(perm[c],perm[d]);
			addRange(points[perm[c]],points[perm[d]]);
		}else{
			delRange(points[perm[c]],points[perm[c+1]]);
			delRange(points[perm[d-1]],points[perm[d]]);
			swap(perm[c],perm[d]);
			addRange(points[perm[c]],points[perm[c+1]]);
			addRange(points[perm[d-1]],points[perm[d]]);
		}
		if(c > 0)addRange(points[perm[c-1]],points[perm[c]]);
		if(d < n-1)addRange(points[perm[d]],points[perm[d+1]]);
		en = *(endings.begin());
		st = *(startings.begin());

		

		if(en.ff == 0 or st.ff == INF or (en.num != INF and abs(st.num*en.denom) > abs(en.num*st.denom))){
			
			cout << "NIE" << endl;
		}else {
			if(en.num == INF){
				cout << "1000000000/1" << endl;

			}else{
				ll g = __gcd(abs(en.ff),abs(en.ss));	
				cout << abs(en.ff)/g << "/" << abs(en.ss)/g << endl;	
			}
			
		}

	}

	return 0;
}