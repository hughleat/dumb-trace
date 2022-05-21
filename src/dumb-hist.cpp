#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

FILE* out_file = nullptr;
static std::map<const std::string, unsigned> hist;

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
    if (out_file) {
        for (const auto &p: hist) {
            fprintf(out_file, "%s=%u\n", p.first.c_str(), p.second);
        }
    }
    if (out_file && out_file != stdout) {
        fclose(out_file);
        out_file = nullptr;
    }
}

extern "C"
void __dumb_trace(const char* msg, unsigned i) {
    std::string key = msg + std::to_string(i);
    hist[key]++;
}