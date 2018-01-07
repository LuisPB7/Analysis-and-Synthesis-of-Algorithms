#include <iostream>
#include <queue>
#include <vector>
#include <cstdio> /* printf e scanf */

#define INFINITY  2147483647 /* Máximo para um inteiro de 32 bits, boa aproximação ao infinito */

using namespace std;

class Node{
	private:
		int value;
		Node* next;
		int weight;
	public:
		Node(int v, Node* n, int w): value(v), next(n), weight(w){ }
		int getValue() const{ return value; }
		Node* getNext() const{ return next; }
		int getWeight() const { return weight; }
		~Node(){ delete next; }
};

class Graph{
	private:
		int nVertices;
		vector<int> distances;
		vector<Node*> adjacencyList;
		vector<int> I;
		vector<int> U;
		
	public:
		Graph(int Vertices): nVertices(Vertices), distances(Vertices), adjacencyList(Vertices), I(Vertices){ }
		
		int getVertices() const{ return nVertices; }
		vector<Node*> getAdjacencyList() const{ return adjacencyList; }
		vector<int> getDistances() const{ return distances; }
		
		void insertEdge(int v, int w, int wei){
			adjacencyList[v-1] = new Node(w, adjacencyList[v-1], wei);
		}
		
		void BellmanFord(int s){
			int i,j, value, weight, value2;
			for(i = 0; i < nVertices; i++){
				distances[i] = INFINITY;
			}
			distances[s-1] = 0;
			for(i = 0; i < nVertices; i++){
				for(j = 0; j < nVertices; j++){
					Node* aux = adjacencyList[j];
					while(aux){
						value = aux->getValue();
						weight = aux->getWeight();
						if(distances[j] + weight < distances[value-1]){
							if(i == nVertices-1){
								I[value-1] = 1;
								Node* aux2 = adjacencyList[value-1];
								while(aux2){
									value2 = aux2->getValue();
									I[value2-1] = 1;
									aux2 = aux2->getNext();
								}
							}
							distances[value-1] = distances[j] + weight;
						}
						aux = aux->getNext();
					}
				}
			}
		}
		
		void displayDistances(){
			for(int i = 0; i<nVertices; i++){
				if(distances[i] == INFINITY){
				   printf("U\n");
				}
				else if(I[i] == 1){
					printf("I\n");
				}
				else{
				  printf("%d\n", distances[i]);
				}
			}
		}
}; 

int main(){
	int N,C,Empresa,u,v,w;
	scanf("%d %d", &N, &C);
	scanf("%d", &Empresa);
	Graph* G = new Graph(N);
	for(int i = 0; i<C; i++){
		scanf("%d %d %d", &u, &v, &w);
		G->insertEdge(u,v,w);
	}
	G->BellmanFord(Empresa);
	G->displayDistances();
	delete G;
	return 0;
}
