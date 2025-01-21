# Shared-Memory-IPC-Example

This repository contains an example of interprocess communication (IPC) using shared memory in the C programming language. The project consists of two programs:

- `reader.c`: Reads messages from shared memory.
- `writer.c`: Writes messages to shared memory.

## Features

- Example usage of the `shmget`, `shmat`, and `shmdt` functions for managing shared memory.
- Capability to send up to 5 messages from the `writer` process to the `reader` process.
- Process synchronization using the `complete` flag.
