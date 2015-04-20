#include "Calculator.h"
#include<string>
#include<list>
#include<iostream>
using namespace std;

void Calculator::Addition(){
	int s = 0;
	x = a.end();
	x--;
	y = b.end();
	y--;
	while (1){
		ans.push_front(*x+*y+s);
		if (ans.front()>9){
			ans.front() -= 10;
			s = 1;
		} else 
			s = 0;
		if (x != a.begin() && y != b.begin()){
			x--;
			y--;
		} else {
			if (x != a.begin()){
				while (x != a.begin()){
					x--;
					ans.push_front(*x+s);
					if (ans.front()>9){
						ans.front() -= 10;
						s = 1;
					} else
						s = 0;
				}
			} else 
			if (y != b.begin()){
				while (y != b.begin()){
					y--;
					ans.push_front(*y+s);
					if (ans.front()>9){
						ans.front() -= 10;
						s = 1;
					} else
						s = 0;
				}
			}
			if (s)
				ans.push_front(s);
			break;
		}
	}
}

int Calculator::Pre_Subtration(list<int> a, list<int> b){
	if (a.size()>b.size()){
		ans = Subtration(a,b);
		return 0;
	} else if (a.size()<b.size()){
		ans = Subtration(b,a);
		return 1;
	} else {
		list<int>::iterator x,y;
		x = a.begin();
		y = b.begin();
		while (x != a.end()){
			if (*x>*y){
				ans = Subtration(a,b);
				return 0;
			} else if (*x<*y){
				ans = Subtration(b,a);
				return 1;
			} else {
				x++;
				y++;
			}
		}
		ans.push_front(0);
		return 0;
	}
}

list<int> Calculator::Subtration(list<int> a, list<int> b){
	int rent = 0;
	list<int> ans;
	list<int>::iterator x,y;
	x = a.end();
	x--;
	y = b.end();
	y--;
	while (1){
		if (*x >= *y+rent){
			ans.push_front(*x-*y-rent);
			rent = 0;
		} else {
			ans.push_front(*x+10-*y-rent);
			rent = 1;
		}

		if (y!=b.begin()){
			x--;
			y--;
		} else {
			if (x!=a.begin()){
				x--;
				while (x!=a.begin()) {
					if (*x >= rent){
						ans.push_front(*x-rent);
						rent = 0;
					} else {
						ans.push_front(*x+10-rent);
						rent = 1;
					}
					x--;
				}
				ans.push_front(*x-rent);
			}
			break;
		}
	}
	return ans;
} 

list<int> Calculator::Multiplication(list<int> a, list<int> b){
	list<int> ans;
	int count = 0;
	a.push_front(0);
	b.push_front(0);
	x = a.end();
	x--;
	for (;x != a.begin();x--){
		count++;
		z = ans.end();

		int u = count,carry = 0;
		while (u){
			u--;
			if (z == ans.begin())
				ans.push_front(0);
			z--;
		}

		y = b.end();
		y--;
		for (;y != b.begin();y--){
			*z = *z+(*x)*(*y)+carry;
			carry = int(*z/10);
			*z = *z%10;
			if (z == ans.begin())
				ans.push_front(0);
			z--;
		}
		while (carry){
			*z = *z+carry;
			carry = int(*z/10);
			*z = *z%10;
			if (z == ans.begin())
				ans.push_front(0);
			z--;
		}
	}
	return Erase_Zero(ans);
}

list<int> Calculator::Erase_Zero(list<int> u){
	list<int>::iterator uu;
	for (uu=u.begin();uu!=u.end();uu++){
		if (*uu==0){
			u.pop_front();
			continue;
		}
		else
			break;
	}
	return u;
}

int Calculator::Compare(list<int> a,list<int> b){
	if (a.size() < b.size())
		return 0;
	else if (a.size() > b.size())
		return 1;	
	list<int>::iterator aa,bb;
	for (aa = a.begin(),bb = b.begin();aa != a.end();aa++,bb++){
		if (*aa > *bb)
			return 1;
		else if (*aa < *bb)
			return 0;
	}
	return 1;
}

