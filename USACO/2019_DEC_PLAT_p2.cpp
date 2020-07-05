/*
Segtree to store number of unique color. another segtree to see if an ancestor is marked by that same color. a set to remove all descendent markers of same color. O((n+q)logn)
*/
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
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
//#define endl '\n'
using namespace std;
const int MAXN = 1e5 + 5;

struct SegmentTree{
    ll st[MAXN*4];
    ll lz[MAXN*4];

    SegmentTree(){
    	FOR(i,4*MAXN)st[i] = lz[i] = 0;
    }

    void push_down(int node,int ss,int se){
        st[node] += lz[node]*(se-ss+1);
        if(ss != se){
            lz[node*2+1] += lz[node];
            lz[node*2+2] += lz[node];
        }
        lz[node] = 0;
    }

    void update(int node,int ss,int se,int l,int r,ll val){
    	push_down(node,ss,se);
        if(ss > r or se < l)return;
        if(l <= ss and se <= r){
            lz[node] += val;
            push_down(node,ss,se);
            return;
        }
        int mid = (ss+se)/2;
        update(node*2+1,ss,mid,l,r,val);
        update(node*2+2,mid+1,se,l,r,val);
        st[node] = st[node*2+1] + st[node*2+2];
    }

    ll get(int node,int ss,int se,int l,int r){
    	push_down(node,ss,se);
        if(ss > r or se <l )return 0;
        if(l <=  ss and se <=  r)return st[node];
        int mid = (ss+se)/2;
        return get(node*2+1,ss,mid,l,r) + get(node*2+2,mid+1,se,l,r);
    }
};






vi g[MAXN];
int tin[MAXN];
int tout[MAXN];
int euler[MAXN];
set<int> s[MAXN];
int T = 0;

void dfs(int node,int p = -1){
    euler[T] = node;
    tin[node] = T++;
    for(auto e: g[node])if(e != p)dfs(e,node);
    tout[node] = T-1;
}

struct Node{
	int data;
	int left;
	int right;
	Node(){
		data = 0;
		left = -1;
		right = -1;
	}
};
Node buff[(int)5e6];
int PTR = 0;
inline int getP(){
	return PTR++;
}
struct NormalSegtree{
	int head;
	NormalSegtree(){
		head = getP();
	}
	inline void expand(int node){
		if(buff[node].left == -1)buff[node].left = getP();
		if(buff[node].right == -1)buff[node].right = getP();
	}
	void update(int node,int ss,int se,int i,int val){
		if(i > se or i < ss)return;
		expand(node);
		if(ss == se){
			buff[node].data = val;
			return;
		}
		int mid = (ss+se)/2;
		update(buff[node].left,ss,mid,i,val);
		update(buff[node].right,mid+1,se,i,val);
		buff[node].data = max(buff[buff[node].left].data,buff[buff[node].right].data);
	}
	int get(int node,int ss,int se,int l,int r){
		if(node == -1 or r < ss or l > se)return 0;

		if(l <= ss and se <= r)return buff[node].data;
		int mid = (ss+se)/2;
		return max(get(buff[node].left,ss,mid,l,r),get(buff[node].right,mid+1,se,l,r));
	}
} stree[MAXN];


#define cin fin
#define cout fout
int main(){
    ifstream fin;
    ofstream fout;
    fin.open("snowcow.in");
    fout.open("snowcow.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    
    int n,q;
    cin >> n >> q;
    FOR(i,n-1){
        int a,b;
        cin >> a >> b;
        a--;b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(0);
    SegmentTree segtree;
    
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int node,color;
            cin >> node >> color;
            node--;
            int vl = stree[color].get(stree[color].head,0,MAXN,0,tin[node]-1);
            if(vl >= tout[node]){
            	continue;
            }
            auto it = s[color].lower_bound(tin[node]);
            while(it != s[color].end()){
          		if((*it) > tout[node])break;
                int item = euler[*it];
                segtree.update(0,0,MAXN,tin[item],tout[item],-1);
                
                s[color].erase(it++);
            }
            
            segtree.update(0,0,MAXN,tin[node],tout[node],1);
            stree[color].update(stree[color].head,0,MAXN,tin[node],tout[node]);

            s[color].insert(tin[node]);
        }else{
            int v;
            cin >> v;
            v--;
            cout << segtree.get(0,0,MAXN,tin[v],tout[v]) << endl;
        }
    }
    
    return 0;
}
//12mins  + 12:34 - now