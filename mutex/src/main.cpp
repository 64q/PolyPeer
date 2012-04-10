#include <iostream>
#include <pthread.h>

#include "../include/Mutex.hpp"

using namespace std;

//structure permettant de passer des param�tres � la fonction pthread_create()
typedef struct {
   Mutex* mut;
   int i;
} threadParams;


//fonction lanc�e dans le thread
void* start(void* tp)
{
	//lock()
	((threadParams*)tp)->mut->lock();

	for(int i = 0; i<30; i++)
	{
		cout<<((threadParams*)tp)->i<<":"<<i<<endl;
	}
	cout<<"FINI"<<endl;

	//unlock()
	((threadParams*)tp)->mut->unlock();
}

int main()
{
	//on d�clare le m�me utex pour tous les threads
	Mutex mut;

	threadParams tp1;
	tp1.i = 1;
	tp1.mut = & mut;

	threadParams tp2;
	tp2.i = 2;
	tp2.mut = & mut;

	threadParams tp3;
	tp3.i = 3;
	tp3.mut = & mut;


	//on lance les 3 thread avec le m�me mutex mais la variable i diff�rentes pour pouvoir les diff�rencier
	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, start, &tp1);

	pthread_create(&thread2, NULL, start, &tp2);

	pthread_create(&thread3, NULL, start, &tp3);

	//on attend qu'il soient tous finis
	pthread_join(thread3, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread1, NULL);



}



