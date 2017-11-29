import tensorflow as tf
import matplotlib.pyplot as plt
import os


def main1():
    '''
    读取图片文件
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('images.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        print(img_data.eval())
        plt.imshow(img_data.eval())
        plt.show()
        # img_data=tf.image.convert_image_dtype(img_data,dtype=tf.float32)
        encoded_image = tf.image.encode_jpeg(img_data)
        with tf.gfile.GFile('out.jpeg', 'wb') as f:
            f.write(encoded_image.eval())


def main2():
    '''
    调整图片大小
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('images.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        print(img_data.eval())
        # plt.imshow(img_data.eval())
        # plt.show()
        img_resized = tf.image.resize_images(img_data,size=(300,300),method=1)
        # print(img_resized.get_shape())
        # img_resized=tf.image.convert_image_dtype(img_resized,dtype=tf.uint8)
        img_resized=tf.image.resize_image_with_crop_or_pad(img_resized,100,100)
        img_resized=tf.image.central_crop(img_resized,0.5)
        plt.imshow(img_resized.eval())
        plt.show()
def main3():
    '''
    图像翻转
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('images.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        img_flipped=tf.image.flip_left_right(img_data)
        img_flipped=tf.image.flip_up_down(img_flipped)
        plt.imshow(img_flipped.eval())
        plt.show()

def main4():
    '''
    图像色彩调整
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('images.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        #亮度
        img_brightness=tf.image.adjust_brightness(img_data,0.5)
        img_brightness=tf.image.random_brightness(img_data,0.5)
        # img_flipped=tf.image.flip_up_down(img_flipped)
        #contrast
        img_cont=tf.image.adjust_contrast(img_data,5)
        img_cont = tf.image.random_contrast(img_data, 1,5)
        plt.imshow(img_cont.eval())
        plt.show()

if __name__ == '__main__':
    main4()
