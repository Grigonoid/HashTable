Node* Create_Node (char* data)
{
	Node* new_node = new Node;
	new_node->data = new char[strlen(data) + 1];
	strcpy(new_node->data, data);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void Add_Node (List* list, char* data)
{
	if (Find_Node(*list, data) == NULL) {
		Node* new_node = Create_Node(data);
		if (!list->head) {
			list->head = new_node;
		}
		else {
			new_node->next = list->head;
			list->head->prev = new_node;
			list->head = new_node;
		}
		list->size++;
	}
	//else printf("Element already exists\n");
}

Node* Find_Node (List list, char* data)
{
	if (!list.head) return NULL;
	while (list.head)
		if (!strcmp(list.head->data, data))
			return list.head;
		else
		   	list.head = list.head->next;
	return NULL;
}	

void Delete_Node (List* list, char* data)
{
	Node* node_to_delete = Find_Node(*list, data); 
	if (node_to_delete != NULL) {
		delete []node_to_delete->data;
		if (node_to_delete->next != NULL)
			node_to_delete->next->prev = node_to_delete->prev;
		if (node_to_delete->prev == NULL) 
			list->head = node_to_delete->next;
		else 
			node_to_delete->prev->next = node_to_delete->next;
		delete node_to_delete;
		list->size--;
		node_to_delete = NULL;
	}
	//else printf("Nothing to delete\n");
}

void Delete_List (List* list)
{
	if (list->head != NULL) {
		while (list->head->next != NULL) {
			delete []list->head->data;
			list->head = list->head->next;
			delete list->head->prev;
		}
		delete []list->head->data;
		delete list->head;
		list->head = NULL;
		list->size = 0;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int Calculate_Size (FILE* read)
{
	fseek (read, 0, SEEK_END);
	int size = ftell(read);
	fseek (read, 0, SEEK_SET);
	return size;
}
	
int Read_Data (char** buf_ptr, char read_file[])
{
	FILE* read = fopen(read_file, "r");
	if (!read) {printf("Cannot open %s.\n", read_file); return ERROR;}
	int size = Calculate_Size(read);
	*buf_ptr = (char*) calloc(size+1, sizeof(char));
	if (*buf_ptr == NULL) {printf("Can't create array.\n"); return ERROR;}
	int last = fread (*buf_ptr, sizeof(char), size, read);
	*buf_ptr = (char*) realloc(*buf_ptr, (last+1)*sizeof(char));
	if (*buf_ptr == NULL) {printf("Can't create array.\n"); return ERROR;}
	(*buf_ptr)[last] = '\n';
	fclose(read);
	return last;
}

int Count_And_Adapt (char* buf, int last)
{
	int nlines = 0;
	for (int i = 0; i <= last; ++i) {
		if (buf[i] == '\n') {
			++nlines;
			buf[i] = '\0';
			while (i + 1 <= last && buf[i+1] == '\n')
				++i;
		}
	}
	return nlines;
}

void Fill_Text (char** text, char* buf, int last, int nlines)
{
	text[0] = &buf[0];
	int count = 1;
	for (int i = 0; i < last; ++i) { 
		if (buf[i] == '\0') {
			while (i + 1 <= last && buf[i+1] == '\n')
				++i;
			text[count] = &buf[i+1];
			++count;
			if (count == nlines) break;
		}
	}
}
