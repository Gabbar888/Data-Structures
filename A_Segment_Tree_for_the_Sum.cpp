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

struct segtree
{
    int size;
    vector<int> sums;
    void init(int n)
    {
        size =1;
        while(size<n)size*=2;
        sums.assign(2*size,0LL);
    }

    void build(vi &a,int x, int lx, int rx)
    {
        if(rx-lx == 1)
        {
            if(lx<(int)a.size())sums[x] = a[lx];
            return;
        }
        int m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }
    void build(vi &a)
    {
        build(a,0,0,size);
    }
    void set(int i, int v,int x,int lx,int rx)
    {
        if(rx - lx == 1)
        {
            sums[x] =v;
            return;
        }
        int m = (lx+rx)/2;
        if(i<m)
        {
            set(i,v,2*x+1,lx,m);
        }
        else set(i,v,2*x+2,m,rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }

    void set(int i, int v)
    {
        set(i,v,0,0,size);
    }

    int sum(int l, int r,int x,int lx, int rx)
    {
        if(lx>=l && rx <= r){
            return sums[x];
        }
        if(lx>=r || rx <= l)return 0;
        int m = (lx+rx)/2;
        int s1 = sum(l,r,2*x+1,lx,m);
        int s2 = sum(l,r,2*x+2,m,rx);
        return s1+s2;
    }

    int sum(int l, int r)
    {
        return sum(l,r,0,0,size);
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
vi a(n);
for0(i,n)cin>>a[i];
segtree st;
st.init(n);
st.build(a);
while(m--)
{
    int op;
    cin>>op;
    if(op == 1)
    {
        int i,v;
        cin>>i>>v;
        st.set(i,v);
    }
    else
    {
        int l,r;
        cin>>l>>r;
        cout<<st.sum(l,r)<<endl;
    }
}

return 0;
}