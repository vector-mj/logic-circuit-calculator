#include<iostream>
#include<vector>
#include<stack>
#include<fstream>
#include<cmath>
#include<map>
#include <conio.h>
using namespace std;

map<string,string> index_operator;
map<string,string> index_value;
vector<string> temp;
map<string,string> temp_value;
//stack<string> stack_values;
//stack<string> stack_operator;

////////////////////////////////////////////////////
////          Function Extraction form file
////////////////////////////////////////////////////
vector<string> cases(ifstream &myfile,string cas){
	string text;
	vector<string> op;
	while(getline(myfile,text)){
		if(text==cas){
			while(text!=""){
				if(text==cas)getline(myfile,text);
				op.push_back(text);
				getline(myfile,text);
			}
		}
	}
	return op;	
}
////////////////////////////////////////////////////
////             Function print vector
////////////////////////////////////////////////////
void printvec(vector<string> &s){
	for(vector<string>::const_iterator i=s.begin();i!=s.end();i++){
		cout<<*i<<'\n';
	}	
}
////////////////////////////////////////////////////
////             Function print stack
////////////////////////////////////////////////////
void printsta(stack<string> s){
	string a="";
	while(!s.empty()){
		a=s.top()+a;
		s.pop();
		
	}
	cout<<a;	
}
////////////////////////////////////////////////////
////             Function explode
////////////////////////////////////////////////////
vector<string> explode(string str, string separator){
	vector<string> results;
    int found;
    found = str.find_first_of(separator);
    while(found != string::npos){
        if(found > 0){
            results.push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results.push_back(str);
    }
    return results;
}
////////////////////////////////////////////////////
////        Function String to Array
////////////////////////////////////////////////////
char stringToArray(string s,int a=0){
	int c = s.length();
	char ch[s.length()];
    for (int i = 0; i < sizeof(ch); i++) {
        ch[i] = s[i];
        if(a==1)cout<<ch[i];
    }
//	return ch;	
}
////////////////////////////////////////////////////
////        Function String and int
////////////////////////////////////////////////////
string multiply(string a,int b){
	string c;
	while(b>0){
		c+=a;
		b--;
	}
	return c;
}
////////////////////////////////////////////////////
////        Function calc truth table
////////////////////////////////////////////////////
vector<string> caltruthtable(vector<string> &s){
	vector<string> n;
	int size = pow(2,s.size());
	int step=1;
	string a0,a1;
	for(int i=0;i<=s.size();i++){
		a0=a1="";
		a0=multiply("0",size/2);
		a1=multiply("1",size/2);
		if(i!=0){a1=multiply(a0+a1,step);}else{a1=a0+a1;}
		size/=2;
		step*=2;
		n.push_back(a1);
	}
	return n;
}////////////////////////////////////////////////////
////     Function calculate two binary number
////////////////////////////////////////////////////
void _calc_(string val1,string val2,string op){
	op = index_operator[op];
	string v1=index_value[val1];
	string v2=index_value[val2];
	string res="";
	if(op=="and"){
		op="*";
		for(int i=0;i<v1.length();i++){
			if(v1[i]=='0'||v2[i]=='0'){
				res+="0";
			}else{
				res+="1";
			}
		}
		index_value["("+val1+op+val2+")"]=res;
//		cout<<"("+val1+op+val2+")"<<" = "<<index_value["("+val1+op+val2+")"]<<"\n";
	}else if(op=="or"){
		op="+";
		for(int i=0;i<v1.length();i++){
			if(v1[i]=='1'||v2[i]=='1'){
				res+="1";
			}else{
				res+="0";
			}
		}
		index_value["("+val1+op+val2+")"]=res;
//		cout<<"("+val1+op+val2+")"<<" = "<<index_value["("+val1+op+val2+")"]<<"\n";
	}else if(op=="xor"){
		op="@";
		for(int i=0;i<v1.length();i++){
			if(v1[i]!=v2[i]){
				res+="1";
			}else{
				res+="0";
			}
		}
		index_value["("+val1+op+val2+")"]=res;
//		cout<<"("+val1+op+val2+")"<<" = "<<index_value["("+val1+op+val2+")"]<<"\n";	
	}
	temp.push_back("("+val1+op+val2+")");
}
////////////////////////////////////////////////////
////         Function Write in excel
////////////////////////////////////////////////////
void writeInExcel(string filename){
	string first_filename=filename;
	///start make excel ////
	filename+=".xml";
	string s;
	fstream excel(filename.c_str(),ios::out);
	excel<<"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
	excel<<"<data-set>\n";
	s=index_value["a1"];
	string val="";
	for(int j=0;j<s.length();j++){
		excel<<"<record>";
		for(map<string,string>::iterator i=index_value.begin();i!=index_value.end();i++){
			val=i->second;
			excel<<"\n    <"+i->first+">"+val[j]+"</"+i->first+">";
		}
		excel<<"\n</record>\n";
	}
	excel<<"</data-set>\n";
	excel.close();
	///end make excel ////
	///start make csv ////
	val="";
	string index="";
	int count_br=0;
	filename=first_filename+".txt";
	fstream csv(filename.c_str(),ios::out);
	for(map<string,string>::iterator i=index_value.begin();i!=index_value.end();i++){
		index=i->first;
		count_br+=index.length();
		csv<<i->first<<"|";
	}
	csv<<"\n";
	csv<<multiply("#",count_br*1.2)<<"\n";
	for(int j=0;j<s.length();j++){
		for(map<string,string>::iterator i=index_value.begin();i!=index_value.end();i++){
			index=i->first;
			val=i->second;
			csv<<val[j]<<multiply(" ",index.length()-1)<<"|";
		}
		csv<<"\n";
//		csv<<"\n"<<multiply("-",count_br*1.2)<<"\n";
	}
	csv.close();
//	for(map<string,string>::iterator it = index_value.begin(); it != index_value.end(); ++it) {
//	  	cout << "Key: " << it->first <<" = "<<it->second<<"\n";
//		//printf("keys: %.50s = %.256s\n",it->first.c_str(),it->second.c_str());
//	}
}
////////////////////////////////////////////////////
////        Function ~calc logic experssion
////////////////////////////////////////////////////
void _notcalc_(string val){
	string res="";
	string val2;
	val2=index_value[val];
	for(int i=0;i<val2.length();i++){
		if(val2[i]=='0'){
			res+="1";
		}else{
			res+="0";
		}
	}
	index_value["~"+val]=res;
//	cout<<"~"+val<<" = "<<index_value["~"+val]<<"\n";	
}
////////////////////////////////////////////////////
////        Function calc logic experssion
////////////////////////////////////////////////////
void evaluationLogicExpression(string phrase){
	stack<string> stack_operator;
	string ph_first=phrase;
	phrase=phrase.substr(3,-1);
//	cout<<phrase<<'\n';
	stack_operator.push("S");
	stack<string> stack_values;
	
	//(a7+a1)+((a6*a5*a8)@a7)
	for(int i=0;i<phrase.length();i++){
		string ss="";
		ss=phrase[i];
		if(phrase[i]==' '){
			continue;
		}else if(phrase[i]=='('){
			stack_operator.push("(");
		}else if(phrase[i]=='~'){
			string o="";
			o+=phrase[i+1];
			o+=phrase[i+2];
			_notcalc_(o);
			o=phrase[i]+o;
			stack_values.push(o);
			i+=2;
			
		}else if(phrase[i]==')'){
			while(!stack_operator.empty()&&stack_operator.top()!="("){
//				cout<<"op = ";
//				printsta(stack_operator);
//				cout<<"\nval = ";
//				printsta(stack_values);
//				cout<<"\n";
				string _op = stack_operator.top();
				stack_operator.pop();
				string _val1 = stack_values.top();
				stack_values.pop();
				string _val2 = stack_values.top();
				stack_values.pop();
				_calc_(_val1,_val2,_op);
				stack_values.push("("+_val1+_op+_val2+")");
			}
			if(!stack_operator.empty()){
				stack_operator.pop();
			}
		}else if(isdigit(phrase[i])){
				string a="";
				a+=phrase[i-1];
				a+=phrase[i];
				stack_values.push(a);
		}else if(index_operator.find(ss)!=index_operator.end()){
			stack_operator.push(ss);
		}
	}
	while(stack_operator.top()!="S" && !stack_operator.empty()){
		string _op = stack_operator.top();
		stack_operator.pop();
		string _val1 = stack_values.top();
		stack_values.pop();
		string _val2 = stack_values.top();
		stack_values.pop();
//				cout<<'\n'+_val1+_op+_val2+'\n';
		_calc_(_val1,_val2,_op);
		stack_values.push("("+_val1+_op+_val2+")");
	}
//	cout<<stack_operator.top();
	
//	cout<<"op = ";
//	printsta(stack_operator);
//	cout<<"\nval = ";
//	printsta(stack_values);

//	cout<<index_value.begin()->first;
//	cout<<temp.back();
	temp_value[ph_first.substr(0,2)]=index_value[temp.back()];
	cout<<"\n\n\n\n";
	string j;
	for(int o=0;o<ph_first.length();o++){
		if(ph_first[o]!='='){
			j+=ph_first[o];
		}else{
			break;
		}
	}
	writeInExcel(j);
}

////////////////////////////////////////////////////
////             Function Main
////////////////////////////////////////////////////

int main(){
	////////////////////////////////////////////////////////
	ifstream myfile1("input.txt");
	vector<string> operation= cases(myfile1,"operation:");
	myfile1.close();
	
	ifstream myfile2("input.txt");
	vector<string> value = cases(myfile2,"value:");
	myfile2.close();
	
	ifstream myfile3("input.txt");
	vector<string> function= cases(myfile3,"function:");
	myfile3.close();
	
//	printvec(function);
	for(int i=0;i<operation.size();i++){
		vector<string> temp =explode(operation[i]," ");
		index_operator[temp[0]]=temp[1];
//		cout<<temp[0]<<" = "<<index_operator[temp[0]]<<"\n";
	}
	////////////////////////////////////////////////////////
	value=explode(value[0],",");
	vector<string> truthtable = caltruthtable(value);
	for(int i=0;i<value.capacity();i++){
//		index_value.insert(pair<string,string>(value[i],truthtable[i]));
		index_value[value[i]]=truthtable[i];
//		cout<<value[i]<<" = "<<truthtable[i]<<"\n";
	}
	////////////////////////////////////////////////////////	
	for(int i=0;i<=function.size()-1;i++){
		
		evaluationLogicExpression(function[i]);
		index_value.clear();
		for(int j=0;j<value.capacity();j++){
//			index_value.insert(pair<string,string>(value[i],truthtable[i]));
			index_value[value[j]]=truthtable[j];
//			cout<<value[j]<<" = "<<truthtable[j]<<"\n";
		}
		for(map<string,string>::iterator o=temp_value.begin();o!=temp_value.end();o++){
			index_value[o->first]=o->second;
//			cout<<o->first<<" = "<<o->second<<"\n";
		}
		string name=function[i];
		string j;
		for(int o=0;o<name.length();o++){
			if(name[o]!='='){
				j+=name[o];
			}else{
				break;
			}
		}
		name = j+".txt";
		cout<<"FUNCTION: "<<function[i]<<"\n\n";
		fstream o(name.c_str());
		string s;
		while(getline(o,s)){
			cout<<s<<"\n";
		}
		o.close();
	}
	getch();
////////////////////////////////////
}

