#importing libraries
import numpy as np 
import pickle
from keras.layers import Dropout, BatchNormalization
from keras import layers #for building layers of neural net
from keras.models import Model
import string

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

path_to_labels = "./bin/treinamentoCNN_labels_file" # trocar para "dados/CAPTCHA-10k/labels"
test_labels_path = "./bin/validacaoCNN_labels_file"
path_vectors_train = "./bin/treinamentoCNN_imagens"
path_vectors_valid = "./bin/validacaoCNN_imagens"

with open(path_vectors_train, 'rb') as file:
        X_train = pickle.load(file)   
with open(path_to_labels, 'rb') as file:
        y_train = pickle.load(file)
        
with open(path_vectors_valid, 'rb') as file:
        X_test = pickle.load(file)
with open(test_labels_path, 'rb') as file:
        y_test = pickle.load(file)

X_train = np.stack(X_train, axis=0)
X_test = np.stack(X_test, axis=0)

y_train = np.stack(y_train, axis=0)
y_test = np.stack(y_test, axis=0)

hist = model.fit(X_train, y_train, batch_size=32, epochs=15,validation_data=(X_test,y_test))

model.save("./my_trained_model_10_epochs.h5")

with open('./training_history_10_epochs.pk1', 'wb') as file:
	pickle.dump(hist.history, file)
