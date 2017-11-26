// Interface for editing backends. Different backends will provide an identical interface
// In the future maybe there's a per-buffer config variable to specify the backend to be
// used?

#pragma once

#include <stddef.h>

// A handle for an editor buffer
struct editor_buf;


// Create a new empty editor buffer
struct editor_buf* editor_buf_new(const char *backend);

// Create a new editor buffer with the given string content
struct editor_buf* editor_buf_new_with_str(const char *backend, const char *str);

// Get length of buffer
size_t editor_buf_len(const struct editor_buf *buf);

// Get string content within given limits (from -> from + len)
// Return number of characters actually written
size_t editor_buf_get_str(const struct editor_buf *buf, size_t from, size_t len, char *data);

// Get string content of LINES within given limits (from -> from + num)
// Fill the data in *data, and reallocate if required, based on *data_len
// NOTE: data should be malloc-allocated
size_t editor_buf_get_lines(const struct editor_buf *buf, size_t from, size_t num, char **data, size_t *data_len);

// Free an editor buffer instance
void editor_buf_free(struct editor_buf *buf);
