import tensorflow as tf
from numpy.random import RandomState
import random


def main1():
    sess = tf.InteractiveSession()
    v1 = tf.constant([1, 22, 3, 44])
    v2 = tf.constant([11, 2, 33, 4])

    print(tf.where(tf.greater(v1, v2), v1, v2).eval())


def main2():
    '''
    自己定义损失函数
    '''
    batchSize = 128
    x = tf.placeholder(tf.float32, [None, 2], name='x_input')
    y_ = tf.placeholder(tf.float32, [None, 1], name='y_input')

    w = tf.Variable(tf.truncated_normal([2, 1], stddev=0.01), name='w')
    y = tf.matmul(x, w)

    loss_less = 10
    loss_more = 1
    loss = tf.reduce_sum(
        tf.where(tf.greater(y_, y), loss_less * (y_ - y), loss_more * (y - y_)))
    train_step = tf.train.AdamOptimizer(0.01).minimize(loss)

    rdm = RandomState(1)
    dataSet = 128
    X = rdm.rand(dataSet, 2)
    Y = [[x1 + x2 + rdm.rand() / 10.0 - 0.05] for (x1, x2) in X]

    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        for i in range(1001):
            start = (i * batchSize) % dataSet
            end = min(start + batchSize, dataSet)
            sess.run(train_step, feed_dict={
                     x: X[start:end], y_: Y[start:end]})
            print(sess.run(w))
if __name__ == '__main__':
    main2()
