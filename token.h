struct param_cmd{
	char *comand;
	char *in;
	char *out;
};

struct value_var{
	int var;
	char *variable;
	char *value;
};

struct list* tokenizar(char *line, char *cut);
struct param_cmd* get_in_out(char *line);
struct value_var* check_var_value(char *ins);


struct value_var* check_var_value(char *ins){
	char *aux;
	char *var;
	char *value;
	struct value_var *param;
	
	param=(struct value_var *)malloc(sizeof(struct value_var));
	
	aux=strchr(ins, '=');
	
	if (aux!=NULL){
		var=strtok(ins, "=");
		value=strtok(NULL, "=");
		if (var && *var==*ins){
		
			param->var=1;
			
		}else{
			param->var=0;
		}
	}
	
	param->variable=var;
	param->value=value;

	return param;
};
 
struct param_cmd* get_in_out(char *line){
	char *in;
	char *out;
	char *aux=line;
	struct param_cmd *param;
	
	param=(struct param_cmd *)malloc(sizeof(struct param_cmd ));
	param->comand=NULL;
	
	in=strchr(aux,'<');
	out=strchr(aux,'>');
	
	if (in!=NULL && out!=NULL){
		if (strlen(in)>strlen(out)){
			//printf("Salida:%s\n", strtok(strtok(out,">"),"<"));
			//printf("Entrada:%s\n", strtok(strtok(in,"<"),">"));
			//printf("MSN:%s\n",strtok(line, "<"));
			
			//param->out=(char *)malloc(sizeof(strtok(strtok(out,">"),"<"))+1);
			param->out=strdup(strtok(strtok(out,">"),"<"));
			//param->in=(char *)malloc(sizeof(strtok(strtok(in,"<"),">"))+1);
			param->in=strdup(strtok(strtok(in,"<"),">"));
			
			if (strlen(line)-1>strlen(strtok(line, "<"))){
			//param->comand=(char *)malloc(sizeof(strtok(line, "<"))+1);
				param->comand=strdup(line);
			}
			
		}else{
			//printf("Entrada:%s\n", strtok(strtok(in,"<"),">"));
			//printf("Salida:%s\n", strtok(strtok(out,">"),"<"));
			//printf("MSN:%s\n",strtok(line, ">"));
			
			//param->in=(char *)malloc(sizeof(strtok(strtok(in,"<"),">"))+1);
			param->in=strdup(strtok(strtok(in,"<"),">"));
			//param->out=(char *)malloc(sizeof(strtok(strtok(out,">"),"<"))+1);
			param->out=strdup(strtok(strtok(out,">"),"<"));
			
			if (strlen(line)-1>strlen(strtok(line, ">"))){
			//param->comand=(char *)malloc(sizeof(strtok(line, ">"))+1);
				param->comand=strdup(line);
			}
		}
	}else if (in!=NULL){
		//printf("Entrada:%s\n", strtok(in,"<"));
		//printf("MSN:%s\n",strtok(line, "<"));
		
		//param->in=(char *)malloc(sizeof(strtok(in,"<"))+1);
		param->in=strdup(strtok(in,"<"));
		
		param->out=NULL;
			
	//	param->comand=(char *)malloc(sizeof(strtok(line, "<"))+1);
		if (strlen(line)-1>strlen(strtok(line, "<"))){
			//param->comand=(char *)malloc(sizeof(strtok(line, "<"))+1);
			param->comand=strdup(line);
		}
		
	}else if (out!=NULL){
		//printf("Salida:%s\n", strtok(out,">"));
		//printf("MSN:%s\n",strtok(line, ">"));
		
		//param->out=(char *)malloc(sizeof(strtok(out,">"))+1);
		param->out=strdup(strtok(out,">"));
		
		param->in=NULL;
			
		//param->comand=(char *)malloc(sizeof(strtok(line, ">"))+1);
		if (strlen(line)-1>strlen(strtok(line, ">"))){
			//param->comand=(char *)malloc(sizeof(strtok(line, ">"))+1);
			param->comand=strdup(line);
		}
	}else{
		param->out=NULL;
		param->in=NULL;
	//	param->comand=(char *)malloc(sizeof(line)+1);
			
		param->comand=strdup(line);
	
	}
	//Comprobar si debido a los strtok estoy teniendo leek de memoria, debido a que me modifica mi string?¿?¿
	return param;
			
	
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
