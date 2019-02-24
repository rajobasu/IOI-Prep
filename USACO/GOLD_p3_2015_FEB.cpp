
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


inline void ppl(pll p){
	cout << p.ff << " " << p.ss << endl;
}


//#define cin fin
//#define cout fout

ld inter(pll p1,pll p2){
	return (p2.ss - p1.ss)*1.0/(p1.ff - p2.ff);	
}

class ConvexHullOpti{
	pll lines[MAXN]; // m*x + b;
	int PTR = 0; // where the current line needs to be added.
	#define m ff
	#define c ss


	
	inline bool replace(pll line1, pll line2,pll line3){
		/*
		ll x1 = c2-c1/m1-m2;
		x2 = c3-c1/m1-m3;
		replace if x2 <=x1
		*/
		//return false;


		ll val1 = (line3.c - line1.c);
		ll val2 = (line1.m - line2.m);
		ll val3 = (line2.c - line1.c);
		ll val4 = (line1.m - line3.m);

		
		int cntNeg1 = (val1 < 0) + (val2 < 0);
		int cntNeg2 = (val3 < 0) + (val4 < 0);

		
		val1 = abs(val1);
		val2 = abs(val2);		
		val3 = abs(val3);
		val4 = abs(val4);		
		
		if(val1*val2 < 0 or val3*val4 < 0)cout << "OHNO" << endl;

		if(cntNeg1 == 1 and (cntNeg2 == 0 or cntNeg2 == 2))return true;
		if((cntNeg1 == 0 or cntNeg2 == 2) and cntNeg1 == 1)return false;

		// now we can work with absolute values.
		unsigned ll v1 = abs(val1);
		unsigned ll v2 = abs(val2);
		unsigned ll v3 = abs(val3);
		unsigned ll v4 = abs(val4);
		if(line2.ff == -203334535){
			cout << inter(line3 ,line1) << " " << inter(line2,line1) << endl;
		}
		return inter(line3,line1) < inter(line2,line1);


		return v1*v2 <= v3*v4;

	}
	public :
	void addLine(ii newLine){
		while(PTR > 1 and replace(lines[PTR-2],lines[PTR-1],newLine)){

			if(lines[PTR-1].ff == -203334535){
				ppl(lines[PTR-2]);
				ppl(lines[PTR-1]);
				ppl(newLine);
			}
			PTR--;
		}
		lines[PTR++] = newLine;
	}






	inline ld eval(ld x,int i){
		return lines[i].m*x + lines[i].c;
	}

	vector<pll> query(ld x){


		int low = 0;int high = PTR-1;
	
		vector<pll> ret;
		FOR(i,PTR){
			ret.pb(lines[i]);
		}
		return ret;

		while(low <= high){
			if(high - low <= 10){
				FORE(i,low,high){
					ret.pb(lines[i]);
				}
				return ret;
			}else{
				int mid = (low+high)/2;
				ld v1 = eval(x,mid);
				ld v2 = eval(x,mid-1);
				ld v3 = eval(x,mid+1);

				if(v1 <= v2 and v2 <= v3){
					high = mid-1;
				}else if(v1 >= v2 and v3 >= v2){
					low = mid - 4;
					high = mid+4;
				}else{
					low = mid+1;
				}
				ret.pb(lines[mid]);
				ret.pb(lines[mid-1]);
				ret.pb(lines[mid+1]);
			}
		}
		return ret;
	}
};

ll prod(pll p1,pll p2){
	return p1.ff*p2.ff + p1.ss*p2.ss;
}


void testing(){
	//-203334576 41875999
	//-203334535 41832197
	//-203334218 41871662
	pll p1 = {-203334576,41875999};
	pll p2 = {-203334535,41832197};
	pll p3 = {-203334218,41871662};
	pll	p = {98669047,232475852 };
	cout << prod(p1,p) << endl;
	cout << prod(p2,p) << endl;
	cout << prod(p3,p) << endl;

	cout << inter(p1,p2) << endl;;
	cout << inter(p3,p2) << endl;;
	cout << inter(p1,p3) << endl;;


}


int main(){


	testing();
	//return 0;
	//cin.tie(NULL);
	//cout.tie(NULL);
	ifstream fin;
	ofstream fout;
	//fin.open("fencing.in");
	//fout.open("fencing.out");

	
	int n,q;
	cin >> n >> q;
	
	ConvexHullOpti cht_max;
	ConvexHullOpti cht_min;

	vector<pll> all;
	

	ll mxX = (ll)-INF;
	ll mnX = (ll)INF;
	FOR(i,n){
		ll x,y;
		cin >> x >> y;
		all.pb(mp((ll)x,(ll)y));


		mxX = max(mxX,x);
		mnX = min(mnX,x);

	}
	//cout << all.size() << endl;
	sort(all.begin(), all.end(),greater<pll>());
	FOR(i,n){
	//	cout << "step " << i << endl;
		//maxcht.add_line(all[i].ff,all[i].ss);
		//mincht.add_line(all[i].ff,all[i].ss);
		//ds1.addLine(all[i].ff,all[i].ss);
		//ds2.addLine(-all[i].ff,-all[i].ss);

		//cht_min.addLine(all[i]);
		cht_max.addLine({-all[i].ff,-all[i].ss});
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
			//ds2.addLine(-x,-y);
		}else{
			ll a,b,c;
			cin >> a >> b >> c;
			ll mx = -INF;
			pll bestLineMax;
			if(b != 0){

				auto vv = cht_max.query((1.0*a)/b);
				for(auto ele:vv){
					if(ele.ff == -203334535){
						cout << "SHOUTOUT" << endl;
					}
					ll val = -(ele.ff*a + ele.ss*b);
					if(val > mx){
						mx = val;
						bestLineMax = ele;
					}
				}
			}
			else{ 
				mx = max(a*mnX,a*mxX);
			}

			FOR(i,some.size()){
				ll val = some[i].ff*a + some[i].ss*b;
				if(val > mx){
					mx = val;
					bestLineMax = some[i];
				}
			}

			
			ll mn = INF;
			

			if(b != 0){
				auto vv = cht_min.query((a*1.0)/b);
				for(auto ele:vv){
					mn = min (mn, ele.ff*a + ele.ss*b);
				}
			}
			else{ 
				mn = min(a*mnX,a*mxX);
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
			bool bb = 0;
			if(bb){		
				mx = -INF;
				mn = INF;
				//cout << mx << "  " << mn << endl;
				FOR(i,all.size()){
					ll val = all[i].ff*a + all[i].ss*b;
					if(val > mx){
						mx = val;
						bestLineMax = all[i];
					}
					mn = min(mn,all[i].ff*a + all[i].ss*b);
				}
			}
				



			cout << mx << " " << mn << endl;
			ppl(bestLineMax);

			if(abs(mx-c) == 0 or abs(mn-c) == 0){
				cout << "NO" << endl;
			}else if((mx >= c and mn <= c)){
				cout << "NO" << endl;
			}else{
				cout << "YES" << endl;
			}
		}
	}
	//cout << rejected[0].size() << endl;

	return 0;
}