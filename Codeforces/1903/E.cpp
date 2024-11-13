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
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        // cout << "READ N " << n << endl;
        if(n==-1) return 0;
        pair<int,int> start;
        vt<pair<int,int>> points(n);
        cin >> start.f >> start.s;
        F0R(i, n) {
            // cout << "LINE 154 " << i << endl;
            cin >> points[i].f >> points[i].s;
            // cout << "LINE 156 " << i << endl;
        }
        set<int> evenInd, oddInd;
        F0R(i, n) {
            int dist = abs(start.f-points[i].f)+abs(start.s-points[i].s);
            if(dist%2) oddInd.insert(i);
            else evenInd.insert(i);
        }
        // cout << evenInd << oddInd << endl;
        if(evenInd.size()>=oddInd.size()) {
            cout << "First" << endl;
            bool myTurn = true;
            while(evenInd.size()||oddInd.size()) {
                if(myTurn&&oddInd.size()) {
                    auto fuck = *(oddInd.begin());
                    cout << fuck+1 << endl;
                    oddInd.erase(fuck);
                } else if(myTurn) {
                    auto fuck = *(evenInd.begin());
                    cout << fuck+1 << endl;
                    evenInd.erase(fuck);
                } else {
                    int x;
                    cin >> x;
                    x--;
                    oddInd.erase(x);
                    evenInd.erase(x);
                }
                myTurn=!myTurn;
            }
        } else {
            cout << "Second" << endl;
            bool myTurn = false;
            while(evenInd.size()||oddInd.size()) {
                if(myTurn&&evenInd.size()) {
                    auto fuck = *(evenInd.begin());
                    cout << fuck+1 << endl;
                    evenInd.erase(fuck);
                } else if(myTurn) {
                    auto fuck = *(oddInd.begin());
                    cout << fuck+1 << endl;
                    oddInd.erase(fuck);
                } else {
                    int x;
                    cin >> x;
                    x--;
                    oddInd.erase(x);
                    evenInd.erase(x);
                }
                myTurn=!myTurn;
            }
        }
        // cout << "GOT TO LINE 202" << endl;
    }
    return 0;
}