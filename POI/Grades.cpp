/*
Problem is same as counting i such that max of [1..i] = i. To do this, for every i keep track of i-sm(i) where sm(i)= number of elements j, arr[j] <= i and j < i. Use {min,mincnt} to count 0's along with lazy.
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")

#include <stdio.h>     
#include <stdlib.h>    
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
#define ld long double
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define il pair<int,ll>
#define ii pair<int,int>
#define lii pair<pair<ll,int>,il>
#define iii pair<int,ii>
#define iiii pair<iii,int>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 1e6+5;
const int INF = 1e8;

void print(ii s){
    cout << "PAIR: " << s.ff << " " << s.ss << endl;
}

struct SegmentTree{
    ii st[4*MAXN];
    int lz[4*MAXN];
    inline ii combine(ii a,ii b){
        if(a.ff < b.ff)return a;
        if(b.ff < a.ff)return b;
        return {a.ff,a.ss+b.ss};
    }

    void push_down(int node,int ss,int se,bool b1 = 1){
        st[node].ff += lz[node];
        if(ss != se){
            lz[node*2+1] += lz[node];
            lz[node*2+2] += lz[node];
            int mid = (ss+se)/2;
            if(b1)push_down(node*2+1,ss,mid,0);
            if(b1)push_down(node*2+2,ss,mid,0);

        }
        lz[node] = 0;
    }

    void build(int node,int ss,int se){
        if(ss==se){
            st[node] = {ss+1,1};
        }else{
            int mid = (ss+se)/2;
            build(node*2+1,ss,mid);
            build(node*2+2,mid+1,se);
            st[node] = combine(st[node*2+1],st[node*2+2]);
        }
    }

    void update(int node,int ss,int se,int l,int r,int val){
        if(l > se or r < ss)return;
        if(l <= ss and se <= r){
            lz[node] += val;
            push_down(node,ss,se);
            return;
        }
        push_down(node,ss,se);
        int mid = (ss+se)/2;
        update(node*2+1,ss,mid,l,r,val);
        update(node*2+2,mid+1,se,l,r,val);
        st[node] = combine(st[node*2+1],st[node*2+2]);
    }

    int get(int node,int ss,int se,int l,int r){
        if(l > se or r < ss)return 0;
        push_down(node,ss,se);
        if(l <= ss and se <= r){
            if(st[node].ff == 0)return st[node].ss;
            else return 0;
        }
        int mid = (ss+se)/2;
        return get(node*2+1,ss,mid,l,r) + get(node*2+2,mid+1,se,l,r);
    }
} segtree;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    int arr[n];
    FOR(i,n)cin >> arr[i];
    FOR(i,n)arr[i]--;
    //FOR(i,n)segtree.update(0,0,n,i,i,i+1);
    segtree.build(0,0,n);
    FOR(i,n)segtree.update(0,0,n,max(i,arr[i]),n-1,-1);
    cout << segtree.get(0,0,n,0,n-1) << endl;
    FOR(i,q-1){
        int a,b;
        cin >> a >> b;
        a--;b--;
        segtree.update(0,0,n,max(a,arr[a]),n-1,+1);
        segtree.update(0,0,n,max(b,arr[b]),n-1,+1);
        swap(arr[a],arr[b]);
        segtree.update(0,0,n,max(a,arr[a]),n-1,-1);
        segtree.update(0,0,n,max(b,arr[b]),n-1,-1);
        cout<< segtree.get(0,0,n,0,n-1) << endl;
    }
    return 0;
}
