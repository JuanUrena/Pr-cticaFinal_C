#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
   // printf() displays the string inside quotation
   char *aux="$PATH";
   char *aux2=strtok(aux,"$");
   
   aux2=(getenv(aux2));
   printf("\n%s\n", aux2);
   free(aux);
   if (aux2!=NULL){
		printf("\n%d\n", *aux2);
	}
   return 0;
}
