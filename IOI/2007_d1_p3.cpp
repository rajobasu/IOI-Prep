#include <bits/stdc++.h>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define ff first
#define ss second
#define vv vector
#define pb push_back
 
using namespace std;
 
/////////////////////////////////////////////////////////
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uid(1,1<<30);
inline int getrandom(){
    return uid(rng);
}
/////////////////////////////////////////////////////////
 
 
const int MAXN = 1e5 + 10;
 
struct Treap{
    struct Node{
        int left,right;
        int val;
        int prior;
        int lzp;
        int sz;
        Node(int v = 0,int l = -1,int r = -1){
            val = v;
            left = l;
            right = r;
            lzp = 0;
            sz = 1;
            prior = getrandom();
            
        }
    };
    Node B[5*100*100*10];
    int PTR = 0;
    inline int get(){
    	
    	return PTR++;
    }
    
    int head = -1;
    Treap(){
        head = -1;
    }
    inline void reform(int node){
    	if(node==-1)return;
        B[node].sz = 1;
        if(B[node].left != -1)B[node].sz += B[B[node].left].sz;
        if(B[node].right != -1)B[node].sz += B[B[node].right].sz;
    }
    
    inline void pushdown(int node){
	    if(node==-1)return;
        if(B[node].left != -1){
            B[B[node].left].val += B[node].lzp;
            B[B[node].left].lzp += B[node].lzp;
        }
        if(B[node].right != -1){
            B[B[node].right].val += B[node].lzp;
            B[B[node].right].lzp += B[node].lzp;
        }
        B[node].lzp = 0;
    }
    
    int getValue(int node,int togo){
        pushdown(node);
        reform(node);
        int lft = B[node].left == -1? 0 : B[B[node].left].sz;
        int rgt = B[node].right == -1 ? 0 : B[B[node].right].sz;
            
        if(togo == lft + 1){
            return B[node].val;
        }else{
            if(lft >= togo){
                return getValue(B[node].left,togo);
            }else{
                return getValue(B[node].right,togo - lft - 1); 
            }
        }
    }
    
    void split(int currnode,int& L,int& R,int val){
        if(currnode == -1){
            L = -1;
            R = -1;
            return;
        }
      	//cout <<"PRINTING THIS : " <<  currnode->val << endl;
 
        if(B[currnode].lzp > 0)pushdown(currnode);
        //cout << "VALUE PUSHED " << endl;
        if(val > B[currnode].val){
            L = currnode;
            split(B[currnode].right,B[L].right,R,val);
        }else{
            R = currnode;
            split(B[currnode].left,L,B[R].left,val);
        }
        reform(currnode);
    }
    void merge(int left,int right,int& node){
        if(left == -1 and right == -1){
            node = -1;
        }else if(left == -1){
            node = right;
        }else if(right == -1){
            node = left;
        }else{
            if(B[left].lzp > 0)pushdown(left);
            if(B[right].lzp > 0)pushdown(right);
            if(B[left].prior > B[right].prior){
                node = left;
                merge(B[left].right,right,B[node].right);
            }else{
                node = right;
                merge(left,B[right].left,B[node].left);
            }
        }
        reform(node);
    }
    
    void updateSuffix(int node,int suf,int updv){
        if(node == -1 or suf <= 0)return;
        if(B[node].lzp > 0)pushdown(node);
        reform(node);
        
        int lft = B[node].left  == -1?0:B[B[node].left].sz;
        int rgt = B[node].right == -1?0:B[B[node].right].sz;
        if(B[node].sz - lft <= suf){
            // this node needs to be updated as well
            B[node].val += updv;
        }
        if(suf == B[node].sz){
            B[node].lzp += updv;
            return;
        }
        updateSuffix(B[node].left,suf - 1 - rgt,updv);
        updateSuffix(B[node].right,min(suf,rgt),updv);
    }
    
    inline void insert(){
        int node = get();
        //cout << "CH" << endl;
        merge(node,head,head);
        //cout << node << endl;
    }
    
    void markPref(int x){
    	//cout << "booo" << endl;
        int val = getValue(head,x);
        int lft = -1,mid = -1,rgt =-1;
        //cout << "HEHE" << endl;
        split(head,lft,rgt,val+1);
        //cout << "SPLITTING 1 DONE" << endl;
        split(lft,lft,mid,val);
        //cout << "TWO SPLITTINGS DONE" << endl;
        if(mid != -1){
            // stuff is there to break and update
            int lftover = x - (lft == -1?0:B[lft].sz);
            if(lftover > 0)
                updateSuffix(mid,lftover,1);
        }
        if(lft != -1){
            B[lft].val++;
            B[lft].lzp++;
        }
        merge(lft,mid,lft);
        merge(lft,rgt,head);
    }
    
    void traverse(int node,vi& v){
        if(node == -1)return;
        pushdown(node);
        v.pb(B[node].val);
        traverse(B[node].left,v);
        traverse(B[node].right,v);
    }
    
} treap;
 
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;cin >> n;
	vv<ii> all;
	FOR(i,n){
	    int a,b;
	    cin >> a >> b;
	    all.pb({a,b});
	}
	sort(all.begin(),all.end());
	int lst = 0 ;
	for(auto e : all){
	    //cout << e.ff << endl;
        while(lst < e.ff){
        	//cout << "bnubu" << endl;
        	treap.insert();
        	lst++;
//        	cout << lst << endl;
        }
        //cout << "G" << endl;
        treap.markPref(e.ss);
	}
	vi x;
	treap.traverse(treap.head,x);
	sort(x.begin(),x.end());
	ll cost = 0;
	lst = -1;
	ll cnt = 0;
	for(auto e:x){
		//cout << "FINAL VALUIE : : : : : " << e<< endl;
	    cost += ((ll)(e))*(e-1)/2;
	}
	cout << cost << endl;
	return 0;
}