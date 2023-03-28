# NN-neighbor_machine_learning
_________________________________________________________________________

Solution:


Dataset
Best Feature Set
Accuracy
Small data #30
Forward selection = {9,3,8}
0.95
Small data #30
Backward elimination = {10, 8 ,6, 5, 3, 2}
0.86
Large data #30
Forward selection = {6,2}
0.965
Large data #30
Backward elimination = {40,39,37,36,35,34,33,32,31,30,29,28,27,26,23,20,19,18,17,16,15,14,13,12,11,9,7,6,4,2}
0.784


Introduction

The program is designed to look through a given dataset and determine the best features set. It then can be used to estimate the class of future items with the best features. To compute the possibilities to correctly classify an item of each feature, the program needs to find each item’s features nearest neighbour and if it is correctly classified. The total number of correctly classified classes divided by the total number of data will be the probability. 

 
Challenges

The challenges of the program are mostly the program designs in my opinion. Since C++ classification and libraries are a bit different from Python, the value types have to be accurate while calculating the shortest distance. I have caused a bug in my old code simply due to a valuable type of integer changing my classification correctness. Moreover, C++ doesn’t have a numpy library, so I wrote a function to loop and calculate the features distance.

Code Design

The code design has been generalised to accept different sizes of dataset, which in a format of first column being the class (in integer) and the columns after it are the features’ data. I designed it to store the dataset into a vector of integer vectors. Data[i][0] will be the class label of item i and Data[i][j] will be the value of item i’s feature j.
 
Dataset details

Small_data__30.txt: 10 features, 40 instances

X-axis: feature 8, y-axis: feature 3


Large_data__30.txt: 40 features. 100 instances

X-axis: feature 6, y-axis: feature 2


Algorithm

Forward selection and backward elimination use similar approaches to calculate the possibility of correct classification. Forward checks each new feature from empty initial and adds the best one, while backward checks all features as initial and eliminates one feature to find the best one.

Analysis 

Experiment 1: Comparing Forward Selection vs Backward Elimination

	Without feature selection, the P(class) will always be the highest number of classes in the dataset. On the other hand, feature selection draws a linear classification and reduces the chance to incorrectly classify an instance based on how identical the feature is.

	Forward selection generates the highest accuracy faster than backward elimination, while backward elimination is slower but it has a bigger feature with highest local accuracy than forward.

	Backward starts with aff features and eliminates the least relevant feature, but it is generally slower than forward. On the other hand, Forward is faster in computing accuracy but adding new features may make other added features less significant.

Experiment 2: Effect of normalisation

	The accuracy might differ between normalisation and without normalisation, since normalisation reduces redundant data.

Experiment 3: Effect of number neighbours (k)

Larger values of k will reduce the influences of noise instances. 
 
Conclusion

After making the program into work, I have realised how much more I will need to practise and learn to make more practical code that can deal with problems with large data. The generalisation part definitely becomes more important. The forward and backward algorithms as well as writing function class to compute matrices are definitely a good practice of my coding structure and refresh my knowledge.

The potential improvements are improving the runtime of matrix distance calculations. Better classification and data organisation can also be done for clearer code and future modification of the code.
 
Trace of my dataset


Forward selection with small data set, #30:



Forward selection with large data set, #30:


Backward Elimination with small data set, #30:



Backward Elimination with large data set, #30:

