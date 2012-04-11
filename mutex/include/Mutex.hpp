#ifndef __H_MUTEX__
#define __H_MUTEX__

#include <pthread.h>

/**
 * Enveloppe des mutex de pthread.
 */

class Mutex
{
	public:
		/**
		 * Constructeur initialisant à 1 le mutex.
		 */
		Mutex();

		/**
		 * Similaire à pthread_mutex_lock() de pthread.
		 */
		void lock();

		/**
		 * Similaire à pthread_mutex_unlock() de pthread.
		 */
		void unlock();

	private:
		/**
		 * la variablee mutex de pthread.
		 */
		pthread_mutex_t mutex;
};


#endif
