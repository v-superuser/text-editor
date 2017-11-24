// The entry point of the backend server

#include <stdio.h>
#include <editor.h>
#include <stdlib.h>

static char* _read_file(const char *filename) {
    FILE *f;
    char *str;
    size_t len;
    if (!(f = fopen(filename, "r"))) {
        fprintf(stderr, "Error: Could not open file: '%s'\n", filename);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (!(str = malloc(len +  1))) {
        return NULL;
    }
    fread(str, 1, len, f);
    str[len] = '\0';
    return str;
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    char *str;
    if (!(str = _read_file(argv[1]))) {
        return -1;
    }
    printf("STR: %s\n", str);
    struct editor_buf *buf = editor_buf_new_with_str("rope", str);
    free(str);
    editor_buf_free(buf);
    return 0;
}
