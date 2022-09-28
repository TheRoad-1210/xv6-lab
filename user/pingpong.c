#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    if(argc != 1){
        printf("pingpong no argument!\n");
        exit(-1);
    }
    else{
        
        int p[2]; 
        int pp[2];
        char pi[5] = {"ping"};
        char po[5] = {"pong"};
        pipe(p);    //创建管道
        if(fork() != 0){   
        /*父进程*/
        close(p[0]);    //关闭p读端
        write(p[1],pi, 4);  //写入ping
        close(p[1]);    //写入完毕，关闭p写端

        sleep(5);  //父进程稍等片刻

        close(pp[1]);    //关闭pp写端
        read(pp[0],po,5);  //读取pong
        close(pp[0]);   //读取完毕，关闭pp读端
        printf("%d: received %s\n",getpid(),po);
        }
        else{
        /*子进程*/
        close(p[1]);    //关闭写端
        read(p[0], pi, 5); //读取管道
        close(p[0]);    //关闭读端  
        
        //       for(int i = 0; i < 5; i++){
        //     printf("%c",pi[i]);
        // }

        printf("%d: received %s\n",getpid(),pi);    //打印

        pipe(pp);   //创建新管道
        close(pp[0]);   //关闭读端
        write(pp[1],po,4);   //写入pong
        }


    }
   exit(0);
}