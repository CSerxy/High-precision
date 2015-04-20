#include "Calculator.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

void translate(string u,list<int> &test,int &sym);
int main(){
	list<int> a,b;
	int sym_a = 0,sym_b = 0;
	string u;
	char Operator;
	cout<<"Please input the first number: ";
	cin>>u;
	translate(u,a,sym_a);
	cout<<"Please input the operator: ";
	cin>>Operator;
	cout<<"Please input the second number: ";
	cin>>u;
	translate(u,b,sym_b);
	Calculator ans(sym_a,a,sym_b,b,Operator);
	ans.Choose();
	cout<<"The answer is: "<<ans.GetResult()<<endl;
	if (Operator=='/')
		cout<<"The remainder is: "<<ans.GetRemainder()<<endl;
	return 0;
}

void translate(string u,list<int> &test,int &sym){
	int i;
	if (!(u[0]<=57 && u[0]>=48))
		sym = 1;
	else {
		test.push_back(int(u[0])-48);
	}
	for (i=1;i<u.length();i++) {
		test.push_back(int(u[i])-48);
	}
}
