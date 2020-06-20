/*
SOLUTION:
Treat every d-digit number differently. for upto 6 digit, brute. for 7 and 9, we can again brute for prime factorisation. For d = 8, 1*8 and 2*4 forms are easy. Lets solve the 2*2*2 form. for this, its basically product of 3 primes, p1,p2,p3. Note that largest prime <=1e8/(2*3). so factorise till that using linear sieve. Then, compute all possible products P = p1*p2. Now, we can count number of valid p3s for every query separately using binsrch. It reduces to two binsrchs, for every query. We try to find all valid 8 digit good numbers of p1p2p3 form. ie, QUERY_NUM >= i >=1e7. thus, 2 binsrchs. For the first binsrch, precompute all the needed locations (ie, for the 1e7/P binsrch). For the second binsrch, we can binsrch on a reduced range rather than the whole prime array. This is enough to give 100. 
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
#define pll pair<ll,ll>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXP = (int)(1.6667e7);

int PTR = 0;
int primes[MAXP];
bool isP[MAXP+5];
int spf[(int)1e6 + 6];


int PTR2 = 0;
int allValidNums[MAXP+5];


int tptr = 0;
int tmp[MAXP];

void buildTill6Digit(){
    FORE(j,2,((int)1e6)-1){
        map<int,int> mp;
        int v = j;
        int cj = j;
        int ctr = 0;
        while(cj > 0){
            ctr++;
            cj /= 10;
        }
        while(v > 1){
            mp[spf[v]]++;
            v /= spf[v];
        }
        ll fc = 1;
        for(auto e: mp)fc *= e.ss+1;
        if(fc == ctr){
            allValidNums[PTR2++]= j;
        }
    }
}

void build7Digits(){
    FOR(i,PTR){
        ll v = primes[i];
        v = v*v*v;
        v *= v;
        if(v >= 1e7)break;
        if(v >= 1e6)allValidNums[PTR2++]=v;
    }
}
int cnt = 0;
void build8Digits(){
    tptr = 0;
    FOR(i,PTR){
        ll v = primes[i];
        v = v*v*v;
        if(v >= 1e8)break;
        int x = lower_bound(primes,primes+PTR,((int)1e7)/v)-primes;
        FORE(j,x,PTR-1){
            if(i == j)continue;
            ll val = v * primes[j];
            if(val >= 1e8)break;
            if(val >= 1e7){
                tmp[tptr++] = val;
            }
        }
    }


    // build for 8 = 1*8
    FOR(i,PTR){
        ll v = primes[i];
        v = v*v*v;
        v *= v;
        v *= primes[i];
        if(v >= 1e8)break;
        if(v >= 1e7)tmp[tptr++] = v;
    }
    
    sort(tmp, tmp+tptr);
    FOR(i,tptr)allValidNums[PTR2++]=tmp[i];
}

void build9digits(){
    int x = PTR;
    //vi all9;
    tptr = 0;
    FOR(i,x){
        ll a = primes[i];
        if(a*a*4 >= 1e9)break;
        FOR(j,i){
            ll b = primes[j];
            ll y = a*a*b*b;
            if(y >= 1e9)break;
            if(y >= 1e8)tmp[tptr++] = y;//all9.pb(a*a*b*b);
        }
    }
    FOR(i,x){
        ll a = primes[i];
        ll b = a*a*a*a;
        b *= b;
        if(b >= 1e9)break;
        if(b >= 1e8)tmp[tptr++] = b;//all9.pb(b);
    }

    sort(tmp,tmp+tptr);
    FOR(i,tptr)allValidNums[PTR2++]=tmp[i];
}

int p1p2PTR = 0;
ii p1p2[MAXP];
int indVal[MAXP];

void calcp1p2(){
    int x = PTR;
    FOR(i,x){
        ll aa = primes[i];
        if(aa > 500)break;
        FORE(j,i+1,x-1){
            ll bb = primes[j];
            if(aa*bb*bb > 1e8)break;
            p1p2[p1p2PTR++] = {bb*aa,bb};
        }
    }
    sort(p1p2,p1p2 + p1p2PTR);
    FOR(i,p1p2PTR){
        ll cc = p1p2[i].ss;
        ll bb = p1p2[i].ff;
        //if(bb*cc>b)break;
        ll z = 1e7/bb;
        int ind1 = lower_bound(primes, primes + PTR,max(z,cc+1)) - primes;
        indVal[i] = ind1;
    }
}

void preprocess(){
    FOR(i,MAXP)isP[i] = 1;
    FOR(i,1e6+4)spf[i] = i;
    FORE(i,2,MAXP){
        if(isP[i])primes[PTR++] = i;

        for(int x = 0;x < PTR and i*primes[x] < MAXP;x++){
            int y = i*primes[x];
            isP[y] = false;
            if(y <= 1e6)spf[y] = min(spf[y],primes[x]);
            if(i%primes[x] == 0)break;
        }
    }
    // we have calculated all the primes;
    allValidNums[PTR2++]=1;
    buildTill6Digit();
    build7Digits();
    build8Digits();
    build9digits();
    calcp1p2();
    
}

int get(int b){
    int x = PTR;
    int ccX = 0;
    b = min(b,(int)1e8);
    if(b > 1e7){
        int p1 = PTR;
        int p2 = PTR;
        FOR(i,p1p2PTR){
            ll cc = p1p2[i].ss;
            ll bb = p1p2[i].ff;
            if(bb*cc>b){
                continue;
            }
            int ind1 = indVal[i];//lower_bound(primes, primes + p1+5,max(z,cc+1)) - primes;

            ll zz = b/bb;
            int ind2 = lower_bound(primes,primes + p2+5,max(zz,cc+1)) - primes;
            p1 = ind1;
            p2 = ind2;
            //cout << zz << " " << cc+1 <<" " << ind2 << endl;
            if(primes[ind2]*bb > b)ind2--;
            if(primes[ind1]*bb >= 1e7)ind1--;
            ccX += ind2 - ind1;
        }
    }
    return ccX;
}

void test(){
    int pr[] = {1,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    int b = 15;
    int cc = 0;
    ll bb = 5;
    ll z = 3/bb;// bb * z >= 3
    PTR = 16;
    int ind1 = lower_bound(pr, pr + PTR,max(z,bb+1)) - pr;

    ll zz = b/bb;//bb*z <= 15
    cout << max(zz,bb+1) << endl;
    int ind2 = lower_bound(pr,pr + PTR,max(zz,bb+1)) - pr;
    cout << ind1 << " " << ind2 << endl;
    if(pr[ind2]*bb > b)ind2--;
    if(pr[ind1]*bb >= 3)ind1--;
    cc += ind2 - ind1;
    cout << cc << endl;
}


void solve(){
    int a,b;
    cin >> a >> b;
    auto it1 = upper_bound(allValidNums, allValidNums+PTR2,b) - allValidNums;
    if(it1 == 0){
        cout << 0 << endl;
    }else{
        int cc = get(b)-get(a-1);
        it1--;
        int it2 = upper_bound(allValidNums, allValidNums+PTR2,a-1) - allValidNums;
        if(it2 != 0){
            it2--;
            cout << it1-it2  + cc << endl;    
        }else{
            cout << (int)(it1-it2) + 1 + cc << endl;
        }   
    }
}

int main(){
    //test();
    //return 0;
    preprocess();
    //cout << get(1e8) << endl;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--)solve();
    return 0;
}