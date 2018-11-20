#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int l,c,aux,n_pecas = 0;
vector< vector<int> > v;
vector< vector<int> > check;

int n_s_d = 0;
unordered_map <long long,int> pd;
unordered_map <long long,int> :: iterator it;

// print de debug
void p_debug(vector< vector<int> > v){
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void check_i(int i,	int j){

	p_debug(check);

	//cima
	if(i>0 && check[i-1][j] == 0 && v[i-1][j] != 0){
		
		check[i-1][j] = 1;
		check_i(i-1,j);
	}

	//baixo

	if(i < l-1 && check[i+1][j] == 0 && v[i+1][j] != 0){
	
		check[i+1][j] = 1;
		check_i(i+1,j);
	}

	//direita

	if(j < c-1 && check[i][j+1] == 0 && v[i][j+1] != 0){
		
		check[i][j+1] = 1;
		check_i(i,j+1);
	}

	//esquerda

	if(j > 0 && check[i][j-1] == 0 && v[i][j-1] != 0){
		
		check[i][j-1] = 1;
		check_i(i,j-1);
	}

	cout << "fim recursao " << endl;

}

int ilhas(int p_i, int p_j){

	check.resize(l);

	for (int i = 0; i < l; ++i){
		check[i].resize(c);

		for (int j = 0; j < c; ++j){
			check[i][j] = 0;
		}
	}
	
	cout << "vou pintar a partir dessa matriz " << endl;
	p_debug(v);	
	check[p_i][p_j] = 1;
	check_i(p_i,p_j);

	for (int i = 0; i < l; ++i){
		for (int j = 0; j < c; ++j){
			if(check[i][j] == 0 && v[i][j] != 0){
				return 1; // achei uma ilha
			}
		}
	}	

	return 0; // nao tem ilhas
}

long long b_4(vector< vector<int> > v){

	long long resp = 0;
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); j++){
			resp |= v[i][j] << (c*i + j)*2;
		}
	}

	return resp;
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


int acha_solucao(int l, int c, int n_pecas){
	
	int p_aux; // aux da posicao a ser retirada;
	int n_maneiras = 0;


	if(acabou(n_pecas) == 0){
		cout << "entrei na acha s" << endl;
		p_debug(v);
		cout << endl;

		for (int i = 0; i < l; ++i){
			for (int j = 0; j < c; j++){
				if(v[i][j] != 0){ // se a célula atual nao esta vazia

					if(i>0 && pode_mover(v[i][j],v[i-1][j]) == 1){ // pra cima

						p_aux = v[i-1][j];

						v[i-1][j] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						it = pd.find(b_4(v));
						if(it == pd.end()){

							if(ilhas(i-1,j) == 1){
								pd[v[i-1][j]] = 0;

								v[i][j] = v[i-1][j];
								v[i-1][j] = p_aux;
								n_pecas++;

								return 0;
							}else{
								n_maneiras += acha_solucao(l,c,n_pecas);	
							}
							
						}else{
							n_maneiras += pd[b_4(v)];
						}
						

						v[i][j] = v[i-1][j];
						v[i-1][j] = p_aux;
						n_pecas++;
					}
					if(i < l-1 && pode_mover(v[i][j],v[i+1][j]) == 1){ // pra baixo

						p_aux =v[i+1][j] ;

						v[i+1][j] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						it = pd.find(b_4(v));
						if(it == pd.end()){

							if(ilhas(i+1,j) == 1){
								pd[v[i+1][j]] = 0;

								v[i][j] = v[i+1][j];
								v[i+1][j] = p_aux;
								n_pecas++;

								return 0;
							}else{
								n_maneiras += acha_solucao(l,c,n_pecas);	
							}

						}else{
							n_maneiras += pd[b_4(v)];
						}

						v[i][j] = v[i+1][j];
						v[i+1][j] = p_aux;
						n_pecas++;
					}
					if(j < c-1 && pode_mover (v[i][j],v[i][j+1]) == 1){ // pra direita
						p_aux = v[i][j+1];

						v[i][j+1] = v[i][j];
						v[i][j] = 0;
						n_pecas--;
						//cout << "here" << endl;
						it = pd.find(b_4(v));
						if(it == pd.end()){
							
							if(ilhas(i,j+1) == 1){
								pd[v[i][j+1]] = 0;

								v[i][j] = v[i][j+1];
								v[i][j+1] = p_aux;
								n_pecas++;

								return 0;
							}else{
								n_maneiras += acha_solucao(l,c,n_pecas);	
							}

						}else{
							n_maneiras += pd[b_4(v)];
						}

						v[i][j] = v[i][j+1];
						v[i][j+1] = p_aux;
						n_pecas++;
					}
					if(j > 0 && pode_mover (v[i][j],v[i][j-1]) == 1){ // pra esquerda

						p_aux = v[i][j-1];

						v[i][j-1] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						it = pd.find(b_4(v));
						if(it == pd.end()){
							if(ilhas(i,j-1) == 1){

								pd[v[i][j-1]] = 0;
								v[i][j] = v[i][j-1];
								v[i][j-1] = p_aux;
								n_pecas++;

								return 0;
							}else{
								n_maneiras += acha_solucao(l,c,n_pecas);	
							}
						}else{
							n_maneiras += pd[b_4(v)];
						}

						v[i][j] = v[i][j-1];
						v[i][j-1] = p_aux;
						n_pecas++;
					}
				}
			}
		}

		pd[b_4(v)] = n_maneiras;	
		return n_maneiras;

	}else{
		cout << "achei solucao " << n_pecas << endl;

		p_debug(v);

		pd[b_4(v)] = 1;

		cout << endl;
		return 1;
	}
}

int main (){

	ios :: sync_with_stdio(false);

	cin >> l >> c;
	v.resize(l);

	for (int i = 0; i < l; ++i){
		for (int j = 0; j < c; ++j){
			cin >> aux;
			if(aux != 0 ){
				n_pecas++;
			}
			v[i].push_back(aux);
		}
	}

	acha_solucao(l,c,n_pecas);

	cout << "n maneiras " << pd[b_4(v)] << endl;

	for (it = pd.begin(); it != pd.end(); it++){
		cout << it->first << endl;
	}

}