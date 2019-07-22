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
#include <fstream>
#include <complex>
#include <random>
#include <stack>
#include <chrono>
#include <set>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define il pair<int,ll>
#define li pair<ll,int>
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,ll>
#define vv vector
 
using namespace std;
 
const int MAXN = 501;
 
int n,k;
vv<int> all[MAXN];
vi allV;
 
int XX[20000][501];
int ptr = 0;
inline int* get(){
    return XX[ptr++];
}

// for subspace : 1 = taken, 0 = not to be taken. 2 = can be either.
 
 
 
struct data{
    int* arr;
    int sum;
    data(int* a,int s){
        arr = a;
        sum = s; 
    }
};
 
bool comp(const data& d1,const data& d2){
    return d1.sum < d2.sum;
}
 
//queue<int*> q;
priority_queue<data,vector<data>, function<bool(const data&,const data&)> > pq(comp);
 
int evaluateSpace(int* arr,vi& ans){
    //cout << "ENTERED" << endl;
    //FOR(i,n)cout << arr[i] << " ";cout << endl;
    vi valid;
    vi taken;
    FOR(i,n){
        if(arr[i] == 2)valid.pb(i);
        else if(arr[i] == 1)taken.pb(i);
    }
    if(taken.size() == k){
        int xx[k];
        FOR(i,k)xx[i] = 0;
           
        for(auto e : taken){
            FOR(i,k)xx[i] = max(xx[i],all[e][i]);
        }
        int sum = 0;
        FOR(i,k)sum += xx[i];
            
        return sum;
    }
    if(valid.size() == 0)return 0;
 
    int numT = k - taken.size();
    if(valid.size() < numT){
        return 0;
    }
    set<int> goood;
    FOR(sortItem,k){
        if(valid.size() == 0)break;
        int besti = -1;
        for(auto x : valid){
            if(goood.find(x) != goood.end())continue;
            if(besti == -1){
                besti = x;
            }else{
                if(all[x][sortItem] > all[besti][sortItem]){
                    besti = x;
                }
            }
        }

        goood.insert(besti==-1?*goood.begin() : besti);
        /*sort(valid.begin(), valid.end(),[&](int a,int b){
            if(goood.find(a) != goood.end())return false;
            if(goood.find(b) != goood.end())return true;
            return all[a][sortItem] > all[b][sortItem];
        });
        goood.insert(valid[0]);*/
    }
    vi good;
    for(auto e : goood)good.pb(e);
 
    int mx = 0;
    
    
    //cout << numT << endl;
    //cout << good.size() << endl;
    
    FOR(mask,1<<good.size()){
        if(numT > good.size())break;
        vi cc;
        FOR(j,good.size()){
            if(((1<<j)&mask) > 0){
                cc.pb(good[j]);
            }
        }
        if(cc.size() == numT){
            // this is a candidate choice
            int sum = 0;
            int xx[k];
            FOR(i,k)xx[i] = 0;
            for(auto e : taken){
                FOR(i,k)xx[i] = max(xx[i],all[e][i]);
            }
            for(auto e : cc){
                FOR(i,k)xx[i] = max(xx[i],all[e][i]);   
            }
            FOR(i,k)sum += xx[i];
            if(sum > mx){
 
                mx = sum;
                ans = cc;
            }
        }
    }
 
    //cout << "EXITED" << endl;
    return mx;
}
 
inline void processSubspace(int* space){
    vi ans;
    vi ans2;
    int an;
    an = evaluateSpace(space,ans);
    
    if(an == 0)return;
    allV.pb(an);
    
    //cout << an << endl;
    // ans now contains the stuff that i am to take.
    FOR(i,ans.size()){
        int* arr = get();
        FOR(j,n)arr[j] = space[j];
        FOR(j,i){
            arr[ans[j]] = 1;
        }
        arr[ans[i]] = 0;
        int x = evaluateSpace(arr,ans2);
        pq.push(data(arr,x));
    }
    ans2.clear();
}
 
void solve(){
    int arr[n];
    FOR(i,n)arr[i] = 2;
    processSubspace(arr);
    while(!pq.empty() and allV.size() < 3000){
        data d = pq.top();pq.pop();
        processSubspace(d.arr);
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int c;
    cin >> n >> k >> c;
    FOR(i,n){
        FOR(j,k){
            int a;
            cin >> a;
            all[i].pb(a);
        }
    }
    solve();
    //cout << allV.size() << endl;
    //for(auto e : allV)cout << e << " ";cout << endl;
    sort(allV.begin(), allV.end(), greater<int>());
    int ctr = 0;
    for(auto e : allV){
        ctr++;
        if(c == ctr){
 
            cout << e << endl;
            return 0;
        }
        //cout << e << endl;
    }
    return 0;
}
