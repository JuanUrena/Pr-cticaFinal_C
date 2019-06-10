#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

int check_lastchar(char *ins){
	int i=1;
	int result =0;
	int l=strlen(ins);
	while(i<=l){
		if(ins[l-i]=='E' && l-i){
			if (ins[l-i-1]=='R' &&
			ins[l-i-2]=='E' &&
			ins[l-i-3]=='H'){
				result=1;
			}
			break;
		}else if(ins[l-i]==' '){
			i++;
		}else{
			break;
		}
	}
	return result;
}

int main(){
	
	char *phrase=strdup("HERE");
	int l=strlen(phrase);
	
	if(!NULL){
		printf("%d\n",l);
		free(phrase);
	}
	return 0;
}
