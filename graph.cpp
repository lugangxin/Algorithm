#include<iostream>
using namespace std;
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
#include<stack>
struct Edge;
struct Node {
	int value;
	int in;//入度
	int out;
	vector<Node*> nexts;
	vector<Edge*> edges;//相当于出去的边
	Node(int value) :value(value),in(0),out(0),nexts(){}
};
struct Edge {
	int weight;
	Node* from;
	Node* to;
	Edge(int weight,Node* from,Node* to):weight(weight),from(from),to(to) {}
};
struct Graph {
	unordered_map<int, Node*> nodes;
	unordered_set<Edge*> edges;
	Graph() :nodes(),edges(){}
};
//转化矩阵    [边的权重   从哪个节点    指向哪个节点]
Graph* createGraph(vector<vector<int>> matrix) {
	Graph* graph = new Graph();
	for (int i = 0; i < matrix.size();i++) {
		int weight = matrix[i][0];
		int from = matrix[i][1];
		int to = matrix[i][2];
		if (!graph->nodes.count(from)) {
			graph->nodes[from]=new Node(from);
		}
		if (!graph->nodes.count(to)) {
			graph->nodes[to] = new Node(to);
		}
		Node* fromNode = graph->nodes[from];
		Node* toNode = graph->nodes[to];
		Edge* newEdge = new Edge(weight,fromNode,toNode);
		fromNode->nexts.push_back(toNode);
		fromNode->out++;
		toNode->in++;
		fromNode->edges.push_back(newEdge);
		graph->edges.insert(newEdge);
	}
	return graph;

}
//宽度优先遍历
void bfs(Node* node) {
	if (node == NULL) return;
	queue<Node*> que;
	unordered_set<Node*> set;
	que.push(node);
	set.insert(node);//防止重复   无向图跑不完    有向图有环的话也跑不完
	while (!que.empty()) {
		Node* cur = que.front();
		que.pop();
		cout << cur->value;
		for (Node* next:cur->nexts) {
			if (!set.count(next)) {
				set.insert(next);
				que.push(next);
			}
		}
	}
}
//深度优先遍历  栈
void dfs(Node* node) {
	if (node == NULL) return;
	stack<Node*> st;
	unordered_set<Node*> set;
	st.push(node);
	set.insert(node);
	cout << node->value;
	while (!st.empty()) {
		Node* cur = st.top();
		st.pop();
		for (Node* next:cur->nexts) {
			if (!set.count(next)) {
				st.push(cur);//可以理解为回溯
				st.push(next);
				set.insert(next);
				cout << next->value;
				break;//找到一个邻居就不看其他邻居
			}
		}
	}
}
//拓扑排序
vector<Node*> topology_sort(Graph* graph) {
	unordered_map<Node*, int> inMap;
	queue<Node*> zeroInQueue;
	for (auto it = graph->nodes.begin(); it != graph->nodes.end();it++) {
		inMap[it->second] = it->second->in;
		if (it->second->in == 0) zeroInQueue.push(it->second);
	}
	vector<Node*> result;
	while (!zeroInQueue.empty()) {
		Node* cur = zeroInQueue.front();
		zeroInQueue.pop();
		result.push_back(cur);
		for (Node* next:cur->nexts) {
			inMap[next] = inMap[next] - 1;
			if (inMap[next] == 0) zeroInQueue.push(next);
		}

	}
	return result;
}
//最小生成树     无向图
struct MySets {
	unordered_map<Node*, vector<Node*>> setMap;
	MySets() :setMap(unordered_map<Node*, vector<Node*>>{}) {}
	void insertSet(Node* node) {
		vector<Node*> set;
		set.push_back(node);
		setMap[node] = set;
	}
	//判断是否有环
	bool isSameSet(Node* from,Node* to) {
		vector<Node*> fromSet = setMap[from];
		vector<Node*> toSet = setMap[to];
		return fromSet == toSet;
	}
	void unionNode(Node* from,Node* to) {
		vector<Node*> fromSet = setMap[from];
		vector<Node*> toSet = setMap[to];
		for (Node* toNode:toSet) {
			fromSet.push_back(toNode);
			setMap[toNode] = fromSet;
		}
	}
};
struct cmp
{
	bool operator()(Edge* e1, Edge* e2) {
		return e1->weight > e2->weight;
	}
};
vector<Edge*> kruskalMST(Graph* graph) {
	MySets* set=new MySets();
	for (unordered_map<int, Node*>::iterator it = graph->nodes.begin(); it != graph->nodes.end();it++) {
		set->insertSet(it->second);
	}
	priority_queue<Edge*, vector<Edge*>, cmp> que;
	for (Edge* edge:graph->edges) {
		que.push(edge);
	}
	vector<Edge*> result;
	while (!que.empty()) {
		Edge* edge = que.top();
		que.pop();
		if (!set->isSameSet(edge->from,edge->to)) {
			result.push_back(edge);
			set->unionNode(edge->from,edge->to);
		}
	}
	return result;

}
vector<Edge*> primMST(Graph* graph) {
	//解锁的边进入小根堆
	priority_queue<Edge*, vector<Edge*>, cmp> que;
	//看这条边的to点是否在集合内
	unordered_set<Node*> set;
	vector<Edge*> result;
	//for循环是为了防止随机森林   如果一棵树本来就是连通的可以不要
	for (unordered_map<int, Node*>::iterator it = graph->nodes.begin(); it != graph->nodes.end();it++) {
		if (!set.count(it->second)) {
			set.insert(it->second);
			for (Edge* edge:it->second->edges) {//由一个点解锁相连的边
				que.push(edge);
			}
			while (!que.empty()) {
				Edge* edge = que.top();
				que.pop();
				Node* toNode = edge->to;
				if (!set.count(toNode)) {
					set.insert(toNode);
					result.push_back(edge);
					for (Edge* nextEdge:toNode->edges) {
						que.push(nextEdge);//边可能会重复放，但是点不会
					}
				}
			}
		}
	}
	return result;
}
//Dijkstra   要求没有权值为负的边   不能有累加和为负数的环
//找最小的记录，并且不能是已经被选过的
//可以自己实现小根堆优化
Node* getMinDistanceAndUnselectedNode(unordered_map<Node*,int> distanceMap,unordered_set<Node*> selectedNodes) {
	int min=INT_MAX;
	Node* node=new Node(0);
	for (unordered_map<Node*, int>::iterator it = distanceMap.begin(); it != distanceMap.end();it++) {
		if (it->second<min&&!selectedNodes.count(it->first)) {
			min = it->second;
			node = it->first;
		}
	}
	return node;
}
unordered_map<Node*, int> dijkstra(Node* head) {
	unordered_map<Node*, int> distanceMap;
	distanceMap[head] = 0;
	//记录以求出距离的点
	unordered_set<Node*> selectedNodes;
	Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
	while (minNode!=NULL) {
		int distance = distanceMap[minNode];
		for (Edge* edge:minNode->edges) {
			Node* toNode = edge->to;
			if (!distanceMap.count(toNode)) {
				distanceMap[toNode] = distance + edge->weight;
			}
			distanceMap[toNode] = min(distanceMap[toNode],distance+edge->weight);
		}
		selectedNodes.insert(minNode);
		minNode = getMinDistanceAndUnselectedNode(distanceMap,selectedNodes);
	}
	return distanceMap;
}
class NodeRecord {
public:
	Node* node;
	int distance;
	NodeRecord(Node* node, int distance) :node(NULL), distance(0) {}

};
class NodeHeap {
private:
	vector<Node*> nodes;
	unordered_map<Node*, int> heapIndexMap;//node在堆的位置    方便查节点在不在堆上，或者改记录
	unordered_map<Node*, int> distanceMap;//node到head的距离
	int size;
	//node有没有进过堆
	bool isEntered(Node* node) {
		return heapIndexMap.count(node);
	}
	//节点位置进去又出去后记为-1
	bool inHeap(Node* node) {
		return isEntered(node) && heapIndexMap[node] != -1;
	}
	//两个节点换位置  数组和heapIndexMap中的位置都要调
	void swap(int index1,int index2) {
		heapIndexMap[nodes[index1]] = index2;
		heapIndexMap[nodes[index2]] = index1;
		Node* temp = nodes[index1];
		nodes[index1] = nodes[index2];
		nodes[index2] = temp;
	}
	void insertHeapify(Node* node,int index) {
		while (distanceMap[nodes[index]]<distanceMap[nodes[(index-1)/2]])
		{
			swap(index,(index-1)/2);
			index = (index - 1) / 2;
		}
	}
	void heapify(int index,int size) {
		int left = index * 2 + 1;
		while (left<size) {
			int smallest = left + 1 < size && distanceMap[nodes[left + 1]] < distanceMap[nodes[left]] ? left + 1 : left;
			smallest = distanceMap[nodes[smallest]] < distanceMap[nodes[index]] ? smallest : index;
			if (smallest == index) break;
			swap(smallest,index);
			index = smallest;
			left = index * 2 + 1;
		}
	}
public:
	NodeHeap(int size) :nodes(size), heapIndexMap({}), distanceMap({}) ,size(0){}
	bool isEmpty() { return size == 0; }
	void addOrUpdateOrIgnore(Node* node, int distance) {
		if (inHeap(node)) {
			distanceMap[node] = min(distanceMap[node],distance);
			insertHeapify(node,heapIndexMap[node]);
		}
		if (!isEntered(node)) {
			nodes[size] = node;
			heapIndexMap[node] = size;
			distanceMap[node] = distance;
			insertHeapify(node, size++);
		}
	}

	NodeRecord* pop() {
		NodeRecord* nodeRecord = new NodeRecord(nodes[0],distanceMap[nodes[0]]);
		swap(0,size-1);
		heapIndexMap[nodes[size - 1]] = -1;
		distanceMap.erase(nodes[size-1]);
		nodes[size - 1] = NULL;
		heapify(0,--size);
		return nodeRecord;
	}
};
unordered_map<Node*, int> dijkstra2(Node* head,int size) {
	NodeHeap* nodeHeap = new NodeHeap(size);
	nodeHeap->addOrUpdateOrIgnore(head,0);
	unordered_map<Node*, int> result;
	while (!nodeHeap->isEmpty())
	{
		NodeRecord* record = nodeHeap->pop();
		Node* cur = record->node;
		int distance = record->distance;
		for (Edge* edge:cur->edges) {
			nodeHeap->addOrUpdateOrIgnore(edge->to,edge->weight+distance);
		}
		result[cur] = distance;
	}
	return result;
}
int main5() {
	return 0;
}