#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void func(int val){
    std::cout<<"this is func\r\n"<<std::endl;
}

void test_func(int val){
    static int count = 0;
    std::cout<<"count is "<<count++<<"\r\n"<<std::endl;
}

void init_sigaction(){
    struct sigaction act;
    //设置处理信号的函数
    act.sa_handler = test_func;
    act.sa_flags = 0;

    sigemptyset(&act.sa_mask);
    //时间到发送SIGROF
    sigaction(SIGPROF,&act,NULL);
}

void init_time(){
    struct itimerval val;
    // 1秒后启用定时器
    val.it_value.tv_sec = 1;
    val.it_value.tv_usec = 0;
    //定时器间隔为1s
    val.it_interval = val.it_value;

    setitimer(ITIMER_PROF,&val,NULL);
}


int main(){
    // signal(SIGALRM,func);
    // alarm(2);

    init_sigaction();
    init_time();

    while(1);

    return 0;
}
