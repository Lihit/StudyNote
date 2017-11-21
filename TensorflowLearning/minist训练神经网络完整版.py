import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

INPUT_NODE = 784  # 输入层
OUTPUT_NODE = 10  # 输出层

LAYER1_NODE = 500  # 隐藏层节点
BATCH_SIZE = 100

LEARNING_RATE_BASE = 0.8  # 基础的学习率
LEARNING_RATE_DECAY = 0.99  # 学习率的衰减率
REGULARIZATION_RATE = 0.0001  # 正则化再损失函数中的系数
TRAINING_STEPS = 30000  # 训练的轮数
MOVING_AVERAGE_DECAY = 0.99  # 滑动平均衰减率


def interface(input_tensor, avg_class, weights1, biases1, weights2, biases2):
    if avg_class is None:
        layer1 = tf.nn.relu(tf.matmul(input_tensor, weights1) + biases1)
        return tf.matmul(layer1, weights2) + biases2
    else:
        layer1 = tf.nn.relu(tf.matmul(input_tensor, avg_class.average(
            weights1)) + avg_class.average(biases1))
        return tf.matmul(layer1, avg_class.average(weights2)) + avg_class.average(biases2)


def train(mnist):
    x = tf.placeholder(tf.float32, shape=[None, INPUT_NODE], name='x-input')
    y_ = tf.placeholder(tf.float32, shape=[None, OUTPUT_NODE], name='y-input')

    weights1 = tf.Variable(tf.truncated_normal(
        shape=[INPUT_NODE, LAYER1_NODE], stddev=0.1), name='weight1')
    biases1 = tf.Variable(tf.constant(0.1, shape=[LAYER1_NODE]), name='bias1')

    weights2 = tf.Variable(tf.truncated_normal(
        shape=[LAYER1_NODE, OUTPUT_NODE], stddev=0.1), name='weight2')
    biases2 = tf.Variable(tf.constant(0.1, shape=[OUTPUT_NODE]), name='bias2')

    y = interface(x, None, weights1, biases1, weights2, biases2)

    # 定义存储训练的轮数，一般设置为不可训练
    global_step = tf.Variable(0, trainable=False)
    # 初始化滑动平均类
    variable_average = tf.train.ExponentialMovingAverage(
        MOVING_AVERAGE_DECAY, global_step)

    # 在所有代表的神经网络参数的变量上使用滑动平均，其他辅助变量就不需要如global_step,
    # tf.trainable_variables返回的是图上的集合中所有的除了trainable=False的参数
    variable_average_op = variable_average.apply(tf.trainable_variables())

    average_y = interface(x, variable_average, weights1,
                          biases1, weights2, biases2)

    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(
        logits=y, labels=y_)
    cross_entropy_mean = tf.reduce_mean(cross_entropy)

    # 计算L2正则化
    regularizer = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    regularization = regularizer(weights1) + regularizer(weights2)
    loss = cross_entropy_mean + regularization

    # 设置学习率
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE_BASE, global_step, mnist.train.num_examples / BATCH_SIZE, LEARNING_RATE_DECAY)
    train_step = tf.train.GradientDescentOptimizer(
        learning_rate).minimize(loss, global_step=global_step)

    # 再训练神经网络时，没过一遍数据急需要通过反向传播来更新神经网络中的参数
    # 又要更新每一个参数的滑动平均值
    # 需要用到tf.group()
    train_op = tf.group(train_step, variable_average_op)

    # 判断华东平均模型的神经网路前向传播过程是否正确
    correction_prediction = tf.equal(
        tf.arg_max(y_, 1), tf.arg_max(average_y, 1))
    accuracy = tf.reduce_mean(tf.cast(correction_prediction, tf.float32))
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        validate_feed = {x: mnist.validation.images,
                         y_: mnist.validation.labels}
        test_feed = {x: mnist.test.images, y_: mnist.test.labels}
        for i in range(TRAINING_STEPS):
            if i % 100 == 0:
                validate_acc = sess.run(accuracy, feed_dict=validate_feed)
                print("step:%d\tvalidation_acc:%f" % (i, validate_acc))
            xs, ys = mnist.train.next_batch(BATCH_SIZE)
            sess.run(train_op, feed_dict={x: xs, y_: ys})
        test_acc = sess.run(accuracy, feed_dict=test_feed)
        print("test_acc:%f" % test_acc)


def main(argv=None):
    mnist = input_data.read_data_sets("MNIST/MNIST_data/", one_hot=True)
    train(mnist)

if __name__ == '__main__':
    tf.app.run()
