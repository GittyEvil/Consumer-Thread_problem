#include <pthread.h>
#include <stdio.h>

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
*/


 /*
 Buffer
     Anpassningsbar?
     kommer hålla alla items från P
     C kommer kunna ta items från lista
 */

//wait funktion
void Wait() {

}

/*
producer thread
    wait funktion
    create funktion mha timeIntervall
*/
void Producer(int Buffer[],int timeIntervall) {
    
}
/*
Consumer thread
    wait funktion
    create funktion
*/
void Consumer(int Buffer[]) {
    
}

int main(/*int argc, char *argv[]*/) {
    int N,bufferSize,timeIntervall;
    
    scanf("%d %d %d",&N,&bufferSize,&timeIntervall);
    //n antal C + 1 P, lista som håller alla threads
    phtread_t threads[N + 1];

    int Buffer[bufferSize];

    //skapande av threads
    pthread_create(threads[0],NULL,Producer,NULL);

    for(int i = 1; i < N;i++) {
            pthread_create(threads[i],NULL,Producer,NULL);
    }



    
    return 0;
}










