#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "alist.h"

void print_list(const struct alist *l)
{
	printf("size:%d head:%x count:%d\n", l->size, l->head, l->count);	
}

void run_tests(void)
{
	struct alist list;
	size_t first, second, third;

	printf("* initializing list\n");

	alist_init(&list, 3);
	print_list(&list);
	
	printf("count:");
	assert(0 == alist_count(&list));
	printf("OK\n");
	printf("empty:");
	assert(alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");

	printf("* adding one item\n");
	first = alist_add(&list);
	print_list(&list);

	printf("count:");
	assert(1 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("first:");
	assert(first == alist_first(&list));
	printf("OK\n");
	printf("last:");
	assert(first == alist_last(&list));
	printf("OK\n");

	printf("* adding a second item\n");
	second = alist_add(&list);
	assert(second != first);
	print_list(&list);

	printf("count:");
	assert(2 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("first:");
	assert(first == alist_first(&list));
	printf("OK\n");
	printf("last:");
	assert(second == alist_last(&list));
	printf("OK\n");

	printf("* adding a third item\n");
	third = alist_add(&list);
	assert(third != second);
	assert(third != first);
	print_list(&list);
	
	printf("count:");
	assert(3 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("full:");
	assert(alist_is_full(&list));
	printf("OK\n");
	printf("first:");
	assert(first == alist_first(&list));
	printf("OK\n");
	printf("last:");
	assert(third == alist_last(&list));
	printf("OK\n");

	printf("* dequeing one item\n");
	printf("front:");
	assert(first == alist_front(&list));
	printf("OK\n");
	printf("dequeue:");
	assert(first == alist_dequeue(&list));
	printf("OK\n");
	print_list(&list);
	printf("count:");
	assert(2 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("new front:");
	assert(second == alist_front(&list));
	printf("OK\n");

	printf("* dequeing another item\n");
	printf("dequeue:");
	assert(second == alist_dequeue(&list));
	printf("OK\n");
	print_list(&list);
	printf("count:");
	assert(1 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("new front:");
	assert(third == alist_front(&list));
	printf("OK\n");

	printf("* dequeue the last item\n");
	printf("dequeue:");
	assert(third == alist_dequeue(&list));
	printf("OK\n");
	print_list(&list);
	printf("count:");
	assert(0 == alist_count(&list));
	printf("OK\n");
	printf("empty:");
	assert(alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");

	printf("* pushing two items\n");
	first = alist_push(&list);
	second = alist_push(&list);
	assert (first != second);
	print_list(&list);
	
	printf("count:");
	assert(2 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("top:");
	assert(second == alist_top(&list));
	printf("OK\n");
	
	printf("* popping one element\n");
	printf("pop:");
	assert(second == alist_pop(&list));
	printf("OK\n");
	print_list(&list);
	
	printf("count:");
	assert(1 == alist_count(&list));
	printf("OK\n");
	printf("not empty:");
	assert(!alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");
	printf("top:");
	assert(first == alist_top(&list));
	printf("OK\n");

	printf("* popping the last element\n");
	printf("pop:");
	assert(first == alist_pop(&list));
	printf("OK\n");
	print_list(&list);

	printf("count:");
	assert(0 == alist_count(&list));
	printf("OK\n");
	printf("empty:");
	assert(alist_is_empty(&list));
	printf("OK\n");
	printf("not full:");
	assert(!alist_is_full(&list));
	printf("OK\n");


	printf("OK, no problem.\n");
}

int main(void)
{
	struct alist list;
	char list_data[10] = {};

	run_tests();
	
	/* Example usage: */

	alist_init(&list, sizeof(list_data) / sizeof(char));

	/* **Always** check if the list is full before adding. */
	for (char c = '0'; !alist_is_full(&list); c++) {
		list_data[alist_push(&list)] = c;
	}

	/* **Always** check if the list is empty before accessing. */
	while (!alist_is_empty(&list)) {
		putchar(list_data[alist_pop(&list)]);
	}
	putchar('\n');

	return 0;
}
