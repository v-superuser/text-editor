// Implementation of the editor backend which manages an editor buffer
// There can be multiple backends following different text-management
// algorithms

#include "editor_internal.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Existing editing backends
extern struct editor_backend editor_backend_rope;

static struct editor_backend* _BACKENDS[] = {
    &editor_backend_rope,
    NULL
};

// Get a pointer to the editor backend of the given name
static struct editor_backend* _resolve_backend(const char *name) {
    int i;
    for (i = 0; _BACKENDS[i]; i++) {
        if (_BACKENDS[i]->name && !strcmp(_BACKENDS[i]->name, name)) {
            return _BACKENDS[i];
        }
    }
    return NULL;
}

// Create a new empty editor buffer
struct editor_buf* editor_buf_new(const char *name) {
    struct editor_backend *backend;
    if (!name) {
        fprintf(stderr, "[error]: Invalid backend name: (null)\n");
        return NULL;
    }
    if (!(backend = _resolve_backend(name))) {
        fprintf(stderr, "[error]: Could not resolve backend: '%s'\n", name);
        return NULL;
    }
    if (!backend->new) {
        fprintf(stderr, "[error]: Opening new buffer not yet implemented for backend: '%s'\n"
                        "Please file an issue at %s\n", name, ORIGIN_REPO_URL);
        return NULL;
    }
    return backend->new();
}

// Create a new editor buffer with the given string content
struct editor_buf* editor_buf_new_with_str(const char *name, const char *str) {
    struct editor_backend *backend;
    if (!name) {
        fprintf(stderr, "[error]: Invalid backend name: (null)\n");
        return NULL;
    }
    if (!(backend = _resolve_backend(name))) {
        fprintf(stderr, "[error]: Could not resolve backend: '%s'\n", name);
        return NULL;
    }
    if (!backend->new_with_str) {
        fprintf(stderr, "[error]: Opening new buffer not yet implemented for backend: '%s'\n"
                        "Please file an issue at %s\n", name, ORIGIN_REPO_URL);
        return NULL;
    }
    return backend->new_with_str(str);
}

// Free an editor buffer instance
void editor_buf_free(struct editor_buf *e) {
    if (!e) {
        return;
    }
    if (e->backend && e->backend->close) {
        e->backend->close(e);
        return;
    }
    free(e);
}
