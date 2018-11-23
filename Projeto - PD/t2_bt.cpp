#include <bits/stdc++.h>
#include <unordered_map>
#define ll long long
#define ull unsigned long long

using namespace std;

int l,c,aux;
vector< vector<int> > v;
vector< vector<int> > check;

vector< vector<int> > s1;

unordered_map <ull,ull> pd;
unordered_map <ull,ull> :: iterator it;

vector< pair<int,int> > direcao;
/*
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
*/

void check_i(int i,	int j){


	check[i][j] = 1; // pinta posicao atual
	//p_debug(check);

	for (pair<int, int> dir : direcao){
		int ni = i + dir.first;
		int nj = j + dir.second;
		if(ni>=0 && ni < l && nj >= 0 && nj < c && 
			check[ni][nj] == 0 && v[ni][nj] != 0){
			check_i(ni,nj);
		}	
	}


}

int ilhas(int p_i, int p_j){

	check.resize(l);

	for (int i = 0; i < l; ++i){
		check[i].resize(c);

		for (int j = 0; j < c; ++j){
			check[i][j] = 0;
		}
	}
	
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

ull b_4(vector< vector<int> > v){
    ull hash = 0;
    for(int i = 0; i < l; i++)
        for(int j = 0; j < c; j++)
            hash |= ((ull)(v[i][j] & 0b11) << (2*j + (2*c*i)));
    return hash;
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

void guarda_solucao(){

	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j){
			if(v[i][j] != 0){

				vector<int> m(3);
				m[0] = i+1;
				m[1] = j+1;
				m[2] = v[i][j];

				s1.push_back(m);
				return;
			}
		}
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

ull acha_solucao(int l, int c, int n_pecas){
	
	int p_aux; // aux da posicao a ser retirada;
	ull n_maneiras = 0;

	/*cout << "Tentando Achar Solução " << (n_pecas) <<  endl;
	p_debug(v);*/

	if(acabou(n_pecas) == 0){	

		for (int i = 0; i < l; ++i){
			for (int j = 0; j < c; j++){

				for (pair<int, int> dir : direcao){
					int ni = i + dir.first;
					int nj = j + dir.second;

					if(ni >= 0 && ni < l && nj >= 0 && nj < c &&
						pode_mover(v[i][j],v[ni][nj]) == 1 ){

						p_aux = v[ni][nj];
						v[ni][nj] = v[i][j];
						v[i][j] = 0;
						n_pecas--;

						ull key = b_4(v);


						it = pd.find(key);

						if(it == pd.end()){

							if(ilhas(ni,nj) == 1){
								pd[key] = 0;
							}else{
								n_maneiras += acha_solucao(l,c,n_pecas);	
							}
							
						}else{
							n_maneiras += pd[key];
						}

						v[i][j] = v[ni][nj];
						v[ni][nj] = p_aux;
						n_pecas++;
	

					}

				}

			}
			
		}	
		
		return pd[b_4(v)] = n_maneiras;

	}else{ // achei solução == resta uma peça

		guarda_solucao();

		pd[b_4(v)] = 1;
		return 1;
	}
}

int main (){

	ios :: sync_with_stdio(false);
	int n_pecas = 0;

	cin >> l >> c;
	v.resize(l);

	direcao.push_back(make_pair(0,1));
	direcao.push_back(make_pair(0,-1));
	direcao.push_back(make_pair(1,0));
	direcao.push_back(make_pair(-1,0));

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
	sort(s1.begin(),s1.end());
	cout <<  pd[b_4(v)] << endl; // nº de maneiras de chegar em soluções
	cout << s1.size() << endl; // nº de soluções diferentes

	for (int i = 0; i < s1.size(); ++i){
		for (int j = 0; j < s1[i].size(); j++){
			cout << s1[i][j] << " ";
		}
		cout << endl;
	}

}