import cv2
import numpy as np
import pickle
import os
import string

def preprocess(image):
    _, thresholded_image = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    kernel = np.ones((3, 3), np.uint8)
    denoised_image = cv2.morphologyEx(thresholded_image, cv2.MORPH_CLOSE, kernel)
    # image = resize(denoised_image, (128,64))
    denoised_image = denoised_image / 255.0
    return denoised_image

def calculate_features(image, all_features):
    # segmentação
    image = image[:, 12:]
    tile_width = image.shape[1] // 6

    for x in range(0, image.shape[1], tile_width):
        left = x
        right = x + tile_width

        section = image[:, left:right]
        all_features.append(section)

def get_training_set(path_to_images, path_to_labels, path_save_vectors=None, path_save_labels=None):
    files = os.listdir(path_to_images)
    files.sort()
    
    files_labels = os.listdir(path_to_labels)
    files_labels.sort()

    all_features = []
    all_labels = []

    for file in files:
        file_path = os.path.join(path_to_images, file)
        with open(file_path, "r") as f:
            img = cv2.imread(file_path, 0)
            img = preprocess(img)
            calculate_features(img, all_features)
            
    for file in files_labels:
        file_path_label = os.path.join(path_to_labels, file)
        with open(file_path_label, "r") as f:
            content = f.read().replace('\n', '')
            label = [character.find(k) for k in content]  # Convert label characters to indices
            one_hot_label = np.zeros((len(content), nchar))
            one_hot_label[np.arange(len(content)), label] = 1  # Perform one-hot encoding
            all_labels.extend(one_hot_label)

    if path_save_vectors:
        with open(path_save_vectors, 'wb') as file:
            pickle.dump(all_features, file)

    if path_save_labels:
        with open(path_save_labels, 'wb') as file:
            pickle.dump(all_labels, file)

    return all_features, all_labels

# Assume nchar and character are defined as before
nchar = 36
character = string.ascii_uppercase + "0123456789"

path_to_images = "./treinamento_imags" # trocar para "dados/CAPTCHA-10k/treinamento"
path_to_labels = "./treinamento_labels" # trocar para "dados/CAPTCHA-10k/labels"
path_vectors_train = "./bin/treinamentoCNN_imagens"
path_labels_train = "./bin/treinamentoCNN_labels_file"

test_images = "./validacao_imags"
test_labels = "./validacao_labels"
path_vectors_valid = "./bin/validacaoCNN_imagens"
path_labels_valid = "./bin/validacaoCNN_labels_file"

path_to_test_images = "./teste_imags" # trocar para "dados/CAPTCHA-10k/treinamento"
path_to_test_labels = "./teste_labels" # trocar para "dados/CAPTCHA-10k/labels"
path_vectors_test = "./bin/testeCNN_imagens"
path_labels_test = "./bin/testeCNN_labels_file"

print("Recolhendo os dados para treinamento\n")
features, labels = get_training_set(path_to_images, path_to_labels, path_vectors_train, path_labels_train)

print("Recolhendo os dados para validacao\n")
valid_features, valid_labels = get_training_set(test_images, test_labels,path_vectors_valid, path_labels_valid)

print("Recolhendo os dados para teste\n")
features, labels = get_training_set(path_to_test_images, path_to_test_labels, path_vectors_test, path_labels_test)
