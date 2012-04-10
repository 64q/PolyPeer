#include "../include/Mutex.hpp"

Mutex::Mutex()
{
	pthread_mutex_init (&mutex, NULL);
}
void Mutex::lock()
{
	pthread_mutex_lock (&mutex);
}
void Mutex::unlock()
{
	pthread_mutex_unlock(&mutex);
}
