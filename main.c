/* https://opensource.com/article/19/5/how-write-good-c-main-function*/

/* main.c */
/* 0 copyright/licensing */
/* 1 includes */
/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

/*author: ardavic*/
# include <stdio.h>
# include <pthread.h>


typedef struct{
    pthread_t thread;
    int mutex;
}foobar;

int InitFoobar(foobar* foo);
void FreeFoobar(foobar* foo);

typedef struct{
    int value;
}Binary;
void setBinaryTrue(Binary binaryobj, int value);
void setBinaryFalse(Binary binaryobj, int value);

void* doSomeThing(void *param);

int counter;





int main(int argc, char *argv[]) {

    doSomeThing(NULL);
    return 0;
};

int mainCOPY() {
    /*
    int i = 0;
    int err;
    pthread_mutex_t* lock;
    pthread_mutex_lock(&lock);

    
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while(i < 2)
    {

        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
    */

    //pthread_mutex_lock(&lock);
    //foobar fooStruct;
    //InitFoobar(&fooStruct);
    //FreeFoobar(&fooStruct);

    return 0;
};


int InitFoobar(foobar* foo){
    /*
    //err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
    pthread_t *pthread = foo -> thread;
    int err = pthread_create(pthread, NULL, &doSomeThing, NULL);
    if (err != 0){
        printf("can't create thread\n");
        return err;
    }else {

        return 1;
    }                                                           */

   //oneCreate(&foo->mutex);
}

void FreeFoobar(foobar* foo){
   //oneDestroy(foo->mutex);
}





/* 8 function declarations */
void* doSomeThing(void *param){
    pthread_attr_t tattr;
    pthread_t tid;
    extern void *start_routine(void *arg);
    void *arg;
    int ret; 


    //pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=2; i<(0xFFFFFFFF);i=i*i);

    printf("\n Job %d finished\n", counter);

    //pthread_mutex_unlock(&lock);

    return NULL;
}