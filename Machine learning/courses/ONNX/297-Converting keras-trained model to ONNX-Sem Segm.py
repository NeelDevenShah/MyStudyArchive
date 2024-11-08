# https://youtu.be/3L1fRBLssAk
"""
Author: Dr. Sreenivas Bhattiprolu 

Semantic segmentation using ONNX model
A complete project that walks through the process of training a keras model using
data augmentation, exporting it to ONNX, and segmenting using the ONNX model. 

In this project, we will be working with Mitochondria data set https://www.epfl.ch/labs/cvlab/data/data-em/
We will be using small dataset (12 images and masks of 768x1024 each - further divided into 256x256 patches)
Augmentation is used to artifically enhance the number of training images. 
NOTE: While augmentation helps, you cannot augment your way out of having limited training data.

We will use a simple 2D U-net model for segmentation.

The trained model will be saved as a keras (.h5) model.
We will segment a few images using the trained keras model. 

This model will then be saved as ONNX. 
The ONNX model will be used to segment some images. 

"""

from simple_unet_model import simple_unet_model  #Our model saved in the accompanying python file
import numpy as np
from matplotlib import pyplot as plt
from patchify import patchify
import tifffile as tiff

#I saved 12 random images and corresponding masks into a tiff stack.
#Here, let us load the image and mask stacks.
large_image_stack = tiff.imread('small_dataset_for_training/images/12_training_mito_images.tif')
large_mask_stack = tiff.imread('small_dataset_for_training/masks/12_training_mito_masks.tif')

##########
#Divide images and masks into smaller patches (e.g., 256x256)
#You can use patchify library if you want
all_img_patches = []
for img in range(large_image_stack.shape[0]):
    #print(img)     #just stop here to see all file names printed
     
    large_image = large_image_stack[img]
    
    patches_img = patchify(large_image, (256, 256), step=256)  #Step=256 for 256 patches means no overlap
    

    for i in range(patches_img.shape[0]):
        for j in range(patches_img.shape[1]):
            
            single_patch_img = patches_img[i,j,:,:]
            single_patch_img = (single_patch_img.astype('float32')) / 255.
            
            all_img_patches.append(single_patch_img)

images = np.array(all_img_patches)
images = np.expand_dims(images, -1)

all_mask_patches = []
for img in range(large_mask_stack.shape[0]):
    #print(img)     #just stop here to see all file names printed
     
    large_mask = large_mask_stack[img]
    
    patches_mask = patchify(large_mask, (256, 256), step=256)  #Step=256 for 256 patches means no overlap
    

    for i in range(patches_mask.shape[0]):
        for j in range(patches_mask.shape[1]):
            
            single_patch_mask = patches_mask[i,j,:,:]
            single_patch_mask = single_patch_mask / 255.
            
            all_mask_patches.append(single_patch_mask)

masks = np.array(all_mask_patches)
masks = np.expand_dims(masks, -1)

print(images.shape)
print(masks.shape)
print("Pixel values in the mask are: ", np.unique(masks))
##########

#Split images/masks into train and test data
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(images, masks, test_size = 0.25, random_state = 0)
print(X_train.shape)
print(X_test.shape)

################
#Import the U-net model

IMG_HEIGHT = images.shape[1]
IMG_WIDTH  = images.shape[2]
IMG_CHANNELS = images.shape[3]

def get_model():
    return simple_unet_model(IMG_HEIGHT, IMG_WIDTH, IMG_CHANNELS)

model = get_model()

#################
#Sanity check, view few mages
import random
import numpy as np
image_number = random.randint(0, len(X_train))
plt.figure(figsize=(12, 6))
plt.subplot(121)
plt.imshow(np.reshape(X_train[image_number], (256, 256)), cmap='gray')
plt.subplot(122)
plt.imshow(np.reshape(y_train[image_number], (256, 256)), cmap='gray')
plt.show()

###############
#Define generators for data augmentation
#New generator with rotation and shear where interpolation that comes with rotation and shear are thresholded in masks. 
#This gives a binary mask rather than a mask with interpolated values. 
seed=24
from tensorflow.keras.preprocessing.image import ImageDataGenerator

img_data_gen_args = dict(rotation_range=90,
                     width_shift_range=0.3,
                     height_shift_range=0.3,
                     shear_range=0.5,
                     zoom_range=0.3,
                     horizontal_flip=True,
                     vertical_flip=True,
                     fill_mode='reflect')

mask_data_gen_args = dict(rotation_range=90,
                     width_shift_range=0.3,
                     height_shift_range=0.3,
                     shear_range=0.5,
                     zoom_range=0.3,
                     horizontal_flip=True,
                     vertical_flip=True,
                     fill_mode='reflect',
                     preprocessing_function = lambda x: np.where(x>0, 1, 0).astype(x.dtype)) #Binarize the output again. 

image_data_generator = ImageDataGenerator(**img_data_gen_args)
image_data_generator.fit(X_train, augment=True, seed=seed)

image_generator = image_data_generator.flow(X_train, seed=seed)
valid_img_generator = image_data_generator.flow(X_test, seed=seed)

