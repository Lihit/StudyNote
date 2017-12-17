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
        img_resized = tf.image.resize_images(
            img_data, size=(300, 300), method=1)
        # print(img_resized.get_shape())
        # img_resized=tf.image.convert_image_dtype(img_resized,dtype=tf.uint8)
        img_resized = tf.image.resize_image_with_crop_or_pad(
            img_resized, 100, 100)
        img_resized = tf.image.central_crop(img_resized, 0.5)
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
        img_flipped = tf.image.flip_left_right(img_data)
        img_flipped = tf.image.flip_up_down(img_flipped)
        plt.imshow(img_flipped.eval())
        plt.show()


def main4():
    '''
    图像色彩调整
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('1.jpg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        # 亮度
        img_brightness = tf.image.adjust_brightness(img_data, 0.5)
        img_brightness = tf.image.random_brightness(img_data, 0.5)
        # img_flipped=tf.image.flip_up_down(img_flipped)
        # contrast
        img_cont = tf.image.adjust_contrast(img_data, 5)
        img_cont = tf.image.random_contrast(img_data, 1, 5)
        plt.imshow(img_cont.eval())
        plt.show()


def main5():
    '''
    图片标准化效果图
    '''
    image_raw_data = tf.gfile.FastGFile('4.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        adjusted = tf.image.per_image_whitening(img_data)
        plt.imshow(sess.run(adjusted))
        plt.show()

def main6():
    '''
    标注框和图像的随机裁剪
    :return: 
    '''
    image_raw_data = tf.gfile.FastGFile('4.jpeg', 'rb').read()
    with tf.Session() as sess:
        img_data = tf.image.decode_jpeg(image_raw_data)
        img_data=tf.image.resize_images(img_data,180,220,method=1)
        batched=tf.expand_dims(tf.image.convert_image_dtype(img_data,tf.float32),0)
        boxes=tf.constant([[[0.35,0.47,0.5,0.56],[0.35,0.47,0.5,0.56]]])
        rsult=tf.image.draw_bounding_boxes(batched,boxes)
        #可以通过提供标注框的方式来告诉随机采取图像的算法哪些部分是“有信息量”的
        begin,size,bbox_for_draw=tf.image.sample_distorted_bounding_box(tf.shape(img_data),bounding_boxes=boxes)
        batched = tf.expand_dims(tf.image.convert_image_dtype(img_data, tf.float32), 0)
        image_with_box=tf.image.draw_bounding_boxes(batched,bbox_for_draw)
        distorted_image=tf.slice(img_data,begin,size)
if __name__ == '__main__':
    main5()
