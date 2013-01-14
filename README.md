# array.c

A list implementation in c similar to arrays in javascript.

## Usage

It is easy to use.

``` c
#include <stdio.h>
#include "array.h"

int main () {
	array_t *lst = array_init();

	array_push(lst, "hello world");

	printf("length is %zu\n", array_length(lst));
	printf("list[0] is %s\n", array_get(lst, 0));

	return 0;
}
```

## API

``` c
array_t *array_init ();

array_t *array_init_with_size (size_t size);

void array_push (array_t *self, void *data);

void array_unshift (array_t *self, void *data);

void array_insert (array_t *self, size_t index, void *data);

void *array_get (array_t *self, size_t index);

void array_put (array_t *self, size_t index, void *data);

ssize_t array_indexof (array_t *self, void *data);

int array_contains (array_t *self, void *data);

void *array_remove (array_t *self, size_t index);

void *array_remove_item(array_t *self, void *data);

void *array_shift (array_t *self);

void *array_pop (array_t *self);

void *array_incref (array_t *self);

void array_decref (array_t *self);

#define array_length(self) self->length
```

## License
MIT