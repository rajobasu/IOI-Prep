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
#include <stack>
#include <set>

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
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int INF = 1e9+10;
const int MAXN = 1000*100*10+10;
const int MAXVAL = 1e9+10;

int CountCritical();

// stage 1 means that all have degree atmost 2
// stage 2 means that there is degree atmost 3,
// stage 3 means that there is a node of degree 4 or higher.
int stage = 1;
int deg[MAXN];

vi g[MAXN];
vector<ii> edges;

int n;

struct DSU{
    int parent[MAXN];
    int compSize[MAXN];
    int ID = 0;
    void init(int n, bool b=0){
        //parent = new int[n];
        //if(b)compSize = new int[n];
        
        FOR(i,n)parent[i] = i;
        FOR(i,n)compSize[i] = 1;
    }
    inline int find(int a){
        if(parent[a] != a)parent[a] = find(parent[a]);
        return parent[a];
    }
    inline void merge(int a,int b){
        int pa = find(a);
        int pb = find(b);
        parent[pa] = pb;
        compSize[pb] += compSize[pa];
    }
    inline bool isSame(int a,int b){
        return find(a) == find(b);
    }
    inline int sizeOf(int a){
        return compSize[find(a)];
    }
};  

DSU dsu1;
set<int> impNodes;
DSU dsu[10];
int degindi[10][MAXN];
bool sedd[10];

vi impNd;
set<int> componentWithHighDeg;
int componentWithCycle;
bool doomed;

void Init(int N){
    doomed = false;
    n = N;//gdsu = new DSU(n);
    dsu1.init(n,1);
    componentWithCycle = -1;
}

int cntDeg;
void initStage2(int a,int b){
    impNd.clear();
    impNodes.clear();
    /*
    FOR(i,10){
        dsu[i].init(n);
        FOR(j,MAXN)degindi[i][j] = 0;
        sedd[i] = 0;
    }*/

    stage = 2;
    int ctr = 0;
    
    cntDeg = ctr;
    
    FOR(i,n){
        if(deg[i] > 2){
            impNodes.insert(i);
            for(auto e:g[i])impNodes.insert(e);

            break;
        }
    }


    for(auto e : impNodes){
        impNd.pb(e);
    }
    int xx = 0;
    for(auto x : impNd){
        dsu[xx].init(n);

        for(auto edge : edges){
            if(edge.ff == x or edge.ss == x)continue;
            degindi[xx][edge.ff]++;
            degindi[xx][edge.ss]++;
            // see if the graph has any 3deg nodes left
            if(max(degindi[xx][edge.ff],degindi[xx][edge.ss]) > 2){
                sedd[xx] = 1;
            }else{
                // check if graph has any cycles remaining
                if(dsu[xx].isSame(edge.ff,edge.ss)){
                    sedd[xx] = 1;
                }else{
                    dsu[xx].merge(edge.ff,edge.ss);
                }
            }
        }
        xx++;
    }

}

void initStage3(){
    stage = 3;
    set<int> deg4;
    dsu[9].init(n);
    FOR(i,n){
        if(deg[i] >= 4){
            deg4.insert(i);
        }
    }
    if(deg4.size() > 1){
        doomed = 1;
        return;
    }else{
        impNd.clear();
        for(auto e : deg4){
            impNd.pb(e);
        }
        int mynode = impNd[0];
        
        //cout << mynode << endl;
        for(auto e : edges){
            if(e.ff == mynode or e.ss == mynode)continue;
            degindi[9][e.ff]++;
            degindi[9][e.ss]++;
            if(degindi[9][e.ff] > 2 or degindi[9][e.ss] > 2){
                doomed = 1;
            }else if(dsu[9].isSame(e.ff,e.ss)){
                //cout << e.ff << " " << e.ss << endl;
                //cout << dsu[9].find(e.ff) << " " << dsu[9].find(e.ss) << endl;
                //cout << "MEHH" << endl;
                doomed = 1;
            }else{
                dsu[9].merge(e.ff,e.ss);
            }
        }
    }
}
bool reset = 0;

void Link(int a,int b){
    g[a].pb(b);
    g[b].pb(a);
    edges.pb({a,b});
    deg[a]++;
    deg[b]++;
    if(doomed)return;
    if(stage == 1){

        if(deg[a] > 2 or deg[b] > 2){
    //      cout << "INITING STAGE 2" << endl;
            initStage2(a,b);
        }else{
    //      cout << "PROCESSING IN STAGE 1" << endl;
            // we still have atmost degree 2
            if(dsu1.isSame(a,b)){
                // this means we are creating a cycle in this component.
                if(componentWithCycle == -1){
                    // this means this is the first component with the cycle
                    componentWithCycle = dsu1.find(a);
                }else{
                    doomed = true;
                }
            }else{
                dsu1.merge(a,b);
            }
        }
    }else if(stage == 2){
        if(deg[a] > 3 or deg[b] > 3){
    //      cout << "INITING STAGE 3" << endl;
            initStage3();
        } else {

            int xx = 0;
            
    //      cout << "PROCESSING in STAGE 2" << endl;
            for(auto x : impNd){
                if(a == x or b == x){
                    xx++;
                    continue;
                }
    //          cout << "xx : " <<  xx << endl;
                degindi[xx][a]++;
                degindi[xx][b]++;
                if(max(degindi[xx][a], degindi[xx][b]) > 2){
                    sedd[xx] = 1;
                }else{
                    if(dsu[xx].isSame(a,b)){
                        sedd[xx] = 1;
                    }else{
                        dsu[xx].merge(a,b);
                    }
                }
                xx++;
            }
        }
    }else if(stage == 3){
    //  cout << "PROCESSING STAGE 3" << endl;
        int mynode = impNd[0];
        if(deg[a] > 3 and mynode != a){
            doomed = 1;
        } else if(deg[b] > 3 and mynode != b){
            doomed = 1;
        } else {
            if(a == mynode or b == mynode)return;
            degindi[9][a]++;
            degindi[9][b]++;
            if(degindi[9][a] > 2 or degindi[9][b] > 2){
                doomed = 1;
            } else {
                if(dsu[9].isSame(a,b)){
                    doomed = 1;
                }else{
                    dsu[9].merge(a,b);
                }
            }
        }

    }

    //cout << CountCritical() << endl;
}
/*
inline bool isCritical(int x){
    DSU dsu(n);
    int deg[n];
    FOR(i,n)deg[i] = 0;

    for(auto e : edges){
        if(e.ff == x or e.ss == x)continue;
        deg[e.ff]++;
        deg[e.ss]++;
        if(dsu.find(e.ff) == dsu.find(e.ss)){

            return 0;
        }
        dsu.merge(e.ff,e.ss);
    }
    FOR(i,n)if(deg[i] > 2)return 0;
    return 1;
}*/

int CountCritical(){
    if(doomed)return 0;
    if(stage == 1 and componentWithCycle == -1){
        return n;
    }
    if(stage == 1 and componentWithCycle != -1){
        return dsu1.sizeOf(componentWithCycle);
    }
    if(stage == 2){
        int ctr = 0;
        FOR(i,impNd.size()){
            ctr += !sedd[i];
        }
        return ctr;
    }

    //while(1);
    return 1;
}

int ma1in(){
    Init(10);
    //cout << CountCritical() << endl;
    Link(0,1);
    Link(1,2);
    
    Link(3,4);
    Link(3,5);
    Link(4,5);
    Link(2,0);

    //Link(2,3);
    //Link(2,4);
    /*
    Link(4,5);
    Link(5,6);
    Link(4,6);
    */
    return 0;
}

