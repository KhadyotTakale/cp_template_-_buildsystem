#include <bits/stdc++.h>


using namespace std;
/* clang-format off */
/* TYPES  */
#ifdef khadyot
#include "debug.h"
#else
#define dbg(...) ;
#define debug(...) ;
#define crndl ;
#endif
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>f
#define nline "\n"

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back
#define sorting(arr) sort(arr.begin(),arr.end())
#define reversing(arr) reverse(arr.begin(),arr.end())
#define upperbound(arr,x) upper_bound(arr.begin(),arr.end(),x) - arr.begin()
#define lowerbound(arr,x) lower_bound(arr.begin(),arr.end(),x) - arr.begin()

//gcd



//seive isPrime? 
bool isPrime(ll n, ll k){
    vector<bool> isPrime(n+1,true);
    isPrime[0] = isPrime[1] = false;
    for(ll i = 2; i <= n; i++){

        if(isPrime[i]){
            for(ll j = i * i; j <= n; j += i){
                isPrime[j] = false;
            }
        }
    }
    if(isPrime[k] == true){
        return true;
    }
    return false;
}
//seive prime

void seive(ll n){
    vector<bool> isPrime(n+1,true);
    isPrime[0] = isPrime[1] = false;

    for(ll i = 2; i <= n; i++){
        if(isPrime[i]){
            for(ll j = i*i; j <= n; j += i){
                isPrime[j] = false; 
            }
        }
    }

    for(ll i = 0; i <= n+1; i++){
        if(isPrime[i] == true){
            cout << i << " ";
        }
    }
}

//smallest prime factorization

vector<ll> smallestPrimeFactor(ll n){
    vector<bool> isPrime(n+1,true);
    vector<ll> spf(n+1);
    isPrime[0] = isPrime[1] = false;

    for(ll i = 2; i <= n; i++){
        if(isPrime[i]){
            spf[i] = i; 
            for(ll j = i*i; j <= n; j += i){
                isPrime[j] = false;
                if(spf[j] == 0) 
                    spf[j] = i;
            }
        }
    }
    return spf;
}

//expo
ll expo(ll p, ll n, ll m) {
    ll res = 1;
    p = p % m;
    while (n > 0) {
        if (n & 1)
            res = (res * p) % m;
        n = n >> 1;
        p = (p * p) % m;
    }
    return res;
}

//binary modular exponential

ll binpow(ll a, ll b){

    ll ans = 1;
    while(b > 0){
        if(b & 1){
            ans = ans * a;
        }
        a = a * a;
        b >>= 1;
    }
    return ans;
}

//hashing of string function

ll p = 1000, m = 1e9 + 7;

ll hash1(string s){
    int n = s.length();
    ll hashSoFar = 0;
    ll powerOfP = 1;
    for(int i = 0; i < n; i++){
        int charchterValue = s[i] - 'a' + 1;
        hashSoFar = (hashSoFar + charchterValue * powerOfP) % m;
        powerOfP = (powerOfP * p) % m;
    }
    return hashSoFar;
}

//mmiprimefunction

ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = gcdExtended(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

ll mminvprime(ll a, ll m) {
    ll x, y;
    ll g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        return -1; 
    else {
        ll res = (x%m + m) % m;
        return res;
    }
}

// Struct Hashing


struct Hashing{
    string s;
    ll p = 1000;
    ll m = 1e9 + 7;
    int n;
    vector<ll> prefixHash;
    vector<ll> powersOfP;
    vector<ll> inversePowersOfP;
    Hashing(string queryString){
        s = queryString;
        n = s.size();
        prefixHash.resize(n);
        powersOfP.resize(n);
        inversePowersOfP.resize(n);
        calculatePowersAndInversePowersOfP();
        calculatePrefixHashes();
    }
    void calculatePowersAndInversePowersOfP(){ // O(n)
        ll currentPower = 1;
        for(int i = 0; i < n; i++){
            powersOfP[i] = currentPower;
            currentPower = (currentPower * p) % m;
        }
        inversePowersOfP[n - 1] = mminvprime(powersOfP[n - 1], m);
        for(int i = n - 2; i >= 0; i--){
            inversePowersOfP[i] = (inversePowersOfP[i + 1] * p) % m;
        }
    }
    void calculatePrefixHashes(){
        ll hashSoFar = 0;
        for(int i = 0; i < n; i++){
            hashSoFar = (hashSoFar + (s[i] - 'a' + 1) * powersOfP[i]) % m;
            prefixHash[i] = hashSoFar;
        }
    }
    
    
    ll substringHash(int l, int r){  // O(1)
        ll val1 = prefixHash[r];
        ll val2 = l > 0 ? prefixHash[l - 1] : 0LL;
        return ((val1 - val2 + m) * inversePowersOfP[l]) % m;
    }
};

//eulers totient function

ll phi(ll n){

    ll ans = n;

    for(int i = 2; i * i <= n; i++){

        if(n % i == 0){

            while(n % i == 0){
                n = n / i;
                ans -= ans / i;
            }
        }

    }
    if(n > 1){
        ans -= ans / n;

    }
    return ans;
}

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void bob() { cout << "Bob\n"; }
void alice() { cout << "Alice\n"; }

/*  All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
/*____________________________________________________________________________________________________________________________________________*/

 
void solve(){
 
}

int main() {
#ifdef khadyot
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
freopen("error.txt", "w", stderr);
#endif 
    
    solve();
}

