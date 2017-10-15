#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ngrams.h"
Index* init_trie() {
	Index *trie;
	int i;
	trie = malloc(sizeof(Index));
	trie->root_size = 100;
	trie->root = malloc(trie->root_size * sizeof(trie_node*));
	for (i = 0; i < trie->root_size; i++)
	{
		trie->root[i] = NULL;
	}
	trie->root_num = 0;
	return trie;

}
trie_node* create_trie_node() {
	trie_node* node;
	node = malloc(sizeof(trie_node));
	node->word = malloc(40 * sizeof(char));
	node->node_size = 20;
	node->children = malloc(node->node_size * sizeof(trie_node *));
	int i = 0;
	for (i = 0; i < node->node_size; i++) {
		node->children[i] = NULL;
	}
	node->is_final = 'N';				//  N=no , Y=yes  //
	node->child_num = 0;
	return node;
}
int insert_ngram(Index *indx, char *phrase)
{
	char *str = strtok(phrase, " ");
	int i = 0;
	int found = -1;
	for (i = 0; i < indx->root_num; i++)
	{
		if (!strcmp(phrase, indx->root[i]->word))
		{
			found = i;
			break;
		}
	}
	if (found == -1)	//den vrethike i leksh sto root//
	{
		printf("den vrethike to prefix\n");
		if (indx->root_size == indx->root_num) //an o pinakas root einai gematos kanoume realloc(diplasiazoume)//
		{
			printf("kanw realloc\n");
			indx->root_size *= 2;
			indx->root = realloc(indx->root,indx->root_size * sizeof(trie_node));
		}
		indx->root_num++;
		indx->root[indx->root_num - 1] = create_trie_node();
		strcpy(indx->root[indx->root_num - 1]->word, str);
		char *str1 = strtok(NULL, "\n");
		if (str1 == NULL) //an exei mono mia leksh h psrash//
		{
			indx->root[indx->root_num - 1]->is_final = 'Y';
			return 1;
		}
		insert_node(indx->root[indx->root_num-1],str1);
	}
	else //to phrase uparxei sto root//
	{
		printf("vrethike to prefix\n");
		char *str1 = strtok(NULL, "\n");
		if (str1 == NULL) //an exei mono mia leksh h psrash//
		{
			printf("mia leksh\n");
			for(i=0;i<indx->root_num;i++)
				print_trie(indx->root[i]);
			indx->root[found]->is_final = 'Y';
			return 1;
		}
		insert_node(indx->root[found],str1);
	}
	for(i=0;i<indx->root_num;i++)		//PRINT VOITHITIKH GIA EMAS//
		print_trie(indx->root[i]);
}
trie_node* insert_node(trie_node* node,char* phrase)		//anadromikh sunarthsh gia insert
{
	int i;
	char *str = strtok(phrase, " ");		//pairnoume thn prwth leksh apo thn phrash pou theloume na valoume //
	char *str1 = strtok(NULL, "\n");		//pairnoume thn upoloiph frash ektos ths parapanw lekshs//
	for(i=0;i<node->child_num;i++)			//ELENXOUME AN UPARXEI H LEKSH POU PHRAME SE KAPOIO PAIDI TOU KOMVOU POU VRISKOMASTE//
	{
		if(!strcmp(str,node->children[i]->word))
		{
			insert_node(node->children[i],str1);
			return NULL;		//AN UPARXEI TERMATIZOUME EDW//
		}
	}
	node->child_num++;			//ALLIWS AUKSANOUME METRHTH PAIDIWN KAI FTIAXNOUME KAINOURGIO PAIDI(NODE)//
	node->children[node->child_num-1]=create_trie_node();
	strcpy(node->children[node->child_num-1]->word,str);	//ANTIGRAFOUME TO STRING POU PHRAME PARAPANW MESA STO NODE//
	if(str1==NULL)
	{
		return NULL;
	}
	insert_node(node->children[node->child_num-1],str1);	//PHGAINW ANADROMIKA APO TO NODE POU VRISKOMAI STO PAIDI//
}
int delete_ngram(Index* indx)
{
	return 1;
}
char* search(Index* indx)
{
	return NULL;
}
void print_trie(trie_node* node)		//ektupwnei to dentro anadromika(komvos->prwto paidi komvou->prwto paidio paidiou komvou->...->deuterp paidi komvou->deutero paidi paidiou komovou->....//
{
	int i;
	printf("word=%s\n",node->word);
	for(i=0;i<node->child_num;i++)
	{
		//printf("child_num=%d\nis_final=%c\nnode_size=%d\nword=%s\n",node->child_num,node->is_final,node->node_size,node->word);
		print_trie(node->children[i]);
	}
	//printf("teleiwsa me string=%s\n",node->word);
}
