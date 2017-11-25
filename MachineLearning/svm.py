# coding=utf-8
from sklearn import svm
import numpy as np
import matplotlib.pyplot as plt
import pylab as pl


def main1():
    '''
    binary classfication
    :return: None
    '''
    X = [[0, 0], [1, 0], [1, 1], [0, 1]]
    y = [0, 1, 0, 1]
    clf = svm.SVC()
    clf.fit(X, y)
    # predicted
    ret = clf.predict([[2, 1]])
    print(ret)
    # support_vector
    print(clf.support_vectors_)
    # index of support_vector
    print(clf.support_)
    # support vector of each class
    print(clf.n_support_)


def main2():
    '''
    multi-class classfication
    one-against-one
    :return: None
    '''
    X = [[0], [1], [2], [3]]
    y = [0, 1, 2, 3]
    clf = svm.SVC(decision_function_shape='ovo')  # one-vs-one
    clf.fit(X, y)
    ret = clf.predict([[3]])
    print(ret)
    dec = clf.decision_function([[3]])
    print(dec)
    print(dec.shape)

    clf.decision_function_shape = 'ovr'  # one-vs-rest
    dec = clf.decision_function([[3]])
    print(dec.shape)


def main3():
    '''
    LinearSVC 实现了“one-vs-the-rest”多类的策略，这样训练一个n_class个模型。如果仅仅有两个类，仅仅需要训练一个模型
    :return: None
    '''
    lin_clf = svm.LinearSVC()
    X = [[0], [1], [2], [3]]
    y = [0, 1, 2, 3]
    lin_clf.fit(X, y)
    dec = lin_clf.decision_function([[1]])
    print(lin_clf.predict([[1]]))
    print(dec.shape)


def main4():
    '''
    对于非平衡级分类超平面，使用不平衡SVC找出最优分类超平面，基本的思想是，我们先找到一个普通的分类超平面，自动进行校正，求出最优的分类超平面

    这里可以使用 SVC(kernel="linear")

    针对下面的svc可以使用 clf=SGDClassifier(n_iter=100,alpha=0.01)代替
    :return: 
    '''
    # we create 40 separable points
    rng = np.random.RandomState(0)
    n_samples_1 = 1000
    n_samples_2 = 100
    X = np.r_[1.5 * rng.randn(n_samples_1, 2), 0.5 * rng.randn(n_samples_2, 2) + [2, 2]]
    y = [0] * (n_samples_1) + [1] * (n_samples_2)

    # fit the model and get the separating hyperplane
    clf = svm.SVC(kernel='linear', C=1.0)
    clf.fit(X, y)

    w = clf.coef_[0]
    a = -w[0] / w[1]  # a可以理解为斜率
    xx = np.linspace(-5, 5)
    yy = a * xx - clf.intercept_[0] / w[1]  # 二维坐标下的直线方程

    # get the separating hyperplane using weighted classes
    wclf = svm.SVC(kernel='linear', class_weight={1: 10})
    wclf.fit(X, y)

    ww = wclf.coef_[0]
    wa = -ww[0] / ww[1]
    wyy = wa * xx - wclf.intercept_[0] / ww[1]  # 带权重的直线

    # plot separating hyperplanes and samples
    h0 = plt.plot(xx, yy, 'k-', label='no weights')
    h1 = plt.plot(xx, wyy, 'k--', label='with weights')
    plt.scatter(X[:, 0], X[:, 1], c=y)
    plt.legend()

    plt.axis('tight')
    plt.show()


def main5():
    '''
    svm implement linear regression
    :return: 
    '''
    ###############################################################################
    # Generate sample data
    X = np.sort(5 * np.random.rand(40, 1), axis=0)  # 产生40组数据，每组一个数据，axis=0决定按列排列，=1表示行排列
    y = np.sin(X).ravel()  # np.sin()输出的是列，和X对应，ravel表示转换成行

    ###############################################################################
    # Add noise to targets
    y[::5] += 3 * (0.5 - np.random.rand(8))

    ###############################################################################
    # Fit regression model
    svr_rbf = svm.SVR(kernel='rbf', C=1e3, gamma=0.1)
    svr_lin = svm.SVR(kernel='linear', C=1e3)
    svr_poly = svm.SVR(kernel='poly', C=1e3, degree=2)
    y_rbf = svr_rbf.fit(X, y).predict(X)
    y_lin = svr_lin.fit(X, y).predict(X)
    y_poly = svr_poly.fit(X, y).predict(X)

    ###############################################################################
    # look at the results
    lw = 2
    plt.scatter(X, y, color='darkorange', label='data')
    plt.hold('on')
    plt.plot(X, y_rbf, color='navy', lw=lw, label='RBF model')
    plt.plot(X, y_lin, color='c', lw=lw, label='Linear model')
    plt.plot(X, y_poly, color='cornflowerblue', lw=lw, label='Polynomial model')
    plt.xlabel('data')
    plt.ylabel('target')
    plt.title('Support Vector Regression')
    plt.legend()
    plt.show()


def main6():
    x = [[2, 0], [1, 1], [2, 3]]
    y = [0, 0, 1]
    clf = svm.SVC(kernel='linear')
    clf.fit(x, y)
    print(clf)
    print(clf.support_vectors_)
    print(clf.support_)
    print(clf.n_support_)


def main7():
    np.random.seed(0)
    x = np.r_[np.random.randn(20, 2) - [2, 2], np.random.randn(20, 2) + [2, 2]]
    y = [0] * 20 + [1] * 20
    clf = svm.SVC(kernel='linear')
    clf.fit(x, y)

    w = clf.coef_[0]
    a = -w[0] / w[1]
    xx = np.linspace(-5, 5)
    yy = a * xx - (clf.intercept_[0]) / w[1]
    print(yy)
    b1 = clf.support_vectors_[0]
    yy_down = a * xx + (b1[1] - a * b1[0])
    b2 = clf.support_vectors_[-1]
    yy_up = a * xx + (b2[1] - a * b2[0])

    print(yy_down)
    print(yy_up)
    pl.plot(xx, yy, 'r-')
    pl.plot(xx, yy_down, 'r--')
    pl.plot(xx, yy_up, 'r--')

    pl.scatter(clf.support_vectors_[:, 0], clf.support_vectors_[:, 1], s=80)
    pl.scatter(x[:, 0], x[:, 1], c=y, cmap=pl.cm.Paired)
    pl.axis('tight')
    pl.show()


if __name__ == '__main__':
    main7()
