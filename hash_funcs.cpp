unsigned Hash_Func_1 (char* data)
{
	return data[0];
}

unsigned Hash_Func_2 (char* data)
{
	return strlen(data);
}

unsigned Hash_Func_3 (char* data)
{
	unsigned sum = 0;
	for (int i = 0; i < strlen(data); ++i)
		sum += data[i];
	return sum;
}

unsigned Hash_Func_4 (char* data)
{
	unsigned sum = 0;
	for (int i = 0; i < strlen(data); ++i)
		sum += data[i] * i;
	return sum;
}

unsigned Hash_Func_5 (char* data)
{
	unsigned sum = 0;
	unsigned mult = 1;
	for (int i = 0; i < strlen(data); ++i) {
		sum += data[i] * mult;
		mult *= base;
	}
	return sum;
}
