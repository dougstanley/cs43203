/**
 * pack.c
 *
 * Over simplified example of packing
 * a struct to disk, and then unpacking
 * it again.
 *
 * Uses an extra field to declare string
 * length to make unpacking easier.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned short item_id;
	unsigned int item_count;
	unsigned int item_desc_len;
	char *item_desc;
} item;

int pack(item *i, FILE *db){
	fwrite( &i->item_id, sizeof(unsigned short), 1, db);
	fwrite( &i->item_count, sizeof(unsigned int), 1, db);
	fwrite( &i->item_desc_len, sizeof(unsigned int), 1, db);
	fwrite( i->item_desc, sizeof(char), i->item_desc_len, db);
}

int unpack( item *i, FILE *db){
	fread( &i->item_id, sizeof(unsigned short), 1, db);
	fread( &i->item_count, sizeof(unsigned int), 1, db);
	fread( &i->item_desc_len, sizeof(unsigned int), 1, db);

	//malloc enough memory to store the string
	i->item_desc = (char *)malloc(sizeof(char) * i->item_desc_len);
	//read in the number of bytes specified in the item_desc_len
	fread( i->item_desc, sizeof(char), i->item_desc_len, db);
}

int main(){

	FILE *db;
	item foo;

	db = fopen("test.dat","wb");

	foo.item_id = 5;
	foo.item_count = 10000002;
	foo.item_desc = "Some test item";
	foo.item_desc_len = strlen(foo.item_desc);

	pack( &foo, db );

	fclose(db);
	
	memset( &foo, 0, sizeof(item) );

	db = fopen("test.dat", "rb");
	unpack( &foo, db );
	fclose(db);

	printf("%s\n", foo.item_desc);

	return 0;
}
