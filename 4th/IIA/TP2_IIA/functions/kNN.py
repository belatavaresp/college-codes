import numpy as np

class KNN:
    
    def __init__(self, neighbors=3):
        """
        Inicializa os parâmetros do algoritmo KNN.

        Parameters:
        - neighbors (int): Número de vizinhos a serem considerados.
        """
        self.neighbors = neighbors
        self.data = None
        self.labels = None
        
    def fit(self, data, labels):
        """
        Define os dados de treinamento e os rótulos.

        Parameters:
        - data (numpy.ndarray): Dados de treinamento.
        - labels (numpy.ndarray): Rótulos correspondentes aos dados de treinamento.
        """
        self.data = data
        self.labels = labels
    
    def euclidean_distance(self, point1, point2):
        """
        Calcula a distância euclidiana entre dois pontos.

        Parameters:
        - point1 (numpy.ndarray): Primeiro ponto.
        - point2 (numpy.ndarray): Segundo ponto.

        Returns:
        - float: Distância euclidiana entre os dois pontos.
        """
        return np.sqrt(np.sum((point1 - point2) ** 2))
    
    def find_neighbors(self, point):
        """
        Encontra os índices dos vizinhos mais próximos de um ponto.

        Parameters:
        - point (numpy.ndarray): Ponto para o qual encontrar vizinhos.

        Returns:
        - numpy.ndarray: Índices dos vizinhos mais próximos.
        """
        distances = np.array([self.euclidean_distance(point, x) for x in self.data])
        neighbor_indices = np.argsort(distances)[:self.neighbors]
        return neighbor_indices
    
    def predict(self, point):
        """
        Prevê a classe de um ponto com base nos vizinhos mais próximos.

        Parameters:
        - point (numpy.ndarray): Ponto para o qual fazer a previsão.

        Returns:
        - int: Classe predominante prevista para o ponto.
        """
        neighbor_indices = self.find_neighbors(point)
        neighbor_labels = self.labels[neighbor_indices]
        predominant_class = np.argmax(np.bincount(neighbor_labels))
        return predominant_class
    
    def confusion_matrix(self, test_data, test_labels):
        """
        Calcula a matriz de confusão.

        Parameters:
        - test_data (numpy.ndarray): Dados de teste.
        - test_labels (numpy.ndarray): Rótulos correspondentes aos dados de teste.

        Returns:
        - numpy.ndarray: Matriz de confusão.
        """
        num_classes = len(np.unique(self.labels))
        confusion_matrix = np.zeros((num_classes, num_classes), dtype=int)
        
        for i in range(len(test_data)):
            real_class = test_labels[i]
            predicted_class = self.predict(test_data[i])
            confusion_matrix[real_class, predicted_class] += 1
        
        return confusion_matrix
    
    def metrics(self, confusion_matrix):
        """
        Calcula métricas de avaliação.

        Parameters:
        - confusion_matrix (numpy.ndarray): Matriz de confusão.

        Returns:
        - float: Acurácia.
        - numpy.ndarray: Precisão para cada classe.
        - numpy.ndarray: Recall para cada classe.
        - numpy.ndarray: F1-score para cada classe.
        """
        # Calcular métricas
        precision = confusion_matrix[1, 1] / np.sum(confusion_matrix[:, 1])
        recall = confusion_matrix[1, 1] / np.sum(confusion_matrix[1, :])
        f1_score = 2 * (precision * recall) / (precision + recall)

        # Acurácia
        accuracy = np.sum(np.diag(confusion_matrix)) / np.sum(confusion_matrix)

        return accuracy, precision, recall, f1_score
    
    def evaluate(self, test_data, test_labels):
        """
        Avalia o desempenho do modelo nos dados de teste.

        Parameters:
        - test_data (numpy.ndarray): Dados de teste.
        - test_labels (numpy.ndarray): Rótulos correspondentes aos dados de teste.

        Returns:
        - float: Acurácia.
        - numpy.ndarray: Precisão para cada classe.
        - numpy.ndarray: Recall para cada classe.
        - numpy.ndarray: F1-score para cada classe.
        - numpy.ndarray: Matriz de confusão.
        """
        confusion_matrix = self.confusion_matrix(test_data, test_labels)
        accuracy, precision, recall, f1_score = self.metrics(confusion_matrix)
        
        return accuracy, precision, recall, f1_score, confusion_matrix
