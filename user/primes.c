#include "kernel/types.h"
#include "user.h"
#include"stdbool.h"


int main(int argc,char* argv[]){
    if(argc != 1){
        printf("primes no argument!\n");
        exit(-1);
    }
    
    else{   
        int p[2];               
        pipe(p);
        int i;
        if(fork() != 0){
            /*father*/\

            close(p[1]);    //关闭写端

            while(read(p[0],&i,sizeof(i)) != 0){
                printf("prime %d\n",i);
            }                
            //读不到数字，输出完毕
                close(p[0]);
                exit(0);
        }

        else{
            /*son*/
           
           close(p[0]);  //关闭读端

            for (int i = 2; i < 35; i++)
            {
                bool flag = true;
                for (int j = 2; j < i; j++)
                {
                    /* 判断是否为质数 */
                    if(i%j == 0 && i!=j){
                        flag = false;
                        break;
                    }
                        
                }
                if(flag){
                    write(p[1],&i,sizeof(i));
                }
            } 
            close(p[1]);  
        }

         
    }
    exit(0);
}