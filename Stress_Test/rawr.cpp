#include <bits/stdc++.h>
using namespace std; 

vector<int> colorPlanarGraph(int n, int m, vector<int> xi, vector<int> yi, vector<int> u, vector<int> v) {
	vector<vector<int>> adj(n);

	for(int i = 0; i < m; i++){
		u[i]--, v[i]--;
		adj[u[i]].push_back(v[i]);
		adj[v[i]].push_back(u[i]);
	}

	vector<int> color(n, 0);
    vector<bool> vis(n, 0);

    function<void(int)> dfs = [&](int u) -> void {
        if(vis[u]) return;
        vis[u] = 1;

        vector<bool> ok(5, 1);
        for(int &v : adj[u])
            ok[color[v]] = 0;
        
        for(int i = 4; i > 0; i--)
            if(ok[i])
                color[u] = i;

        for(int &v : adj[u]) dfs(v);
    };

    color[0] = 1;
    for(int i = 0; i < n; i++)
        dfs(i);

	return color;
}

int main() {
    auto color = colorPlanarGraph(5, 8, {0, 2, 0, 2, 1}, {0, 0, 2, 2, 1},
    {1, 1, 1, 2, 2, 3, 3, 4}, {2, 3, 5, 4, 5, 4, 5, 5});
    for(int &c : color) cout << c << ' ';
    return 0;
}

// C++ 17
vector<int> colorPlanarGraph(int n, int m, vector<int> xi, vector<int> yi, vector<int> u, vector<int> v) {
	vector<vector<int>> adj(n);
	vector<int> deg(n, 0);

	for(int i = 0; i < m; i++){
		u[i]--, v[i]--;
		adj[u[i]].push_back(v[i]);
		adj[v[i]].push_back(u[i]);
		deg[u[i]]++;
		deg[v[i]]++;
	}

	vector<int> color(n, -1);

	for(int i = 0; i < n; i++){
		if(deg[i] < 4) continue;

		int c = 1;
		set<int> s;
		for(int &j : adj[i]) s.insert(color[j]);

		for(int j = 1; j <= 4; j++){
			if(s.find(j) == s.end()){
				c = j;
				break;
			}
		}

		color[i] = c;
	}

	for(int i = 0; i < n; i++){
		if(color[i] != -1) continue;

		int c = 1;
		set<int> s;
		for(int &j : adj[i]) s.insert(color[j]);

		for(int j = 1; j <= 4; j++){
			if(s.find(j) == s.end()){
				c = j;
				break;
			}
		}

		color[i] = c;
	}

	return color;
}
