import tensorflow as tf
import numpy as np
from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets


class MNIST_NET(object):

    def __init__(self, labelNum, keep_prob):
        self.labelNum = labelNum
        self.keep_prob = keep_prob

    def weight_variable(self, shape, name):
        return tf.Variable(tf.truncated_normal(shape=shape, stddev=0.1), name=name)

    def bias_variable(self, shape, name):
        return tf.constant(0.1, shape=shape, name=name)

    def interface(self, inputData):
        # 将输入reshape成合适的shape
        with tf.name_scope('input_data'):
            x_image = tf.reshape(inputData, shape=[-1, 28, 28, 1])

        # 第一层卷积层
        with tf.name_scope('conv1'):
            with tf.name_scope('weights'):
                W_conv1 = self.weight_variable([5, 5, 1, 32], 'W_conv1')
                tf.summary.histogram('weight', W_conv1)
            with tf.name_scope('biases'):
                b_conv1 = self.bias_variable([32], 'b_conv1')
                tf.summary.histogram('bias', b_conv1)
            conv1 = tf.nn.bias_add(tf.nn.conv2d(
                x_image, W_conv1, strides=[1, 1, 1, 1], padding='SAME'), b_conv1)
            conv1_relu = tf.nn.relu(conv1, name='conv1_relu')
            conv1_maxpool = tf.nn.max_pool(
                conv1_relu, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1],
                padding='SAME', name='conv1_maxpool')

        # 第二层卷积层
        with tf.name_scope('conv2'):
            with tf.name_scope('weights'):
                W_conv2 = self.weight_variable([5, 5, 32, 64], 'W_conv2')
                tf.summary.histogram('weight', W_conv2)
            with tf.name_scope('biases'):
                b_conv2 = self.bias_variable([64], 'b_conv2')
                tf.summary.histogram('bias', b_conv2)
            conv2 = tf.nn.bias_add(tf.nn.conv2d(
                conv1_maxpool, W_conv2, strides=[1, 1, 1, 1], padding='SAME'), b_conv2)
            conv2_relu = tf.nn.relu(conv2, name='conv2_relu')
            conv2_maxpool = tf.nn.max_pool(
                conv2_relu, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1],
                padding='SAME', name='conv2_maxpool')

        # 密集连接层(全连接层)
        with tf.name_scope('fc1'):
            conv2_maxpool_shape = conv2_maxpool.get_shape().as_list()
            nodesNum = conv2_maxpool_shape[
                1] * conv2_maxpool_shape[2] * conv2_maxpool_shape[3]
            conv2_maxpool_reshape = tf.reshape(
                conv2_maxpool, shape=[-1, nodesNum])
            with tf.name_scope('weights'):
                W_fc1 = self.weight_variable([nodesNum, 1024], 'W_fc1')
                tf.summary.histogram('weight', W_fc1)
            with tf.name_scope('biases'):
                b_fc1 = self.bias_variable([1024], 'b_fc1')
                tf.summary.histogram('bias', b_fc1)
            fc1 = tf.nn.relu(tf.matmul(conv2_maxpool_reshape,
                                       W_fc1) + b_fc1, name='fc1')
        # 防止过拟合，使用dropout
        fc1_drop = tf.nn.dropout(fc1, self.keep_prob, name='fc1_drop')

        # 输出层(全连接层)
        with tf.name_scope('fc2'):
            with tf.name_scope('weights'):
                W_fc2 = self.weight_variable([1024, self.labelNum], 'W_fc2')
                tf.summary.histogram('weight', W_fc2)
            with tf.name_scope('biases'):
                b_fc2 = self.bias_variable([self.labelNum], 'b_fc2')
                tf.summary.histogram('bias', b_fc2)
            with tf.name_scope('logits'):
                logits = tf.add(tf.matmul(fc1_drop, W_fc2),
                                b_fc2, name='logits')
                tf.summary.histogram('logits', logits)
        return logits

    def getAccuracy(self, logits, inputlabel):
        with tf.name_scope('accuracy'):
            logits_softmax = tf.nn.softmax(logits)
            logitsEqual = tf.equal(
                tf.argmax(logits_softmax, 1), tf.argmax(inputlabel, 1))
            acc = tf.reduce_mean(
                tf.cast(logitsEqual, 'float'), name='accuracy')
            tf.summary.scalar('acc', acc)
        return acc


def train():
    mnist = read_data_sets('MNIST_data/', one_hot=True)
    labelNum = 10
    learningRate = 0.01
    keep_prob = 1
    mynet = MNIST_NET(labelNum, keep_prob)
    inputData = tf.placeholder('float', shape=[None, 784], name='inputData')
    inputlabel = tf.placeholder(
        'float', shape=[None, labelNum], name='inputlabel')
    logits = mynet.interface(inputData)
    acc = mynet.getAccuracy(logits, inputlabel)
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=inputlabel,
                                                            logits=logits,
                                                            name='cross_entropy')
    with tf.name_scope('loss'):
        cross_entropy_mean = tf.reduce_mean(
            cross_entropy, name='cross_entropy_mean')
        tf.summary.scalar('cross_entropy_mean', cross_entropy_mean)
    train_optimizer = tf.train.GradientDescentOptimizer(learningRate).minimize(cross_entropy_mean,
                                                                               name='train_optimizer')
    saver = tf.train.Saver()
    merged = tf.summary.merge_all()
    with tf.Session() as sess:
        print('-------start training------')
        writer = tf.summary.FileWriter('MNIST_logs/', sess.graph)
        sess.run(tf.global_variables_initializer())
        for i in range(1001):
            batch = mnist.train.next_batch(50)
            [logits_val, acc_val, loss_val, _, summary_val] = sess.run([logits, acc, cross_entropy_mean, train_optimizer, merged],
                                                                       feed_dict={
                inputData: batch[0],
                inputlabel: batch[1]
            })
            writer.add_summary(summary_val, i)
            if i % 100 == 0:
                print('step:%d  loss:%f  acc:%f' % (i, loss_val, acc_val))
            if i == 1000:
                saver.save(sess, 'MNIST_models/MNIST-model', global_step=i)
        print('-------start validating------')
        acc_val = sess.run(acc,
                           feed_dict={
                               inputData: mnist.test.images,
                               inputlabel: mnist.test.labels
                           })
        print('test acc:%g' % acc_val)
if __name__ == '__main__':
    train()
