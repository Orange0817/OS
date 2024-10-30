#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

int buffer_size, producer_speed, consumer_speed;
int in=0; // 紀錄生產者目前在buffer放入多少項目
int out=0; // 紀錄消費第幾個item
int item=1; // 紀錄已經生產多少項目

pid_t gettid()
{
    return syscall(SYS_gettid);
}

void *p(void *param)
{
    printf("生產者程序ID: %d\n", gettid());
    while(1)
    {
        sleep(producer_speed); // 模擬生產速度
        if(in<buffer_size)
        {
                in++;
                printf("生產者：已生產item%d，緩衝區中還有%d個空位。\n", item, buffer_size-in);
                item++;
        }
        else
        {
                printf("生產者：緩衝區已滿，暫時停止生產。\n");
        }
    }
}

void *c(void *param)
{
    printf("消費者程序ID: %d\n", gettid());
    while(1)
    {
        sleep(consumer_speed); // 模擬消費速度
        if(in>0)
        {
                in--;
                out++;
                printf("消費者：已消費item%d，緩衝區還有%d個空位\n", out, buffer_size-in);
        }
        else
        {
                printf("消費者：緩衝區已空，暫時停止消費\n");
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc!=4)
    {
        fprintf(stderr, "請輸入三個參數\n");
        return -1;
    }

    buffer_size=atoi(argv[1]); // 將字串轉為整數
    producer_speed=atoi(argv[2]);
    consumer_speed=atoi(argv[3]);

    if(buffer_size<=0||producer_speed<=0||consumer_speed<=0)
    {
        fprintf(stderr, "輸入的參數只能是正整數\n");
        return -1;
    }

    pthread_t pt, ct;

    pthread_create(&pt, NULL, p, NULL);
    pthread_create(&ct, NULL, c, NULL);

    pthread_join(pt, NULL);
    pthread_join(ct, NULL);

    return 0;
}