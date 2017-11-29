from sklearn import neighbors
from sklearn import datasets

def main():
    knn=neighbors.KNeighborsClassifier()
    iris=datasets.load_iris()
    print(iris)
    print(type(iris))
    print(iris.data)
    print(iris.target)
    knn.fit(iris.data,iris.target)
    predictedLabel=knn.predict([[0.1,0.2,0.3,0.4]])
    print(predictedLabel)

if __name__=='__main__':
    main()