#include <glob.h>

glob_t getFiles(struct list *mylist);
char* get_route(char *program);
char* env_variable(char *word);


char* env_variable(char *word){
	char *pointer=NULL;
	char *var;
	char *aux;
	if (word){
		pointer=strchr(word,'$');
	}

	if (pointer){
		var=strtok(pointer,"$");
		if (var){
			aux=(getenv(var));
			if (aux){
				free(word);
				char *resolve=strdup(aux);
				return resolve;
			}else{
				fprintf(stderr, "for failed");
				exit(1);
			}
		}
	}
	return word;
}


char* get_route(char *program){
	char *path=strdup(getenv("PATH"));
	char *aux2;
	char *aux;
	aux2=strdup(program);
	
	if(!access(aux2, F_OK)){
		free(path);
		return aux2;
	}
		
	free(aux2);
	aux=strtok(path, ":");
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


glob_t expand_arg(struct list *mylist){
	struct cell *iterator=mylist->first;
	int i=1;
	glob_t globbuf;
	
	glob(iterator->ins, GLOB_NOCHECK, NULL, &globbuf);	
	
	while (i<mylist->number_element){
		iterator=iterator->next;
		i++;
		glob(iterator->ins, GLOB_NOCHECK|GLOB_APPEND, NULL, &globbuf);	
	}
	return globbuf;
}
