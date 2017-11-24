# text-editor
[WIP] A basic text editor written in C.

# Initial design idea
A text editor which natively supports collaborative editing across multiple client platforms?

So the editor will be made of two logical parts - a back-end server, and multiple clients,
communicating on a socket-based API. The server will handle the actual editing of buffers,
and the clients will handle user interaction. A terminal-based client implementation is being
written in `clients/term/`

# Coding guidelines
    - Indentation with tabs
    - Tab width = 4 spaces