list<int> Calculator::Deal_Division(list<int> a, list<int> b){
	list<int> rem;
	list<int> test;
	list<int> deal;
	if (a.size()<b.size()){
		ans.push_back(0);
		return a;
	}
	int i;
	for (i = 0;i<10;i++){
		deal.push_front(i);
		test = Multiplication(deal,b);
		if (Compare(a,test)==0){
			ans.push_back(i-1);
			deal.pop_front();deal.push_front(i-1);
			rem = Subtration(a,Multiplication(deal,b));
			return Erase_Zero(rem);
		}
		deal.pop_front();
	}
	ans.push_back(9);
	deal.push_front(9);
	rem = Subtration(a,Multiplication(deal,b));
	return Erase_Zero(rem);
}

list<int> Calculator::Division(list<int> a,list<int> b){
	ans.clear();
	list<int> rem;
	list<int>::iterator x;
	x = a.begin();
	while (x!=a.end()){
		rem.push_back(*x);
		rem = Deal_Division(rem,b);
		x++;
	}
	return rem;
}

void Calculator::Choose(){
	switch (Operator){
		case '+':{ 
			if ((sym_a+sym_b)%2 == 0){
				Addition();
				sym_ans = (sym_a+sym_b == 2)?1:0;
			} else {
				if (sym_b)
					sym_ans = Pre_Subtration(a,b);
				else
					sym_ans = (Pre_Subtration(b,a)+1)%2;
			}
			break;
		}
		case '-':{
			if ((sym_a+sym_b)%2 == 0){
				if (sym_a+sym_b == 0){
					sym_ans = Pre_Subtration(a,b);
				} else {
					sym_ans = Pre_Subtration(b,a);
				}
			} else {
				if (sym_a == 1){
					Addition();
					sym_ans = 1;
				} else {
					Addition();
					sym_ans = 0;
				}
			}
			break;
		}
		case '*':{
			ans = Multiplication(a,b);
			sym_ans = (sym_a+sym_b)%2;
			break;
		}
		case '/':{
			remainder = Division(a,b);
			sym_ans = (sym_a+sym_b)%2;
			break;
		}
	}
}

string Calculator::GetResult(){
	Result = "";
	int test = 0;
	if (sym_ans==1)
		Result += "-";
	for (z=ans.begin();z!=ans.end() && *z==0;z++);
	if (z==ans.end()){
		ans.push_back(0);
		z--;
	}
	for (;z!=ans.end();z++)
		Result += (char)(*z+48);
	return Result;
}

string Calculator::GetRemainder(){
	Remainder_ = "";
	int test = 0;
	if (sym_ans==1)
		Remainder_ += "-";
	for (z=remainder.begin();z!=remainder.end() && *z==0;z++);
	if (z==remainder.end()){
		remainder.push_back(0);
		z--;
	}
	for (;z!=remainder.end();z++)
		Remainder_ += (char)(*z+48);
	if (Remainder_=="-0")
		Remainder_ = "0";
	return Remainder_;
}

int Calculator::count(list<int> &b){
	list<int>::iterator y;
	y = b.end();
	y--;
	while (*y==0){
		if (y==b.begin())
			return 0;
		y--;
	}
	(*y)--;
	y++;
	for (;y!=b.end();y++)
		*y = 9;
	return 1;
}

int Calculator::Equal_Zero(list<int> b){
	list<int>::iterator bb = b.begin();
	if (b.begin()==b.end() || (++bb==b.end() && b.front()==0))
		return 0;
	else 
		return 1;
}

list<int> Calculator::exponent(list<int> b){
	list<int> c,result;
	c.push_front(2);
	while (Equal_Zero(b)){
		result.push_front(Division(b,c).back());
		b = Erase_Zero(ans);
	}
	return result;
}

list<int> Calculator::Key(){
	int judge = 1;
	list<int> ans,exp,some;
	list<int>::iterator x;
	ans.push_front(1);
	exp = exponent(b);
	x = exp.end();
	some = a;
	while (x != exp.begin()){
		x--;
		if (*x){
			ans = Multiplication(ans,some);
			ans = Division(ans,c);
		}
		some = Multiplication(some,some);
		some = Division(some,c);
	}
	return ans;
}
