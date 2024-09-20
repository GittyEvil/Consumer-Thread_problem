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

    -
*/


int N,bufferSize,timeIntervall;

 /*
 Buffer
     Anpassningsbar?
     kommer hålla alla items
 */
int buffer[];

//wait funktion
void Wait() {

}

/*
producer thread
    wait funktion
    create funktion mha timeIntervall
*/
void Producer() {
    
}
/*
Consumer thread
    wait funktion
    create funktion
*/
void Consumer() {

}



int main(int argc, char *argv[]) {


//ex create Producer(paramtrar);

//Consumer(parametrar);


}