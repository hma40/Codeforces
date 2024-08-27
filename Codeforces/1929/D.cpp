#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
#define double long double
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n;
vt<vt<int>> adj;
// vt<int> par;
vt<vt<int>> dp;
struct Math {
    ll m;
    vt<ll> facts;
    vt<ll> invFact;
    int curSieve = 0;
    //lp is 0 if its prime
    vt<int> lp;
    vt<int> primes;
    vt<vt<int>> allFactors;
    vt<int> mobius;
    Math(int md):m(md) {}
    Math(): m(1000000007) {};
    void mob(int n) {
        mobius.assign(n+1,-1);
        vt<int> p(n+1, 1);
        mobius[0] = 0, mobius[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (p[i]) {
                for (int j = 2; j*i <= n; j++) {
                    // cout << "LINE 142 " << i << " " << j << endl;
                    if (j%i) mobius[i*j] = mobius[i]*mobius[j];
                    else mobius[i*j] = 0;
                    p[i*j] = 0;
                }
            }
        }
    }
    ll bexpo(ll b, ll e) {
        ll a = 1;
        while(e) {
            if(e%2) {
                a*=b;
                a%=m;
            }
            e/=2;
            b*=b;
            b%=m;
        }
        return a;
    }
    void fact(int bound) {
        facts.assign(bound,0);
        invFact.assign(bound,0);
        facts[0]=invFact[0]=1;
        FOR(i, 1, bound) {
            facts[i]=facts[i-1]*i;
            facts[i]%=m;
            invFact[i]=bexpo(facts[i], m-2);
        }
    }
    void sieve(int bound) {
        if(curSieve>=bound) return;
        curSieve=bound;
        lp.assign(bound+1, 0);
        primes.clear();
        for(int i = 2; i <= bound; i++) {
            if(lp[i]==0) {
                lp[i]=i;
                primes.add(i);
            }
            for(int j = 0;i * primes[j]<=bound; j++) {
                lp[i*primes[j]]=primes[j];
                if(primes[j]==lp[i]) break;
            }
        }
    }
    ll nck(int n, int k) {
        if(n<k||k<0||n<0) return 0;
        return facts[n]*invFact[k]%m*invFact[n-k]%m;
    }
    ll gcd(ll a, ll b) {
        if(a>b) swap(a,b);
        while(a!=0) {
            int t = a;
            a=b%a;
            b=t;
        }
        return b;
    }
    ll lcm(ll a, ll b) {
        return a/gcd(a,b)*b;
    }
    ll inv(ll x) {
        return bexpo(x, m-2);
    }
    bool isprime(ll n) {    
        sieve(1000000);
        if (n < lp.size()) {
            if(lp[n]==n) {
                return true;
            } else {
                return false;
            }
        }
        if (n%2 == 0) return false;
        ll d = n-1, r = 0;
        while (d%2 == 0) r++, d >>= 1;
        for (int k = 0; k < 30; k++) {
            __int128_t x = 1, a = uniform_int_distribution<ll>(2, n-2)(rnd);
            for (ll i = 1; i <= d; i <<= 1) {
                if (d&i) x = (x*a)%n;
                a = (a*a)%n;
            }
            bool f = 0;
            if (x == 1 || x == n-1) f = 1;
            for (int i = 1; i < r; i++)
                f = f || (x = (x*x)%n) == n-1;
            if (!f) return false;
        }
        return true;
    }   
 
// returns a sorted list of all prime factors of n in O(min(n^(1/2), n^(1/4)+log^3(n)+10^5)) time.
// works for n <= 10^18
    vector<ll> primefactors(ll n) {
        if(isprime(n)) {
            return {n};
        }
        // static vector<ll> small = primesupto(1000000);
        // if (isprime(n)) return {n};
        vector<ll> out;
        for (ll p : primes) {
            if (p*p > n) break;
            while (n%p == 0)
                n /= p, out.push_back(p);
        }
        if (n == 1 || isprime(n)) {
            if (n != 1) out.push_back(n);
            return out;
        }
        __int128_t x = 2, y = 2;
        ll ff = 0;
        for (ll z = 1; 1; z <<= 1) {
            y = x;
            for (ll i = 0; i < z; i++) {
                (x = (x*x+1)%n);
                ff = std::gcd(ll(x-y), n);
                if(ff > 1) {
                    out.push_back(min(ff, n/ff)), out.push_back(max(ff, n/ff));
                    return out;
                }
            }
        }
        return out;
    }
    vector<ll> divisors(ll n) {
        map<ll, int> p;
        for (ll x : primefactors(n)){
            p[x]++;
        }
        // cout << p << endl;
        vector<ll> out = {1};
        for (auto& [q, f] : p) {
            vector<ll> tmp;
                for (ll x : out) {
                    ll r = 1;
                    for (int i = 0; i <= f; i++) {
                        tmp.push_back(x*r);
                        r *= q;
                    }
                }
            out = tmp;
        }
        return out;
    }
    void factorAll(int bound) {
        allFactors.assign(bound+1, vt<int>{});
        FOR(i, 1, bound+1) {
            for(int j = i; j <= bound; j+=i) {
                allFactors[j].add(i);
            }
        }
    }
};  
Math ma(mod);
void dfs(int node, int par) {
    trav(x, adj[node]) {
        if(x!=par) {
            dfs(x, node);
        }
    }
    int prod = 1;
    trav(x, adj[node]) {
        if(x==par) continue;
        prod*=dp[x][0];
        prod%=mod;
    }
    //current node is not dangerous, none of its children are dangerous
    dp[node][0]=prod;
    //current node is dangerous, none of its children are dangerous
    dp[node][1]=prod;
    //current node is not dangerous, each child has at most one dangerous city
    int prod2 = 1;
    trav(x, adj[node]) {
        if(x==par) continue;
        prod2*=(dp[x][0]+dp[x][1]);
        prod2%=mod;
    }
    prod2-=prod;
    prod2%=mod;
    prod2+=mod;
    prod2%=mod;
    dp[node][1]+=prod2;
    dp[node][1]%=mod;
    //current node is not dangerous, one child has 2 dangerous cities while every other child has none
    int temp;
    trav(x, adj[node]) {
        if(x==par) continue;
        temp=prod;
        temp*=ma.inv(dp[x][0]);
        temp%=mod;
        temp*=dp[x][2];
        temp%=mod;
        dp[node][2]+=temp;
        dp[node][2]%=mod;
    }
    //current node is dangerous, one child has 1 dangerous intersection while every other child has none
    trav(x, adj[node]) {
        temp=prod;
        temp*=ma.inv(dp[x][0]);
        temp%=mod;
        temp*=dp[x][1];
        temp%=mod;
        dp[node][2]+=temp;
        dp[node][2]%=mod;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n;
        adj.assign(n, vt<int>());
        // par.assign(n, vt<int>());
        dp.assign(n, vt<int>(3));
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        dfs(0,-1);
        // cout << dp << endl;
        cout << (dp[0][0]+dp[0][1]+dp[0][2])%mod << endl;
    }
    return 0;
}
/*
dp[a][b] = ways to select subtree of a such that any path passing through a downwards has at most b dangerous cities
*/