#include <iostream>
using namespace std;
class Hashing{
public:
	string name;
	long num;
	Hashing(){
		this->name="--";
		this->num=0;
	}
};
void Display(Hashing ht1[]){
	cout<<"Client Name\t" << "Phone number "<<endl;
	for(int i=0;i<10;i++){
		cout<<ht1[i].name<<"\t\t"<<ht1[i].num<<endl;
	}
}
void search(Hashing ht1[]){
	string Name;
	int key;
	cout<<"Enter the number of clients to search :";
	cin>>key;
	for(int i=0;i<key;i++){
		cout<<"Enter client name :";
		cin>>Name;
		int asci=0;
		for(int j=0;Name[j]!='\0';j++){
			asci=asci+Name[j];
		}
		int index=asci%10;
		int comp=1;
		while(ht1[index].name!=Name){
			comp++;
			index=(index+1)%10;
		}
		cout<<"Client Name :"<<ht1[index].name<<endl;
		cout<<"Phone Number :"<<ht1[index].num<<endl;
		cout<<"Comparisons :"<<comp<<endl;
	}
}
void Create(Hashing ht2[]){
	int num;
	cout<<"Enter the number of clients :";
	cin>>num;
	for(int i=0;i<num;i++){
		int asci=0;
		int sum=0;
		cout<<"Enter name :";
		string Name;
		cin>>Name;


		cout<<"Enter Phone number :";
		long Num;
		cin>>Num;
		for(int i=0;Name[i]!='\0';i++){
			sum=sum+Name[i];
		}
		asci=sum%10;
		if(ht2[asci].num==0){
			ht2[asci].name=Name;
			ht2[asci].num=Num;
		}
		else{
			string stored=ht2[asci].name;
			int old_asci=0;
			int old_sum=0;
			for(int x=0;stored[x]!='\0';x++){
				old_sum=old_sum+stored[x];
			}
			old_asci=old_sum%10;
			if(old_asci!=asci){
				int  new_asci=asci;


				while(ht2[new_asci].num!=0){
					new_asci=(new_asci+1)%10;
				}
				ht2[new_asci].name=ht2[asci].name;
				ht2[new_asci].num=ht2[asci].num;
				ht2[asci].name=Name;
				ht2[asci].num=Num;
			}
			else{
				int new_asci=0;
				while(ht2[new_asci].num!=0){
					new_asci=(new_asci+1)%10;
				}
				ht2[new_asci].name=Name;
				ht2[new_asci].num=Num;
			}
		}
	}
}
void create(Hashing ht1[]){
	int num;
	cout<<"Enter number of clients :";
	cin>>num;
	for(int i=0;i<num;i++){
	int hashkey;
	int sum=0;
	cout<<"Enter Name:";
	string Name;
	cin>>Name;
	cout<<"Enter Phone Number :";
	long Num;
	cin>>Num;
	for(int i=0;Name[i]!='\0';i++){
		sum=sum+Name[i];
	}
	hashkey=sum%10;
	if(ht1[hashkey].num==0){
		ht1[hashkey].name=Name;
		ht1[hashkey].num=Num;
	}
	else{
	while(ht1[hashkey].num!=0){
		hashkey=(hashkey+1)%10;
	}
	ht1[hashkey].name=Name;
	ht1[hashkey].num=Num;
	}

	}
}
int main() {
	Hashing ht1[10];
	create(ht1);
	Display(ht1);
	search(ht1);
	Hashing ht2[10];
	Create(ht2);
	Display(ht2);
	search(ht2);

	return 0;
}