#include<bits/stdc++.h>
using namespace std;

class Node{

    int dest;
    Node* next;

public:
    Node(){
        dest = 0;
        next = NULL;
    }
    Node(int dest){
        this->dest = dest;
        this->next  = NULL;
    }
    friend class Graph;
};

class Graph{

    string* places;
    Node** adjList;
    int nv;

public:
    Graph(){
        places = NULL;
        adjList = NULL;
        nv = 0;
    }
    Graph(int n){
        nv = n;
        adjList = new Node *[nv];

        for(int i=0;i<nv;i++){
            adjList[i] = nullptr;
        }

        places = new string[nv];
    }

    int getIndex(string place){
        for(int i=0;i<nv;i++){
            if(places[i] == place){
                return i;
            }
        }
        return -1;
    }

    void addEdge(int s, int d){
        Node* new_node = new Node(d);
        new_node->next = adjList[s];
        adjList[s] = new_node;
    }

    void createGraph(){
        for(int i=0;i<nv;i++){
            cout<<"Enter place at index["<<i<<"]: ";
            cin>>places[i];
        }
        string des;
        for(int i=0;i<nv;i++){
            for(int j=0;j<nv-1;j++){
                cout<<"Add places connected to "<<places[i]<<": ";
                cin>>des;
                int srcID = getIndex(places[i]);
                int desID = getIndex(des);

                if(srcID == -1 || desID == -1){
                    break;
                }

                addEdge(srcID, desID);
            }
        }
    }

    void display(){
        for(int i=0;i<nv;i++){
            Node* temp = adjList[i];
            cout<<places[i]<<" -> ";
            while(temp){
                cout<<places[temp->dest]<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }
    }

    void bfs(int src){
        bool visited[nv];
        for(int i=0;i<nv;i++){
            visited[i] = false;
        }
        queue<int> q;
        q.push(src);
        visited[src] = true;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            cout<<places[curr]<<" ";

            Node* temp = adjList[curr];

            while(temp){
                int neighbour = temp->dest;
                if(!visited[neighbour]){
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
                temp = temp->next;
            }
        }
        cout<<endl;
    }

    void dfs(int src){
        bool visited[nv];
        for(int i=0;i<nv;i++){
            visited[i] = false;
        } 

        stack<int> st;
        st.push(src);
        visited[src] = true;

        while(!st.empty()){
            int curr = st.top();
            st.pop();
            cout<<places[curr]<<" ";

            Node* temp = adjList[curr];
            while(temp){
                int neighbour = temp->dest;
                if(!visited[neighbour]){
                    visited[neighbour] = true;
                    st.push(neighbour);
                }
                temp = temp->next;
            }
        }
        cout<<endl;
    }

};

int main(){

    int nv;
    cout<<"Enter number of places: ";
    cin>>nv;

    Graph* g = new Graph(nv);
    g->createGraph();
    g->display();
    int srcID = g->getIndex("a");
    g->bfs(srcID);
    g->dfs(srcID);
    
    return 0;

}