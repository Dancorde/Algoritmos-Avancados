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

int acabou (int resto){
	if(resto == 1){
		//cout << "Acabo " << resto << endl;
		return 1;
	}else {
		return 0;
	}
}

int pode_mover(int p1, int p2){
	if(p1 == 1){
		if(p2 == 2){
			return 1;
		}
	}else if(p1 == 2){
		if(p2 == 3){
			return 1;
		}
	}else if(p1 == 3){
		if(p2 == 1){
			return 1;
		}
	}

	return 0; 
}


void acha_solucao(vector< vector<int> > v, int l, int c, int n_pecas){
	
	// verificar se o jogo ja acabou

	if(acabou(n_pecas) == 0){
		p_debug(v);
		cout << endl;
		for (int i = 0; i < l; ++i){
			for (int j = 0; j < c; j++){
				if(v[i][j] != 0){ // se a célula atual nao esta vazia

					if(i>0 && pode_mover(v[i][j],v[i-1][j]) == 1){ // pra cima
						v[i-1][j] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						acha_solucao(v,l,c,n_pecas);
					}else if(i < l-1 && pode_mover(v[i][j],v[i+1][j]) == 1){ // pra baixo
						v[i+1][j] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						acha_solucao(v,l,c,n_pecas);
					}else if(j < c-1 && pode_mover (v[i][j],v[i][j+1]) == 1){ // pra direita
						v[i][j+1] = v[i][j];
						v[i][j] = 0;
						n_pecas--;
						//cout << "here" << endl;
						acha_solucao(v,l,c,n_pecas);
					}else if(j > 0 && pode_mover (v[i][j],v[i][j-1]) == 1){ // pra esquerda
						v[i][j-1] = v[i][j];
						v[i][j] = 0;
						n_pecas--;
						acha_solucao(v,l,c,n_pecas);
					}

				}
			}
		}
	}else{
		cout << "achei solucao " << n_pecas << endl;
		p_debug(v);
	}

	

	// game acabou, salvar como esta


}




int main (){

	ios :: sync_with_stdio(false);

	int l,c,aux,n_pecas = 0;
	cin >> l >> c;
	
	vector< vector<int> > v(l);

	for (int i = 0; i < l; ++i){
		for (int j = 0; j < c; ++j){
			cin >> aux;
			if(aux != 0 ){
				n_pecas++;
			}
			v[i].push_back(aux);
		}
	}
	p_debug(v);
	cout << endl;	
	acha_solucao(v,l,c,n_pecas);
	//void acha_solucao(vector< vector<int> > v, int l, int c, int n_pecas){
	
	//cout << endl << n_pecas << endl;

}