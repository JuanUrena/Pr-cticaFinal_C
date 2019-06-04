#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

int check_lastchar(char *ins, char letter){
	int i=1;
	int result =0;
	int l=strlen(ins);
	while(i<=l){
		if(ins[l-i]==letter){
			result=1;
			i=l+1;
		}else if(ins[l-i]==' '){
			i++;
		}else{
			i=l+1;
		}
	}
	return result;
}

int main(){
	
	char *igualdad=strdup("hola como estas&");
	if (igualdad){
		printf("\n%s",igualdad);
		if(check_lastchar(igualdad, '&')){
			printf("\n%s",igualdad);
		} 
	}
	return 0;
}
