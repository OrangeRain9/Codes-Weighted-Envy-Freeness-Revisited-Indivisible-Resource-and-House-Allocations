#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "common.hpp"

/*
setting = "sum", "avg" or "sumavg"
*/
bool bruteforce_house(const instance_t& ins, string setting) {

    vector<int> v; 
    vector<set<int> > ans;
    ans.resize(ins.n + 1);
    allocation_t allo(ans, ins.n, ins.m);
    bool ok = 0;
    for (int i = 1; i <= ins.m; i++) {
        v.push_back(i); 
    }
    do {
        vector<set<int> > ans;
        ans.resize(ins.n + 1);
        for (int i = 1; i <= ins.n; i++) {
            ans[i].insert(v[i - 1]); 
        }
        allo.pi = ans;
        bool tmpok = verify(ins, allo, setting);
        if(tmpok) {
            ok = 1;
            break;
        } 
    } while (next_permutation(v.begin(), v.end()));

    return ok;
}


/*
setting = "sum", "avg" or "sumavg"
*/

int sz[101];
bool dfs(vector<int> v, int pos, const instance_t &ins, string setting, bool ok, int more) {
    if(more > ins.m - ins.n)
        return false;
    if(ok == 1) {
        return ok;
    }
    if(pos > ins.m) {
        vector<set<int> > ans;
        ans.resize(ins.n + 1);
        for (int i = 1; i <= ins.m; i++) {
            ans[v[i]].insert(i); 
        }
        allocation_t allo(ans, ins.n, ins.m);
        bool tmpok = verify(ins, allo, setting);
        return (ok || tmpok);
    }
    for (int i = 1; i <= ins.n; i++) {
        v[pos] = i;
        int moreplus = 0;
        if(sz[i] >= 1)
            moreplus = 1;
        sz[i]++;
        bool okk = dfs(v, pos + 1, ins, setting, ok, more + moreplus);
        sz[i]--;
        if(okk)
            return okk;
    }
    return ok;
}

bool bruteforce_indivisible(const instance_t& ins, string setting) {
    for (int i = 1; i <= ins.m; i++)
        sz[i] = 0;
    vector<int> v; 
    v.resize(ins.m + 1);
    bool ok = 0;
    bool okk = dfs(v, 1, ins, setting, ok, 0);
    return okk;
}



#endif