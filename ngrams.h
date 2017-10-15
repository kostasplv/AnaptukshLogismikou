#ifndef NGRAMS_H_
#define NGRAMS_H_
typedef struct Index Index;
typedef struct trie_node trie_node;
struct trie_node
{
	char* word;
	trie_node** children;
	char is_final;
	int child_num;
	int node_size;
};
struct Index
{
	trie_node** root;
	int root_size;
	int root_num;
};

Index* init_trie();
trie_node* create_trie_node();
int insert_ngram(Index*,char*);
int delete_ngram(Index*);
trie_node* insert_node(trie_node* node,char* phrase);
char* search(Index*);
void print_trie(trie_node*);





#endif /* NGRAMS_H_ */
