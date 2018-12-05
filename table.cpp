#include "table.h"

int main()
{
	char read_file[] = "poem.txt";
	char* buf = NULL;
	int last = 0, nlines = 0;
	if ((last = Read_Data(&buf, read_file)) == ERROR) return ERROR;
	nlines = Count_And_Adapt(buf, last);
	char** text = (char**) calloc(nlines, sizeof(char*));
	if (text == NULL) {printf("Can't create array.\n"); return ERROR;}
	Fill_Text(text, buf, last, nlines);
    
	/*table.hash_f = Hash_Func_5;
	char str[] = "Grisha";
	table.Register(str);
	Node* user = table.Find_User(str);
	printf("%s ", user->data);
	table.Register(str);*/

	HashTable table = {};
	unsigned (*hash_func_arr[nfuncs]) (char*) = {Hash_Func_1, Hash_Func_2, Hash_Func_3, \
	 										     Hash_Func_4, Hash_Func_5};
	char* filenames[nfuncs] = {"res_h1.csv", "res_h2.csv", "res_h3.csv", \
							   "res_h4.csv", "res_h5.csv"};
	for (int i = 0; i < nfuncs; ++i) {
		table.hash_f = hash_func_arr[i];
		for (int i = 0; i < nlines; ++i)
			table.Register(text[i]);
		table.Dump_To_File(filenames[i]);
		table.Clear();
	}
	printf("Success.\n");
}	
