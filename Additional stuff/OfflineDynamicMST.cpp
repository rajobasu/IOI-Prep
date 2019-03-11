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
#define piil pair<pair<int,int> , ll>


using namespace std;

const int MOD = 1000000007;
const ll INF = 100000000000000;
const int MAXN = 100001;

int n;
class DSU{
	int parent[MAXN];
	public : 
	inline void init(){
		FOR(i,MAXN)parent[i] = i;
	}
	inline void init(vi v){
		for(auto ele:v)parent[ele] = ele;
	}
	int find(int node){
		if(parent[node] != node)parent[node] = find(parent[node]);
		return parent[node];
	}
	inline void merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		parent[pa] = pb;
	}
	inline bool isSame(int a,int b){
		return find(a) == find(b);
	}
};

class MST{
	bool isMSTEdge[MAXN];
	bool isBatchEdge[MAXN];
	int componentID[MAXN];
	int UID = 0;
	inline int getUID(){
		return UID++;
	}

	vector<pair<piil,int> > allEdges;// .ff.ff.ff = u,.ff.ff.ss = v, .ff.ss = len,.ss = UID;
	//vector<piil> qedges;
	DSU dsu;
	ll best;

	vector<pair<pair<int,ll>,int > > g[MAXN];

	void computeMST(){

		FOR(i,MAXN)isMSTEdge[i] = 0;
		
		sort(allEdges.begin(), allEdges.end(),[](pair<piil,int>& a,pair<piil,int>& b){
			return a.ff.ss < b.ff.ss;
		});
		
		dsu.init();
		best = INF;
		for(auto edge:allEdges){
			if(!dsu.isSame(edge.ff.ff.ff,edge.ff.ff.ss)){
				
				dsu.merge(edge.ff.ff.ff,edge.ff.ff.ss);
				isMSTEdge[edge.ss] = 1;
				if(dsu.isSame(0,n-1))best = min(best, edge.ff.ss);
			}

		}
	}
	void dfs(int node,int p,int c){
		componentID[node] = c;
		for(auto child:g[node]){
			if(!isMSTEdge[child.ss] or child.ff.ff == p or isBatchEdge[child.ss]){
				continue;
			}
			dfs(child.ff.ff,node,c);
		}
	}


	public : 
	vector<ll> solveBatch(vector<piil> edges){
		FOR(i,UID)isBatchEdge[i] = 0;
		FOR(i,edges.size())isBatchEdge[allEdges.size()+i] = 1;
		int ID[edges.size()];
		FOR(i,edges.size())ID[i] = getUID();
		int PTR = 0;
		
		for(auto edge : edges){
			allEdges.pb(mp(edge, ID[PTR]));
			g[edge.ff.ff].pb(mp(mp(edge.ff.ss,edge.ss),ID[PTR]));
			g[edge.ff.ss].pb(mp(mp(edge.ff.ff,edge.ss),ID[PTR++]));
		}

		computeMST();


		FOR(i,MAXN)componentID[i] = -1;
		FOR(i,n)if(componentID[i] == -1)dfs(i,-1,i);
		vector<ll> ans(edges.size());
		FOR(i,n)dsu.merge(i,componentID[i]);
		for(auto& ele:ans)ele = INF;
		if(best == INF){
			for(auto& ele: ans)ele = INF;
		}else if(componentID[0] == componentID[n-1]){
			for(auto& ele:ans)ele = best;
		}else{
			vi cc;
			set<int> st;
			FOR(i,n)st.insert(componentID[i]);
			for(auto ele:st)cc.pb(ele);

			//cout << "HOHOOH" << endl;
			//for(auto ele:cc)cout << ele << " " ;cout << endl;
			FOR(i,edges.size()){
				
				sort(edges.begin(), edges.begin() + i +1,[&](piil& a,piil& b){
					return a.ss < b.ss;
				});
				
				dsu.init();
				FOR(j,i+1){
					dsu.merge(componentID[edges[j].ff.ff],componentID[edges[j].ff.ss]);
					if(dsu.isSame(componentID[0],componentID[n-1])){
						ans[i] = max(best,edges[j].ss);
						break;
					}
				}
			}

		}

		return ans;
	}
};


struct Edge{
    int u,v,a,b;
    Edge(int uu,int vv,int aa,int bb){
        u = uu;
        v = vv;
        a = aa;
        b = bb;
    } 
};

int main(){
	int m;
    cin >> n >> m;
    vector<Edge*> allE;
    FOR(i,m){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a--;b--;
        allE.pb(new Edge(a,b,c,d));
    }
    DSU dsu;


    sort(allE.begin(), allE.end(),[](Edge* e1,Edge* e2){
        return e1->b < e2->b;
    });
    ll ans[m];
    vector<piil> edd;
    int allB[m];
    
    FOR(j,m){
       	Edge* ed = allE[j];
       	edd.pb({{ed->u,ed->v},ed->a});
       	allB[j] = ed->b;
    }

    int T = 300;
    MST mst;
   	vector<piil> toPass;
   	vector<ll> res;
    FOR(i,m){
    	toPass.pb(edd[i]);
    	if((i+1)%T == 0){
    		vector<ll> ret = mst.solveBatch(toPass);
    		for(auto ele: ret)res.pb(ele);
    		toPass.clear();
    	}
    }
    if(toPass.size()!= 0){
    	vector<ll> ret = mst.solveBatch(toPass);
    	for(auto ele: ret)res.pb(ele);
    }
	ll mn = INF;
	//FOR(i,m)cout << allB[i] << " ";cout << endl;
	//for(auto ele:res)cout << ele << " ";cout << endl;
	FOR(i,m){
		mn = min (mn,allB[i]+ res[i]);
	}

	if(mn == INF)cout << -1 << endl;
	else cout << mn << endl;


    return 0;
}
/*
    FOR(i,m){
        ll val = allE[i]->b;
        sort(allE.begin(),allE.begin() + i + 1,[](Edge* e1,Edge* e2){
            return e1->a < e2->a;
        });

        ll cost = INF;
        dsu.init();
        FOR(j,i+1){
            dsu.merge(allE[j]->u,allE[j]->v);
            if(dsu.isSame(0,n-1)){
                cost = allE[j]->a;
                break;
            }
        }
        //cout << i << " " << val << " " << cost << endl;
       	cost += val;
        ans[i] = cost;
    }
    ll mn = INF;
    FOR(i,m)mn = min(mn,ans[i]);

    
    MST mst;
    vector<ll> allAns = mst.solveBatch(edd);

    FOR(i,m){
    	cout << allAns[i]+allB[i] << " " << ans[i] << endl;
    }
    cout << endl;
    if(mn < INF)cout << mn << endl;
    else cout << -1 << endl;

    return 0;
}





*/