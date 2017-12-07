import time

import numpy as np
import matplotlib.pyplot as plt

from sklearn.cluster import MiniBatchKMeans, KMeans
from sklearn.metrics.pairwise import pairwise_distances_argmin
from sklearn.datasets.samples_generator import make_blobs

from sklearn.externals import joblib
import numpy

def main1():
    # 获取数据
    np.random.seed(0)

    batch_size = 45
    centers = [[1, 1], [-1, -1], [1, -1]]


    n_clusters = len(centers)
    X, labels_true = make_blobs(n_samples=3000, centers=centers, cluster_std=0.7)

# kmeans
# Compute clustering with Means

    k_means = KMeans(init='k-means++', n_clusters=3, n_init=10)
    t0 = time.time()
    k_means.fit(X)
    t_batch = time.time() - t0

# MiniBatchKMeans

    mbk = MiniBatchKMeans(init='k-means++', n_clusters=3, batch_size=batch_size,
                      n_init=10, max_no_improvement=10, verbose=0)
    t0 = time.time()
    mbk.fit(X)
    t_mini_batch = time.time() - t0

def main2():
    ## step 1: 加载数据
    print("step 1: load data...")
    dataSet = []
    fileIn = open('./data.txt')
    for line in fileIn.readlines():
        lineArr = line.strip().split(' ')
        dataSet.append([float(lineArr[0]), float(lineArr[1])])

    #设定不同k值以运算
    for k in range(2,10):
        clf = KMeans(n_clusters=k) #设定k  ！！！！！！！！！！这里就是调用KMeans算法
        s = clf.fit(dataSet) #加载数据集合
        numSamples = len(dataSet)
        centroids = clf.labels_
        print(centroids,type(centroids)) #显示中心点
        print(clf.inertia_)  #显示聚类效果
        mark = ['or', 'ob', 'og', 'ok', '^r', '+r', 'sr', 'dr', '<r', 'pr']
        #画出所有样例点 属于同一分类的绘制同样的颜色
        for i in range(numSamples):
            #markIndex = int(clusterAssment[i, 0])
            plt.plot(dataSet[i][0], dataSet[i][1], mark[clf.labels_[i]]) #mark[markIndex])
        mark = ['Dr', 'Db', 'Dg', 'Dk', '^b', '+b', 'sb', 'db', '<b', 'pb']
        # 画出质点，用特殊图型
        centroids =  clf.cluster_centers_
        for i in range(k):
            plt.plot(centroids[i][0], centroids[i][1], mark[i], markersize = 12)
            #print centroids[i, 0], centroids[i, 1]
        plt.show()
if __name__ == '__main__':
    main1()
