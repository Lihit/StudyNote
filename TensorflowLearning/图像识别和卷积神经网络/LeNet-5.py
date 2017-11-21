import tensorflow as tf

# 配置神经网络的参数
INPUT_NODE = 784
OUTPUT_NODE = 10

IMAGE_SIZE = 32
NUM_CHANNELS = 1
NUM_LABELS = 10


def interface(input_tensor, train, regularizer):
    with tf.variable_scope('layer1-conv1'):
        conv1_weights = tf.get_variable('weight', shape=[
                                        5, 5, 1, 6], initializer=tf.truncated_normal_initializer(stddev=0.1))
        if regularizer is not None:
            tf.add_to_collection('losses', conv1_weights)
        conv1_bias = tf.get_variable(
            'bias', shape=[32], initializer=tf.constant_initializer(0))
        conv1 = tf.nn.bias_add(tf.nn.conv2d(input_tensor, conv1_weights, strides=[
                               1, 1, 1, 1], padding='VALID'), conv1_bias, name='conv1')
        relu1 = tf.nn.relu(conv1, name='relu1')
    with tf.variable_scope('layer2-pool1'):
        pool1 = tf.nn.max_pool(relu1, ksize=[1, 2, 2, 1], strides=[
                               1, 2, 2, 1], padding='SAME', name='pool1')
    with tf.variable_scope('layer3-conv2'):
        conv2_weights = tf.get_variable('weight', shape=[
                                        5, 5, 6, 16], initializer=tf.truncated_normal_initializer(stddev=0.1))
        if regularizer is not None:
            tf.add_to_collection('losses', conv2_weights)
        conv2_bias = tf.get_variable(
            'bias', shape=[16], initializer=tf.constant_initializer(0))
        conv2 = tf.nn.bias_add(tf.nn.conv2d(pool1, conv2_weights, strides=[
                               1, 1, 1, 1], padding='VALID'), conv2_bias, name='conv2')
        relu2 = tf.nn.relu(conv2, name='relu2')
    with tf.variable_scope('layer4-pool2'):
        pool2 = tf.nn.max_pool(relu2, ksize=[1, 2, 2, 1], strides=[
                               1, 2, 2, 1], padding='SAME', name='pool2')
    pool2_shape = pool2.get_shape().as_list()
    pool2_nodes = pool2_shape[1] * pool2_shape[2] * pool2_shape[3]
    pool2_reshaped = tf.reshape(pool2, [pool2_shape[0], pool2_nodes])
    with tf.variable_scope('layer5-fc1'):
        fc1_weights = tf.get_variable('weight', shape=[
            pool2_nodes, 120], initializer=tf.truncated_normal_initializer(stddev=0.1))
        if regularizer is not None:
            tf.add_to_collection('losses', fc1_weights)
        fc1_bias = tf.get_variable(
            'bias', shape=[120], initializer=tf.constant_initializer(0))
        fc1 = tf.nn.relu(
            tf.matmul(pool2_shape, fc1_weights)+fc1_bias, name='fc1')
        if train:
            fc1 = tf.nn.dropout(fc1, 0.5)
    with tf.variable_scope('layer6-fc2'):
        fc2_weights = tf.get_variable('weight', shape=[
            120, 84], initializer=tf.truncated_normal_initializer(stddev=0.1))
        if regularizer is not None:
            tf.add_to_collection('losses', fc2_weights)
        fc2_bias = tf.get_variable(
            'bias', shape=[84], initializer=tf.constant_initializer(0))
        fc2 = tf.nn.relu(
            tf.matmul(fc1, fc2_weights)+fc2_bias, name='fc2')
        if train:
            fc2 = tf.nn.dropout(fc2, 0.5)
    with tf.variable_scope('layer7-fc3'):
        fc3_weights = tf.get_variable('weight', shape=[
            84, 10], initializer=tf.truncated_normal_initializer(stddev=0.1))
        if regularizer is not None:
            tf.add_to_collection('losses', fc3_weights)
        fc3_bias = tf.get_variable(
            'bias', shape=[10], initializer=tf.constant_initializer(0))
        logits=tf.matmul(fc2,fc3_weights)+fc3_bias
    return logits