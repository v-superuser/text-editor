// Implementation of the rope data structure as a text editing backend
// A rope is basically a binary tree with string data at the leaves. It
// allows for efficient insert/delete operations. Also possibly is
// suitable for parallel, multithreaded edits on different parts of the
// rope. We'll see.
//
// NOTE: Even though we're not going into multithreading just now, still,
// the code should be written in a  way that is condusive to the later
// addition of multithreading

#include "editor_internal.h"
#include <common.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
static struct editor_buf* _new();
static struct editor_buf* _new_with_str(const char *str);
static void _close(struct editor_buf *buf);

struct editor_backend editor_backend_rope = {
    .name = "rope",
    .desc = "implementation of the rope data structure as a text editing backend",
    .new = _new,
    .new_with_str = _new_with_str,
    .close = _close
};


#define MIN_SIZE 512
#define MAX_SIZE 1023

// The type of a node in the rope
enum rope_node_type {
    ROPE_NODE_TYPE_LEAF,
    ROPE_NODE_TYPE_NODE,
};

// A node in the rope data structure
struct rope_node {
    union {
        struct {
            char *str;      // String content of the leaf
        } leaf;
        struct {
            struct rope_node *l, *r;    // Children
            unsigned height;            // Height of the node
        } node;
    } data;
    size_t len;               // Length of string (NOT CAPACITY)
    enum rope_node_type type;   // Type of node
};

// Get height of a rope node
static unsigned _rope_node_height(const struct rope_node *node) {
    switch (node->type) {
    case ROPE_NODE_TYPE_LEAF:
        return 0;
    case ROPE_NODE_TYPE_NODE:
        return node->data.node.height;
    }
}

// Free resources of a rope node recursively. Can't be NULL, so no need to
// promote unnecessary defensive programming
static void _rope_node_free(struct rope_node *node) {
    switch (node->type) {
    case ROPE_NODE_TYPE_LEAF:
        free(node->data.leaf.str);
        free(node);
        return;
    case ROPE_NODE_TYPE_NODE:
        _rope_node_free(node->data.node.l);
        _rope_node_free(node->data.node.r);
        free(node);
    }
}

// Get rope node containing given string
// r - l is length, so str[r] is NOT included in the string
static struct rope_node* _rope_node_from_str(const char *str, size_t l, size_t r) {
    size_t len = r - l;
    struct rope_node *node;
    if (!str) {
        return NULL;
    }
    if (!(node = malloc(sizeof(struct rope_node)))) {
        return NULL;
    }
    if (len <= MAX_SIZE) {
        if (!(node->data.leaf.str = malloc(MAX_SIZE + 1))) {
            free(node);
            return NULL;
        }
        strncpy(node->data.leaf.str, str + l, len);
        node->data.leaf.str[len] = '\0';
        node->len = len;
        node->type = ROPE_NODE_TYPE_LEAF;
        return node;
    }
    if (!(node->data.node.l = _rope_node_from_str(str, l, l + (len / 2)))) {
        free(node);
        return NULL;
    }
    if (!(node->data.node.r = _rope_node_from_str(str, l + (len / 2), r))) {
        free(node->data.node.l);
        free(node);
        return NULL;
    }
    node->data.node.height = MAX(_rope_node_height(node->data.node.l), _rope_node_height(node->data.node.r));
    node->len = len;
    node->type = ROPE_NODE_TYPE_NODE;
    return node;
}

// Get a new empty buffer
static struct editor_buf* _new() {
    return _new_with_str("");
}

// Get a buffer with the given string content
static struct editor_buf* _new_with_str(const char *str)  {
    struct editor_buf *ret;
    struct rope_node *node;
    size_t len = strlen(str);
    if (!(ret = malloc(sizeof(struct editor_buf)))) {
        return NULL;
    }
    ret->backend = &editor_backend_rope;
    if (!(node = _rope_node_from_str(str,  0, len))) {
        free(ret);
        return NULL;
    }
    ret->data = (void*) node;
    return ret;
}

// Free resources for a buffer
static void _close(struct editor_buf *buf) {
    struct rope_node *node = (struct rope_node*) buf->data;
    if (node) {
        _rope_node_free(node);
    }
    free(buf);
}
