struct list{
//comando, con el numero de aegumentos que lo componene
	struct cell *first;
	int number_element;
};

struct cell{
//Cada palabra, ins o arg
	char *ins;
	struct cell *next;
};

struct comands{
//Todos los ins, es mi linea de comandos
	struct list *list;
	struct comands *next;
};

struct list* tokenizar(char *line, char *cut);
void add_element(struct list *mylist, char *new_ins);
void print(struct list *mylist);
void print_all(struct comands *cmdlist);
void free_list(struct list *mylist);
void free_all(struct comands *cmdlist);
struct comands* cmdlist2cmdmatrix(struct list *ins_list);


struct comands* golast(struct comands *list){
	struct comands *list2=list;
	struct comands *aux;
	while (list2){
		aux=list2;
		list2=list2->next;
	}
	return aux;
}
struct list* tokenizar(char *line, char *cut){
	struct list *mylist;
	
	mylist=(struct list *)malloc(sizeof(struct list));
	mylist->first=NULL;
	mylist->number_element=0;

	//printf("\n2:%s",line);
	char *copy = strdup(line);
	char *token;
	//printf("\n3:\n%s",copy);
	token=strtok(copy, cut);
	
	while(token != NULL ) {
		//printf("\n3:\n%d\n",*token);
		char *aux=strdup(token);
		add_element(mylist, token);
		free(aux);
		token = strtok(NULL, cut);
	}
	free(copy);	
	
	//print(mylist);
	//printf("\nFIN");
	return mylist;
};


struct comands* cmdlist2cmdmatrix(struct list *ins_list){
	struct comands *list_comand;
	struct comands *list_comand2;
	struct comands *aux;
	
	struct cell *ins=ins_list->first;
	int i=0;
	
	while(i<ins_list->number_element){
		struct list *arg_list=tokenizar(ins->ins, " ");
		if(!i){
			list_comand=(struct comands *) malloc (sizeof(struct comands));
			list_comand->list=NULL;
			list_comand->next=NULL;
			list_comand->list=arg_list;
		}else{
			aux= golast(list_comand);
			list_comand2=(struct comands *) malloc (sizeof(struct comands));
			list_comand2->next=NULL;
			list_comand2->list=arg_list;
			aux->next=list_comand2;
		}
		ins=ins->next;
		i++;
	}
	return list_comand;
}





void add_element(struct list *mylist, char *new_ins){

	struct cell *new;
	
	//Estamos copiando la dir de memoria, valorar copiar el contenido a una nueva dir de memoria, para que sea un ente a parte, en vez de un punto al que apuntan dos cosas. 
	new=(struct cell *)malloc(sizeof(struct cell));
	new->ins=strdup(new_ins);
	new->next=NULL;
	//printf("\n3:\n%d\n",*new->ins);
	
	if (mylist->first==NULL){
		mylist->first=new;
	//	printf("token:%s\n", mylist->first->ins);
		mylist->number_element++;
	}else{
		struct cell *aux;
		aux=mylist->first;
	
		while(aux->next!=NULL){
			aux=aux->next;
		}
		aux->next=new;
		mylist->number_element++;
	}
}


void print(struct list *mylist){
	
	struct cell *aux;
	int i=0;
	aux=mylist->first;
	//printf("\nd:\n%d",mylist->number_element);
	while(i<mylist->number_element){
		char *word=strdup(aux->ins);
		//printf("\n%d:%s",i, word);
		free(word);
		aux=aux->next;
		i++;
	//	printf("\nvuelta");
	} 
	//printf("\nFIN");
};

void print_all(struct comands *cmdlist){

	struct comands *aux;
	aux=cmdlist;
	while(aux){
		//printf("\nNuevo comando\n");
		print(aux->list);
		aux=aux->next;
	} 
}

void free_list(struct list *mylist){

	struct cell *aux;
	struct cell *aux2;
	
	aux2=mylist->first;
	
	while (aux2!=NULL){
		aux=aux2->next;
		free (aux2->ins);
		free(aux2);
		aux2=aux;
	}
	free(mylist);
}

void free_all(struct comands *cmdlist){

	struct comands *aux;
	
	while(cmdlist){
		aux=cmdlist->next;
		free(cmdlist);
		cmdlist=aux;
	}
}


