#include <bits/stdc++.h>

using namespace std;


void p_debug(vector< vector<int> > v){
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}

}

void acha_solucao(vector< vector<int> > v, int l, int c){



}


int main (){

	ios :: sync_with_stdio(false);

	int l,c,aux;
	cin >> l >> c;
	
	vector< vector<int> > v(l);

	for (int i = 0; i < l; ++i){
		for (int j = 0; j < c; ++j){
			cin >> aux;
			v[i].push_back(aux);
		}
	}
	p_debug(v);	
	


}