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
#include <chrono>
#include <random>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<ll,ll>
#define il pair<int,ll>
#define li pair<ll,int>
//#define x ff
//#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define pll pair<ll,ll>
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const ll INF = 1000000000000000;

const ll MOD = 1000000007;
const int MAXN = 1000*1000+1;

ll pref[MAXN];
int arr[MAXN];
ll pref_sq_arr[MAXN];
ll pref_two_at_a_time[MAXN];

void precalc(int n){
    pref[0] = arr[0];
    FORE(i,1,n-1)pref[i] = arr[i] + pref[i-1];
    pref_sq_arr[0] = arr[0]*arr[0];
    FORE(i,1,n-1)pref_sq_arr[i] = arr[i]*arr[i] + pref_sq_arr[i-1];
    FOR(i,n)pref_two_at_a_time[i] = (pref[i]*pref[i] - pref_sq_arr[i])/2;
}

inline ll sum(int l,int r){
    return pref[r] - (l>0?pref[l-1]:0);
}

ll cost(int l,int r){ // cost of 2 at a time from l to r
    if(l == 0){
        return pref_two_at_a_time[r];
    }else{  
        return pref_two_at_a_time[r] - pref_two_at_a_time[l-1] - sum(l,r)*sum(0,l-1);
    }
}

typedef long double ld;
const ld inf = 1e18;

class CHT{

    inline ll intersect(pll p1,pll p2){
        long double x = p2.ss-p1.ss;
        return x/(p1.ff-p2.ff);
    }
    inline ll eval(pll p1,ll x){
        return p1.ff*x+p1.ss;
    }
    deque<pll> dq;
    int ptr = 0;
    public :
    void addLine(ll a,ll b){
        pll p = {a,b};
        while(dq.size() > 1 and intersect(dq[(int)dq.size()-2],p) > intersect(dq.back(),p)){
            dq.pop_back();
            ptr = min(ptr,(int)dq.size()-1);
        }
        dq.pb(p);
    }

    ll query(ll x){
        int lo = 0;
        int hi = (int)(dq.size())-1;
        ll best = -INF;
        while(hi >= lo){
            int mid =(hi+lo)/2;
            best = max(best,eval(dq[hi],x));
            best = max(best,eval(dq[lo],x));
            best = max(best,eval(dq[mid],x));
            if(mid+1 < dq.size()){
                best = max(best, eval(dq[mid+1],x));
            }
            if(mid >0){
                best = max(best, eval(dq[mid-1],x));
            }
           // cout << "d" << endl; 
            if(hi == lo){
                break;
            }else{
                if(mid+1 >= dq.size()){
                    hi = mid-1;
                }else if(mid == 0){
                    lo = mid+1;
                }else{
                    ll v1 = eval(dq[mid-1],x);
                    ll v2 = eval(dq[mid-0],x);
                    ll v3 = eval(dq[mid+1],x);

                    if(v2 > v1 and v2 > v3){
                        break;
                    }else if(v1 <= v2 and v2 <= v3){
                        lo = mid+1;
                    }else{
                        hi = mid-1;
                    }
                }
            } 
        }
        //cout << "there" << endl;
        return best;
    }
} ds;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    ll a,b,c;
    cin >> n >> a >> b >> c;
    FOR(i,n)cin >> arr[i];
    precalc(n);
    ll g;
    FOR(i,n){
        ll vc = a*pref_sq_arr[i]+ b*pref[i]+ c+ 2*a*pref_two_at_a_time[i];
        ll v = ds.query(pref[i]);
        g = a*pref_sq_arr[i] + b*pref[i] + c + 2*a*cost(0,i);
        g = max(g,v+vc);
        //cout << g << endl;
        ds.addLine(-2*a*pref[i],-a*pref_sq_arr[i]  - b*pref[i]  + g  - 2*a*pref_two_at_a_time[i] +2*a*pref[i]*pref[i]);
    }
    cout << g << endl;
    

    return 0;
}