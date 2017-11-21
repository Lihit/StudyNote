import tensorflow as tf


def main1():
    w = tf.constant([[1., 2.], [-3., -4.]])  # 需要是float类型的
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        print(sess.run(tf.contrib.layers.l2_regularizer(0.5)(w)))
        print(sess.run(tf.contrib.layers.l1_regularizer(0.5)(w)))


def get_weight(shape, lamda,name):
    var = tf.Variable(tf.random_normal(shape=shape), dtype=tf.float32,name=name)
    tf.add_to_collection('losses', tf.contrib.layers.l2_regularizer(lamda)(var))
    return var


def main2():
    x=tf.placeholder(dtype=tf.float32,shape=(None,2))
    y_=tf.placeholder(dtype=tf.float32,shape=(None,1))

    batch_size=8
    layer_dimension=[2,10,10,10,1]
    n_layers=len(layer_dimension)
    cur_layer=x
    in_dimension=layer_dimension[0]
    for i in range(1,n_layers):
        out_dimension=layer_dimension[i]
        weight=get_weight([in_dimension,out_dimension],0.001,'w%d'%i)
        bias=tf.Variable(tf.constant(0.1,shape=[out_dimension]),name='b%d'%i)
        cur_layer=tf.nn.relu(tf.matmul(cur_layer,weight)+bias)
        in_dimension=out_dimension[i]
    mse_loss=tf.reduce_mean(tf.square(y_-cur_layer))
    tf.add_to_collection('losses',mse_loss)
    loss=tf.add_n(tf.get_collection('losses'))

if __name__ == '__main__':
    main1()
