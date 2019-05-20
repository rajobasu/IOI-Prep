#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
//#include <string>
//#include <map>
//#include <complex>
//#include <chrono>
//#include <random>
//#include <stack>
//#include <set>
//#include <fstream>
 
#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<ll,ll>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define pll pair<ll,ll>
#define vi vector<int>
#define pb push_back
#define mp make_pair
 
#include "aliens.h"
 
using namespace std;
 
const ll INF = 1e18;
 
vector<ii> all;
 
vector<ii> reduceList(vector<ii> v){
    sort(v.begin(), v.end());
    vector<ii> res;
    ll mx = 0;
    for(auto e:v){
 
        if(res.empty())res.pb(e);
        else if(res.back().ff < e.ff){
            if(e.ss > mx)res.pb(e);
        }else{
            res.back() = e;
        }
        mx = max(mx,e.ss);
    }
    return res;
}
 
vector<ii> createRanges(vi r,vi c,int n){
    vector<ii> all;
    FOR(i,n)all.pb({min(r[i],c[i]),max(r[i],c[i])});
    return all;
}
 
ll C1[100*1000+1];
void prec(){
    C1[0] = 0;  
    FORE(i,1,(int)all.size()-1){
        C1[i] = max((ll)0,all[i-1].ss - all[i].ff+1);
        C1[i] *= C1[i];
    }
}
 
ll cost(int t,int i){
    i--;
    ll t1 = all[i].ss - all[t].ff + 1; t1*=t1;
    ll t2 = C1[t];
    return t1 - t2;
}
 
 
class SqrtSegtree{
    deque<pair<pll,int> > cht;
    #define ld long double
    inline ld intersect(pll p1,pll p2){
        return ((ld)(p1.ss-p2.ss)*1.0)/(p2.ff-p1.ff);
    }
    inline ll eval(pll p1,ll x){
        return p1.ff*x+p1.ss;
    }
    inline void update(pair<pll,int> e){
        while(cht.size() > 1 and intersect(cht[(int)cht.size()-2].ff,e.ff) > intersect(cht.back().ff,e.ff))
            cht.pop_back();
 
        cht.push_back(e);
    }
 
    li binsrch(ll x){
        int lo = 0;int hi = (int)cht.size()-1;
        li best = {INF,0};
        while(hi >= lo){
            if(hi-lo < 10){
                FORE(i,lo,hi){
                    ll val = eval(cht[i].ff,x);
                    if(best.ff > val){
                        best.ff = val;
                        best.ss = cht[i].ss;
                    }
                }
                break;
            }
            int mid = (lo+hi)/2;
            ll val1 = eval(cht[mid].ff,x);
            ll val2 = eval(cht[mid+1].ff,x);
            ll val3 = eval(cht[mid-1].ff,x);
 
            if(best.ff > val1){
                best.ff = val1;
                best.ss = cht[mid].ss;
            }
            if(best.ff > val2){
                best.ff = val2;
                best.ss = cht[mid+1].ss;
            }
            if(best.ff > val3){
                best.ff = val3;
                best.ss = cht[mid-1].ss;
            }
 
            //best = min(best,min(val1,min(val2,val3)));
            if(val1 < val2 and val1 < val3){
                break;
            }else if(val1 >= val2){
                lo = mid+1;
            }else if(val1 >= val3){
                hi = mid-1;
            }
        }
        return best;
    }
 
    public : 
    inline void addLine(ll m,ll c,int id){
        update({{m,c},id});
    }
    inline li query(ll x){ 
        return binsrch(x);
    }
    inline void init(){
        cht.clear();
    }
};
 
li dp[100*1000+1];
ll E[100*1000+1];
SqrtSegtree ds;
li computeDp(ll CC){
    int n = all.size();
 
    vector<pll> lns;
    vector<ll> add;
    FOR(i,n){
        add.pb(all[i].ss*all[i].ss + 1 + 2*all[i].ss);
    }
    
    FOR(i,n)E[i] = all[i].ff*all[i].ff - 2*all[i].ff;
    ds.init();
    dp[0] = {0,0};
    for(int i = 1;i <= n;i++){
        ds.addLine((-2*all[i-1].ff),(CC + dp[i-1].ff - C1[i-1] + E[i-1]) , dp[i-1].ss);
        li mn = ds.query(all[i-1].ss);
        dp[i] = {mn.ff + add[i-1],mn.ss+1};
    }
    return dp[n];
}
 
int check(ll C,int k){
    li v1 = computeDp(C);
    return v1.ss;
}
 
ll binsrch(int k){
    ll toRet =  INF;
    ll lo = 0;ll hi = INF;
    
    while(hi >= lo){
        ll mid = (hi+lo)/2;
        ll val = check(mid,k);
        if(val <= k){
            toRet = min(toRet,mid);
            hi = mid-1;
        }else{
            lo = mid+1;
        }
    }
    li vv = computeDp(toRet);
    return vv.ff - k*toRet;
    outer:
    while(hi >= lo){
        if(hi - lo <= 10){
            for(ll v = lo;v <= hi;v++){
                int x = check(v,k);
                if(x == 0 or x == 2){
                    toRet = min(toRet, computeDp(v).ff - k*v);
                }
            }
            return toRet;
        }else{
            ll mid = (hi+lo)/2;
            switch(check(mid,k)){
                case 1:{
                    lo = mid+1;
                    break;
                }
                case 2:{
                    hi = mid;
                    toRet = min(toRet,computeDp(mid).ff-k*mid);
                    break;
                }case -1:{
                    hi = mid;
                    break;
                }case 0:{
                    toRet = min(toRet, computeDp(mid).ff - k*mid);
                    return toRet;
                    break;
                }
            }
        }
 
    }
    return toRet;
} 
ll take_photos(int n,int m,int k,vi r,vi c){
    all = reduceList(createRanges(r,c,n));
    prec();
    k = min(k,(int)all.size());
    ll ans = binsrch(k);
    return ans;
}
