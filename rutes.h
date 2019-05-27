#include <glob.h>

void getFiles(struct list *mylist);

void getFiles(struct list *mylist){
	
	struct cell *iterator=mylist->first;
	
//Declare glob_t for storing the results of globbing
	glob_t globbuf;
  
//Glob.. GLOB_TILDE tells the globber to expand "~" in the pattern to the home directory
//Primer elemento sin apend
	
	glob(iterator->ins, GLOB_NOCHECK, NULL, &globbuf);
	printf("word:\n%s\n",iterator->ins);
	
	int i=1;
	
	while (i<mylist->number_element){
		iterator=iterator->next;
		i++;
		printf("word:\n%s\n",iterator->ins);	
		glob(iterator->ins, GLOB_NOCHECK|GLOB_APPEND, NULL, &globbuf);	
	}
	printf("number:\n%zd\n",globbuf.gl_pathc);
  
  

	for(i = 0; i < globbuf.gl_pathc; i++ ){
		printf("path:\n%s\n",globbuf.gl_pathv[i]);
	}
  //Free the globbuf structure
}
