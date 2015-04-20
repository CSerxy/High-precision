#ifndef _Calculator_H
#define _Calculator_H

#include<list>
#include<string>
using namespace std;

class Calculator{
	private:
		list<int> a,b,c,ans,remainder;
		list<int>::iterator x,y,z;
		char Operator;
		string Result,Remainder_;
		int sym_a,sym_b,sym_ans;
		void Addition();
		list<int> Subtration(list<int>, list<int>);
		int Pre_Subtration(list<int>, list<int>);
		list<int> Multiplication(list<int>, list<int>);
		list<int> Deal_Division(list<int>,list<int>);
		list<int> Division(list<int>,list<int>);
		list<int> Erase_Zero(list<int>);
		int Compare(list<int>,list<int>);
		list<int> Key();
		int count(list<int>&);
		int Equal_Zero(list<int>);
		list<int> exponent(list<int>);

	public:
		Calculator(int sym_aa, list<int>aa, int sym_bb, list<int>bb, char cc): sym_a(sym_aa), a(aa), sym_b(sym_bb), b(bb), Operator(cc){}
		Calculator(list<int>aa,list<int>bb,list<int>cc): a(aa), b(bb), c(cc){
			ans = Key();
		}
		void Choose();
		string GetResult();
		string GetRemainder();
};

#endif
