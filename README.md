# dumb-trace
This the world's most stupid basic block tracer. I built it for a friend, just to show how to do instrumentation in LLVM. If you are looking for a feature rich, performant tracer, this ain't it. (If you are looking for a good example of instrumenting in LLVM, this probably isn't it either - it's just a quick hack.)

Good tracers don't instrument every block, this does. Good tracers don't write strings as they go, they make things efficient, this does write strings.

## Building
- Clone it somewhere.
- Ensure you LLVM dev installed (probably conda install llvmdev)
- `mkdir build`
- `cd build`
- `cmake ..`

This should build:

- `build/dumb-instrument`: a tool to stupidly instrument LLVM bitcode
- `build/libdumb-trace.a`: an implementation of `__dumb_trace` that prints to a file or stdout every time it executes a basic block
- `build/libdumb-hist.a`: an implementation of `__dumb_trace` that prints a basic block histogram to a file or stdout

Then you can test that it works:

- `cd ../test`
- `make`

## What does it do?
### `dumb-instrument`
The main part of this project is a tool, called `dumb-instrument`, that adds instrumentation to LLVM bitcodes. It adds a call to `__debug_trace(const char *msg, unsigned bb)` to each basic block in the bitcode.

The `msg` is a string made up from `[prefix.]<function-name>` and `bb` tells you which basic block in the function is executing.  The `prefix` is optional and only used if provided on the command line.


In addition, there are two implementations of `__debug_trace` provided so that you can link them in to programs that have had instrumentation added. 

The tool has the following usage:

    dumb-instrument [options] <bitcode-input>

Where the options are:

    -o=<filename> - Specify output filename (default stdout)
    -p=<string>   - Prefix for messages

The bitcode files can be either `.bc` or `.ll`.

So, if you want to instrument `foo.c` to create `foo.o`, you might execute these commands:

    clang -c -emit-llvm -O3 foo.c # makes foo.bc
    dumb-instrument foo.bc -o foo-instr.bc -p foo
    clang -c foo-instr.bc -O3 foo.o

You then need to link `foo.o` with an implementation of `__debug_trace`. 

If `foo.c` has functions `fish` and `badger`, then you might get a sequence of calls to `__debug_trace` like:

    __debug_trace("foo.fish", 0)
    __debug_trace("foo.fish", 1)
    __debug_trace("foo.fish", 1)
    __debug_trace("foo.badger", 0)
    __debug_trace("foo.fish", 2)

The prefix (from the `-p` command line option) allows you to distinguish functions of the same name from different compilation units, in case you are instrumenting more than one file.

### `libdumb-trace.a`
The first implementation of `__debug_trace`, `libdumb-trace.a`, prints `msg`+'.'+`i` to a file every time `__debug_trace` is called. The file can set by an environment variable `DUMB_TRACE_PATH`. If that isn't set, then it prints to the standard output.

So, given `foo.o`, built like above, you could build the executable like this:

    clang foo.o libdumb-trace.a -o foo

If you want to run it and have the trace recorded in `foo-trace.txt`, do this:

    DUMB_TRACE_PATH=foo-trace.txt ./foo 

If that has `fish` and `badger` functions like above, then `foo-trace.txt` will have this in it:

    foo.fish.0
    foo.fish.1
    foo.fish.1
    foo.badger.0
    foo.fish.2
 
That file will be appended to, so if you run that command twice then `foo-trace.txt` will contain both traces.

### `libdumb-hist.a`
The second implementation of `__debug_trace`, `libdumb-hist.a`, prints a histogram of all the `msg`+'.'+`i` from calls to `__debug_trace`. The file can set by an environment variable `DUMB_TRACE_PATH`. If that isn't set, then it prints to the standard output.

So, given `foo.o`, built like above, you could build the executable like this:

    clang foo.o libdumb-hist.a -o foo

If you want to run it and have the trace recorded in `foo-hist.txt`, do this:

    DUMB_TRACE_PATH=foo-hist.txt ./foo 

If that has `fish` and `badger` functions like above, then `foo-hist.txt` will have this in it:

    foo.fish.0=1
    foo.fish.1=2
    foo.badger.0=1
    foo.fish.2=1
 
That file will be appended to, so if you run that command twice then `foo-hist.txt` will contain two copies of the histogram.

## Warning
This is not well tested and probably has lots of bugs. It is not well documented. I don't stand by it at all :-)