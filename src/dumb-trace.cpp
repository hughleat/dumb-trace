#include <cstdio>
#include <cstdlib>
#include <cstring>

FILE* out_file = nullptr;

__attribute__((constructor))
static void open_trace() {
    // Get the file to write to
    const char* out_file_path = getenv("DUMB_TRACE_PATH");
    if (out_file_path) {
        out_file = fopen(out_file_path, "a");
    } else {
        out_file = stdout;
    }
}

__attribute__((destructor))
static void close_trace() {
    if (out_file && out_file != stdout) {
        fclose(out_file);
        out_file = nullptr;
    }
}

extern "C"
void __dumb_trace(unsigned bbid) {
    if (out_file) {
        fprintf(out_file, "%u\n", bbid);
    }
}