
char* env_variable(char *word);

//Función para sacar las variables de entorno

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


int check_lastchar(char *phrase, char letter)
{
	int i=1;
	int result =0;
	int l=strlen(phrase);
	while(i<=l){
	//SWITCH?¿?
		if(phrase[l-i]==letter){
			result=1;
			i=l+1;
		}else if(phrase[l-i]==' '){
			i++;
		}else{
			i=l+1;
		}
	}
	return result;
}
