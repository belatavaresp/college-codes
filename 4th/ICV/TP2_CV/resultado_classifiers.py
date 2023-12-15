import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score
import string
import pickle
import matplotlib.pyplot as plt
import os

imgshape = (50, 28, 1)
character= string.ascii_uppercase + "0123456789" # All symbols captcha can contain
nchar = len(character)

model_filename = './modelos/logreg_model.pkl'

# Load the model
with open(model_filename, 'rb') as model_file:
    model = pickle.load(model_file)
    
path_vectors_test = os.getcwd() + '/teste_vetores_10'
path_labels_test = os.getcwd() + '/teste_labels_file_10'

with open(path_vectors_test, 'rb') as file:
    test_features = pickle.load(file)

with open(path_labels_test, 'rb') as file:
    test_labels = pickle.load(file)

scaler = StandardScaler()
test_features_scaled = scaler.fit_transform(test_features)
test_labels_1d = np.argmax(test_labels, axis=1)

# Load the model
with open(model_filename, 'rb') as model_file:
    loaded_model = pickle.load(model_file)

# Make predictions
test_predictions = loaded_model.predict(test_features_scaled)

# Evaluate the accuracy of the regression on the test set
accuracy = accuracy_score(test_labels_1d, test_predictions)
print(f"Logistic Regression Accuracy on Testing Set: {accuracy}")

# Map predicted labels to characters
predicted_characters = [character[label] for label in test_predictions]
actual_characters = [character[label] for label in test_labels_1d]

# Reshape predicted characters into a matrix
predicted_matrix = np.reshape(predicted_characters, (-1, 6))

# Reshape actual characters into a matrix
actual_matrix = np.reshape(actual_characters, (-1, 6))

right = []  # Initialize an empty list

for i in range(len(actual_matrix)):
    n = 0
    for j in range(len(actual_matrix[0])):
        if predicted_matrix[i][j] == actual_matrix[i][j]:
            n += 1
    right.append(n)  # Use append to add the count to the list

amount = [0] * (7) # Initialize with zeros, assuming the maximum count is characters_per_captcha

for i in range(len(right)):
    amount[right[i]] += 1
        
for i in range(len(amount) - 2, -1, -1):
    amount[i] += amount[i + 1]
        
for i in range(len(amount)):
    amount[i] *= 0.1
    
print(amount)

# Plot the graphic
plt.plot(range(1, len(amount)), amount[1:], 'g')
plt.xlabel('Number of characters')
plt.ylabel('Percentage of correctness')
plt.title('Correctly Guessed Characters in Captchas - HOG + Log_Reg')
plt.show()
