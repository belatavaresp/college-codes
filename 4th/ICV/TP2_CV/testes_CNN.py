import numpy as np
from keras.models import load_model, Model
from keras.layers import Dropout, BatchNormalization
from keras import layers
from sklearn.metrics import classification_report
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

def createmodel1():
    img = layers.Input(shape=(50, 28, 1))  # Change input shape
    conv1 = layers.Conv2D(32, (3, 3), activation='relu')(img)
    mp1 = layers.MaxPooling2D((2, 2))(conv1)
    conv2 = layers.Conv2D(64, (3, 3), activation='relu')(mp1)
    mp2 = layers.MaxPooling2D((2, 2))(conv2)
    conv3 = layers.Conv2D(64, (3, 3), activation='relu')(mp2)
    
    flat = layers.Flatten()(conv3)
    dense = layers.Dense(64, activation='relu')(flat)
    output = layers.Dense(nchar, activation='sigmoid')(dense)

    # Compile model and return it
    model = Model(img, output)
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=["accuracy"])
    return model

#Create model
model=createmodel()
model1 = createmodel1()

model = load_model("my_trained_model.h5")
#model1 = load_model("my_trained_model_1.h5")

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
preds = model.evaluate(X_train,y_train)
print("Loss on training set =", preds[0])
print("Accuracy on training set =", preds[1])

print()
#Finding loss on test set
preds = model.evaluate(X_valid, y_valid)
print ("Loss on validation set= " + str(preds[0]))
print("Accuracy on validation set =", preds[1])

print()
#Finding loss on test set
preds = model.evaluate(X_test, y_test)
print ("Loss on testing set= " + str(preds[0]))
print("Accuracy on testing set =", preds[1])

predictions = model.predict(X_test)
y_pred = np.argmax(predictions, axis=1)  # Assuming axis 2 corresponds to the one-hot encoded labels
y_true = np.argmax(y_test, axis=1)

y_pred_flat = y_pred.flatten()
y_true_flat = y_true.flatten()

print(classification_report(y_true_flat, y_pred_flat))

with open('./training_history.pk1', 'rb') as file:
        hist = pickle.load(file)  
 
#graph of loss vs epochs
for label in ["loss"]:
        plt.plot(hist[label],label=label)
plt.legend()
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.show()

#graph of accuracy vs epochs
for label in ["accuracy"]:
    plt.plot(hist[label], label=label)

plt.legend()
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.show()

#graph of loss vs epochs
for label in ["val_loss"]:
        plt.plot(hist[label],label=label)
plt.legend()
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.show()

#graph of accuracy vs epochs
for label in ["val_accuracy"]:
    plt.plot(hist[label], label=label)

plt.legend()
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.show()
