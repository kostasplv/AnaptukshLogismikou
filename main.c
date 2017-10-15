#include <stdio.h>
#include "ngrams.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int i;
	Index *Trie;
	Trie=init_trie();
	char* init_file,*query_file,*phrase;
	FILE* init_f,*query_f;
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-i"))
		{
			init_file=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(init_file==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(init_file,argv[i+1]);
		}
		if(!strcmp(argv[i],"-q"))
		{
			query_file=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(query_file==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(query_file,argv[i+1]);
		}
	}
	init_f=fopen(init_file,"r");
	query_f=fopen(query_file,"r");
	while(1)
	{
		/*if(fscanf(init_f,"%[^\n]\n",phrase)==0)
		{
			printf("Error\n");
		}
		perror("string");
		printf("phrase=%s\n",phrase);*/
		int phrase_size=20;
		phrase=malloc(phrase_size*sizeof(char));
		int counter=0;
		char c;
		c=fgetc(init_f);
		if(c==EOF) break;
		while(c!=EOF && c!='\n')
		{
			if(counter==phrase_size)
			{
				phrase_size*=2;
				phrase=realloc(phrase,phrase_size*sizeof(char));
			}
			phrase[counter]=c;
			counter++;
			c=fgetc(init_f);
		}
		if(counter==phrase_size)
		{
			phrase_size*=2;
			phrase=realloc(phrase,phrase_size*sizeof(char));
		}
		phrase[counter]='\0';
		printf("phrase=%s\n",phrase);
		insert_ngram(Trie,phrase);
		free(phrase);
		phrase=NULL;
		if(c==EOF) break;
	}

}
