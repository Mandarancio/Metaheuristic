#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <map>

using namespace std;

bool AND(stack<bool> &, vector<bool>);
bool OR(stack<bool> &, vector<bool>);
bool NOT(stack<bool> &, vector<bool>);
bool XOR(stack<bool> &, vector<bool>);

bool V1(stack<bool> &, vector<bool>);
bool V2(stack<bool> &, vector<bool>);
bool V3(stack<bool> &, vector<bool>);
bool V4(stack<bool> &, vector<bool>);

vector<bool (*f)(stack<bool>&,vector<bool>)> randProg(vector<bool (*f)(stack<bool>&,vector<bool>)>, unsigned int length);

int execute(vector<bool (*f)(stack<bool>&,vector<bool>)>, map<vector<bool>, bool> );

int main(int argc,char **argv){
    cout<<"Test\n";
    return 0;
}
