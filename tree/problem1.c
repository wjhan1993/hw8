/* problem1.c - implementation of Linux `tree` 
 * Wenjie Han (whan02)
 * EE200, hw8
 *
 */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
  // function declaration
  void tree(DIR *, int, char *);
  
  DIR *dir;
  char *directory;
  
  if (argc > 1)
    // input directory
    directory = argv[1];
  else  
    // current directory
    directory = ".";
  
  dir  = opendir(directory);

  // If directory is not given validly, terminate the process
  if (dir == NULL)
  {
    printf("No valid input directory!");
    return(1);
  }
  
  // tree prints out the subdirectory structure 
  tree(dir,0,directory);
  
  closedir(dir);
  return(0);
}

// space is the number of indent spaces, initialized as 0 
void tree(DIR *dir,int space, char * currentDir)
{
  struct dirent * dp;
  
  // prints out all subdirectories
  while((dp = readdir(dir)) != NULL)
    {
      if (strcmp(dp->d_name,"..") && strcmp(dp->d_name,".") \
	                          && strcmp(dp->d_name,".DS_Store"))
	// .DS_Store is automatically generated in Mac OS
	{
	  int i;
	  // print spaces for indenting
	  for (i = 0; i < space; i++)
	      printf("%s"," ");
	  
	  // print the current working directory
          printf("%s\n",dp->d_name);

	  // get subdirectory's full path
	  char subPath[500];
	  snprintf(subPath,sizeof(subPath),"%s/%s",currentDir,dp->d_name);
	  
          DIR *subDir = opendir(subPath);
	  if (subDir != NULL)
	    {
	      space = space + 4;
              // recursion
	      tree(subDir,space,subPath);
	      space = space - 4;
	    }
	}
    }
}

