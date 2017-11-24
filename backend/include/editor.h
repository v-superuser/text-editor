// Interface for editing backends. Different backends will provide an identical interface
// In the future maybe there's a per-buffer config variable to specify the backend to be
// used?

#pragma once

// A handle for an editor buffer
struct editor_buf;


// Create a new empty editor buffer
struct editor_buf* editor_buf_new(const char *backend);

// Create a new editor buffer with the given string content
struct editor_buf* editor_buf_new_with_str(const char *backend, const char *str);

// Free an editor buffer instance
void editor_buf_free(struct editor_buf *e);
