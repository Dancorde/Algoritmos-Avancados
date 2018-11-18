#include <bits/stdc++.h>

using namespace std;

// print de debug
void p_debug(vector< vector<int> > v){
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}

}

bool acabou (int resto){
	if(resto == 1){
		return true;
	}else {
		return false;
	}
}

bool pode_mover(int p1, int p2){
	if(p1 == 1){
		if(p2 == 2){
			return true;
		}
	}else if(p1 == 2){
		if(p2 == 3){
			return true;
		}
	}else if(p1 == 3){
		if(p2 == 1){
			return true;
		}
	}

	return false; 
}


void acha_solucao(vector< vector<int> > v, int l, int c, int n_pecas){
	
	// verificar se o jogo ja acabou

	for (int i = 0; i < l; ++i){
		for (int j = 0; j < c; j++){
			if(v[i][j] != 0){ // se a célula atual nao esta vazia

				if(i>0 && pode_mover (v[i][j],v[i-1][j])){ // pra cima
					v[i-1][j] = v[i][j];
					v[i][j] = 0;
					n_pecas--;
					acha_solucao(v,l,c,n_pecas);
				}else if(i < l-1 && pode_mover (v[i][j],v[i+1][j])){ // pra baixo
					v[i+1][j] = v[i][j];
					v[i][j] = 0;
					n_pecas--;
					acha_solucao(v,l,c,n_pecas);
				}else if(j < r-1 && pode_mover (v[i][j],v[i][j+1])){ // pra direita
					v[i][j+1] = v[i][j];
					v[i][j] = 0;
					n_pecas--;
					acha_solucao(v,l,c,n_pecas);
				}else if(j > 0 && pode_mover (v[i][j],v[i][j-1])){ // pra esquerda
					v[i][j-1] = v[i][j];
					v[i][j] = 0;
					n_pecas--;
					acha_solucao(v,l,c,n_pecas);
				}

			}
		}
	}

	// game acabou, salvar como esta


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