#ifndef __H_SEMAPHORE__
#define __H_SEMAPHORE__

#include <pthread.h>
#include <semaphore.h>

/**
 * Surcouche aux semaphores posix
 * Par Olivier
 */

class Semaphore
{
    public:
        /**
         * Constructeur initialisant la semaphore (val par defaut : 10).
         */
        Semaphore();

        /**
         * Constructeur initialisant la semaphore avec une valeur.
         */
        Semaphore(int value);
        
        /**
         * Destructeur
         */
        ~Semaphore();

        /**
         * Incremente la valeur de la sémaphore
         */
        void free();

        /**
         * Consomme une valeur de la sem
         */
        void wait();



    private:

        /**
         * Variable de la semaphore
         */
        sem_t semaphore;
};


#endif
