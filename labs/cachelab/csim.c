#include <stdio.h>  
#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

struct Cacheline{
    int valid; //记录这一行是空还是有数据 
    unsigned long long tag;//保存块
    unsigned long long last_used;//保存最后一次访问序号
};
void newstatus(int s,int setindex,int E,int b,unsigned long long address,struct Cacheline* cachespace,
int* hit_count,int* miss_count,int* eviction_count,int* access_count){
    unsigned long long tag=address>>(b+s);
    int status=0;
    int filled=0;
    *access_count+=1;
    for(int i=setindex*E;i<setindex*E+E;i++){
        if(cachespace[i].valid==1){
            if(cachespace[i].tag==tag){
                *hit_count+=1;
                cachespace[i].last_used=*access_count;
                status=1;
                filled=1;
                break;
            }
        }
    }
    if(status==0){
        for(int i=setindex*E;i<setindex*E+E;i++){
            if(cachespace[i].valid==0){
                cachespace[i].valid=1;
                cachespace[i].tag=tag;
                cachespace[i].last_used=*access_count;
                filled=1;
                break;
            }
        }
        if(filled==0){
            int minindex;
            unsigned long long minnum=ULLONG_MAX;
            for(int i=setindex*E;i<setindex*E+E;i++){
                if(cachespace[i].last_used<=minnum){
                    minnum=cachespace[i].last_used;
                    minindex=i;
                }
            }
            cachespace[minindex].valid=1;
            cachespace[minindex].tag=tag;
            cachespace[minindex].last_used=*access_count;
            *eviction_count+=1;
        }
        *miss_count+=1;

    }
}
int main(int argc,char *argv[])
{
    int option;
    char* tracefile;
    int s;
    int E;
    int b;
    int space;
    FILE* trace;
    char instruction;
    unsigned long long address;
    int size;
    unsigned long long tag;
    int setindex;
    int hit_count=0;
    int miss_count=0;
    int eviction_count=0;
    int access_count=0;
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    while((option=getopt(argc,argv,"s:E:b:t:"))!=-1 ){
        if (option=='s'){
            s=atoi(optarg);
        }
        else if (option=='E'){
            E=atoi(optarg);
        }
        else if (option=='b'){
            b=atoi(optarg);
        }
        else if(option=='t'){
            tracefile=optarg;
        }
    }
    int S=1<<s;
    space=S*E*sizeof(struct Cacheline);
    struct Cacheline* cachespace=malloc(space);
    if(cachespace!=NULL){
        for (int i=0; i<S*E;i++){
            cachespace[i].valid=0;
            cachespace[i].tag=0;
            cachespace[i].last_used=0;
        }
    }
    trace=fopen(tracefile,"r");
    if(trace!=NULL){
        while (fscanf(trace, " %c %llx,%d", &instruction, &address, &size) == 3) {
            if(instruction=='I'){
                continue;
            }
            printf("%c %llx, %d\n",instruction, address, size);
            setindex=(address>>b)&(S-1);
            tag=address>>(b+s);
            printf("%d,%llu\n",setindex,tag);
            if(instruction=='L'){
                newstatus(s,setindex,E,b,address,cachespace,&hit_count,&miss_count,&eviction_count,&access_count);
            }
            if(instruction=='S'){
                newstatus(s,setindex,E,b,address,cachespace,&hit_count,&miss_count,&eviction_count,&access_count);
            }
            if(instruction=='M'){
                newstatus(s,setindex,E,b,address,cachespace,&hit_count,&miss_count,&eviction_count,&access_count);
                newstatus(s,setindex,E,b,address,cachespace,&hit_count,&miss_count,&eviction_count,&access_count);
            }
        }
            
    }
     

      
    printSummary(hit_count, miss_count, eviction_count);
    return 0;

}
