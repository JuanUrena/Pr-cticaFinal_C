#include <glob.h>

glob_t getFiles(struct list *mylist);
char* prepare_value(char *word);
char* get_route(char *program);


char* get_route(char *program){
	char *path=strdup(getenv("PATH"));
	
	
	char *aux2;
	
	
	aux2=strdup(program);
	
	if(!access(aux2, F_OK)){
		free(path);
		return aux2;
	}
		
	free(aux2);

	char *aux=strtok(path, ":");
	
	while (aux!=NULL){
		aux2=calloc(1, strlen(aux)+strlen(program)+2);
		
		strcpy(aux2,aux);
		strcat(aux2,"/");
		strcat(aux2,program);
		
		if(!access(aux2, F_OK)){
			free(path);
			return aux2;
		}
		
		free(aux2);
		aux=strtok(NULL, ":");
	}
	free(path);
	return NULL;
}


char* prepare_value(char *word){

	char *value=NULL;
	glob_t globbuf;
	
	if (word){
		//	printf("word:\n%s\n",word);
		glob(word, GLOB_NOCHECK, NULL, &globbuf);
	
		int i;
		
		for(i = 0; i < globbuf.gl_pathc; i++ ){
		//	printf("valor antes:\n%s\n",value);
		//	printf("path:\n%s\n",globbuf.gl_pathv[i]);
			if (value){
				value=(char *) realloc(value, strlen(value)+strlen(globbuf.gl_pathv[i])+2);
				strcat(value, ":");
			}else{
				value=(char *) calloc(1,strlen(globbuf.gl_pathv[i])+1);
			}
		//	printf("value:\n%s\n",value);
		//	printf("i:\n%s\n",globbuf.gl_pathv[i]);
			strcat(value, globbuf.gl_pathv[i]);
		//	printf("valor despues:\n%s\n",value);
		}
		globfree(&globbuf);
		
	}else{
		value=strdup("\0");
	}

	return value;
}


glob_t getFiles(struct list *mylist){
	
	struct cell *iterator=mylist->first;
	
//Declare glob_t for storing the results of globbing
	glob_t globbuf;
  
//Glob.. GLOB_TILDE tells the globber to expand "~" in the pattern to the home directory
//Primer elemento sin apend
	
	glob(iterator->ins, GLOB_NOCHECK, NULL, &globbuf);
	//printf("word:\n%s\n",iterator->ins);
	
	int i=1;
	
	while (i<mylist->number_element){
		iterator=iterator->next;
		i++;
	//	printf("word:\n%s\n",iterator->ins);	
		glob(iterator->ins, GLOB_NOCHECK|GLOB_APPEND, NULL, &globbuf);	
	}
	//printf("number:\n%zd\n",globbuf.gl_pathc);
	return globbuf;
  //Free the globbuf structure
}
