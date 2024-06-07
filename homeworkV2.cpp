#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// تم اخذ السودو كود لخوارزمية غابو من محاضرة الدكتور رائد و قمنا بكتابته على شكل كود في هذه اللغة
// NOTICE : new state is 0 , active state is 1 , and finally finished state is 2
const int MAXN = 100005;
vector<int> adj[MAXN];
int state[MAXN];
int dfsNum[MAXN];
int dfsCounter = 1;
stack<int> Ostack, Rstack;
int comp[MAXN];
vector<int> adj1[MAXN];
vector<int> adj2[MAXN];
int visited1[MAXN];
int visited2[MAXN];
int CycleNum;
int parent[MAXN];
int matrixback[1000][1000];
int matrixtree[1000][1000];

//  بمعنى علاقة ينتمي التابع التالي
//subTeamOne Gabow code by (Rayan,Nadra,Enas,Sara,Riham)
bool IsBelong(stack<int> s, int target) {
    stack<int> temp = s;
    while (!temp.empty()) {
        if (temp.top() == target) {
            return true;
        }
        temp.pop();
    }
    return false;
}

void dfs(int v) {
    if (state[v] == 1) {
        return;
    }

    state[v] = 1;
    dfsNum[v] = dfsCounter++;
    Ostack.push(v);
    Rstack.push(v);

    for (int w : adj[v]) {
        if (state[w] == 0) {
            dfs(w);
        } else {
            if (!Rstack.empty() && IsBelong(Rstack, w)) {
                while (dfsNum[w] < dfsNum[Rstack.top()]) {
                    Rstack.pop();
                }
            }
        }
    }

    state[v] = 2;

    if (v == Rstack.top()) {
        Rstack.pop();
        int w;
        do {
            w = Ostack.top();
            Ostack.pop();
            comp[w] = v;
        } while (w != v);
    }
}
//jens Schmdit algorithm code by Khaled
//for making matrix and dfs by Majd
 void dfs1(int k) {
        visited2[k] = true;

        for(int i = 0; i < adj1[k].size(); i++) {
            int v = adj1[k][i];
            if (!visited1[v]) {
                parent[v] = k;
                //cout << k << " -> " << v << " is a tree edge\n";
                matrixtree[k][v]=1;
                adj2[k].push_back(v);
                dfs1(v);
            } else if (parent[k] != v && (matrixback[k][v]==0 && matrixback[v][k]==0) ) {
                //cout << k << " -> " << v << " is a back edge\n";
                 CycleNum++;
                  adj2[k].push_back(v);
                matrixback[k][v]=1;
            }
        }
    }
 bool IsBelongChain(int k) {
     if(!visited2[k]){
        visited2[k] = true;
        for(int i = 0; i < adj2[k].size(); i++) {
            int v = adj2[k][i];
            if (!visited2[v]) {
                IsBelongChain(v);
        }
    }
     }
     else{
        if(k!=0){
            return false;
        }
     }
     return true;
 }
int main() {
    int n, m;//the two variabel by ahmad
    cin >> n >> m;//the two variabel by qusai
// subTeamTwo yosef && khalil for inputing graph
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }

for (int i = 0; i < n; i++) {
comp[i]=-1;
dfsNum[i]=-1;
    }

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            dfs(i);
        }
    }

    /*
    cout << "Strongly connected components:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " belongs to component " << comp[i] << endl;
    }
*/

//هذا التعديل المنطقي لايجاد هل هو متصل بقوة عن طريق اختبار ان كان كل البيان مكون واحد
bool first=1;
for (int i = 0; i < n; i++) {
        if(comp[i]!=comp[0]) {
            first=0;
        break;
}
    }
if(first==1){

        for (int i = 0; i < n; i++) {
        if (visited1[i] == 0) {
            dfs1(i);
        }
    }
     for (int i = 0; i < n; i++) {
        IsBelongChain(i);
        if( IsBelongChain(i)){

        }
        else if(CycleNum>1){

        }
        else{
            cout<<"strongly biconnected graph"<<endl;
        }
    }


}
    return 0;
}
