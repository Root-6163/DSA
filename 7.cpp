#include<iostream>
using namespace std;

class Tree{
	int a[20][20],l,u,w,i,j,v,e,visited[20];
public:
	void input();
	void display();
	void minimum();
};
void Tree::input(){
	cout<<"Enter The No. Of Branches : ";
	cin>>v;
	for (i=0 ;i<v ;i++){
		visited[i]=0;

		for (j=0 ;j<v ;j++){
			a[i][j]=999;
		}
	}

	cout<<"\n Enter The No. Of Connections : ";
	cin>>e;

	for(i=0 ;i<e ;i++ ){
		cout<<"\n Enter The End Branches Of Connections : "<<endl;
		cin>>l;
		cin>>u;
		cout<<"Enter The Phone Company Charges For This Connection : "<<endl;
		cin>>w;
		a[l-1][u-1] = a[u-1][l-1] = w;
	}
};


void Tree::display(){
	cout<<"\n Adjacent Matrix : ";
	for (i=0 ;i<v ;i++ ){
		for (j=0 ;j<v ;j++ ){
			cout<<a[i][j] <<"   "<<endl;
		}
		cout<<endl;
	}
};

void Tree::minimum(){
	int p=0 , q=0 , total=0 , min;
	visited[0] = 1;
	for(int count=0; count<(v-1) ; count++){
		min = 999;
		for(i=0 ;i<v ;i++){
			if(visited[i]==1){
				for(j=0 ;j<v ;j++){
					if(visited[j]!=1){
						if(min > a[i][j]){
							min = a[i][j];
							p=i;
							q=j;
						}
					}
				}
			}
		}
		visited[p] = 1;
		visited[q] = 1;
		total = total+min;
		cout<<"Minimum Cost Connection is "<<(p+1)<< " -> "<<(q+1)<<" With charge : "<<min<<endl;
	}
	cout<<"The Minimum Total cost of connection of all Branches is : "<<total<<endl;
};

int main(){
	int choice;
	Tree t;
	do{
		cout<<"==========PRIM'S ALGORITHM================="<<endl;
		cout<<"\n1.INPUT\n \n2.DISPLAY\n \n3.MINIMUM\n"<<endl;
		cout<<"Enter your choice :"<<endl;
		cin>>choice;

		switch(choice){
			case 1: cout<<"*******INPUT YOUR VALUES*******"<<endl;  
				t.input();
				break;

			case 2: cout<<"*******DISPLAY THE CONTENTS********"<<endl;
				t.display();
				break;

			case 3: cout<<"*********MINIMUM************"<<endl;
				t.minimum();
				break;
		}
	}
	while(choice!=4);
	return 0;
};

