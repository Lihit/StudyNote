#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * stat
 * 查看文件的状态
 * int stat(const char *path, struct stat *buf);
 *int fstat(int fd, struct stat *buf);
 *int lstat(const char *path, struct stat *buf);
 */
void main1(){
    struct stat buf;
    int ret=stat("../touch.txt",&buf);
    printf("%d",buf.st_uid);
    time_t t=buf.st_ctime;
    printf("%f",t);
}

/**
 * access
 * chmod
 * chown
 */
void main2(){
    int ret=access("../touch1.txt",F_OK);
    if(ret<0){
        printf("hello");
    }
    printf("%d",ret);

   /* int chmod(const char *path, mode_t mode);
    int fchmod(int fd, mode_t mode);*/
    int ret1=chmod("../touch.txt",0666);
    if(ret1<0){
        printf("erro chmod");
    }
    /*int chown(const char *path, uid_t owner, gid_t group);
    int fchown(int fd, uid_t owner, gid_t group);
    int lchown(const char *path, uid_t owner, gid_t group);*/
}

/**
 * rename
 * getcwd
 */
void main3(){
    int ret=rename("../touch.txt","../hello.txt");
    if(ret>=0){
        printf("rename sucess");
    }
    char buf[100];
    char *ret1=getcwd(buf,100);
    printf("%s",buf);
//    printf("%s",ret);
}

/**
 * 目录操作
 * mkdir
 * rmdir
 */
void main4(){
    int ret=mkdir("../test",0644);
    if(ret>=0){
        printf("sucess mkdir");
    } else{
        printf("error mkdir");
        return;
    }
    sleep(3);
    int ret2=rmdir("../test");
    if(ret2>=0){
        printf("sucess rmdir");
    } else{
        printf("error rmdir");
        return;
    }
}
/**
 * 打开目录
 * opendir，readdir
 */
void main5(){
    DIR* dirname=opendir("../test");
    struct dirent * ret=readdir(dirname);
    printf("%s",ret->d_name);
    closedir(dirname);
}

/**
 * 递归遍历目录
 */
/* dirwalk: apply fcn to all files in dir */
#define MAX_PATH 1024
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0
            || strcmp(dp->d_name, "..") == 0)
            continue; /* skip self and parent */
        if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
/* fsize: print the size and name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%8ld %s\n", stbuf.st_size, name);
}
void main6(){
    fsize("../test");
}
int main(){
    main6();
    return 0;
}