import tensorflow as tf 

def main1():
    '''
    看看张量是什么
    '''
    a = tf.constant([11], name='a')
    b = tf.constant([111], name='b')
    result = tf.add(a, b,name='add_result')
    print(result)
    print(type(result.shape))
    print(result.get_shape())
    print(result.shape[0])
    print(result.name)
    print(result.dtype)

def main2():
    '''
    会话的使用
    交互会话tf.InteractiveSession()
    '''
    a = tf.constant([11], name='a')
    b = tf.constant([111], name='b')
    result = tf.add(a, b,name='add_result')
    sess=tf.InteractiveSession()
    print(result.eval())
    sess.close()

if __name__=='__main__':
    main2()