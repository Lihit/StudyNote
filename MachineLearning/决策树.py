from sklearn.feature_extraction import DictVectorizer
import csv
from sklearn import preprocessing
from sklearn import tree
from sklearn.externals.six import StringIO
import numpy as np

allElectronicsData=open('test.csv')
reader=csv.reader(allElectronicsData)
headers=next(reader)

print(headers)
featureList=[]
labelList=[]
for row in reader:
    labelList.append(row[len(row)-1])
    rowDict={}
    for i in range(1,len(row)-1):
        rowDict[headers[i]]=row[i]
    featureList.append(rowDict)

print(featureList)
print(labelList)

vec=DictVectorizer()
dummyX=vec.fit_transform(featureList).toarray()
print(dummyX)
print(vec.get_feature_names())

lb=preprocessing.LabelBinarizer()
dummyY=lb.fit_transform(labelList)
print(dummyY)

clf=tree.DecisionTreeClassifier(criterion='entropy')
clf=clf.fit(dummyX,dummyY)
print(clf)

with open('test.dot','w') as f:
    f=tree.export_graphviz(clf,feature_names=vec.get_feature_names(),out_file=f)

newRowX=dummyX[0,:]
newRowX[0]=1
newRowX[2]=0
print(newRowX)
predictedY=clf.predict(np.atleast_2d(newRowX))
print(predictedY)