#include <glob.h>

glob_t getFiles(struct list *mylist);
char* get_route(char *program);
char* env_variable(char *word);


char* env_variable(char *word){
	char *pointer=NULL;
	char *var;
	char *aux;
	char *resolve;

	if (word){
		pointer=strchr(word,'$');
	}

	if (pointer){
		var=strtok(pointer,"$");
		if (var){
			aux=(getenv(var));
			if (aux){
				free(word);
				resolve=strdup(aux);
				if (!resolve){
					perror("Memory error");
					exit(EXIT_FAILURE);
				}
				return resolve;
			}else{
				fprintf(stderr, "\nerror: var %s does not exist\n", word);
				exit(EXIT_FAILURE);
			}
		}
	}
	return word;
}


char* get_route(char *program){
	char *path;
	char *aux;
	char *aux2;
	aux2=strdup(program);

	if (!aux2){
		perror("Memory error");
		exit(EXIT_FAILURE);
	}
	
	if(!access(aux2, F_OK)){
		free(aux2);
		return program;
	}
	free(aux2);

	path=strdup(getenv("PATH"));

	if (!path){
		perror("Memory error");
		exit(EXIT_FAILURE);
	}

	aux=strtok(path, ":");
	while (aux!=NULL){
		aux2=calloc(1, strlen(aux)+strlen(program)+2);
		if (!aux2){
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
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
	int i=1;
	struct cell *iterator=mylist->first;
	glob_t globbuf;

	glob(iterator->ins, GLOB_NOCHECK, NULL, &globbuf);	
	while (i<mylist->number_element){
		iterator=iterator->next;
		i++;
		glob(iterator->ins, GLOB_NOCHECK|GLOB_APPEND, NULL, &globbuf);	
	}
	return globbuf;
}
