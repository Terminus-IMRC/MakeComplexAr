#ifndef _COMMON_H_INSIDE_
#define _COMMON_H_INSIDE_

#include <endian.h>

#if (__BYTE_ORDER)!=(__LITTLE_ENDIAN)
#	error Non-little-endian architectures are not support yet
#endif

#include <stdint.h>

typedef int ms_t;
typedef uint64_t indexBit_t;
/* can be used in X<=6 at least */
typedef long int num_ar_t;

struct ar_draft_chain_t{
	struct ar_draft_chain_t *next;
	ms_t *par;
};

#include <stdio.h>
#include <assert.h>

extern int X;
extern ms_t **ar, *ar_1dim;
extern indexBit_t *ar_index;
extern num_ar_t num_ar;
extern int depth;

/* in X.c */
int probe_X(char *str);

/* in ar.c */
void ar_init();
struct ar_draft_chain_t* ar_draft_chain_alloc();
void ar_draft_chain_destroy(struct ar_draft_chain_t *stl);
void ar_draft_chain_append_entry(struct ar_draft_chain_t *stl);
void str_to_par(ms_t *par, char *str);
void ar_draft_chain_to_ar();
void alloc_ar();
num_ar_t probe_ar_draft_chain_len();
void print_par(ms_t *par);
void print_ar();
void make_ar_index();

/* in MakeComplexAr.c */
void MakeComplexAr_init();
void MakeComplexAr(int level);
indexBit_t and_index(indexBit_t a, indexBit_t b);
indexBit_t or_index(indexBit_t a, indexBit_t b);
void output_par_pair();

#endif /* _COMMON_H_INSIDE_ */
