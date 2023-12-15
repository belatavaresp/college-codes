import numpy as np 

class MyKMeans:
    def __init__(self, num_clusters=3, max_iterations=1000):
        """
        Inicializa os parâmetros do algoritmo KMeans.

        Parameters:
        - num_clusters (int): Número de clusters desejado.
        - max_iterations (int): Número máximo de iterações do algoritmo.
        """
        self.max_iterations = max_iterations
        self.num_clusters = num_clusters
        self.centroids = None
        
    def process(self, dataset: np.ndarray):
        """
        Executa o algoritmo KMeans para clusterizar o conjunto de dados.

        Parameters:
        - dataset (numpy.ndarray): Conjunto de dados a ser clusterizado.

        Returns:
        - groups (numpy.ndarray): Array indicando a qual cluster cada ponto pertence.
        - centroids (numpy.ndarray): Coordenadas finais dos centroides.
        """
        # Obtém o formato do conjunto de dados.
        num_rows, num_columns = dataset.shape
        
        # Obtém os valores mínimos e máximos de cada coluna.
        min_data = dataset.min(axis=0)
        max_data = dataset.max(axis=0)

        # Gera pontos iniciais aleatórios para os centroides.
        initial_points = []
        for _ in range(0, self.num_clusters):
            centroid_coordinates = []
            for i in range(num_columns):
                centroid_coordinates.append(
                    np.random.uniform(low=min_data[i], high=max_data[i], size=1)[0]
                )
            initial_points.append(centroid_coordinates)
        
        # Define os centroides iniciais.
        self.centroids = np.array(initial_points)
        
        # Processo iterativo do algoritmo KMeans.
        for iteration in range(self.max_iterations):
            # Calcula a distância euclidiana e associa cada registro a um grupo.
            euclidean_distance = np.empty(shape=(dataset.shape[0], self.num_clusters))
            for i in range(self.num_clusters):
                # Distância Euclidiana
                euclidean_distance[:, i] = np.sum((dataset - self.centroids[i])**2, axis=1)
            
            # Define os grupos de cada registro com base na menor distância.
            groups = np.argmin(euclidean_distance, axis=1)
            
            # Calcula novos centroides.
            for i in range(self.num_clusters):
                sub_groups = dataset[groups == i]
                self.centroids[i] = sub_groups.mean(axis=0)    
        
        # Lida com possíveis valores NaN nos centroides finais.
        self.centroids = np.nan_to_num(self.centroids)
            
        return groups, self.centroids
