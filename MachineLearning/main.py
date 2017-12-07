from numpy import genfromtxt
import numpy as np
from sklearn import datasets,linear_model

def main():
    """
    简单应用
    :return: 
    """
    dataPath='mydata.csv'
    deliveryData=genfromtxt(dataPath,deletechars=',')
    x=deliveryData[:,:-1]
    y=deliveryData[:,-1]

    regr=linear_model.LinearRegression()
    regr.fit(x,y)

    print(regr.coef_)
    print(regr.intercept_)

if __name__ == '__main__':
    main()