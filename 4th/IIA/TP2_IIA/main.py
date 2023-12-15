import pandas as pd
import warnings
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix
import numpy as np
from scipy.spatial import distance

from functions.kMeans import MyKMeans
from functions.kNN import KNN

# Função para calcular a distância euclidiana entre os centroides
def calcular_distancia_centroides(centroides1, centroides2):
    distancias = [distance.euclidean(c1, c2) for c1, c2 in zip(centroides1, centroides2)]
    return distancias

warnings.filterwarnings("ignore")

# Carregando os dados dos conjuntos de treino, teste e completo
nba_treino = pd.read_csv('../TP2_IIA/nba_treino.csv')
nba_teste = pd.read_csv('../TP2_IIA/nba_teste.csv')
nba_full_data = pd.read_csv('../TP2_IIA/nba_tudo.csv')

# Seleção de características relevantes
caracteristicas = ['MIN', 'PTS', 'FGM', 'FGA', 'FG%', '3PMade', '3PA', '3P%', 'FTM', 'FTA', 'FT%',
                   'OREB', 'DREB', 'REB', 'AST', 'STL', 'BLK', 'TOV']
caracteristica_goal = ['TARGET_5Yrs']

# Separando características e rótulos do conjunto de treino
caracteristicas_treino = nba_treino.drop('TARGET_5Yrs', axis=1)
vetor_treino = nba_treino['TARGET_5Yrs']

# Separando características e rótulos do conjunto de teste
caracteristicas_teste = nba_teste.drop('TARGET_5Yrs', axis=1)
vetor_teste = nba_teste['TARGET_5Yrs']

# Normalizando os dados
scaler = StandardScaler()
dados_treino_normalizados = scaler.fit_transform(caracteristicas_treino)
dados_teste_normalizados = scaler.transform(caracteristicas_teste)
# Valores de k para teste
valores_k = [2, 10, 50, 101]  # Adicione mais valores se necessário

# Resultados para KNN
resultados_knn = {}
resultados_knn_scikit = {}

print("="*100)
print("K-NEAREST NEIGHBOR\n")

# Avaliação para diferentes valores de k no KNN
for k in valores_k:
    # Instanciando e treinando o modelo KNN
    knn = KNN(neighbors=k)
    scikit_knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(dados_treino_normalizados, vetor_treino)
    scikit_knn.fit(dados_treino_normalizados, vetor_treino)

    # Avaliando no conjunto de teste
    acuracia, precisao, recall, f1, matriz_confusao = knn.evaluate(dados_teste_normalizados, vetor_teste)
    y_pred = scikit_knn.predict(dados_teste_normalizados)
    
    acuracia_sci = accuracy_score(vetor_teste, y_pred)

    # Calculando precisão
    precisao_sci = precision_score(vetor_teste, y_pred)

    # Calculando recall
    recall_sci = recall_score(vetor_teste, y_pred)

    # Calculando F1-score
    f1_sci = f1_score(vetor_teste, y_pred)

    # Matriz de confusão
    matriz_confusao_sci = confusion_matrix(vetor_teste, y_pred)

    # Armazenando resultados
    resultados_knn[k] = {'Acuracia': acuracia, 'Precisao': precisao, 'Recall': recall, 'F1': f1, 'Matriz Confusao': matriz_confusao}
    resultados_knn_scikit[k] = {'Acuracia': acuracia_sci, 'Precisao': precisao_sci, 'Recall': recall_sci, 'F1': f1_sci, 'Matriz Confusao': matriz_confusao_sci}

# Exibindo resultados do KNN
for (k, resultado), (_, resultado_sci) in zip(resultados_knn.items(), resultados_knn_scikit.items()):
    print(f"Resultados para k={k} (Implementação vs. Scikit-learn):")
    print(f"Sua Implementação:")
    print(f"Acurácia: {resultado['Acuracia'] * 100:.2f}%")
    print(f"Precisão: {resultado['Precisao']}")
    print(f"Recall: {resultado['Recall']}")
    print(f"F1: {resultado['F1']}")
    print(f"Matriz de Confusão:")
    print(resultado['Matriz Confusao'])
    
    print("\nScikit-learn:")
    print(f"Acurácia: {resultado_sci['Acuracia'] * 100:.2f}%")
    print(f"Precisão: {resultado_sci['Precisao']}")
    print(f"Recall: {resultado_sci['Recall']}")
    print(f"F1: {resultado_sci['F1']}")
    print(f"Matriz de Confusão:")
    print(resultado_sci['Matriz Confusao'])
    
    print("\n" + "=" * 50 + "\n")  # Linha de separação

# ------------------------------------------------------------- K MEANS ------------------------------------------------------------------

print("="*100)
print("K-MEANS\n")

# Subconjunto do DataFrame apenas com as características
dados_kmeans = nba_full_data[caracteristicas]
vetor_target = nba_full_data[caracteristica_goal]

# Normalizando os dados
scaler = StandardScaler()
dados_normalizados = scaler.fit_transform(dados_kmeans)
vetor_target = np.array(vetor_target)
vetor_target = np.ravel(vetor_target)

