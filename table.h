#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int nlists = 937;
const int ERROR = -1;
const int nfuncs = 5;
const int base = 53;

struct Node 
{
	char* data;
	Node* next;
	Node* prev;
};

struct List 
{
	Node* head;
	unsigned size;
};

Node* Create_Node (char* data);
void Add_Node (List* list, char* data);
void Delete_Node (List* list, char* data);
Node* Find_Node (List list, char* data);
void Delete_List (List* list);
unsigned Hash_Func_1 (char* data);
unsigned Hash_Func_2 (char* data);
unsigned Hash_Func_3 (char* data);
unsigned Hash_Func_4 (char* data);
unsigned Hash_Func_5 (char* data);

int Read_Data (char** buf_ptr, char read_file[]);
int Calculate_Size (FILE* read);
int Count_And_Adapt (char* buf, int last);
void Fill_Text (char** text, char* buf, int last, int nlines);

struct HashTable
{
	List lists[nlists];
	unsigned (*hash_f) (char*);

	void Register (char* data)
	{
		unsigned n = hash_f(data) % nlists;
		Add_Node(&lists[n], data);
	}

	void Delete_User (char* data)
	{
		unsigned n = hash_f(data) % nlists;
		Delete_Node(&lists[n], data);
	}

	Node* Find_User (char* data)
	{
		unsigned n = hash_f(data) % nlists;
		return Find_Node(lists[n], data);
	}

	void Dump_To_File (char* filename)
	{
		FILE* write = fopen(filename, "w");
		fprintf (write, "number; ");
		for (int i = 0; i < nlists; ++i) 
			fprintf (write, "%d; ", i + 1);
		fprintf (write, "\nsize; ");
		for (int i = 0; i < nlists; ++i)
			fprintf (write, "%u; ", lists[i].size);
	}

	void Clear ()
	{
		for (int i = 0; i < nlists; ++i)
			Delete_List(&lists[i]);
		hash_f = NULL;
	}
};
#include "hash_funcs.cpp"
#include "list_funcs.cpp"
