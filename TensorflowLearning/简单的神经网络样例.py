import tensorflow as tf 
import numpy as np 

def train():
    batchSize=8
    #定义好数据集
    dataSize=128
    rdm=np.random.RandomState(1)    
    x_=rdm.rand(dataSize,2)
    y_=[[int(x1+x2<1)] for (x1,x2) in x_]

    #搭建网络
    x_input=tf.placeholder(tf.float32,shape=[None,2],name='x_input')
    y_input=tf.placeholder(tf.float32,shape=[None,1],name='y_input')
    w1=tf.Variable(tf.truncated_normal(shape=[2,3],stddev=0.1),name='w1')
    y_hidden=tf.matmul(x_input,w1)
    w2=tf.Variable(tf.truncated_normal(shape=[3,1],stddev=0.1),name='w2')
    y=tf.matmul(y_hidden,w2)

    cross_entropy=-tf.reduce_mean(y_input*tf.log(tf.clip_by_value(y,1e-10,1.0)))
    train_step=tf.train.AdamOptimizer(0.001).minimize(cross_entropy)

    #开始训练
    init_op=tf.global_variables_initializer()
    with tf.Session() as sess:
        sess.run(init_op)
        for i in range(5000):
            begin_index=(batchSize*i)%dataSize
            end_index=min(begin_index+batchSize,dataSize)
            feed_dict={x_input:x_[begin_index:end_index],y_input:y_[begin_index:end_index]}
            [cross_entropy_val,_]=sess.run([cross_entropy,train_step],feed_dict=feed_dict)
            if i>0 and i%100==0:
                print("cross_entropy_val:"+str(cross_entropy_val))
                print("w1:")
                print(sess.run(w1))
                print("w2:")
                print(sess.run(w2))

if __name__=='__main__':
    train()