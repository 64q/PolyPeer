#include <Semaphore.hpp>

Semaphore::Semaphore()
{
    sem_init(&semaphore, 0, 5);
}

Semaphore::Semaphore(int value)
{
    if(value < 0)
        value = 1;
    sem_init(&semaphore, 0, value);
}

void Semaphore::free()
{
    sem_post(&semaphore);
}

void Semaphore::wait()
{
    sem_wait(&semaphore);
}

Semaphore::~Semaphore()
{
    sem_destroy(&semaphore); 
}
