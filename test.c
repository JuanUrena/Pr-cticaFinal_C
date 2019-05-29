#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "token.h"
#include "read.h"
#include "rutes.h"


int main() {

	char *text;
	do{
		text=read_line();
	//	text2=strdup(text);
	//compruebo si es EOF
		if(text){
			if (!strlen(text)){
				free(text);
				printf("\n-----FIN-----");
	  			return 0;
			}
			printf("%s\n", text);
		}
	}while (1);
			
}
