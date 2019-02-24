/*
SOLUTION: If we evaluate each point on the line, the sign tells us whether the point is above or below.
We thus have to find the min and maximum dot products. Let the given points be of form(x,y) and the line 
be A,B,C. Then we have to compute dot product between (a,b).(x,y) = Ax+ By = b*((a/b)x + y), which is in CHT
form. so we need a min and max CHT. Now, finally, note that the sign of b can be +/-. We thus need to 
calculate from mincht and maxcht to update BOTH the global max/min. Its not that to update max, we only
use maxcht. (This took me 6-7 hrs or more to debug).
COMPLEXITY: O(nlogn)
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
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 200001;

#define cin fin
#define cout fout

ll prod(pll p1,pll p2){
	return p1.ff*p2.ff + p1.ss*p2.ss;
}

const ld inf = 1e18;


struct chtDynamic {  
    struct line {
        ll m, b; ld x; 
        ld val; bool isQuery; 
        line(ll _m = 0, ll _b = 0) : 
            m(_m), b(_b), val(0), x(-inf), isQuery(false) {} 
        
        ld eval(ld x) const { return m * x + b; }
        bool parallel(const line &l) const { return m == l.m; }
        ld intersect(const line &l) const {
            return parallel(l) ? inf : 1.0 * (l.b - b) / (m - l.m);
        }
        bool operator < (const line &l) const {
            if(l.isQuery) return x < l.val;
            else return m < l.m; 
        }
    };

    set<line> hull; 
    typedef set<line> :: iterator iter; 

    bool cPrev(iter it) { return it != hull.begin(); }
    bool cNext(iter it) { return it != hull.end() && next(it) != hull.end(); }

    bool bad(const line &l1, const line &l2, const line &l3) {
        return l1.intersect(l3) <= l1.intersect(l2); 
    }
    bool bad(iter it) {
        return cPrev(it) && cNext(it) && bad(*prev(it), *it, *next(it));
    }

    iter update(iter it) {
        if(!cPrev(it)) return it; 
        ld x = it -> intersect(*prev(it));
        line tmp(*it); tmp.x = x;
        it = hull.erase(it); 
        return hull.insert(it, tmp);
    }

    void addLine(ll m, ll b) { 
        line l(m, b); 
        iter it = hull.lower_bound(l); 
        if(it != hull.end() && l.parallel(*it)) {
            if(it -> b < b) it = hull.erase(it); 
            else return;
        }

        it = hull.insert(it, l); 
        if(bad(it)) return (void) hull.erase(it);

        while(cPrev(it) && bad(prev(it))) hull.erase(prev(it));
        while(cNext(it) && bad(next(it))) hull.erase(next(it));

        it = update(it);
        if(cPrev(it)) update(prev(it));
        if(cNext(it)) update(next(it));
    }

    pll query(ld x) const { 
        //if(hull.empty()) return -inf;
        line q; q.val = x, q.isQuery = 1;
        iter it = --hull.lower_bound(q);

        return {it->m,it->b};
    }
} ds1,ds2;



int main(){
	ifstream fin;
	ofstream fout;
	fin.open("fencing.in");
	fout.open("fencing.out");
	int n,q;
	cin >> n >> q;
	ll mxX = (ll)-INF;
	ll mnX = (ll)INF;
	FOR(i,n){
		ll x,y;
		cin >> x >> y;
		mxX = max(mxX,x);
		mnX = min(mnX,x);
		ds1.addLine(x,y);
		ds2.addLine(-x,-y);
	}
	while(q--){
		int ID;cin >> ID;

		if(ID == 1){
			ll x,y;
			cin >> x >> y;

			ds1.addLine(x,y);
			ds2.addLine(-x,-y);

			mxX = max(mxX,x);
			mnX = min(mnX,x);
		}else{
			ll a,b,c;
			cin >> a >> b >> c;
			ll mx = -INF;
			ll mn = INF;
			
			pll bestLineMax;
			if(b != 0){

				ll val1 = prod(ds1.query((1.0*a)/b),{a,b});
				ll val2 = -prod(ds2.query((1.0*a)/b),{a,b});

				mx = max(mx,max(val1,val2));
				mn = min(mn,min(val1,val2));
			}
			else{ 
				mx = max(a*mnX,a*mxX);
			}
			if(abs(mx-c) == 0 or abs(mn-c) == 0){
				cout << "NO" << "\n";
			}else if((mx >= c and mn <= c)){
				cout << "NO" << "\n";
			}else{
				cout << "YES" << "\n";
			}
		}
	}

	return 0;
}