#include "common.h"
#include <string.h>

int X;
ms_t **ar, *ar_1dim;
indexBit_t *ar_index;
num_ar_t num_ar;

int main()
{
	char str[0xff];
	struct ar_draft_chain_t *stl;

	ar_init();

	fgets(str, 0xff, stdin);
	X=probe_X(str);
	printf("X: %d\n", X);
	do{
		stl=ar_draft_chain_alloc();
		str_to_par(stl->par, str);
		ar_draft_chain_append_entry(stl);
		fgets(str, 0xff, stdin);
	}while(!feof(stdin));

	ar_draft_chain_to_ar();
	printf("num_ar: %ld\n", num_ar);

	/* only for debug; annoying in slow speed console */
	/*print_ar();*/

	/*MakeComplexAr_init();
	MakeComplexAr(0);*/

	return 0;
}
