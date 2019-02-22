
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


using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 501;

//#define cin fin
//#define cout fout

typedef long double ld;
typedef vector<pll> retType;
const ld inf = 1e1;

vector<pll> rejected[2];


void addReject(ll a,ll b,int ID){
	rejected[ID].pb({a,b});
}

struct chtDynamic { 

	int ID;
	chtDynamic(int id){
		ID = id;
	} 
    struct line {
        ll m, b; ld x; 
        ld val; bool isQuery; 
        line(ld _m = 0, ld _b = 0) : 
            m(_m), b(_b), val(0), x(-inf), isQuery(false) {} 
        
        ld eval(ld x) const { return m * x + b; }
        bool parallel(const line &l) const { return m == l.m; }
        ld intersect(const line &l) const {
            return parallel(l) ? inf : (1.0 * (l.b - b)) / (m - l.m);
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
        ::addReject(it->m,it->b,ID);
        it = hull.erase(it); 
        return hull.insert(it, tmp);
    }



    void addLine(ll m, ll b) { 
        line l(m, b); 
        iter it = hull.lower_bound(l); 
        if(it != hull.end() && l.parallel(*it)) {
            if(it -> b < b){::addReject(it->m,it->b,ID); it = hull.erase(it); }
            else return;
        }

        it = hull.insert(it, l); 
        if(bad(it))  {::addReject(it->m,it->b,ID);hull.erase(it);return;}

        while(cPrev(it) && bad(prev(it))){iter pp = prev(it);::addReject(pp->m,pp->b,ID); hull.erase(prev(it));}
        while(cNext(it) && bad(next(it))){iter pp = next(it);::addReject(pp->m,pp->b,ID); hull.erase(next(it));}

        it = update(it);
        if(cPrev(it)) update(prev(it));
        if(cNext(it)) update(next(it));
    }

    retType query(ld x) const { 
        if(hull.empty()) while(true);
        line q; q.val = x, q.isQuery = 1;
/*
        retType rr;
        for(auto e:hull){
        	rr.pb({e.m,e.b});
        }
        return rr;
*/
        iter it = --(hull.lower_bound(q));

        int ctr = 0;
        while(true and ctr < 10){
        	if(it == hull.begin())break;;
        	it--;
        	ctr++;
        	
        }
        retType r;
      	
        FOR(i,ctr){
        	r.pb({it->m,it->b});
        	it++;
        }
        r.pb({it->m,it->b});
        FOR(i,10){
        	it++;
        	if(it == hull.end())break;;
        	r.pb({it->m,it->b});
        }

        //iter it2 = it-1;
        //iter it3 = it+1;
     	return r;
    }
};

const ld ep = 1e-1;
typedef ll ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype cross(point a, point b) {
    return (conj(a) * b).y();
}
struct CHT1{
	
	vector<point> hull, vecs;

	void add_line(ftype k, ftype b) {
	    point nw = {k, b};
	    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) > 0) {
	        hull.pop_back();
	        vecs.pop_back();
	    }
	    if(!hull.empty()) {
	    	point p;
	    	p.y(1);
	    	p.x(0);
	        vecs.push_back(p* (nw - hull.back()));
	    }
	    hull.push_back(nw);
	}
	ll get(ftype x,ftype y) {
	    point query = {x, y};
	    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
	        return cross(a, b) < 0;
	    });
	    return dot(query, hull[it - vecs.begin()]);
	}
};
struct CHT2{
	
	vector<point> hull, vecs;

	void add_line(ftype k, ftype b) {
	    point nw = {k, b};
	    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
	        hull.pop_back();
	        vecs.pop_back();
	    }
	    if(!hull.empty()) {
	    	point p;
	    	p.y(1);
	    	p.x(0);
	        vecs.push_back(p* (nw - hull.back()));
	    }
	    hull.push_back(nw);
	}
	ll get(ftype x,ftype y) {
	    point query = {x, y};
	    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
	        return cross(a, b) > 0;
	    });
	    return dot(query, hull[it - vecs.begin()]);
	}
};







