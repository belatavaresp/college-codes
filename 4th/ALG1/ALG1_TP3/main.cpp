#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define inf -0x3f3f3f3f3f3f3f3f

// função para preencher a matriz de relações entre conjuntos de manobras
void preencherPontuacao(int K, vector<vector<int>> &pontuacaoConjunto, vector<int> pontuacao)
{
    for (int n = 0; n < (1 << K); n++) // anterior
    {
        for (int m = 0; m < (1 << K); m++) // atual 
        {
            for (int k = 0; k < K; k++)
            {
                if (!((1 << k) & m))
                {
                    continue;
                }
                if ((1 << k) & n)
                {
                    pontuacaoConjunto[n][m] += floor(pontuacao[k] / 2);
                }
                else
                {
                    pontuacaoConjunto[n][m] += pontuacao[k];
                }
            }
        }
    }
}

// Função para calcular o tempo e tamanho total de um conjunto de manobras
void calcularDados(int K, int mask, vector<int> &tempo, vector<int> &tempoConjunto, vector<int> &tamanhoConjunto)
{
    int tempoSequencia = 0;
    int tamanhoSequencia = 0;

    for (int i = 0; i < K; i++)
    {
        // Verifica se a manobra está presente no conjunto (usando a máscara)
        if (mask & (1 << i))
        {
            tempoSequencia += tempo[i];
            tamanhoSequencia++;
        }
    }

    tempoConjunto[mask] = tempoSequencia;
    tamanhoConjunto[mask] = tamanhoSequencia;
}

int main()
{
    // lendo a entrada
    int N, K; // #seções e #manobras
    cin >> N >> K;

    // inicialização vetores iniciais
    vector<int> bonificacao(N);
    vector<int> tamanho(N);

    vector<int> pontuacao(K);
    vector<int> tempo(K);

    // preenchendo dados das N seções
    for (int i = 0; i < N; i++)
    {
        cin >> bonificacao[i] >> tamanho[i];
    }

    // preenchendo dados das K manobras
    for (int j = 0; j < K; j++)
    {
        cin >> pontuacao[j] >> tempo[j];
    }

    // Criando vetores de pontuações, tamanhos e tempos para cada conjunto de manobras
    vector<vector<int>> pontuacaoConjunto(1 << K, vector<int>(1 << K, 0));
    vector<int> tempoConjunto(1 << K);
    vector<int> tamanhoConjunto(1 << K);

    // Preenchendo os vetores
    for (int mask = 0; mask < (1 << K); mask++)
    {
        // Calculando a pontuação total do conjunto de manobras e atribuindo ao vetor
        calcularDados(K, mask, tempo, tempoConjunto, tamanhoConjunto);
    }

    // calculando pontuação relativa das manobras
    preencherPontuacao(K, pontuacaoConjunto, pontuacao);

    // declaração vetor da DP
    vector<vector<long long>> dp(N, vector<long long>(1 << K, inf));
    // declaração vetor de conjunto de manobras usado em cada parte da DP
    vector<vector<int>> used(N, vector<int>((1 << K), -1));

    // Preenchendo a primeira linha da DP (seção 0)
    for (int mask = 0; mask < (1 << K); mask++)
    {
        // Verificar se o tempo total não estoura o tempo da seção
        if (tempoConjunto[mask] <= tamanho[0])
        {
            dp[0][mask] = bonificacao[0] * pontuacaoConjunto[0][mask] * tamanhoConjunto[mask];
        }
    }

    // preechendo o restante da DP
    for (int secao = 1; secao < N; secao++)
    {
        for (int mask = 0; mask < (1 << K); mask++)
        {
            // Iterar sobre os conjuntos anteriores
            for (int prevMask = 0; prevMask < (1 << K); prevMask++)
            {
                // Cálculo do termo do max
                long long termoMax = dp[secao - 1][prevMask] + (bonificacao[secao] * pontuacaoConjunto[prevMask][mask] * tamanhoConjunto[mask]);
                long long termoDP = dp[secao][mask];

                // melhora a pontuação
                if(termoDP <= termoMax){
                    dp[secao][mask] = termoMax;
                    used[secao][mask] = prevMask;
                }
                
                // estoura o tempo -> inválido
                if (tempoConjunto[mask] > tamanho[secao])
                {
                    dp[secao][mask] = inf;
                }
            }
        }
    }

    long long maxPontuacao; // valor da pontuação máxima
    vector<int> sequencia(N); // conjunto de manobras usada em cada seção
    int colunaMaxPontuacao = 0;

    // encontrando a pontuação máxima (maior valor da ultima linha da DP)
    for (int mask = 1; mask < (1 << K); mask++)
    {
        if (dp[N - 1][mask] > maxPontuacao)
        {
            maxPontuacao = dp[N - 1][mask];
            colunaMaxPontuacao = mask;
        }
    }

    vector<int> caminho(N, -1); // vetor para armazenar o caminho do backtracking

    int colunaAtual = colunaMaxPontuacao;

    // backtracking a partir do maior elemento para achar qual conjunto foi usado
    for (int secao = N - 1; secao >= 0; secao--)
    {
        caminho[secao] = colunaAtual; // Armazena a coluna atual na posição correspondente ao índice da seção

        // Atualiza a coluna atual para a próxima seção
        colunaAtual = used[secao][colunaAtual];
    }

    cout << maxPontuacao << endl; // resultado

    // imprimindo as manobras por seção
    for (int secao = 0; secao < N; secao++)
    {
        int mask = caminho[secao];
        if (mask == 0)
        {
            cout << "0";  // Se a máscara for zero, imprimir 0 diretamente
        }
        else
        {
            cout << tamanhoConjunto[mask] << " "; // tamanho do conjunto
            for (int j = 0; j < K; ++j)
            {
                if (mask & (1 << j))
                {
                    cout << j + 1 << " ";
                }
            }
        }

        cout << endl;
    }

    return 0;
}