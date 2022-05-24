#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

FILE* out_file = nullptr;
static std::map<unsigned, unsigned> *hist = nullptr;

__attribute__((constructor))
static void open_hist() {
    const char* out_file_path = getenv("DUMB_TRACE_PATH");
    if (out_file_path) {
        out_file = fopen(out_file_path, "a");
    } else {
        out_file = stdout;
    }
}

__attribute__((destructor))
static void close_hist() {
    if (out_file && hist) {
        for (const auto &p: *hist) {
            fprintf(out_file, "%u=%u\n", p.first, p.second);
        }
    }
    if (out_file && out_file != stdout) {
        fclose(out_file);
        out_file = nullptr;
    }
    if (hist) {
        delete hist;
        hist = nullptr;
    }
}

extern "C"
void __dumb_trace(unsigned bbid) {
    if (!hist) {
        hist = new std::map<unsigned, unsigned>;
    }
    (*hist)[bbid]++;
}