from numpy import genfromtxt
import numpy as np
from sklearn import datasets,linear_model
import os
def main():
    """
    简单应用
    :return: 
    """
    dataPath=os.path.join(os.getcwd(),'mydata.txt')
    deliveryData=np.loadtxt(dataPath,delimiter=',')
    print(deliveryData)
    x=deliveryData[:,:-2]
    y=deliveryData[:,-1]

    regr=linear_model.LinearRegression()
    regr.fit(x,y)

    print(regr.coef_)
    print(regr.intercept_)

if __name__ == '__main__':
    main()