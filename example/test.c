#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
int main(){
	
	char *igualdad=strdup("at");
	char *var;
	char *value;
	char *pointer=NULL;
	
	
	var=(strtok(igualdad, "t"));
	value=(strtok(NULL, "t"));
	if (value){
		pointer=strchr(value,'$');
	}
	//if (value){
		printf("\n%s\n%s\n%s",var, value, pointer);
	//}
	return 0;
}
