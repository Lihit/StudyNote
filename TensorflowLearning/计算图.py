import tensorflow as tf


def main1():
    '''
    简单入门
    '''
    a = tf.constant(1, name='a')
    b = tf.constant(111, name='b')
    result = tf.add(a, b)
    print(a.graph is tf.get_default_graph())
    with tf.Session() as sess:
        print(sess.run(result))


def main2():
    '''
    计算图的使用
    建立两张不同的图
    '''
    g1 = tf.Graph()
    with g1.as_default():
        #v = tf.Variable(tf.zeros(shape=[1]), name='v')
        v=tf.get_variable("v",shape=[1],initializer=tf.zeros_initializer())
        #tf.get_variable(tf.zeros_initializer())

    g2 = tf.Graph()
    with g2.as_default():
        v=tf.get_variable("v",shape=[1],initializer=tf.ones_initializer())

    with tf.Session(graph=g1) as sess:
        tf.global_variables_initializer().run()
        with tf.variable_scope("",reuse=True):
            print(sess.run(tf.get_variable('v')))
    with tf.Session(graph=g2) as sess:
        tf.global_variables_initializer().run()
        with tf.variable_scope("",reuse=True):
            print(sess.run(tf.get_variable('v')))

def main3():
    '''
    可以指定计算运行的设备
    '''
    a = tf.constant(1, name='a')
    b = tf.constant(111, name='b')
    result = tf.add(a, b)
    print(a.graph is tf.get_default_graph())
    with tf.Session() as sess:
        with tf.device('/cpu:0'):
            print(sess.run(result))

if __name__ == "__main__":
    main3()
