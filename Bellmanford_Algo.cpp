#include<iostream>
using namespace std;

struct Node{
    int vertex;
    int weight;
    Node *next;
};

class List{
    public:
        Node* head;
    public:
        List(){
            head=NULL;
        }
        void insert(int v, int w);
};

void List::insert(int v, int w){
    if(head==NULL){
        head = new Node;
        head->vertex = v;
        head->weight = w;
        head->next = NULL;
    }
    else{
        Node* temp = new Node;
        temp->next = head;
        temp->vertex = v;
        temp->weight = w;
        head = temp;
    }
}

struct Table{
    int dist;
    int par;
};

void BellFordAlgo(List graph[],Table t[], int v, int e){
    bool flag=true;
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            Node* temp = graph[j].head;
            while(temp!=NULL){
                if(t[temp->vertex].dist>(t[j].dist+temp->weight)){

                    if(i==(v-1)){
						cout<<"Cant find shortest distance due to negative weighted cycle"<<endl;
						flag=false;
						break;
					}

                    t[temp->vertex].dist=(t[j].dist+temp->weight);
                    t[temp->vertex].par = j;
                }
                temp = temp->next;
            }
            if(flag==false){
                break;
            }
        }
    }
    if(flag==true){
        cout<<"\nVertex  Distance(V)  Parent(V)"<<endl;
		for(int i=0;i<v;i++){
			cout<<"  "<<i<<"         "<<t[i].dist<<"           "<<t[i].par<<endl;
		}
    }
}

int main()
{
    List graph[50];
    Table t[50];
    int v,e,source;
    
    cout<<"\n\n \t\t ***** Bellmangord Algorithm ***** \n\n\n";
    
    cout<<" >> Enter number of vertices = ";
	cin>>v;
    cout<<" >> Enter the number of edges = ";
	cin>>e;
    for(int i=0;i<e;i++){
		int s,d,w; 
        cout<<"\n >>> Enter details of Edge "<<i+1<<":- \n"<<endl;
		cout<<" >> Source =  ";
		cin>>s;
        cout<<" >> Destination =  ";
		cin>>d;
        cout<<" >> Weight = ";
		cin>>w;
        graph[s].insert(d,w);
	}
    cout<<"\n >> Enter the source of Graph = ";
    cin>>source;
    for(int i=0;i<v;i++){
        t[i].par=-1;
        t[i].dist=99999;
    }
    t[source].dist=0;

    BellFordAlgo(graph,t,v,e);

	cout<<endl<<endl;

    return 0;
}
