/*nixudui.cpp
#include <iostream>

using namespace std;
typedef long long LL;
const int N = 100000;
int n, q[N], t[N];

LL nixudui(int l, int r)
{
    if (l >= r) return 0;
    int mid = (l + r) >> 1;
    LL res = nixudui(l, mid) + nixudui(mid + 1, r);
    //merge sort开始
    int k = 0, i = l, j = mid + 1;
    while ( i <= mid && j <= r)
        if (q[i] <= q[j]) t[k++] = q[i++];
        else
        {
            t[k++] = q[j++];
            res += mid - i + 1;
        }
    while (i <= mid) t[k++] = q[i++];
    while (j <= r) t[k++] = q[j++];
    for (int i = l, j = 0; i <= r; i++, j++) q[i] = t[j];
    //merge sort结束
    return res;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> q[i];
    cout << nixudui(0, n-1) << endl;
    for (int i = 0; i < n; i++) cout << q[i];
    return 0;
}*/
/*erfen.cpp
#include <iostream>
using namespace std;
const int N = 100010;
int n, m;
int q[N];

int main(){
    scanf("%d%d", &n, &m);
    for ( int i = 0; i < n; i++ ) cin >> q[i];
    while ( m-- ) {
        int x;
        cin >> x;

        int l = 0, r = n-1;
        while ( l < r ){
            int mid = l + r >> 1;
            if ( q[mid] >= x ) r = mid;
            else l = mid + 1;
        }
        if (q[l] != x) cout << "-1 -1" << endl;
        else{
            cout << l << ' ';
            int l = 0, r = n - 1;
            while ( l < r){
                int mid = l + r + 1 >> 1;
                if ( q[mid] <= x ) l = mid;
                else r = mid - 1;
            }
            cout << l << endl;
        }
    }
    return 0;
}*/
/*高精度加法
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6 + 10;
//C = A + B
vector<int> add(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || i < B.size(); i++)
    {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back( t % 10);
        t /= 10;
    }
    if (t) C.push_back(t);
    return C;
}

int main()
{
    string a, b;
    vector<int> A, B;
    cin >> a >> b; // a = "123456" 
    //push_back就是把元素放到vector的容器里， -'0'是为了把字符转化为数字
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');// A = [6, 5, 4, 3, 2, 1]
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    auto C = add(A, B);
    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << endl;
    return 0;

}*/
/*高精度减法
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
//判断AB谁大
bool cmp(vector<int> &A, vector<int> &B)
{
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i-- )
        if(A[i] != B[i]) return A[i] > B[i];
    return true;
}
// C = A - B
vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++)
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i]; 
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main(){
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for ( int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for ( int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    if (cmp(A, B)){
        auto C = sub(A, B);
        for ( int i = C.size() - 1; i >= 0; i--) cout << C[i];
    }
    else{
        auto C = sub(B, A);
        cout << "-";
        for ( int i = C.size() - 1; i >= 0; i--) cout << C[i];
    }
    cout << endl;
    return 0;

}*/
/*高精度乘以低精度
#include <iostream>
#include <vector>
const int N = 1e6 + 10;

using namespace std;

vector<int> matmul(vector<int> &A, int b)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++){
        t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    return C;

}


int main()
{
    string a;
    int b;
    cin >> a >> b;
    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

    auto C = matmul(A, b);

    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << endl;
    return 0;


}*/
/*高精度除以低精度
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e6 + 10;
// C = A / B
vector<int> div(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i--){
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end()); // 将C倒序输出
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}


int main()
{
    string a;
    int b;
    cin >> a >> b;

    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i-- ) A.push_back(a[i] - '0');

    int r;
    auto C = div(A, b, r);

    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << endl;
    cout << r << endl;
    return 0;
}*/
/*前缀和
#include <iostream>
using namespace std;
const int N = 100000;
int sum[N] = {0};

int main()
{
    int n, m, x;
    int a[N];
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> x;
        sum[i] = x + sum[i - 1];
    }
    while(m--){
        int l, r;
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << endl;
    }
    return 0;
}*/


