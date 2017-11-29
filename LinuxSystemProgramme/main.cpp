#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
void main1(){
    extern char **environ;
    int i;
    for(i=0;environ[i]!=NULL;i++){
        printf("%s\n",environ[i]);
    }
    printf("PATH=%s\n", getenv("PATH"));
    setenv("PATH", "hello", 1);
    printf("PATH=%s\n", getenv("PATH"));
}
void main2(){
    pid_t pid;
    char *message;
    int n;
    pid=fork();
    if(pid<0){
        perror("fork failed!");
        exit(1);
    }
    if(pid==0){
        message="This is the Child";
        n=6;
    }else{
        message="This is the Parent";
        n=3;
    }
    for(;n>0;n--){
        printf("%s:%d\n",message,getpid());
        printf("%d\n",getuid());
        printf("%d\n",getgid());
        sleep(1);
    }
}

void main3(){
    char *const ps_argv[] ={"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
    char *const ps_envp[] ={"PATH=/bin:/usr/bin", "TERM=console", NULL};
    execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
    execv("/bin/ps", ps_argv);
    execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
    execve("/bin/ps", ps_argv, ps_envp);
    execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
    execvp("ps", ps_argv);
}
int main(){
    main3();
    return 0;
}