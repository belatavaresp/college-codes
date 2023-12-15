# Problem Description: CAPTCHA Character Recognition

## Task
Implement two methods that, given an input image, recognize each of the six characters in the CAPTCHA. The first method should use the HOG descriptor covered in class and a classifier of your choice. The second method should involve the use of convolutional neural networks (CNNs). Although the second method is expected to achieve better results, carefully chosen configurations for the first method (HOG + classifier) can lead to results only slightly below those obtained by the second method.

The images containing the CAPTCHAs are available in three directories: training, validation, and test. Any learning should be done only with the images in the training directory, and any parameter validation should be done only with images from the validation directory. Images from the test directory cannot be used for learning or validation; they should only be used for method evaluation (as described below).

After training and validation, your method should load each image from the test directory and perform character recognition on each of them, generating an output that displays the image above a string with the recognized characters.

Additionally, generate a graph showing the recognition rate as a function of the minimum number of characters correctly recognized per captcha, according to the correct recognition (ground-truth) available in the labels10k directory. The example in Figure 3 indicates that only 40% of the time, three or more characters from a captcha are correctly recognized, and only 10% of the time all six characters from a captcha are correctly recognized. The ideal graph would be one where all values on the x-axis correspond to the value 1 on the y-axis (all characters are being recognized correctly).
