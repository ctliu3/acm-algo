// Dijkstra optimized by heap
// Complexity is O(NlogN)
int dijkstra(int s, int t, int n, vector<pair<int, int> > e[]) { // e: <v, w> 
	priority_queue<pair<int, int> > q; // <dis, v> 
	vector<int> dis(n, -1);

	q.push(make_pair(0, s));
	while (!q.empty()) {
		pair<int, int> top = q.top();
		q.pop();
		if (top.second == t) {
			return -top.first;
		}
		dis[top.second] = -top.first; // * 
		for (vector<pair<int, int> >::const_iterator cit = e[top.second].begin(); 
				cit != e[top.second].end(); ++cit) {
			if (dis[cit->first] == -1) {
				q.push(make_pair(top.first - cit->second, cit->first));
			}
		}
	}
}