/*子矩阵 sub of matrix
#include <iostream>
using namespace std;
const int N = 10010;
int sum[N][N] = {{0,0}};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int  x = 0;
            cin >> x;
            sum[i][j] = x + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }       
    }
    while(q--)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1]);
    }
    return 0;
}*/


/*差分
#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 100010;
int a[N], b[N];

void insert(int l, int r, int x)
{
    b[l] += x;
    b[r + 1] -= x;
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        insert(i, i, a[i]);
    while(m--){
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        insert(l, r, x);
    }
    for (int i = 1; i <= n; i++)
        b[i] += b[i - 1];//前缀和
    for (int i = 1; i <= n; i++)
        cout << b[i] << " ";
    return 0;
}*/

/*差分矩阵
#include<iostream>
#include<stdio.h>

const int N = 10010;
using namespace std;
int a[N][N] = {0}, b[N][N]= {0}, q[N] = {0};
void insert(int x1, int y1, int x2, int y2, int c)
{
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;

}
int main()
{
    int n, m ,q;
    cin >> n >> m >> q;
    for (int i = 1; i<= n; i++){
        for (int j = 1; j<= m; j++){
            scanf("%d", &a[i][j]);
            insert(i, j, i, j, a[i][j]);
        }
    }
    while(q--){
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1, y1, x2, y2, c);
    }
    for (int i = 1; i<= n; i++){
        for (int j = 1; j<= m; j++){
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
        }
    }
    for (int i = 1; i<= n; i++){
        for (int j = 1; j<= m; j++) printf("%d ", b[i][j]);
        puts("");
    }
    return 0;
}*/

/*最长连续不重复子序列
#include <iostream>
#include <stdio.h>

using namespace std;
const int N = 100010;
int a[N], s[N];

int main()
{
    int n, res = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0, j = 0; i < n; i++){
        s[a[i]] ++;
        while ( s[a[i]] > 1 )
        {
            s[a[j++]] --;
        }
        res = max(res, i - j + 1);
    }
    cout << res << endl;
    return 0;
}*/

/* array elements sum 
#include <iostream>
#include <stdio.h>

using namespace std;
const int N = 10010;
int A[N], B[N];

int main()
{
    int n, m, x;
    cin >> n >> m >> x;
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    for (int j = 0; j < m; j++) scanf("%d", &B[j]);
    // 原本 O(N ^2) complexity
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         if (A[i]+B[j] == x)
    //         {
    //             printf("%d %d\n", i, j);
    //         }
    //     }
    // }
    for (int i = 0, j = m - 1; i < n; i ++)
    {
        while (j >= 0 && A[i] + B[j] > x) j --;
        if ( j >= 0 && A[i] + B[j] == x)
        {
            cout << i << " " << j << endl;
        }
    }
    return 0;
}*/

/* array elements sum 2
#include <iostream>
using namespace std;

const int N = 10010;
int A[N], B[N];

int main()
{
    int n, m, x;
    std::cin >> n >> m >> x;
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int j = 0; j < m; j++) cin >> B[j];
    
    int i = 0, j = m - 1;
    while (i < n && j >= 0)
    {
        int sum = A[i] + B[j];
        if (sum == x)
        {
            std::cout << i << " " << j << endl;
            i++;
            j--;
        }
        else if (sum < x)
        {
            i++;
        }
        else
        {
            j--;
        }
    }
    return 0;
}*/

/* 判断子序列 
#include <iostream>
#include <cstring>

using namespace std;
const int N = 100010;
int a[N], b[N];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if(a[i] == b[j]) i ++;
        j ++;
    }
    if (i ==n) puts("Yes");
    else puts("No");
    return 0;
} */

/* 二进制中1的个数 
// n的二进制中看k位是几     n >> k & 1 
// lowbit(X):返回x的最低位的1的位置，即x & (-x)
#include <iostream>
using namespace std;
const int N = 100010;

int lowbit( int x)
{
    return x & -x;
}

int main()
{
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++ ){
        cin >> x;
        int res = 0;
        while (x){
            x -= lowbit(x);
            res ++;
        }
        cout << res << ' ';
    }
    return 0;
}*/
