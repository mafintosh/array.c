#include <sys/types.h>
#include <stdlib.h>
#include "array.h"

static void array_resize (array_t *self, size_t size) {
	self->buffer = realloc(self->buffer, size * sizeof(void*));
	self->buffer_size = size;
}

array_t *array_init () {
	return array_init_with_size(ARRAY_DEFAULT_SIZE);
}

array_t *array_init_with_size (size_t size) {
	array_t *self = malloc(sizeof(array_t));

	self->refs = 1;
	self->length = 0;
	self->buffer_size = size;
	self->buffer = malloc(size * sizeof(void*));

	return self;
}

void array_push (array_t *self, void *data) {
	if (self->length == self->buffer_size) array_resize(self, 2 * self->buffer_size);
	self->buffer[self->length] = data;
	self->length++;
}

void array_unshift (array_t *self, void *data) {
	array_insert(self, 0, data);
}

void array_insert (array_t *self, size_t index, void *data) {
	if (index < self->length) {
		array_push(self, NULL); // just make sure the array is long enough
		for (size_t i = self->length-1; i > index; i--) {
			self->buffer[i] = self->buffer[i-1];
		}

		self->buffer[index] = data;
		return;
	}
	if (self->buffer_size < index) {
		size_t size = self->buffer_size;
		while (size < index) {
			size *= 2;
		}

		array_resize(self, size);
	}

	for (size_t i = self->length; i < index; i++) {
		self->buffer[index] = NULL;
	}
	self->length = index+1;
	self->buffer[index] = data;
}

void *array_get (array_t *self, size_t index) {
	return index >= self->length ? NULL : self->buffer[index];
}

void array_put (array_t *self, size_t index, void *data) {
	if (index >= self->length) return array_insert(self, index, data);
	self->buffer[index] = data;
}

ssize_t array_indexof (array_t *self, void *data) {
	for (size_t i = 0; i < self->length; i++) {
		if (self->buffer[i] == data) return i;
	}
	return -1;
}

int array_contains (array_t *self, void *data) {
	return array_indexof(self, data) > -1;
}

void *array_remove (array_t *self, size_t index) {
	if (index >= self->length) return NULL;

	void *removed = self->buffer[index];
	size_t length = --self->length;

	for (; index < length; index++) {
		self->buffer[index] = self->buffer[index+1];
	}

	return removed;
}

void *array_remove_item (array_t *self, void *data) {
	ssize_t index = array_indexof(self, data);
	return index == -1 ? NULL : array_remove(self, index);
}

void *array_shift (array_t *self) {
	return array_remove(self, 0);
}

void *array_pop (array_t *self) {
	return self->length ? self->buffer[--self->length] : NULL;
}

void *array_incref (array_t *self) {
	self->refs++;
	return self;
}

void array_decref (array_t *self) {
	if (--self->refs) return;
	free(self->buffer);
	free(self);
}