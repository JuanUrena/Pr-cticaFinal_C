#define BUFFERSIZE 10

struct my_line{
	struct comands *list_comands;
	char *input;
	char *output;
};

struct param_cmd{
	char *comand;
	char *in;
	char *out;
	int wait;
};

struct value_var{
	int var;
	char *variable;
	char *value;
};

struct value_var* check_var_value(char *ins);
struct param_cmd* get_in_out(char *line);
char* read_line();


struct value_var* check_var_value(char *ins){
	char *aux;
	char *var;
	char *value=NULL;
	struct value_var *param;

	param=(struct value_var *)malloc(sizeof(struct value_var));
	
	aux=strchr(ins, '=');
	param->var=0;
	if (aux!=NULL){
		var=(strtok(ins, "="));
		value=(strtok(NULL, "="));
		if (var && *var==*ins){
			param->var=1;
			param->variable=strdup(var);
			if (value){
				param->value=strdup(value);
			}else{
				param->value=NULL;
			}
		}	
	}
	return param;
}



struct param_cmd* get_in_out(char *line){
	char *in;
	char *out;
	char *aux=line;
	struct param_cmd *param;
	
	param=(struct param_cmd *)malloc(sizeof(struct param_cmd ));
	param->comand=NULL;
	
	in=strchr(aux,'<');
	out=strchr(aux,'>');
	
	if (check_lastchar(line,'&')){
		param->wait=0;
	}else{
		param->wait=1;
	}

	if (in!=NULL && out!=NULL){
		if (strlen(in)>strlen(out)){
			param->out=strdup(strtok(strtok(out,">"),"<"));
			param->in=strdup(strtok(strtok(in,"<"),">"));
			
			if (strlen(line)-1>strlen(strtok(line, "<"))){
				param->comand=strdup(line);
			}
			
		}else{
			param->in=strdup(strtok(strtok(in,"<"),">"));
			param->out=strdup(strtok(strtok(out,">"),"<"));
			
			if (strlen(line)-1>strlen(strtok(line, ">"))){
				param->comand=strdup(line);
			}
		}
	}else if (in!=NULL){
		param->in=strdup(strtok(in,"<"));
		param->out=NULL;
			
		if (strlen(line)-1>strlen(strtok(line, "<"))){
			param->comand=strdup(line);
		}	
	}else if (out!=NULL){
		param->out=strdup(strtok(out,">"));
		param->in=NULL;
		if (strlen(line)-1>strlen(strtok(line, ">"))){
			param->comand=strdup(line);
		}
	}else{
		param->out=NULL;
		param->in=NULL;		
		param->comand=strdup(line);
	}
	//Comprobar si debido a los strtok estoy teniendo leek de memoria, debido a que me modifica mi string?¿?¿
	return param;
}

char* read_line()
{
	char *line;
	line=(char *)calloc(1,1);
	char buffer[BUFFERSIZE];

	if (!line) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	printf(">>>>");
		
	while(fgets(buffer, BUFFERSIZE , stdin) ){
		line = realloc(line, strlen(line)+1+strlen(buffer) );
		if (!line) {
			fprintf(stderr, "lsh: allocation error\n");
			exit(EXIT_FAILURE);
		}
		
		strcat(line, buffer);
		if (buffer[strlen(buffer)-1]=='\n'){
			line=strtok(line, "\n");
			return line;
		}  
	}
	return line;
}
