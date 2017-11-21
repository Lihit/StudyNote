import tensorflow as tf 

def main1():
    '''
    变量的使用
    '''
    #正态分布
    w1=tf.Variable(tf.random_normal([2,3],stddev=0.1,mean=0))
    w2=tf.Variable(tf.truncated_normal([2,3],stddev=0.1,mean=0))

    #平均分布
    w3=tf.Variable(tf.random_uniform([3,4],minval=-1,maxval=1))

    #用常数来初始化
    w4=tf.Variable(tf.zeros([2,3],tf.int32))
    w5=tf.Variable(tf.ones([1,2],tf.int32))
    w6=tf.Variable(tf.fill([4,5],9))
    w7=tf.Variable(tf.constant([1,2,3]))

    #用别的变量的初始值来初始化
    w8=tf.Variable(w1.initialized_value()*2.0)

    w_test=tf.Variable(tf.zeros([3]))
    print(w_test.get_shape)

def main2():
    '''
    矩阵相乘
    '''
    x1=tf.constant([[1.2,2.3]],name='x1')
    w1=tf.Variable(tf.random_normal([2,3],stddev=0.1),name='w1')
    y1=tf.matmul(x1,w1)
    w2=tf.Variable(tf.random_normal([3,1],stddev=0.1),name='w2')
    result=tf.matmul(y1,w2)
    sess=tf.InteractiveSession()
    tf.global_variables_initializer().run()
    print(result.eval())
    sess.close()


if __name__=='__main__':
    main2()