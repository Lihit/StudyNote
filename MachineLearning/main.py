# coding=utf-8
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
from sklearn.datasets.samples_generator import make_classification
from matplotlib.colors import ListedColormap
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import classification_report
from sklearn.cross_validation import train_test_split
import numpy as np


def main1():
    '''
    generate random data
    knn to predict
    plot the map
    :return: 
    '''
    # X为样本特征，Y为样本类别输出， 共1000个样本，每个样本2个特征，输出有3个类别，没有冗余特征，每个类别一个簇
    X, Y = make_classification(n_samples=1000, n_features=2, n_redundant=0,
                               n_clusters_per_class=1, n_classes=3)
    # plt.scatter(X[:, 0], X[:, 1], marker='o', c=Y)
    # plt.show()
    clf = KNeighborsClassifier(n_neighbors=5, weights='distance')
    clf.fit(X, Y)
    cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA', '#AAAAFF'])
    cmap_bold = ListedColormap(['#FF0000', '#00FF00', '#0000FF'])

    # 确认训练集的边界
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    # 生成随机数据来做测试集，然后作预测
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.02),
                         np.arange(y_min, y_max, 0.02))
    print(xx)
    print(yy)
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])

    # 画出测试集数据
    Z = Z.reshape(xx.shape)
    plt.figure()
    plt.pcolormesh(xx, yy, Z, cmap=cmap_light)

    # 也画出所有的训练集数据
    plt.scatter(X[:, 0], X[:, 1], c=Y, cmap=cmap_bold)
    plt.xlim(xx.min(), xx.max())
    plt.ylim(yy.min(), yy.max())
    plt.title("3-Class classification (k = 15, weights = 'distance')")
    plt.show()


def main2():
    '''
    
    :return: 
    '''
    ''''' 数据读入 '''
    data = []
    labels = []
    with open("1.txt") as ifile:
        for line in ifile:
            tokens = line.strip().split(' ')
            data.append([float(tk) for tk in tokens[:-1]])
            labels.append(tokens[-1])
    x = np.array(data)
    labels = np.array(labels)
    y = np.zeros(labels.shape)

    ''''' 标签转换为0/1 '''
    y[labels == 'fat'] = 1

    ''''' 拆分训练数据与测试数据 '''
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2)

    ''''' 创建网格以方便绘制 '''
    h = .01
    x_min, x_max = x[:, 0].min() - 0.1, x[:, 0].max() + 0.1
    y_min, y_max = x[:, 1].min() - 1, x[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                         np.arange(y_min, y_max, h))

    ''''' 训练KNN分类器 '''
    clf = KNeighborsClassifier(algorithm='kd_tree')
    clf.fit(x_train, y_train)

    '''''测试结果的打印'''
    answer = clf.predict(x)
    print(x)
    print(answer)
    print(y)
    print(np.mean(answer == y))

    '''''准确率与召回率'''
    precision, recall, thresholds = precision_recall_curve(y_train, clf.predict(x_train))
    answer = clf.predict_proba(x)[:, 1]
    #print(classification_report(y, answer, target_names=['thin', 'fat']))

    ''''' 将整个测试空间的分类结果用不同颜色区分开'''
    answer = clf.predict_proba(np.c_[xx.ravel(), yy.ravel()])[:, 1]
    z = answer.reshape(xx.shape)
    plt.contourf(xx, yy, z, cmap=plt.cm.Paired, alpha=0.8)

    ''''' 绘制训练样本 '''
    plt.scatter(x_train[:, 0], x_train[:, 1], c=y_train, cmap=plt.cm.Paired)
    plt.xlabel(u'身高')
    plt.ylabel(u'体重')
    plt.show()


if __name__ == '__main__':
    main2()
