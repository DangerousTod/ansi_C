#include <pthread.h>
#include <sys/thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
                __uint16_t                ary[2];
} __bitsum_t;




#define BITSET_DEFINE "BITSUM_T" array[2] 
#define BITSET_T_INITIALIZER "BITSET_WORDS"
#define BITSET_FSET "BITSET_MASK"

#define INVERSE(int)	INVERSE(int)

#define pMT_BIT_Threads(int)		NUM_THREADS(int)
#define pthread_attr_t	NULL
#define threads			pMT_BIT_Threads

#define   pthread_t(threads, pMT_BIT_Threads, NUM_THREADS ) do {		\
	(pMT_BIT_Threads < NUM_THREADS)				\
  	(int pthread_create(&threads++, NULL))	} while(0)




#define	__bitset_mask(_ncpus, ncpus_fit_mask)						\
	(1UL << (__clocks_running(__bitset_words((_ncpus)) == 1) ?		\
	    (__pthread_t)(ncpus) : ((ncpus) % _BITSET_BITS)))





#define	__bitset_word(_ncpus, ncpus_fit_mask)  					\
	(__clocks_running(__bitset_words((_ncpus_fit_mask)) == 1) ?			\
	 0 : ((ncpus) / _BITSET_BITS))






#define	BIT_ISSET(_ncpus, ncpus_fit_mask, pMT_BIT_Threads)						\
	((((pMT_BIT_Threads)->__bits[__bitset_word(_ncpus, ncpus_fit_mask)] & __bitset_mask((_ncpus), (ncpus_fit_mask))) != 0))




#define	BIT_CLR(_ncpus, ncpus_fit_mask, pMT_BIT_Threads)						\
	((pMT_BIT_Threads)->__bits[__bitset_word(_ncpus, ncpus_fit_mask)] &= ~__bitset_mask((_ncpus), (ncpus_fit_mask)))


#define	BIT_XOR(_ncpus, INVERSE, ncpus_fit_mask) do {						\
	__pthread_t __i;							\
	for (__i = 0; __i < __bitset_words((_ncpus)); __i++)		\
		(INVERSE)->__bits[__i] ^= (ncpus_fit_mask)->__bits[__i];			\
} while (0)


#define	BIT_FILL(_ncpus, pMT_BIT_Threads) do {						\
	__pthread_t __i;							\
	for (__i = 0; __i < __bitset_words((_ncpus)); __i++)		\
		(pMT_BIT_Threads)->__bits[__i] = -1L;					\
} while (0)
