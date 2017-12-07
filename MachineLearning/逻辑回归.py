import numpy as np
import random
def gradientDescent(x,y,theta,alpha,m,numIterations):
    xTrans=x.transpose()
    for i in range(numIterations):
        hypothesis=np.dot(x,theta)
        loss=hypothesis-y
        cost=np.sum(loss**2)/(2*m)
        print("Iteration %d / cost %f"%(i,cost))
        gradient=np.dot(xTrans,loss)/m
        theta=theta-alpha*gradient
    return theta
def genData(numPoints,bias,variance):
    x=np.zeros(shape=(numPoints,2))
    y=np.zeros(shape=numPoints)
    for i in range(numPoints):
        x[i][0]=1
        x[i][1]=i
        y[i]=(i+bias)+random.uniform(0,1)*variance
    return x,y

def main1():
    x,y=genData(100,25,10)
    print('x:')
    print(x)
    print('y:')
    print(y)
    m,n=x.shape

    numIterations=10000
    alpha=0.0005
    theta=np.ones(n)
    theta=gradientDescent(x,y,theta,alpha,m,numIterations)
    print(theta)
if __name__=='__main__':
    main1()