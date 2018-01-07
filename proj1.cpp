#include <iostream>
#include <queue>
#include <vector>
#include <cstdio> /* printf e scanf */

using namespace std;

class Node{
	private:
		int value;
		Node* next;
	public:
		Node(int v, Node* n): value(v), next(n){ }
		int getValue() const{ return value; }
		Node* getNext() const{ return next; }
		~Node(){ delete next; }
};

class Graph{
	private:
		int nVertices;
		vector<int> distances;
		vector<Node*> adjacencyList;

		int getMaxErdosNumber() const{
			int max=0;
			for (int i = 0; i < nVertices; i++){
			  if(distances[i] > max)
				  max = distances[i];
			}
			return max;
		}
		
	public:
		Graph(int Vertices): nVertices(Vertices), distances(Vertices), adjacencyList(Vertices){ }
		
		int getVertices() const{ return nVertices; }
		vector<Node*> getAdjacencyList() const{ return adjacencyList; }
		vector<int> getDistances() const{ return distances; }
		
		void insertEdge(int v, int w){
			adjacencyList[v-1] = new Node(w, adjacencyList[v-1]);
			adjacencyList[w-1] = new Node(v, adjacencyList[w-1]);
		}
		
		void BreadthFirstSearch(int s){
			int w,v;
			queue<int> Q;
			Node* aux;
			Q.push(s);
			distances[s-1] = 0;
			while(!Q.empty()){
				v = Q.front();
				Q.pop();
				aux = adjacencyList[v-1];
				while(aux){ /* Vamos iterar a lista de adjacências do vértice v */
					w = aux->getValue();
					if(!distances[w-1] && w != s){ /* Os tempos de descoberta servem como flag. Sendo s o vértice por onde começamos, sabemos que já foi visitado */
						distances[w-1] = distances[v-1] + 1;
						Q.push(w);
					}
					aux = aux->getNext();
				}
			}
		}
		
		void displayQuantities(){
			int M = getMaxErdosNumber();
			vector<int> quantities(M);
			printf("%d\n", M);
			for(int i = 0; i < nVertices; i++){
				if(distances[i] != 0) /* Para não aceder ao indice -1 */
					quantities[distances[i]-1] ++ ; 
			}
			for(int i = 0; i < M; i++)
				printf("%d\n", quantities[i]);
		}
}; 

int main(){
	int N,C,Erdos,u,v;
	scanf("%d %d", &N, &C);
	scanf("%d", &Erdos);
	Graph* G = new Graph(N);
	for(int i = 0; i<C; i++){
		scanf("%d %d", &u, &v);
		G->insertEdge(u,v);
	}
	G->BreadthFirstSearch(Erdos);
	G->displayQuantities();
	delete G;
	return 0;
}
