#include "common.h"
#include <ctype.h>
#include <stdlib.h>

struct ar_draft_chain_t *ar_draft_chain, *ar_draft_chain_orig;

void ar_init()
{
	ar_draft_chain=NULL;
	ar_draft_chain_orig=NULL;

	return;
}

struct ar_draft_chain_t* ar_draft_chain_alloc()
{
	struct ar_draft_chain_t *stl;

	stl=(struct ar_draft_chain_t*)malloc(sizeof(struct ar_draft_chain_t));
	assert(stl);

	stl->par=(ms_t*)malloc(X*sizeof(ms_t));
	assert(stl->par);

	stl->next=NULL;

	return stl;
}

void ar_draft_chain_destroy(struct ar_draft_chain_t *stl)
{
	free(stl->par);
	free(stl);

	return;
}

void ar_draft_chain_append_entry(struct ar_draft_chain_t *stl)
{
	if(!ar_draft_chain)
		ar_draft_chain_orig=stl;
	else
		ar_draft_chain->next=stl;
	ar_draft_chain=stl;

	return;
}

void str_to_par(ms_t *par, char *str)
{
	int i;

	for(i=0; i<X; i++, str++){
		/* isdigit() may be macros so *str should not be *str++ */
		while((str) && (!isdigit(*str)))
			str++;

		par[i]=(ms_t)atoi(str);
	}

	return;
}

void ar_draft_chain_to_ar()
{
	int i;
	ms_t *a;
	struct ar_draft_chain_t *t;

	num_ar=probe_ar_draft_chain_len();
	alloc_ar();

	a=ar_1dim;

	while(ar_draft_chain_orig){
		for(i=0; i<X; i++)
			*a++=ar_draft_chain_orig->par[i];
		t=ar_draft_chain_orig;
		ar_draft_chain_orig=ar_draft_chain_orig->next;
		ar_draft_chain_destroy(t);
	}

	return;
}

void alloc_ar()
{
	int i;

	ar_1dim=(ms_t*)malloc(X*num_ar*sizeof(ms_t));
	assert(ar_1dim);
	ar=(ms_t**)malloc(num_ar*sizeof(ms_t*));
	assert(ar);

	for(i=0; i<num_ar; i++)
		ar[i]=ar_1dim+i*X;

	return;
}

num_ar_t probe_ar_draft_chain_len()
{
	num_ar_t count=1;
	struct ar_draft_chain_t *t=ar_draft_chain_orig;

	while((t=t->next))
		count++;

	return count;
}

void print_par(ms_t *par)
{
	int i;

	for(i=0; i<X; i++)
		printf("%d%c", par[i], i!=X-1?' ':'\n');

	return;
}

void print_ar()
{
	int i;

	for(i=0; i<num_ar; i++)
		print_par(ar[i]);

	return;
}

void make_ar_index()
{
	int i, j;

	ar_index=(indexBit_t*)malloc(num_ar*sizeof(indexBit_t));
	assert(ar_index);

	for(i=0; i<num_ar; i++){
		ar_index[i]=(indexBit_t)1;
		for(j=1; j<X; j++){
			ar_index[i]<<=ar[i][j]-ar[i][j-1];
			ar_index[i]|=(indexBit_t)1;
		}
		ar_index[i]<<=X*X-ar[i][X-1];
	}

	return;
}
