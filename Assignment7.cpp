#include<bits/stdc++.h>
using namespace std;

class Graph{

    int** adjMatrix;
    string* cities;
    int nv;

public:

    Graph(){
        adjMatrix = NULL;
        cities = NULL;
        nv = 0;
    }

    Graph(int nv){
        this->nv = nv;
        adjMatrix = new int*[nv];
        cities = new string[nv];

        for(int i=0;i<nv;i++){
            adjMatrix[i] = new int[nv];

            for(int j=0;j<nv;j++){
                adjMatrix[i][j] = 0;
            }
        }
    }

    int getIndex(string city){
        for(int i=0;i<nv;i++){
            if(cities[i] == city){
                return i;
            }
        }
        return -1;
    }

    void addEdge(int s, int d, int w){
        adjMatrix[s][d] = w;
        adjMatrix[d][s] = w;
    }

    void create(){
        for(int i=0;i<nv;i++){
            cout<<"Enter cities at["<<i<<"] : ";
            cin>>cities[i];
        }
        string des;
        int weight;

        for(int i=0;i<nv;i++){
            for(int j=0;j<nv-1;j++){
                cout<<"Add city connected to "<<cities[i]<<": ";
                cin>>des;
                cout<<"Add cost for connection: ";
                cin>>weight;
                int srcID = getIndex(cities[i]);
                int destID = getIndex(des);

                if(srcID == -1 || destID == -1){
                    break;
                }

                addEdge(srcID, destID, weight);
            }
        }
    }

    void display(){
        for(int i=0;i<nv;i++){
            cout<<cities[i]<<" -> ";
            for(int j=0;j<nv;j++){
                cout<<"("<<cities[j]<<","<<adjMatrix[i][j]<<") ";
            }
            cout<<endl;
        }
    }

    int minKey(int key[], bool mst[]){
        int minIdx;
        int minVal = INT_MAX;
        for(int i=0;i<nv;i++){
            if(mst[i] == false && key[i] < minVal){
                minVal = key[i];
                minIdx = i;
            }
        }
        return minIdx;
    }

    void primsAlgo(){
        int key[nv];
        bool mst[nv];
        int parent[nv];

        for(int i=0;i<nv;i++){
            mst[i] = false;
            key[i] = INT_MAX;
        }

        key[0] = 0;
        parent[0] = -1;

        for(int i=0;i<nv-1;i++){
            int u = minKey(key, mst);

            mst[u] = true;
            for(int j=0;j<nv;j++){
                if(adjMatrix[u][j] && mst[j] == false && adjMatrix[u][j] < key[j]){
                    key[j] = adjMatrix[u][j];
                    parent[j] = u;
                }
            }
        }

        printMST(parent);

    }

    void printMST(int parent[]){
        int minCost = 0;
        for(int i=1;i<nv;i++){
            minCost += adjMatrix[i][parent[i]];
        }
        cout<<"Minimum cost of cabel: "<<minCost<<endl;
    }
};

int main(){

    int nv;
    cout<<"Enter no of cities: ";
    cin>>nv;

    Graph* g = new Graph(nv);
    g->create();
    g->display(); 
    g->primsAlgo();
    
    return 0;
}