# Aplicando o K-Means com k = 2
kmeans = MyKMeans(num_clusters=2)
kmeans_sci = KMeans(n_clusters=2)
grupos, centroides = kmeans.process(dados_normalizados)
pred = kmeans_sci.fit(dados_normalizados)
grupos_sci = pred.labels_
centroides_sci = pred.cluster_centers_

# Imprimindo resultados do K-Means
print("Resultados para K-Means (Implementação vs. Scikit-learn):")
print(f"Implementação:")
print("Centroides para k=2:\n")
for i, centroide in enumerate(centroides):
    print(f"Cluster {i + 1}: {centroide}")
    print()

correlation = np.sum(vetor_target == grupos) / len(vetor_target) * 100
print(f"Acurácia para k=2: {correlation:.2f}%\n")

print("-" * 40)

print("\nScikit-learn:")
print("Centroides para k=2:\n")
for i, centroide_sci in enumerate(centroides_sci):
    print(f"Cluster {i + 1}: {centroide_sci}")
    print()    

# Calcular acurácia para scikit-learn
correlation_sci = np.sum(vetor_target == grupos_sci) / len(vetor_target) * 100
print(f"Acurácia para k=2 (Scikit-learn): {correlation_sci:.2f}%\n")

distancias_k2 = calcular_distancia_centroides(centroides, centroides_sci)

# Imprimindo resultados
print("Distância Euclidiana entre os Centroides para k=2:")
print(distancias_k2)
print("\n")

# Aplicando o K-Means com k = 3
kmeans = MyKMeans(num_clusters=3)
kmeans_sci = KMeans(n_clusters=3)
grupos3, centroides3 = kmeans.process(dados_normalizados)
pred_sci = kmeans_sci.fit(dados_normalizados)
grupos3_sci = pred_sci.labels_
centroides3_sci = pred_sci.cluster_centers_

# Imprimindo resultados do K-Means para k=3
print("Resultados para K-Means (k=3) - Implementação vs. Scikit-learn:")
print(f"Implementação:")
print("Centroides para k=3:\n")
for i, centroide in enumerate(centroides3):
    print(f"Cluster {i + 1}: {centroide}")
    print()

# Comparando Cluster 1 e Cluster 2
indices_cluster_12 = np.where((grupos3 == 0) | (grupos3 == 1))[0]
correlation12 = np.sum(vetor_target[indices_cluster_12] == grupos3[indices_cluster_12]) / len(indices_cluster_12) * 100

# Comparando Cluster 2 e Cluster 3
indices_cluster_23 = np.where((grupos3 == 1) | (grupos3 == 2))[0]
correlation23 = np.sum(vetor_target[indices_cluster_23] == grupos3[indices_cluster_23]) / len(indices_cluster_23) * 100

# Comparando Cluster 1 e Cluster 3
indices_cluster_13 = np.where((grupos3 == 0) | (grupos3 == 2))[0]
correlation13 = np.sum(vetor_target[indices_cluster_13] == grupos3[indices_cluster_13]) / len(indices_cluster_13) * 100

correlation12 = np.nan_to_num(correlation12)
correlation23 = np.nan_to_num(correlation23)
correlation13 = np.nan_to_num(correlation13)

print(f"Acurácia para Cluster 1 e 2: {correlation12:.2f}%")
print(f"Acurácia para Cluster 2 e 3: {correlation23:.2f}%")
print(f"Acurácia para Cluster 1 e 3: {correlation13:.2f}%\n")

print("Scikit-learn:")
print("Centroides para k=3:\n")
for i, centroide_sci in enumerate(centroides3_sci):
    print(f"Cluster {i + 1}: {centroide_sci}")
    print()

# Comparando Cluster 1 e Cluster 2
indices_cluster_12_sci = np.where((grupos3_sci == 0) | (grupos3_sci == 1))[0]
correlation12_sci = np.sum(vetor_target[indices_cluster_12_sci] == grupos3_sci[indices_cluster_12_sci]) / len(indices_cluster_12_sci) * 100

# Comparando Cluster 2 e Cluster 3
indices_cluster_23_sci = np.where((grupos3_sci == 1) | (grupos3_sci == 2))[0]
correlation23_sci = np.sum(vetor_target[indices_cluster_23_sci] == grupos3_sci[indices_cluster_23_sci]) / len(indices_cluster_23_sci) * 100

# Comparando Cluster 1 e Cluster 3
indices_cluster_13_sci = np.where((grupos3_sci == 0) | (grupos3_sci == 2))[0]
correlation13_sci = np.sum(vetor_target[indices_cluster_13_sci] == grupos3_sci[indices_cluster_13_sci]) / len(indices_cluster_13_sci) * 100

correlation12_sci = np.nan_to_num(correlation12_sci)
correlation23_sci = np.nan_to_num(correlation23_sci)
correlation13_sci = np.nan_to_num(correlation13_sci)

print(f"Acurácia para Cluster 1 e 2: {correlation12_sci:.2f}%")
print(f"Acurácia para Cluster 2 e 3: {correlation23_sci:.2f}%")
print(f"Acurácia para Cluster 1 e 3: {correlation13_sci:.2f}%")

# Distância euclidiana entre os centroides para k=3
distancias_k3 = calcular_distancia_centroides(centroides3, centroides3_sci)

print("\nDistância Euclidiana entre os Centroides para k=3:")
print(distancias_k3)