// week5.c
#include <stdio.h>
#include "list_wk5.h"
#include "hashtable_wk5.h"


int main() {
	int command = 1;
	HashTable table = create_hashtable(11);
	char buffer[100];

	while (command) {
		// menu for easier user interaction
		printf("Press 1 for insert\n");
		printf("Press 2 for delete\n");
		printf("Press 3 for print\n");
		printf("Press 0 for exit\n");
		scanf_s("%d", &command);

		switch (command) {
		case 1:
			scanf_s("%s", buffer, 100);
			hash_insert(&table, buffer);
			break;
		case 2: // TODO: remove
			scanf_s("%s", buffer, 100);
			hash_remove(&table, buffer);
			break;
		case 3: // TODO: print
			hash_print(&table);
			break;
		}
		printf("\n");
	}
	// TODO: destroy
	hash_destroy(&table);
}

int main1()
{
	List test1 = new_list();

	insert_at_front(&test1, "Test");
	insert_at_front(&test1, "Test1");
	insert_at_front(&test1, "Test2");
	insert_at_front(&test1, "Test3");

	print_list(&test1);

	delete_from_list(&test1, "Test2");
	print_list(&test1);

	delete_from_list(&test1, "Test3");
	print_list(&test1);

	delete_from_list(&test1, "Test");
	print_list(&test1);

	destroy_list(&test1);

	return 0;
}