import numpy as np
from keras.models import load_model, Model
from keras.layers import Dropout, BatchNormalization
from keras import layers
import string
import pickle
import matplotlib.pyplot as plt

imgshape = (50, 28, 1)
character= string.ascii_uppercase + "0123456789" # All symbols captcha can contain
nchar = len(character)

def createmodel():
    img = layers.Input(shape=(50, 28, 1))  # Change input shape
    conv1 = layers.Conv2D(32, (3, 3), activation='relu')(img)
    mp1 = layers.MaxPooling2D((2, 2))(conv1)
    conv2 = layers.Conv2D(64, (3, 3), activation='relu')(mp1)
    mp2 = layers.MaxPooling2D((2, 2))(conv2)
    conv3 = layers.Conv2D(64, (3, 3), activation='relu')(mp2)

    flat = layers.Flatten()(conv3)
    dense1 = layers.Dense(64, activation='relu')(flat)
    drop1 = Dropout(0.5)(dense1)  # Add dropout
    norm1 = BatchNormalization()(drop1)  # Add batch normalization
    dense2 = layers.Dense(nchar, activation='sigmoid')(norm1)

    # Compile model and return it
    model = Model(img, dense2)
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=["accuracy"])
    return model

#Create model
model=createmodel()
model = load_model("./models/my_trained_model.h5")

#Print the summary
model.summary()

# model1.summary()

path_to_labels = "./bin/treinamentoCNN_labels_file" # trocar para "dados/CAPTCHA-10k/labels"
path_vectors_train = "./bin/treinamentoCNN_imagens"

test_labels_path = "./bin/testeCNN_labels_file"
path_vectors_test = "./bin/testeCNN_imagens"

valid_labels_path = "./bin/validacaoCNN_labels_file"
path_vectors_valid = "./bin/validacaoCNN_imagens"

with open(path_vectors_train, 'rb') as file:
        X_train = pickle.load(file)   
with open(path_to_labels, 'rb') as file:
        y_train = pickle.load(file)
        
with open(path_vectors_valid, 'rb') as file:
        X_valid = pickle.load(file)
with open(valid_labels_path, 'rb') as file:
        y_valid = pickle.load(file)
        
with open(path_vectors_test, 'rb') as file:
        X_test = pickle.load(file)
with open(test_labels_path, 'rb') as file:
        y_test = pickle.load(file)

X_train = np.stack(X_train, axis=0)
X_test = np.stack(X_test, axis=0)
X_valid = np.stack(X_valid, axis=0)

y_train = np.stack(y_train, axis=0)
y_test = np.stack(y_test, axis=0)
y_valid = np.stack(y_valid, axis=0)

print()
#Finding loss on test set
preds = model.evaluate(X_test, y_test)
print ("Loss on testing set= " + str(preds[0]))
print("Accuracy on testing set =", preds[1])

# Make predictions
predictions = model.predict(X_test)
# print(predictions)
predicted_labels = np.argmax(predictions, axis=1)
real_labels = np.argmax(y_test, axis=1)

# Map predicted labels to characters
predicted_characters = [character[label] for label in predicted_labels]
actual_characters = [character[label] for label in real_labels]

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
plt.plot(range(1, len(amount)), amount[1:])
plt.xlabel('Number of characters')
plt.ylabel('Percentage of correctness')
plt.title('Correctly Guessed Characters in Captchas')
plt.show()
