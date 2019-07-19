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
#include <bitset>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int MAXN = 501;
const int MAXK = 60+10;

bitset<MAXN> tempgrid[MAXN];
bitset<MAXN> grid[MAXN];
bitset<MAXN> permgrid[MAXN];

void clearT(){
    FOR(i,MAXN)tempgrid[i].reset();
}

void imprint(){
    FOR(i,MAXN)grid[i] = grid[i] & permgrid[i];
}

void copyto(){
    FOR(i,MAXN)grid[i] = tempgrid[i];
}

void shiftleft(){
    FOR(i,MAXN)tempgrid[i] |= grid[i] << 1;
}
void shiftright(){
    FOR(i,MAXN)tempgrid[i] |= grid[i] >> 1;
}
void shiftup(){
    FOR(i,MAXN-1){
        tempgrid[i] |= grid[i+1];
    }
}
void shiftdown(){
    FOR(i,MAXN-1)tempgrid[i+1] |= grid[i];
}

int main(){
    int r,c,m;
    cin >> r >> c >> m;
    FOR(i,r)permgrid[i].reset();
    FOR(i,r){
        string s;
        cin >> s;
        FOR(j,c){
            if(s[j] == '.'){
                //cout << "hihih" << endl;
                permgrid[i][j] = 1;
            }
        }
    }
    string x;
    cin >> x;
    clearT();
    FOR(i,MAXN)grid[i].set();
    imprint();

    for(auto c : x){
        clearT();
        if(c == 'N'){
            shiftup();
        }else if(c == 'E'){
            shiftleft();
        }else if(c == 'W'){
            shiftright();
        }else if(c == 'S'){
            shiftdown();
        }else{
            shiftup();
            shiftdown();
            shiftleft();
            shiftright();
        }
        copyto();
        clearT();
        imprint();
    }
    int ctr = 0;
    FOR(i,MAXN){
        ctr += grid[i].count();
    }
    cout << ctr << endl;
    return 0;
}