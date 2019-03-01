/**
SOLUTION: Linear scan + binsrch.
 Segtree fails but BIT passes. Also code somehow passes. not sure abt how the binsrch part works.
 COMPLEXITY: O(NLOGNLOGN) with very high constant.
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
const int MAXN = 100001;
const int MAXX = 1000002;

class SegmentTree{
    
    int st[4*MAXX];
    
    inline void upd(int node,int ss,int se,int i, int val){
        if(i < ss or i > se)return ;
        if(ss == se){
            st[node] += val;
            return;
        }
        int mid = (ss+se)/2;
        upd(node*2+1,ss,mid,i,val);
        upd(node*2+2,mid+1,se,i,val);
        st[node] = st[node*2+1] + st[node*2+2];
    } 
    inline int qr(int node,int ss,int se,int l,int r){
        if(ss > r or se < l)return 0;
        if(l <= ss and se <= r)return st[node];
        int mid = (ss+se)/2;
        return qr(node*2+1,ss,mid,l,r) + qr(node*2+2,mid+1,se,l,r);
    }
    public :
    inline void update(int i,int val){upd(0,0,MAXX,i,val);}
    inline int query(int l,int r){return qr(0,0,MAXX,l,r);}
    
};

class BITTree{
    int BITree[MAXX+1];
    int getSum( int index) 
    { 
        int sum = 0; // Iniialize result 
      
        // index in BITree[] is 1 more than the index in arr[] 
        index = index + 1; 
      
        // Traverse ancestors of BITree[index] 
        while (index>0) 
        { 
            // Add current element of BITree to sum 
            sum += BITree[index]; 
      
            // Move index to parent node in getSum View 
            index -= index & (-index); 
        } 
        return sum; 
    } 
  
// Updates a node in Binary Index Tree (BITree) at given index 
// in BITree. The given value 'val' is added to BITree[i] and  
// all of its ancestors in tree. 
    void updateBIT( int n, int index, int val) 
    { 
        // index in BITree[] is 1 more than the index in arr[] 
        index = index + 1; 
      
        // Traverse all ancestors and add 'val' 
        while (index <= n) 
        { 
        // Add 'val' to current node of BI Tree 
        BITree[index] += val; 
      
        // Update index to that of parent in update View 
        index += index & (-index); 
        } 
    }

    public :
    inline void update(int i,int val){
        updateBIT(MAXX,i,val);
    }
    inline int query(int l,int r){
        if(l >0)return getSum(r)-getSum(l-1);
        else return getSum(r);
    }
};


BITTree LEFT,RIGHT;

inline int getM(int n,int v,int i){
   

    int v1 = LEFT.query(0,v);
    int v2 = i+1 - v1;
    int v3 = RIGHT.query(0,v); 
    int v4 = n-v1-v2-v3;

    return max(max(v1,v2),max(v3,v4));

}

int main(){
    ifstream fin;
    ofstream fout;
    #define cin fin
    #define cout fout
    fin.open("balancing.in");
    fout.open("balancing.out");


    int n;
    cin >> n;
    ii points[n];
    FOR(i,n)cin >> points[i].ff >> points[i].ss;
    sort(points, points + n);
    
    FOR(i,n)RIGHT.update(points[i].ss,1);
    int M = n;
    vector<int> yvals;
    set<int> st;
    FOR(i,n)st.insert(points[i].ss);
    for(auto ele: st)yvals.pb(ele);
    sort(yvals.begin(), yvals.end());
    FOR(i,n){
        LEFT.update(points[i].ss,1);
        RIGHT.update(points[i].ss,-1);

        

        int lo = 0,hi = yvals.size()-1;
        
        /*
        for(auto ele:yvals){
            M = min(M,getM(n,ele,i));
        }
        */


        while(lo <= hi){
            if(lo == hi or lo +1 == hi){
                M = min(M,min(getM(n,lo,i),getM(n,hi,i)));
                break;
            }
            int j  = (lo+hi)/2;
            int m1 = getM(n,yvals[j-1],i);
            int m2 = getM(n,yvals[j],i);
            int m3 = getM(n,yvals[j+1],i);

            vector<int> vals;
            FORE(k,max(j-4,0),min(j+4,(int)yvals.size())){
                int xx = getM(n,yvals[k],i);
                vals.pb(xx);
                M = min(M,xx);
            }

            M = min(M,min(m1,min(m2,m3)));
            if(m1 > m2 and m2 < m3){
                break;
            }else if(vals.front() > m2){
                lo = j;
            }else if(vals.back() > m2){
                hi = j;
            }else{
                lo = j;
            }
        }
    }
    cout << M << endl;

    return 0;
}
