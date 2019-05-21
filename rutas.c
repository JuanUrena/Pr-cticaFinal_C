#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <vector>

void getFiles(char pattern[])

{
  //Declare glob_t for storing the results of globbing
  glob_t globbuf;
  
  //Glob.. GLOB_TILDE tells the globber to expand "~" in the pattern to the home directory
  glob(pattern, GLOB_ERR, NULL, &globbuf);
  
	printf("pattern:\n%s\n",pattern);
	printf("number:\n%zd\n",globbuf.gl_pathc);
  
  

  for( int i = 0; i < globbuf.gl_pathc; ++i )
     printf("path:\n%s\n",globbuf.gl_pathv[i]);
  //Free the globbuf structure

  if( globbuf.gl_pathc > 0 )
    globfree( &globbuf );
}

int main(){
	getFiles("/*");
	return 0; 

}
