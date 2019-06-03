#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <err.h>


#include "list.h"
#include "token.h"
#include "read.h"
#include "rutes.h"


void remove_spaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

void subs_env(struct list *mylist){
	int i=0;
	struct cell *aux=mylist->first;
	
	while(i<mylist->number_element){
		aux->ins=env_variable(aux->ins);
		aux=aux->next;
		i++;
	}
}

void generate_pipe(int num_pipes,int pipes[num_pipes][2]){

	for(int i=0; i<num_pipes-1; i++){
		if (pipe(pipes[i]) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    	}
	}
}

void close_pipes(int num, int num_pipes, int pipes[num_pipes][2]){
	for (int i=0; i<num_pipes; i++){
		if(i==num){
			close (pipes[i][0]);
			dup2(pipes[i][1], 1);
			close (pipes[i][1]);
		
		}else if (i==(num-1)){
			close(pipes[i][1]);
			dup2(pipes[i][0], 0);
			close(pipes[i][0]);
		
		}else{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
	} 
}

void son_code(int num, int num_pipes, int pipes[num_pipes][2]){
	close_pipes(num, num_pipes, pipes);	
	printf("mensaje");
	exit(0);
}

void generate_array(glob_t glob, char *arr[glob.gl_pathc+1]){
	int i=0;
	for(i=0;i < glob.gl_pathc; i++ ){
		arr[i]=glob.gl_pathv[i];
	}
	arr[i]=NULL; 
}



// Function to execute builtin commands 
int ownCmdHandler(char *comand) 
{ 
    int NoOfOwnCmds = 1, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
   
    ListOfOwnCmds[0] = "cd";  
  
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(comand, ListOfOwnCmds[i]) == 0) { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
  
    switch (switchOwnArg) { 
    case 1: 
       printf("CD"); 
        return 1; 
    default: 
        break; 
    } 
    return 0; 
} 




int main(int argc, char *argv[])
{
	char *text;
//	char *text2;

	
	struct list *ins_list;
	struct list *arg_list;
	//struct list *list_equiality;
	struct cell *ins;
//	struct list *comand;
	struct comands *list_comand;
	struct comands *list_comand2;
	struct comands *aux;
	
	struct param_cmd *cmd_line;	
//	struct cell *aux;	

  
	do{
		//list_comand=(struct comands *) malloc (sizeof(struct comands));
		list_comand=NULL;
		arg_list=(struct list *) malloc (sizeof(struct list));
		free(arg_list);
		int i=0;
	//La linea de comandos
		text=read_line();
	//	text2=strdup(text);
	//compruebo si es EOF
		if(text){
			if (!strlen(text)){
				free(text);
				printf("\n-----FIN-----");
	  			return 0;
			}
			
			
			cmd_line=get_in_out(text);
			
			free(text);
			//printf("\n%s\n%s\n%s\n",cmd_line->comand, cmd_line->in, cmd_line->out);
		//lista de las instrucciones 
			if (cmd_line->comand){
				ins_list=tokenizar(cmd_line->comand, "|");
				printf("EEEEEEOOOO%d\n",ins_list->number_element);
				
				int conex[ins_list->number_element][2];
				
				generate_pipe(ins_list->number_element-1, conex);
			
			
			//obtengo para cada instruccion su lista de argumentos. 
				ins=ins_list->first;
				//printf("%d",ins_list->number_element);
				while(i<ins_list->number_element){
				//printf("%dSE AÑADE ELEMENTO",ins_list->number_element);
			//	printf("SE AÑADE ELEMENTO");
				arg_list=tokenizar(ins->ins, " ");
			//	printf("SE AÑADE ELEMENTO");
			//	print(arg_list);
					
					
					if(!list_comand){
						//printf("\nSE AÑADE EL PRIMER ELEMENTO");
						list_comand=(struct comands *) malloc (sizeof(struct comands));
						list_comand->list=NULL;
						list_comand->next=NULL;
					
						list_comand->list=arg_list;
					}else{
					//	printf("\nSE AÑADE OTRO ELEMENTO");
						list_comand2=list_comand;
						while (list_comand2){
							aux=list_comand2;
							list_comand2=list_comand2->next;
						}
						list_comand2=(struct comands *) malloc (sizeof(struct comands));
						list_comand2->next=NULL;
						list_comand2->list=arg_list;
						aux->next=list_comand2;
					}
				
					ins=ins->next;
				
					i++;
				};
				
			//	print(ins_list);
			//	ins=ins_list->first;
			//	while (ins!=NULL){
			//		aux=ins->next;
			//		free(ins);
			//		ins=aux;
			//	}
			
			//Vamos a comprobar que cada elemento en la lista si es una asignacion de variable
				//printf("\nINICIO\n"); 
					list_comand2=list_comand;
					struct value_var *check_var;
				int num=0;
				 while (list_comand2!=NULL){
				 	//printf("\nINICIO\n"); 
				 	//getFiles(list_comand2->list);//globbing
				 	//Como hacer el globbing y a la vez la expansion del comando, o quizas deba hacerlo luego sobre valor y value?¿?¿?¿
					switch(fork()){
					case 0:
						//Primero, redirigir mi entrada al fichero
						if (num==0){
							if (cmd_line->in){
								//estamos quitando espacios sin mas, si estan en medio dejarlos?¿
								remove_spaces(cmd_line->in);
								int file=open(cmd_line->in, O_RDONLY);
								if (file>=0){
									printf("%s\n",cmd_line->in); 
									dup2(file, 0);
									close(file);
								}//error!!
							}
						//utlimo, redirijo mi salida
						}
						if(num==ins_list->number_element-1){
							if (cmd_line->out){
								remove_spaces(cmd_line->out);							
								//estamos quitando espacios sin mas, si estan en medio dejarlos?¿
								//valorar la opcion de append si tiene >>?¿?¿?
								int file=open(cmd_line->out, O_WRONLY|O_CREAT, 
S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
								if (file>=0){
									printf("%s\n",cmd_line->out);
									dup2(file, 1);
									close(file);
								}//error!!
							}
						}
						close_pipes(num, ins_list->number_element-1, conex);
						printf("I am child process my ID is   =  %d\n" , getpid());
						check_var=check_var_value(list_comand2->list->first->ins);
						//printf("AQUI:::%d\n", check_var->var); 	
					 	if (check_var->var){
					 		//hacer globbing aqui?¿?¿
					 		check_var->variable=env_variable(check_var->variable);
					 		check_var->value=env_variable(check_var->value);
					 		
					 		char *var_aux=prepare_value(check_var->value);
			
					 		//list_equiality=(struct list *) malloc (sizeof(struct list));
					 		//add_element(list_equiality, check_var->variable);
					 		//add_element(list_equiality, check_var->variable);
					 		printf("\nAsignacion de Variable\n%s\n%s\n", check_var->variable, check_var->value);
					 		int result_env=setenv(check_var->variable, var_aux, 1);
					 		free(check_var->variable);
					 		//printf("1");
					 		//liberar value?¿?¿? me da invalid pointer
					 		//printf("2");
					 		free(check_var);
					 		//printf("3");
					 		free(var_aux);
					 		//printf("4");
					 		return result_env;
					 	}else{
					 		printf("\nEjecución de comando\n");
					 		subs_env(list_comand2->list);
					 		glob_t glob=getFiles(list_comand2->list);//globbing
					 		//Comprobar el free
					 		
					 		if (glob.gl_pathc){
					 			if (!ownCmdHandler(glob.gl_pathv[0])){
					 			
							 		char *route=get_route(glob.gl_pathv[0]);
							 		if (route){
										printf("path:%s\n",route);
									
									}
	
									char *arr[glob.gl_pathc+1];
									
									generate_array(glob, arr);
									for(i=0; i < glob.gl_pathc+1; i++ ){
										printf("\nARG:%s", arr[i]);
									}
									if (route){
										execv(route,arr);
										
									}
								}
						 		globfree(&glob);
						 	}
					 	}
					 	free_all(list_comand);
						free_list(ins_list);
						free(cmd_line->comand);
						free(cmd_line->in);
						free(cmd_line->out);
						free(cmd_line);
						return 0;
					 	break;
					 case -1:
					 	fprintf(stderr, "for failed");
					 	return 1;
					 	break;
					 }
					 	
				 	list_comand2=list_comand2->next;
				 	num++;
				 }
				 int status;
				 for(int x=0;x<num;x++){ 
    				waitpid(-1, &status, 0);
    				if WIFEXITED(status){
    					printf("Fin hijo:%d", status);
    				} 
     			}
				printf("I am DAD process my ID is   =  %d\n" , getpid());
				//printf("\n3:\n%s",text2);
				//print_all(list_comand);
				free_all(list_comand);
				free_list(ins_list);
				free(cmd_line->comand);
				free(cmd_line->in);
				free(cmd_line->out);
				free(cmd_line);				
			}
		}

	}while(1);
  
	return 0;
};