mask_data_generator = ImageDataGenerator(**mask_data_gen_args)
mask_data_generator.fit(y_train, augment=True, seed=seed)
mask_generator = mask_data_generator.flow(y_train, seed=seed)
valid_mask_generator = mask_data_generator.flow(y_test, seed=seed)

def my_image_mask_generator(image_generator, mask_generator):
    train_generator = zip(image_generator, mask_generator)
    for (img, mask) in train_generator:
        yield (img, mask)

my_generator = my_image_mask_generator(image_generator, mask_generator)

validation_datagen = my_image_mask_generator(valid_img_generator, valid_mask_generator)


x = image_generator.next()
y = mask_generator.next()
for i in range(0,1):
    image = x[i]
    mask = y[i]
    plt.subplot(1,2,1)
    plt.imshow(image[:,:,0], cmap='gray')
    plt.subplot(1,2,2)
    plt.imshow(mask[:,:,0])
    plt.show()
#################################

#Train the keras model

batch_size = 16
steps_per_epoch = 3*(len(X_train))//batch_size


history = model.fit(my_generator, validation_data=validation_datagen, 
                    steps_per_epoch=steps_per_epoch, 
                    validation_steps=steps_per_epoch, epochs=10)

#plot the training and validation accuracy and loss at each epoch
loss = history.history['loss']
val_loss = history.history['val_loss']
epochs = range(1, len(loss) + 1)
plt.plot(epochs, loss, 'y', label='Training loss')
plt.plot(epochs, val_loss, 'r', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

acc = history.history['accuracy']
val_acc = history.history['val_accuracy']

plt.plot(epochs, acc, 'y', label='Training acc')
plt.plot(epochs, val_acc, 'r', label='Validation acc')
plt.title('Training and validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()

###############################
#IOU
y_pred=model.predict(X_test)
y_pred_thresholded = y_pred > 0.5

intersection = np.logical_and(y_test, y_pred_thresholded)
union = np.logical_or(y_test, y_pred_thresholded)
iou_score = np.sum(intersection) / np.sum(union)
print("IoU socre is: ", iou_score)


model.save('mito_model_5epochs.h5')  #Save the keras model

#################################################################
#Segmentation using the saved keras model

#Load The saved keras model 
from tensorflow.keras.models import load_model
loaded_keras_model = load_model('mito_model_50epochs.h5', compile=False)


#Predict on a few images
#model = get_model()
#model.load_weights('mitochondria_50_plus_100_epochs.hdf5') #Trained for 50 epochs and then additional 100

test_img_number = random.randint(0, len(X_test))
test_img = X_test[test_img_number]
ground_truth=y_test[test_img_number]
test_img_norm=test_img[:,:,0][:,:,None]
test_img_input=np.expand_dims(test_img_norm, 0)
prediction = (loaded_keras_model.predict(test_img_input)[0,:,:,0] > 0.7).astype(np.uint8)

plt.figure(figsize=(16, 8))
plt.subplot(231)
plt.title('Testing Image')
plt.imshow(test_img[:,:,0], cmap='gray')
plt.subplot(232)
plt.title('Testing Label')
plt.imshow(ground_truth[:,:,0], cmap='gray')
plt.subplot(233)
plt.title('Prediction on test image')
plt.imshow(prediction, cmap='gray')

plt.show()

##################################
#Convert the keras model into onnx format and save the ONNX file
"""
Command line..
python -m tf2onnx.convert --saved-model tensorflow-model-path --output model.onnx
"""

import tf2onnx.convert
import onnx

#Load The saved model 
from tensorflow.keras.models import load_model
loaded_keras_model = load_model('mito_model_50epochs.h5')


onnx_model, _ = tf2onnx.convert.from_keras(loaded_keras_model)
onnx.save(onnx_model, 'onnx_model_50epochs.onnx')

#################################
#Segment images using the saved ONNX model

import onnxruntime

session = onnxruntime.InferenceSession("onnx_model_50epochs.onnx")
session.get_inputs()[0].shape
session.get_inputs()[0].type

input_name = session.get_inputs()[0].name
output_name = session.get_outputs()[0].name

test_img_number = random.randint(0, len(X_test))
test_img = X_test[test_img_number]
ground_truth=y_test[test_img_number]
test_img_norm=test_img[:,:,0][:,:,None]
test_img_input=np.expand_dims(test_img_norm, 0)


result = session.run([output_name], {input_name: test_img_input})

segmented = (result[0][0,:,:,0] >0.5).astype(np.uint8)

keras_prediction = (loaded_keras_model.predict(test_img_input)[0,:,:,0] > 0.5).astype(np.uint8)

plt.figure(figsize=(9, 9))
plt.subplot(221)
plt.title('Testing Image')
plt.imshow(test_img[:,:,0], cmap='gray')
plt.subplot(222)
plt.title('Testing Label')
plt.imshow(ground_truth[:,:,0], cmap='gray')
plt.subplot(223)
plt.title('Prediction usong ONNX')
plt.imshow(segmented, cmap='gray')
plt.subplot(224)
plt.title('Prediction using keras')
plt.imshow(keras_prediction, cmap='gray')

plt.show()



