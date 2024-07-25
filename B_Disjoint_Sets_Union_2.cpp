#include<bits/stdc++.h>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i) // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i) // 1 based indexing

#define pb push_back
#define endl '\n'
#define fi first
#define se second
#define INF INT64_MAX-INT32_MAX
#define inf INT64_MIN - INT32_MIN
#define mp make_pair
#define int long long

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll,ll> pll;
typedef vector<pll> vpll;

#define all(x) (x).begin(), (x).end() //Forward traversal
#define rall(x) (x).rbegin, (x).rend() //reverse traversal

int M=1e9+7;

ll ceil(ll a,ll b)// ceil(a/b)
{
     if(a%b == 0)return a/b;
     else return (a/b)+1;
}

ll pow(long long x,int n, int m)
{
   if(n == 0)return 1;
     else
     {
         ll temp;
         temp = pow(x,n/2,m);
         temp = ((temp%m)*(temp%m))%m;
         if(n%2 == 1)return (temp*x)%m;
         return temp;
     }
}

int log(int x)
{
     return 31 - __builtin_clz(x);
}

class DSU
{
    vi par,sz;
    vi min_,max_;
    public:
        DSU(int n)
        {
            par.resize(n+1);
            sz.resize(n+1);
            min_.resize(n+1);
            max_.resize(n+1);
            for0(i,n+1)
            {
                par[i] =i;
                sz[i]=1;
                min_[i]=i;
                max_[i]=i;
            }
        }

        tuple<int,int,int,int> find(int a)
        {
            if(par[a] == a)return {a,min_[a],max_[a],sz[a]};
            else 
            {
                return tie(par[a],min_[par[a]],max_[par[a]],sz[par[a]]) = find(par[a]);
            }
        }

        void unify(int a,int b)
        {
            int p1,p2;
            tie(p1,ignore,ignore,ignore) = find(a);
            tie(p2,ignore,ignore,ignore) = find(b);
            if(par[p1] == par[p2])return;
            else if(sz[p1] < sz[p2])
            {
                par[p1] = p2;
                sz[p2] += sz[p1];
                min_[p2] = min(min_[p1],min_[p2]);
                max_[p2] = max(max_[p1],max_[p2]);
            }
            else
            {
                par[p2] = p1;
                sz[p1] += sz[p2];
                min_[p1] = min(min_[p1],min_[p2]);
                max_[p1] = max(max_[p1],max_[p2]);
            }
        }
};

int32_t main()
{ // never use power function of c++ ever again
// vector <vector<int>> grid(n,vector<int>(n,-1)); declaring a 2d vector
ios :: sync_with_stdio(false);
cin.tie(NULL);
cout.tie(0);
int n,m;
cin>>n>>m;
DSU dsu(n);
for0(i,m)
{
    string s;
    cin>>s;
    if(s == "union")
    {
        int a,b;
        cin>>a>>b;
        dsu.unify(a,b);
    }
    else
    {
        int c;
        cin>>c;
        int p,min_,max_,sz;
        tie(p,min_,max_,sz) = dsu.find(c);
        cout<<min_<<" "<<max_<<" "<<sz<<endl;
    }
}

return 0;
}