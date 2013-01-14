#ifndef ARRAY_LIST
#define ARRAY_LIST

#ifndef ARRAY_DEFAULT_SIZE
#define ARRAY_DEFAULT_SIZE 64
#endif

typedef struct {
	void **buffer;
	int refs;
	size_t buffer_size;
	size_t length;
} array_t;

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

#endif