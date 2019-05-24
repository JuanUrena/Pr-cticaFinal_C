struct param_cmd{
	char *comand;
	char *in;
	char *out;

};




struct list* tokenizar(char *line, char *cut);
void get_in_out(char *line);


void get_in_out(char *line){
	char *in;
	char *out;
	char *aux=line;
	//struct param_cmd *param;
	
	//param=(struct param_cmd *)malloc(sizeof(struct param_cmd ));
	
	in=strchr(aux,'<');
	out=strchr(aux,'>');
	
	printf("\n\n%zd",strlen(line));
	
	if (in!=NULL && out!=NULL){
		if (strlen(in)>strlen(out)){
			printf("Salida:%s\n", strtok(strtok(out,">"),"<"));
			printf("Entrada:%s\n", strtok(strtok(in,"<"),">"));
		}else{
			printf("Entrada:%s\n", strtok(strtok(in,"<"),">"));
			printf("Salida:%s\n", strtok(strtok(out,">"),"<"));
			
		}
	}else if (in!=NULL){
		printf("Entrada:%s\n", strtok(in,"<"));
	}else if (out!=NULL){
		printf("Salida:%s\n", strtok(out,">"));
	}
	//Comprobar si debido a los strtok estoy teniendo leek de memoria, debido a que me modifica mi string?¿?¿
	free(line);
	
	//Codigo siguiente no valido
	
	/*if (strlen(in)>strlen(out)){
		printf("Significa que in esta antes y por tanto in contiene a out");
		param->out=(char *)malloc(sizeof(strtok(out, ">")+1));
		strcpy(param->out,strtok(out, ">"));
		free(out);
		
		param->in=(char *)malloc(sizeof(strtok(strtok(in, ">"),"<")+1));
		strcpy(param->in,strtok(strtok(in, ">"),"<"));
		free(in);
		
		param->comand=(char *)malloc(sizeof(strtok(line,"<")+1));
		strcpy(param->comand, strtok(line,"<"));
		
	}else{
		printf("significa que out es mas grande y es el que contine a in");
		
		param->in=(char *)malloc(sizeof(strtok(in, "<")+1));
		strcpy(param->in,strtok(in, "<"));
		free(in);
		
		param->out=(char *)malloc(sizeof(strtok(strtok(out, "<"),">")+1));
		strcpy(param->out,strtok(strtok(out, "<"),">"));
		free(out);
		
		param->comand=(char *)malloc(sizeof(strtok(line,">")+1));
		strcpy(param->comand, strtok(line,">"));
		
	}
	return param;*/
};

struct list* tokenizar(char *line, char *cut){
	struct list *mylist;
	
	mylist=(struct list *)malloc(sizeof(struct list));
	mylist->first=NULL;
	mylist->number_element=0;

	//printf("\n2:\n%s",line);
	char *copy = (char *)malloc(strlen(line) + 1);
	strcpy(copy, line);
	char *token;
	
	token=strtok(copy, cut);
	
	while(token != NULL ) {
		add_element(mylist, token);
		token = strtok(NULL, cut);
	}
	free(copy);	
   return mylist;
	
}
