#include <assert.h>
#include <stdio.h>
#include "array.h"

void test_array_init () {
	array_t *l = array_init();

	assert(array_length(l) == 0);
}

void test_array_push_and_pop () {
	array_t *l = array_init();
	array_push(l, l);

	assert(array_length(l) == 1);
	assert(array_get(l, 0) == l);
	assert(array_pop(l) == l);
	assert(array_length(l) == 0);
}

void test_array_unshift () {
	array_t *l = array_init();
	int a = 1, b = 2;

	array_unshift(l, &b);
	array_unshift(l, &a);

	assert(array_length(l) == 2);
	assert(array_get(l, 0) == &a);
	assert(array_get(l, 1) == &b);
}

void test_array_insert () {
	array_t *l = array_init();

	array_insert(l, 9, NULL);
	assert(array_length(l) == 10);
	array_insert(l, 5, NULL);
	assert(array_length(l) == 11);
}

void test_array_put_and_get () {
	array_t *l = array_init();
	int a = 42;

	array_put(l, 9, &a);
	assert(array_length(l) == 10);
	assert(array_get(l, 9) == &a);
	array_put(l, 9, NULL);
	assert(array_length(l) == 10);
	assert(array_get(l, 9) == NULL);
}

void test_array_search () {
	array_t *l = array_init();
	int a = 42, b = 42;

	array_push(l, NULL);
	array_push(l, &a);
	array_push(l, NULL);

	assert(array_length(l) == 3);
	assert(array_contains(l, &a));
	assert(!array_contains(l, &b));
	assert(array_indexof(l, &a) == 1);
	assert(array_indexof(l, &b) == -1);
}

void test_array_remove () {
	array_t *l = array_init();
	int a = 42, b = 42;

	array_push(l, &a);
	assert(array_length(l) == 1);
	array_remove(l, 1);
	assert(array_length(l) == 1);
	array_remove(l, 0);
	assert(array_length(l) == 0);
	array_push(l, &a);
	assert(array_length(l) == 1);
	array_remove_item(l, &b);
	assert(array_length(l) == 1);
	array_remove_item(l, &a);
	assert(array_length(l) == 0);
}

int main () {
	test_array_init();
	test_array_push_and_pop();
	test_array_unshift();
	test_array_insert();
	test_array_put_and_get();
	test_array_search();
	test_array_remove();

	printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
	return 0;
}