#define onlycc ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int, long double> pid;

ll n;
string s;

int main()
{
    onlycc;
    cin >> n;
    cin.ignore();
    for(int i = 1; i <= n; i++)
    {
        getline(cin, s);
        cout << i << ". " << s << '\n';
    }

    return 0;
}
