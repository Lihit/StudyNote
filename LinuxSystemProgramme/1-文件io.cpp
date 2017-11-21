#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * 创建一个文件
 */
void main1() {
    int ret = open("../touch.txt", O_CREAT, 0777);
    if (ret != -1) {
        printf("successfully touch a file-ret:%d!", ret);
    }
    close(ret);
}

/**
 * 读写文件
 */
void main2() {
    int ret = open("../touch.txt", O_WRONLY);
    if (ret == -1) {
        printf("open file error");
        return;
    }
    char *name[] = {"wen", "liu", "zhang"};
    for (int i = 0; i < 3; i++) {
        int f_ret = write(ret, name[i], strlen(name[i]) * sizeof(char));
        if (f_ret == -1) {
            printf("write file error!");
            break;
        }
        write(ret, "\n", 1);
    }
    close(ret);
}

/**
 * 实现文件的复制
 */
void main3() {
    int fd_src = open("../touch.txt", O_RDONLY);
    int fd_dst = open("../touch_copy.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int len = 0;
    char buf[100];
    while ((len = read(fd_src, buf, 10)) > 0) {
        printf("buf:%s buflen:%d\n", buf, len);
        write(fd_dst, buf, len);
    }
    close(fd_dst);
    close(fd_src);
}

/**
 * 堵塞读终端
 */
void main4() {
    char buf[10];
    int n;
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("read STDIN_FILENO");
        exit(1);
    }
    write(STDOUT_FILENO, buf, 10);
}
/**
 * 非堵塞读客户端
 */
#define MSG_TRY "try again\n"

void main5() {
    char buf[10];
    int fd, n;
    fd = open("/dev/tty2", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open /dev/tty2");
        exit(1);
    }
    tryagain:
    n = read(fd, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen((MSG_TRY)));
            goto tryagain;
        }
        perror("read /dev/tty2");
        exit(1);
    }
    write(STDOUT_FILENO,buf,n);
    close(fd);


}
/**
 * 用fcntl改变File Status Flag
 */
void main6(){
    char buf[10];
    int n;
    int flags;
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }
    tryagain:
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read stdin");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
}
/*octl用于向设备发控制和配置命令，有些命令也需要读写一些数据，但这些数据是
不能用read/write读写的，称为Out-of-band数据。也就是说，read/write读写的数据是
in-band数据，是I/O操作的主体，而ioctl命令传送的是控制信息，其中的数据是辅助的数
据。例如，在串口线上收发数据通过read/write操作，而串口的波特率、校验位、停止位通
过ioctl设置，A/D转换的结果通过read读取，而A/D转换的精度和工作频率通过ioctl设置*/
void main7(){
    struct  winsize size;
    if(isatty(STDOUT_FILENO)==0){
        exit(1);
    }
    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&size)<0){
        perror("ioctl error");
        exit(1);
    }
    printf("%d rows,%d cols\n",size.ws_row,size.ws_col);
}
int main() {
    main7();
}