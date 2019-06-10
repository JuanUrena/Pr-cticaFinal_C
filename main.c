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
#include "input.h"
#include "propsys.h"


struct 	conex{
	int input;
	int output;
};


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
	int NoOfOwnCmds = 1;
	int i;
	int switchOwnArg = 0; 
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


int waitchilds(){
	int childs;
	int lastchild=0;
	int result=1;
	int  status;
	do {	
		childs=wait(&status);
		if(status == -1) {
			perror("Error during wait()");
			return(1);
		}
		if (childs>lastchild){
			result=status;
			lastchild=childs;
		}
	} while (childs > 0);

	printf("\n-----FIN-----");
	return(result);
}


void son_code(glob_t glob){
	int i=0;
	char *route;
	
	if (glob.gl_pathc){
		char *arr[glob.gl_pathc+1];
		route=get_route(glob.gl_pathv[0]);	
		if (route){	
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
}


char* prepare_value(char *word){
	char *value=NULL;
	glob_t globbuf;
	int i;
	
	if (word){
		glob(word, GLOB_NOCHECK, NULL, &globbuf);
		for(i = 0; i < globbuf.gl_pathc; i++ ){
			if (value){
				value=(char *) realloc(value, strlen(value)+strlen(globbuf.gl_pathv[i])+2);
				strcat(value, ":");
			}else{
				value=(char *) calloc(1,strlen(globbuf.gl_pathv[i])+1);
			}
			strcat(value, globbuf.gl_pathv[i]);
		}
		globfree(&globbuf);		
	}else{
		value=strdup("\0");
	}
	return value;
}


void env_var_code(struct value_var *check_var){
	char *var_form;
	
	check_var->variable=env_variable(check_var->variable);
	check_var->value=env_variable(check_var->value);
	 						 
	var_form=prepare_value(check_var->value);
	
	setenv(check_var->variable, var_form, 1);					 		
	free(check_var->variable);
	free(var_form);
}


struct conex* modelate_pipe(int i, int total,char *file, int output){
	int in=0;
	int out=0;
	int fd[2];
	
	struct conex *result=(struct conex*) malloc (sizeof(struct conex));
	if(i==total){
		if (file){
			remove_spaces(file);							
			out=open(file, O_WRONLY|O_CREAT, 
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
		} else{
			out=dup(output);
		}
	}else{
		pipe(fd);
		out=fd[1];
		in=fd[0];
	}
	result->input=in;
	result->output=out;
	return result;
}


struct param_cmd* process_line(char *cmd_line){
	struct param_cmd *param_cmd_line;
	
	if(cmd_line){
		if (!strlen(cmd_line)){
			free(cmd_line); 
			exit(waitchilds());
		}
		replace_char(cmd_line, '\t', ' ');
		param_cmd_line=param_line(cmd_line);
		free(cmd_line);
		return param_cmd_line;
	}else{
		return NULL;
	}
}

int process_input(char* file, int wait, int input){
	int in;
	if (file){
	//estamos quitando espacios sin mas, si estan en medio dejarlos?¿
		remove_spaces(file);
		in=open(file, O_RDONLY);
	}else if(!wait){
		in =open("/dev/null",O_RDONLY); 
	} else{
		in =dup(input);
	}
	return in;
}

int wait_cmd_child(int num_child, int last_child)
{
	printf("ultimo %d \n",last_child);
	int status;
	int result=1;
	for(int x=0;x<num_child;x++){ 
		int pid=waitpid(-1, &status, 0);
		if WIFEXITED(status){
			if (pid==last_child){
				result=status;
			}
   		} 
	}
	return result;
}
   
int main(int argc, char *argv[])
{
	char *text;
	char *here_line;
	char *end;
	struct conex *pipe_conex;
	struct list *ins_list;
	struct list *arg_list;
	//struct cell *ins;
	struct comands *list_comand;
	struct comands *list_comand2;
	//struct comands *aux;
	struct value_var *check_var;
	struct param_cmd *cmd_line;	
	
	int child;
	int num=0;
	int input=0;
	int output=0;
	int in;
	int out;
	int n_cmd;
	int fd[2];
  
	do{
		
		list_comand=NULL;
		arg_list=(struct list *) malloc (sizeof(struct list));
		free(arg_list);
		text=read_line();
		cmd_line=process_line(text);
		if (cmd_line && cmd_line->comand){
			ins_list=tokenizar(cmd_line->comand, "|");
			n_cmd=ins_list->number_element;
			list_comand=cmdlist2cmdmatrix(ins_list);
			free_list(ins_list);
			list_comand2=list_comand;
			
			input=dup(0);
			output=dup(1);
			//ext
			if (cmd_line->here){
				pipe(fd);
				out=fd[1];
				in=fd[0];
			}else{
				in =process_input(cmd_line->in, cmd_line->wait, input);
			}
			num=0;	
			
			while (list_comand2!=NULL){	
				check_var=check_var_value(list_comand2->list->first->ins);
				if (check_var->var){
					env_var_code(check_var);
					n_cmd--;
				}else{
					subs_env(list_comand2->list);
					glob_t glob=expand_arg(list_comand2->list);
					if(ownCmdHandler(glob)){
						dup2(in,0);
						close (in);

						pipe_conex=modelate_pipe(num, n_cmd-1,cmd_line->out,output);	
						in=pipe_conex->input;
						dup2(pipe_conex->output,1);
						close(pipe_conex->output);
						free(pipe_conex);
				 		
						child=fork();
						switch(child){
						case 0:
							close(fd[1]);
							son_code(glob);
							free_all(list_comand);
							free(cmd_line->comand);
							free(cmd_line->in);
							free(cmd_line->out);
							free(cmd_line);
							break;
						case -1:
							fprintf(stderr, "for failed");
							return 1;
							break;
						}
						num++;
					}else{
						n_cmd--;
					}
					globfree(&glob);
				}
				list_comand2=list_comand2->next;
			}
			close(fd[0]);
			dup2(input, 0);
			dup2(output,1);
			if (cmd_line->here){
				end=strdup("}");
				char *buff=read_line();
				here_line=(char *)calloc(1,1);
				while(strcmp(buff, end)){
					here_line=realloc(here_line, strlen(here_line)+2+strlen(buff));
					strcat(here_line, buff);
					strcat(here_line, "\n");
					free(buff);
					buff=read_line();
				}
				write(out, here_line, strlen(here_line));
				free(here_line);
				close(out);
				free(here_line);
				free(end);
				dup2(input, 0);
				dup2(output,1);
				close(input);
				close(output);
			}
			if (cmd_line->wait){
				int exit_cmd=wait_cmd_child(num, child);
				printf("SALIDA:%d\n", exit_cmd);
			}
			free_all(list_comand);
			free(cmd_line->comand);
			free(cmd_line->in);
			free(cmd_line->out);
			free(cmd_line);				
		}

	}while(1);
	return 0;
};
