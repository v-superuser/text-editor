// The entry point of the backend server

#include  <stdio.h>
#include <editor.h>

int main(int argc, const char **argv) {
    struct editor_buf *buf = editor_buf_new_with_str("rope", "Hello, world!\n");
    editor_buf_free(buf);
    return 0;
}
