// Mostrar quantas strings são iguais (anagramas) em um array
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Função para remover os anagramas e exibir o numero de strings "unicas"
int removeAnagrams(string arr[], int N)
{
	// vector que guarda o resultado final
	vector<string> ans;

	// set sem ordem pra manter qual foi a ultima palavra buscada
	unordered_set<string> found;

	for (int i = 0; i < N; i++) {

		string word = arr[i];

		// ordena os caracteres da palavra alfabeticamente
		sort(begin(word), end(word));

		// Olha se a string ja nao esta no set
        // depois coloca ela no vector do resultado
        // e insere ela no unordered set
		if (found.find(word) == found.end()) {

			ans.push_back(arr[i]);
			found.insert(word);
		}
	}

	// Arruma o vetor resposta (coloca na ordem de entrada)
    // Não é necessario mas fica bonitinho se quisesse imprimir ele
	sort(begin(ans), end(ans));

    // Retorna o numero de "string unicas"
    return ans.size();
}

// Codigo main
int main()
{
	int n;
    int i;

    while(cin>>n){
        if (n == 0)
            return 0;
        string arr[n];

        for(i = 0; i < n; i++){
            cin>>arr[i];
        }
        cout << removeAnagrams(arr,n) << endl;
    }

	return 0;
}
