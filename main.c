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

//Paquetes propios
#include "list.h"
#include "token.h"
#include "read.h"
#include "rutes.h"


//Comprueba que el ultimo char distinto de espacio en blanco es el indicado
/*int check_lastchar(char *phrase, char letter)
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
}*/


//Elimina los espacios de un string
void remove_spaces(char* source)
{
	char* i = source;
	char* j = source;
	while(*j != 0){
		*i = *j++;
	if(*i != ' ')
		i++;
	}
	*i = 0;
}

//sustituimos en la lista las posibles variables de entorno
void subs_env(struct list *mylist){
	int i=0;
	struct cell *aux=mylist->first;
	
	while(i<mylist->number_element){
		aux->ins=env_variable(aux->ins);
		aux=aux->next;
		i++;
	}
}

//Cambia en el string el char actual por el nuevo
void replace_char(char* string, char actual, char new){
	if (string){
		for(int i=0; i<strlen(string); i++){
			if (string[i]==actual){
				string[i]=new;
			}
		}
	}
}

//NO USADA ACTUALMENTE
void generate_pipe(int num_pipes,int pipes[num_pipes][2]){

	for(int i=0; i<num_pipes-1; i++){
		if (pipe(pipes[i]) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    	}
	}
}


//Funcion para generar el array desde mi lista
void generate_array(glob_t glob, char *arr[glob.gl_pathc+1]){
	int i=0;
	for(i=0;i < glob.gl_pathc; i++ ){
		arr[i]=glob.gl_pathv[i];
	}
	arr[i]=NULL; 
}


// Function to execute builtin commands 
int ownCmdHandler(glob_t glob) 
{ 
	int NoOfOwnCmds = 1, i, switchOwnArg = 0; 
	char* ListOfOwnCmds[NoOfOwnCmds]; 

	int result=1;
	ListOfOwnCmds[0] = "cd";  

	for (i = 0; i < NoOfOwnCmds; i++) { 
		if (strcmp(glob.gl_pathv[0], ListOfOwnCmds[i]) == 0) { 
			switchOwnArg = i + 1; 
			break; 
		} 
	} 
  
	switch (switchOwnArg) { 
	case 1: 
		printf("CD");
		char *home;
		if (glob.gl_pathc>1){
			home=glob.gl_pathv[1];
		}else{
			home=getenv("HOME");
		}
		result=chdir(home);
		return result; 
	default: 
		break; 
	} 
	return 1; 
} 



int main(int argc, char *argv[])
{
	char *text;

	struct list *ins_list;
	struct list *arg_list;
	//struct cell *ins;
	struct comands *list_comand;
	struct comands *list_comand2;
	//struct comands *aux;
	
	struct param_cmd *cmd_line;	

  
	do{
		list_comand=NULL;
		arg_list=(struct list *) malloc (sizeof(struct list));
		free(arg_list);
		int i=0;
	//La linea de comandos
		text=read_line();
	//compruebo si es EOF
		if(text){
			if (!strlen(text)){
				free(text); 
				int childs;
				do {
					int  status;
					childs=wait(&status);
					if(status == -1) {
						perror("Error during wait()");
						abort();
					}
				} while (childs > 0);
								
				printf("\n-----FIN-----");
				return 0;
			}
			replace_char(text, '\t', ' ');
			cmd_line=get_in_out(text);
			
			free(text);
			if (cmd_line->comand){
				ins_list=tokenizar(cmd_line->comand, "|");
				list_comand=cmdlist2cmdmatrix(ins_list);
			/*	ins=ins_list->first;
				i=0;
				while(i<ins_list->number_element){

					arg_list=tokenizar(ins->ins, " ");
					if(!list_comand){
						list_comand=(struct comands *) malloc (sizeof(struct comands));
						list_comand->list=NULL;
						list_comand->next=NULL;
					
						list_comand->list=arg_list;
					}else{
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
				}*/
				list_comand2=list_comand;
				struct value_var *check_var;
					
				int input=dup(0);
				int output=dup(1);
									
				int num=0;
					
				int in;
				if (cmd_line->in){
					//estamos quitando espacios sin mas, si estan en medio dejarlos?¿
					remove_spaces(cmd_line->in);
					in=open(cmd_line->in, O_RDONLY);
				}else if(!cmd_line->wait){
					in =open("/dev/null",O_RDONLY); 
				} else{
					in =dup(input);
				}
					
				int child;
				int out;
					
				while (list_comand2!=NULL){
					
					check_var=check_var_value(list_comand2->list->first->ins);
						

					if (check_var->var){
					 		
						check_var->variable=env_variable(check_var->variable);
						check_var->value=env_variable(check_var->value); 						 
						char *var_aux=prepare_value(check_var->value);
						setenv(check_var->variable, var_aux, 1);					 		
						free(check_var->variable);
						free(check_var);
						free(var_aux);
					}else{
						subs_env(list_comand2->list);
						glob_t glob=getFiles(list_comand2->list);
						if(ownCmdHandler(glob)){
							dup2(in,0);
							close (in);
					 	
							if(num==ins_list->number_element-1){
								if (cmd_line->out){
									remove_spaces(cmd_line->out);							
									out=open(cmd_line->out, O_WRONLY|O_CREAT, 
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
								} else{
									out=dup(output);
								}
							}else{
								int fd[2];
								pipe(fd);
								out=fd[1];
								in=fd[0];
							}
							dup2(out,1);
							close(out);
					 	
							child=fork();
							switch(child){
							case 0:
								if (glob.gl_pathc){
									char *route=get_route(glob.gl_pathv[0]);	
									if (route){
											//printf("%s\n", route);
										char *arr[glob.gl_pathc+1];
										for(i=0;i < glob.gl_pathc; i++ ){
											arr[i]=glob.gl_pathv[i];
										}
										arr[i]=NULL; 
										execv(route,arr);			
									}else{
										exit (0);
									}
							 		globfree(&glob);
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
						 	//printf("\n fail \n");
						 		fprintf(stderr, "for failed");
						 		return 1;
						 		break;
						 	}
							num++;
						}
						globfree(&glob);
					}
					list_comand2=list_comand2->next;
				}
				dup2(input, 0);
				dup2(output,1);
				close(input);
				close(output);
				if (cmd_line->wait){
					int status;
					printf("ultimo %d \n",child);
					for(int x=0;x<num;x++){ 
						int pid=waitpid(-1, &status, 0);
						if WIFEXITED(status){
							printf("Fin hijo %d :%d\n",pid, status);
    					} 
     				}
     			}
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
