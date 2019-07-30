#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
 
#include "prize.h"

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define ll long long int
#define pb push_back
#define vi vector<int>
#define ff first
#define ss second
#define vv vector
#define ii pair<int,int>
 
using namespace std;
 
const int MAXN = 2e5 + 1;
const ll INF = 1e17;

bool sp[MAXN];
int ans = -1;
int brute(int n){
    FOR(i,n){
        vi a = ask(i);
        if(a[0] == 0 and a[1] == 0)return i;
    }
}
int mx = 0;
void binsrch(int l,int r,int sp_left,int sp_right){
    if(l > r)return;
    if(ans != -1)return;
    if(sp_right + sp_left == mx)return;
    int mid = (l+r)/2;
    vi a = ask(mid);
    if(a[0] + a[1] == mx){
        // this is a lollipop;
        binsrch(l,mid-1,sp_left,a[1]);
        binsrch(mid+1,r,a[0],sp_right);
    }else{
        // now we extend the pointers to both directions to find the closest lollipops
        if(a[0] + a[1] == 0){
            ans = mid;
            return;
        }
        int rptr = mid+1;
        vi a1;
        while(rptr <= r){
            a1 = ask(rptr);
            if(a1[0] + a1[1] == 0){
                ans = rptr;
                return;
            }else if(a1[0] + a1[1] == mx){
                binsrch(rptr+1,r,a1[0],sp_right);
                binsrch(l,mid-1,sp_left,a1[1] + (rptr-mid));
                return;
            }else{
                rptr++;
            }
        }
        binsrch(l,mid-1,sp_left,(r-mid+1) + a[1]);
    }
}

int find_best(int n){
    if(n < 5000)return brute(n);
    int ind = 0;
    int ctr = 0;
    vi all;
    FOR(i,500){
        vi a = ask(i);
        if(a[0] + a[1] == 0){
            return i;
        }
        all.pb(a[0] + a[1]);
        if(mx <= (a[0] + a[1])){
            mx = a[0] + a[1];
            ind = i;
        }
    }
    for(auto e : all)ctr += (e < mx);
    binsrch(ind,n-1,ctr,0);

    
    return ans;
}