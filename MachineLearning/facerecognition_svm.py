from time import time
import logging
import matplotlib.pyplot as plt

from sklearn.cross_validation import train_test_split
from sklearn.datasets import fetch_lfw_people
from sklearn.grid_search import GridSearchCV
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.decomposition import RandomizedPCA
from sklearn.svm import SVC

def main():
    logging.basicConfig(level=logging.INFO, format="%(asctime)s %(message)s")

    # 在著名的人脸识别库(LFW)下载数据
    lfw_people = fetch_lfw_people(data_home='./lfw_home', min_faces_per_person=70, resize=0.4)
    n_samples, h, w = lfw_people.images.shape
    print(lfw_people.images[0].shape)
    print((n_samples, h, w))
    x = lfw_people.data
    n_features = x.shape[1]
    print(n_features)

    # 显示数据并划分
    y = lfw_people.target
    target_names = lfw_people.target_names
    n_classes = target_names.shape[0]
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.25)

    # 降维
    n_components = 150
    pca = RandomizedPCA(n_components=n_components, whiten=True).fit(x_train)
    eigenfaces = pca.components_.reshape((n_components, h, w))
    x_train_pca = pca.transform(x_train)
    x_test_pca = pca.transform(x_test)
    print(x_train_pca.shape[1])

    # 训练一个ｓｖｍ分类器
    param_grid = {'C': [1e3, 5e3, 1e4, 5e4, 1e5],
                  'gamma': [0.0001, 0.0005, 0.001, 0.005, 0.01, 0.1]}
    clf = GridSearchCV(SVC(kernel='rbf'), param_grid)
    clf = clf.fit(x_train_pca, y_train)
    print(clf.best_estimator_)

    # 开始测试
    y_pred = clf.predict(x_test_pca)
    print(classification_report(y_test, y_pred, target_names=target_names))
    print(confusion_matrix(y_test, y_pred, labels=range(n_classes)))
    prediction_titles = [title(y_pred, y_test, target_names, i) for i in range(y_pred.shape[0])]
    plot_gallery(x_test, prediction_titles, h, w)

    eigenface_titles = ["eigenface %d" % i for i in range(eigenfaces.shape[0])]
    plot_gallery(eigenfaces, eigenface_titles, h, w)
    plt.show()


def plot_gallery(images, titles, h, w, n_row=3, n_col=4):
    plt.figure(figsize=(1.8 * n_col, 2.4 * n_row))
    plt.subplots_adjust(bottom=0, left=0.01, right=0.99, top=0.90, hspace=0.35)
    for i in range(n_row * n_col):
        plt.subplot(n_row, n_col, i + 1)
        plt.imshow(images[i].reshape((h, w)), cmap=plt.cm.gray)
        plt.title(titles[i], size=12)
        plt.xticks()
        plt.yticks()


def title(y_pred, y_test, target_names, i):
    pre_name = target_names[y_pred[i]].rsplit(' ', 1)[-1]
    true_name = target_names[y_test[i]].rsplit(' ', 1)[-1]
    return "prediced:%s\ntrue:%s" % (pre_name, true_name)


if __name__ == '__main__':
    main()
