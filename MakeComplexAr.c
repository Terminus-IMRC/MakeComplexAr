#include "common.h"
#include <stdlib.h>

indexBit_t cur_index;
num_ar_t *element_history;

void MakeComplexAr_init()
{
	cur_index=(indexBit_t)0;

	element_history=(num_ar_t*)malloc(X*sizeof(num_ar_t));
	assert(element_history);

	return;
}

void MakeComplexAr(int level)
{
	num_ar_t i;
	indexBit_t cur_index_def=cur_index;

	for(i=(level==0?0:element_history[level-1]+1); i<num_ar; i++)
		if(!and_index(cur_index, ar_index[i])){
			cur_index=or_index(cur_index, ar_index[i]);
			element_history[level]=i;
			if(level<X-1)
				MakeComplexAr(level+1);
			else
				output_par_pair();
			cur_index=cur_index_def;
		}

	return;
}

indexBit_t and_index(indexBit_t a, indexBit_t b)
{
	return a&b;
}

indexBit_t or_index(indexBit_t a, indexBit_t b)
{
	return a|b;
}

void output_par_pair()
{
	int i;

	for(i=0; i<X-1; i++)
		printf("%ld%c", element_history[i], i!=(X-1)-1?' ':'\n');

	return;
}
