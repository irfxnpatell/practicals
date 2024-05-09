#include <iostream>
using namespace std;
class Node{
public:
	int key;
	string value;
	Node*next;
	Node(){

		this->next=NULL;
	}
};

class Dict{
public:
	Node *hashtable[10];
	Dict(){
		for(int i=0;i<10;i++){
			hashtable[i]=NULL;
		}
	}
	void search(){
		cout<<"Enter the key to search :";
		int Key;
		cin>>Key;
		int index;
		index=Key%10;
		int c=0;
		Node*temp=hashtable[index];

		while(temp!=NULL){
			c++;
			if(temp->key==Key){
				cout<<"Found"<<endl;
				cout<<"Value :"<<temp->value<<endl;
				cout<<"Comparisons :"<<c<<endl;
				break;
			}
			else{
				temp=temp->next;
			}
		}
		if(temp==NULL){
			cout<<"Not Found!!"<<endl;
		}


	}
	void Delete(int key){
		int index=key%10;
		Node*temp=hashtable[index];
		Node*prev=NULL;
		while(temp!=NULL){
			if(temp->key==key && prev==NULL){

				hashtable[index]=temp->next;
				temp->next=NULL;
				delete temp;
				cout<<"Deleted"<<endl;
				break;
			}
			if(temp->key==key && prev!=NULL){
				prev->next=temp->next;
                temp->next=NULL;
				delete temp;
				cout<<"Deleted"<<endl;
				break;
			}
			else{
				prev=temp;
				temp=temp->next;
			}
		}
		if(temp==NULL){
			cout<<"Key Not Found!!"<<endl;
		}
	}
	void insert(){
		cout<<"Enter the number of key value pair to be inserted :";
				int num;
				cin>>num;
				for(int i=0;i<num;i++){
					cout<<"Enter the key:";
					int Key;
					cin>>Key;
					cout<<"Enter Value :";
					string Value;
					cin>>Value;
					int index=Key%10;
					Node *newnode = new Node();
					newnode->key=Key;
					newnode->value=Value;

					if(hashtable[index]==NULL){
						hashtable[index]=newnode;
					}
					else{
						Node *temp=hashtable[index];
						while(temp->next!=NULL){
							temp=temp->next;
						}
						temp->next=newnode;

					}
				}

	}
	void display(){
		cout<<"Index\tKey\tValue"<<endl;
		for(int i=0;i<10;i++){
			Node*temp=hashtable[i];
			cout<<endl;

			while(temp!=NULL){
				cout<<i<<"\t"<<temp->key<<"\t"<<temp->value<<endl;
				temp=temp->next;
			}
		}
	}
};

int main() {

	Dict obj;

	obj.insert();
	obj.display();
	obj.search();
	obj.Delete(1);
	obj.display();
	return 0;
}