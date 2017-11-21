import tensorflow as tf


def main1():
    '''
    保存模型
    '''
    v1 = tf.Variable(tf.constant(1, shape=[1]), name='v1')
    v2 = tf.Variable(tf.constant(12, shape=[1]), name='v2')
    result = tf.add(v1, v2, name='result')
    saver = tf.train.Saver()
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        print(sess.run(result))
        saver.save(sess, 'model.ckpt')


def main2():
    '''
    恢复模型
    方法一：重复写之前的架构
    '''
    v1 = tf.Variable(tf.constant(1, shape=[1]), name='v1')
    v2 = tf.Variable(tf.constant(12, shape=[1]), name='v2')
    result = tf.add(v1, v2, name='result')
    saver = tf.train.Saver()
    with tf.Session() as sess:
        saver.restore(sess, 'model.ckpt')
        print(sess.run(result))
        saver.save(sess, 'model.ckpt')


def main3():
    '''
    回复模型
    方法2：直接加载已经持久化的图
    '''
    saver = tf.train.import_meta_graph('model.ckpt.meta')
    graph_default = tf.get_default_graph()
    with tf.Session() as sess:
        saver.restore(sess, 'model.ckpt')
        print(sess.run(graph_default.get_tensor_by_name('result:0')))


def main4():
    v = tf.Variable(0, dtype=tf.float32, name='v')
    for variable in tf.all_variables():
        print(variable.name)
    ema = tf.train.ExponentialMovingAverage(0.99)
    maintain_average_op = ema.apply(tf.all_variables())
    for variable in tf.all_variables():
        print(variable.name)
    saver = tf.train.Saver()
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        sess.run(tf.assign(v, 10))
        sess.run(maintain_average_op)
        saver.save(sess, 'model_new.ckpt')
        print(sess.run([v, ema.average(v)]))


def main5():
    v = tf.Variable(0, dtype=tf.float32, name='v')
    saver = tf.train.Saver({"v/ExponentialMovingAverage": v})
    with tf.Session() as sess:
        saver.restore(sess, 'model_new.ckpt')
        print(sess.run(v))


def main6():
    v = tf.Variable(0, dtype=tf.float32, name='v')
    ema = tf.train.ExponentialMovingAverage(0.99)
    print(ema.variables_to_restore())
    saver = tf.train.Saver(ema.variables_to_restore())
    with tf.Session() as sess:
        saver.restore(sess, 'model_new.ckpt')
        print(sess.run(v))

if __name__ == '__main__':
    main6()
