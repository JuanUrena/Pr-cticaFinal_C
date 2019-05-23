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
	struct param_cmd *param;
	
	param=(struct param_cmd *)malloc(sizeof(struct param_cmd));
	
	in=strchr(line,'<');
	out=strchr(line, '>');
	
	if (strlen(in)>strlen(out)){
		printf("Significa que in esta antes y por tanto in contiene a out");
		out =strtok(out, ">");
		param->out=(char *)malloc(sizeof(out)+1);
		strcpy(param->out,out);
		
		in=strtok(in, "<");
		in=strtok(in,">");
		
		param->in=(char *)malloc(sizeof(in)+1);
		strcpy(param->in,in);
	}else{
		printf("significa que out es mas grande y es el que contine a in");
		
		in =strtok(in, "<");
		param->in=(char *)malloc(sizeof(in)+1);
		strcpy(param->in,in);
		
		out=strtok(out, ">");
		out=strtok(out,"<");
		
		param->out=(char *)malloc(sizeof(out)+1);
		strcpy(param->out,out);
	};
} 

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