int main(){

	//cin.tie(NULL);
	//cout.tie(NULL);
	ifstream fin;
	ofstream fout;
	//fin.open("fencing.in");
	//fout.open("fencing.out");

	
	int n,q;
	cin >> n >> q;
	chtDynamic ds1(0),ds2(1);

	vector<pll> all;
	

	ll mxX = (ll)-INF;
	ll mnX = (ll)INF;
	CHT1 maxcht;
	CHT2 mincht;
	FOR(i,n){
		ll x,y;
		cin >> x >> y;
		all.pb(mp((ll)x,(ll)y));


		mxX = max(mxX,x);
		mnX = min(mnX,x);

	}
	//cout << all.size() << endl;
	sort(all.begin(), all.end());
	FOR(i,n){
	//	cout << "step " << i << endl;
		maxcht.add_line(all[i].ff,all[i].ss);
		mincht.add_line(all[i].ff,all[i].ss);
		//ds1.addLine(all[i].ff,all[i].ss);
		//ds2.addLine(-all[i].ff,-all[i].ss);
	}
	//cout << "Good till here" << endl;
	//cout << "SOME MESSAGE : " << endl;
	//cout << onX0max << " " << onX0min << endl;
	vector<pll> some;
	while(q--){
		int ID;cin >> ID;
		if(ID == 1){
			ll x,y;
			cin >> x >> y;
			all.pb(mp((ll)x,(ll)y));
			some.pb(mp(x,y));
			mxX = max(mxX,x);
			mnX = min(mnX,x);
			
			//ds1.addLine(x,y);
			ds2.addLine(-x,-y);
		}else{
			ll a,b,c;
			cin >> a >> b >> c;
			ll mx = -INF;
			if(b != 0){
				/*retType reqLine = ds1.query((a/b));
				FOR(i,reqLine.size()){
					pll pp = reqLine[i];
					if(pp.ff != INF){
						mx = max(mx,pp.ff*a + pp.ss*b);
					}
				}*/
			//	cout << "1" << " ";
				mx = maxcht.get(a,b);
			//	cout << "1" <<endl;
			
			}
			else{ 
				mx = max(a*mnX,a*mxX);
			}

			FOR(i,some.size()){
				mx = max(mx,some[i].ff*a + some[i].ss*b);
			}

			FOR(i,rejected[0].size()){
				//mx = max(rejected[0][i].ff*a + rejected[0][i].ss*b,mx);
			}

			ll mn = INF;
			

			if(b != 0){
				/*retType reqLine = ds2.query((a/b));
				FOR(i,reqLine.size()){
					pll pp = reqLine[i];
					if(pp.ff != INF){
						mn = min(mn,-(pp.ff*a + pp.ss*b));
					}
				}
			*/
				mn = mincht.get(a,b);
			}
			else{ 
				mn = min(a*mnX,a*mxX);
			}


			FOR(i,rejected[1].size()){
				//mn = min(-rejected[1][i].ff*a - rejected[1][i].ss*b,mn);
			}

			FOR(i,some.size()){
				mn = min(mn,some[i].ff*a + some[i].ss*b);
			}


			//cout << mx << " " << mn << endl;
			//cout << onX0max << " " << onX0min << endl;
			//if(x0max) mx = max(mx,onX0max*b);
			//if(x0max) mx = max(mx,onX0min*b);
			//if(x0max) mn = min(mn,onX0max*b);
			//if(x0max) mn = min(mn,onX0min*b);
/*
			FOR(i,some.size()){
				mx = max(mx,some[i].ff*a + some[i].ss*b);
			}
*/

			//mx = -INF;
			//mn = INF;
			//cout << mx << "  " << mn << endl;
			FOR(i,all.size()){
				//mx = max(mx,all[i].ff*a + all[i].ss*b);
				//mn = min(mn,all[i].ff*a + all[i].ss*b);
			}
			cout << mx << " " << mn << endl;

			if(abs(mx-c) < ep or abs(mn-c) < ep){
	//			cout << "NO" << endl;
			}else if((mx >= c and mn <= c)){
	//			cout << "NO" << endl;
			}else{
	//			cout << "YES" << endl;
			}
		}
	}
	//cout << rejected[0].size() << endl;

	return 0;
}