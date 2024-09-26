#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

/*
Krav på uppgift:
    *Input på N för antal konsumenter programmet ska ha.
    *Storlek på Buffer, BufferSize.
    *Intervall tid för skapande av items,TimeInterval.
    *Producers skapar items så länge buffer har plats annars väntar den tills consumer tar bort item
    och plats blir till.


Hur programmet ska funka(iden):
    Producer skapa items mha en timeintervall in i minnesblock
    från minnesblocket så tar consumer items efter att Producern har gjort sitt
    så den kommer behöva vänta på respons eller något från P.
    Buffern spelar som minnesblock för både P och C.

    -Är lista tom måste C vänta
    -Är lista full måste P vänta

//för att fatta kommandon
https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html
https://www.geeksforgeeks.org/multithreading-in-c/
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
https://www.geeksforgeeks.org/use-posix-semaphores-c/


kör kod med detta kommando  
    gcc Laboration1.c -o lab1 -pthread
*/


 /*
 Buffer
     Anpassningsbar?
     kommer hålla alla items från P
     C kommer kunna ta items från lista
 */

int N,bufferSize,timeIntervall,counterItems = 0;
//sätter igång muex lock
pthread_mutex_t lock;
//sempahore
sem_t tom;
sem_t full;

/*
producer thread
    wait funktion + timeIntervall för att få väntan rätta
    create funktion 
*/
void* Producer(void* args) {
    //skapandet
    int* Buffer = (int*)args;

    
    //ska köra oändligt men bara leverera items varje timeIntervall
    while(1) {
        sem_wait(&tom);
        if(counterItems < bufferSize) {
            usleep(timeIntervall*100);
            pthread_mutex_lock(&lock);
            int x = 1;
            Buffer[counterItems] = x;
            counterItems++;
            printf("tillagd: %d\n",x);
            pthread_mutex_unlock(&lock);
        }
        sem_post(&full);
    }
}
/*
Consumer thread
    wait funktion
    remove funktion
*/
void* Consumer(void* args) {
    //borttagandet
    int* Buffer = (int*)args;
    int x = 1;
    //while 1 finns för inf loop, men if sats för att testa å se om jag kan fixa segmentation fault
    while(1) {
        sem_wait(&full);
        if(counterItems >= 0) {
            pthread_mutex_lock(&lock);
            Buffer[counterItems - 1] = x;
            counterItems--;
            printf("borttaget: %d\n",x);
            pthread_mutex_unlock(&lock);
        }
        sem_post(&tom);
    }
}

/*
VART JAG ÄR JUST NU:

jag får nu programmet att funka men får segmentation fault vilket då är minneshantering fel, ser attprogrammet körs så tar C bort mer än P producerar,(tar bort inget från tomt minne) pga av att P inte hinner producera tillräckligt för att C tar bort för fort, måste fixa mutex locks å fixa critical section så enbart en kan jobba i taget å sakta ner Cs jobb

fixa även timeIntervall för P
*/


int main() {
    scanf("%d %d %d",&N,&bufferSize,&timeIntervall);
    //threads
    pthread_t p_Threads[1];
    pthread_t c_Threads[N]; 
    int Buffer[bufferSize];

    sem_init(&tom, 0, bufferSize); 
    sem_init(&full, 0, 0);  

    //mutex locks 
    if(pthread_mutex_init(&lock,NULL)!= 0) {
        printf("error, gick inte å skapa mutex lock");
    }

    //skapa 1 Producer
    for(int i = 0; i < 1;i++) {
        if(pthread_create(&p_Threads[i],NULL,&Producer,(void*)Buffer) != 0) {
            perror("error med skapande av P\n");
        }
    }
    //skapa n Consumers
    for(int i = 1; i < N;i++) {
        if(pthread_create(&c_Threads[i],NULL,&Consumer,(void*)Buffer) != 0) {
            perror("error med skapande av C\n");
        }
    }

    //behöver en join funktion
    for(int i= 0; i < N;i++)  {
        if(pthread_join(c_Threads[i],NULL)!= 0) {
            perror("error c");
        }
    }

    for(int i= 0; i < 1;i++)  {
        if(pthread_join(p_Threads[i],NULL)!= 0) {
            perror("error p");
        }
    }

    pthread_mutex_destroy(&lock);
    
    return 0;
}










