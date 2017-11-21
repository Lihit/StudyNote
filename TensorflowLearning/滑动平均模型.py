import tensorflow as tf 

def main1():
    v1=tf.Variable(0,dtype=tf.float32)
    step=tf.Variable(0,trainable=True)
    ema=tf.train.ExponentialMovingAverage(0.99,step)
    maintain_average_op=ema.apply([v1])
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        print(sess.run([v1,ema.average(v1)]))

        sess.run(tf.assign(v1,5))
        sess.run(maintain_average_op)
        print(sess.run([v1,ema.average(v1)]))

        sess.run(tf.assign(v1,10))
        sess.run(tf.assign(step,1000))
        sess.run(maintain_average_op)
        print(sess.run([v1,ema.average(v1)]))
        print(sess.run(step))

        sess.run(maintain_average_op)
        print(sess.run([v1,ema.average(v1)]))
        print(sess.run(step))

if __name__=='__main__':
    main1()