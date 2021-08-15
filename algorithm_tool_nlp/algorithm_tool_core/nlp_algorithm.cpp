#include "nlp_algorithm.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int min3(int a, int b, int c)
{
    a = a < b ? a : b;
    return a < c ? a : c;
}

int LevenshteinDis(string s, int s_len, string t, int t_len)
{
    int cost;
    //基本情况，若字符串s和t的最小距离为0，则返回其中的最大距离作为编辑距离
    if (s_len == 0)
        return t_len;
    if (t_len == 0)
        return s_len;
    //测试s和t的各自最后一个字符是否匹配
    if (s[s_len - 1] == t[t_len - 1])
        cost = 0;
    else
        cost = 1;
    return min3(LevenshteinDis(s, s_len - 1, t, t_len) + 1,
                LevenshteinDis(s, s_len, t, t_len - 1) + 1,
                LevenshteinDis(s, s_len - 1, t, t_len - 1) + cost);
}

int LevenshteinDP(string s, string t)
{
    //levenshtein距离的自底向上方式的动态规划实现，把重复计算的距离存入一个矩阵中
    int dp[s.length() + 1][t.length() + 1]; //d[i][j]表示字符串s的前i字符和t的前j个字符的莱文斯坦距离
    for (int i = 0; i <= s.length(); i++)
        dp[i][0] = i; //源字符串s到空字符串t只要删除每个字符
    for (int j = 1; j <= t.length(); j++)
        dp[0][j] = j; //从空字符s到目标字符t只要添加每个字符
    for (int j = 0; j < t.length(); j++)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == t[j])
                dp[i + 1][j + 1] = dp[i][j]; //无任何操作
            else
                dp[i + 1][j + 1] = min3(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1);
            //分别为删除、添加、替换操作
        }
    }
    return dp[s.length()][t.length()];
}

int main()
{
    string m = "kittesnsssdcjks";
    string n = "sitdftingwcsdcc";
    clock_t start, finish;
    double totaltime;
    start = clock();
    cout << "recursion: " << LevenshteinDis(m, m.length(), n, n.length()) << endl;
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "递归运行时间为" << totaltime << "秒！" << endl
         << endl;

    start = clock();
    cout << "Dynamic Programming: " << LevenshteinDP(m, n) << endl;
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "DP运行时间为" << totaltime << "秒！" << endl
         << endl;
    return 0;
}
