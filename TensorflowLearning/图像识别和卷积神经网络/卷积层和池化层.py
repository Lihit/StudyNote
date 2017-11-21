import tensorflow as tf 

def main1():
    '''
　　　　　卷积层
    '''
    conv_weight=tf.Variable(tf.truncated_normal(shape=[5,5,3,16],stddev=0.1))
    conv_bias=tf.Variable(tf.truncated_normal(shape=[16],stddev=0.1))
    
    conv=tf.nn.conv2d(x_input,conv_weight,strides=[1,1,1,1],padding='SAME')
    
    ret_conv=tf.nn.relu(tf.nn.bias_add(conv,conv_bias))

def main2():
    '''
    池化层
    '''
    pool=tf.nn.max_pool(ret_conv,ksize=[1,3,3,1],strides=[1,1,1,1],padding='SAME')

if __name__ == '__main__':
    main()