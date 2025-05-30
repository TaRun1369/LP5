# -*- coding: utf-8 -*-
"""DL3_khudse.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1vo4PtBQ0zx1Z0qCkSZRM_U0ra9tFhr8k
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

train = pd.read_csv("/content/fashion-mnist_train.csv")
test = pd.read_csv("/content/fashion-mnist_test.csv")

train.head()

test.head()

train.info()

test.info()

x_train = train.drop("label",axis = 1)
y_train = train['label']
x_test = test.drop("label",axis = 1)
y_test = test['label']

x_train = x_train.astype('float32')/255.0
x_test = x_test.astype('float32')/255.0

x_train_reshape = x_train.values.reshape(-1,28,28,1)
x_test_reshape = x_test.values.reshape(-1,28,28,1)

labels = ['t-shirts','trouser','pullover','dress','coat','sandal','shirt','sneaker','bag','boots']

for i in range(9):
  plt.subplot(3,3,i+1)
  plt.imshow(x_train_reshape[i])
  plt.title(labels[y_train[i]])

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D,MaxPooling2D,Flatten,Dense

model = Sequential()
model.add(Conv2D(filters = 64,kernel_size = (3,3),activation = 'relu',input_shape = (28,28,1)))
model.add(MaxPooling2D(pool_size = (2,2)))
model.add(Flatten())
model.add(Dense(128,activation = 'relu'))
model.add(Dense(10,activation = 'softmax'))
model.compile(optimizer = 'adam',loss = 'sparse_categorical_crossentropy',metrics = ['accuracy'])

model.summary()

model.fit(x_train_reshape,y_train,epochs = 5)

model.evaluate(x_test_reshape,y_test)

predictions = model.predict(x_test_reshape[11:12])
label = labels[np.argmax(predictions)]
print(label)
plt.imshow(x_test_reshape[11:12][0])

