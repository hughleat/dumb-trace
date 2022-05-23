# dumb-trace
This the world's most stupid basic block tracer. I built it for a friend, just to show how to do instrumentation in LLVM. If you are looking for a feature rich, performant tracer, this ain't it. (If you are looking for a good example of instrumenting in LLVM, this probably isn't it either - it's just a quick hack.)

Good tracers don't instrument every block, this does. Good tracers don't write strings as they go, they make things efficient, this does write strings.

## Building
- Clone it somewhere.
- Ensure you LLVM dev installed (probably conda install llvmdev)
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`

This should build:

- `build/dumb-instrument`: a tool to stupidly instrument LLVM bitcode
- `build/libdumb-trace.a`: an implementation of `__dumb_trace` that prints to a file or stdout every time it executes a basic block
- `build/libdumb-hist.a`: an implementation of `__dumb_trace` that prints a basic block histogram to a file or stdout

Then you can test that it works:

- `cd ../test`
- `make`

## What does it do?
### `dumb-instrument`
The main part of this project is a tool, called `dumb-instrument`, that adds instrumentation to LLVM bitcodes. It adds a call to `__debug_trace(unsigned bbid)` to each basic block in the bitcode.

The tool also produces a list of all the basic blocks it has instrumented, one per line. Each line will be of the form `<module-name>:<function-name>:<id>`. The `bbid` passed to `__debug_trace` will be an index into this list.

In addition, there are two implementations of `__debug_trace` provided so that you can link them in to programs that have had instrumentation added. (Note that neither of them writes in binary, which would be more efficient and easy to implement.)

The tool has the following usage:

    dumb-instrument [options] <bitcode-input>

Where the options are:

    -b=<filename> - Block list filename (default stderr)
    -i=<filename> - Include list file name (default none)
    -o=<filename> - Specify output file name (default stdout)

The bitcode files can be either `.bc` or `.ll`.

The include list, if set, is a file with a list of `<module-name>:<function-name>` lines, describing which functions to instrument.

So, if you want to instrument `foo.c` to create `foo.o`, you might execute these commands:

    clang -c -emit-llvm -O3 foo.c # makes foo.bc
    dumb-instrument foo.bc -o foo-instr.bc -b blocks.txt
    clang -c foo-instr.bc -O3 foo.o

The `blocks.txt` file will then contain something like the below which shows which blocks have been instrumented.

    foo.bc:fish:0
    foo.bc:fish:1
    foo.bc:fish:2
    foo.bc:badger:0

The `blocks.txt` file is appended to so that you can instrument multiple source files. Care should be taken to make sure that there are not duplicates. In addition, this is not multi process safe.

You then need to link `foo.o` with an implementation of `__debug_trace`. 

If `foo.c` has functions `fish` and `badger`, then you might get a sequence of calls to `__debug_trace` like:

    __debug_trace(0)  // foo.bc:fish:0
    __debug_trace(1) // foo.bc:fish:1
    __debug_trace(1) // foo.bc:fish:1
    __debug_trace(3) // foo.bc:badger:0
    __debug_trace(2) // foo.bc:fish:2

### `libdumb-trace.a`
The first implementation of `__debug_trace`, `libdumb-trace.a`, prints `bbid` to a file every time `__debug_trace` is called. The file can set by an environment variable `DUMB_TRACE_PATH`. If that isn't set, then it prints to the standard output.

So, given `foo.o`, built like above, you could build the executable like this:

    clang foo.o libdumb-trace.a -o foo

If you want to run it and have the trace recorded in `foo-trace.txt`, do this:

    DUMB_TRACE_PATH=foo-trace.txt ./foo 

If that has `fish` and `badger` functions like above, then `foo-trace.txt` will have this in it:

    0
    1
    1
    3
    2
 
That file will be appended to, so if you run that command twice then `foo-trace.txt` will contain both traces.

You have to parse the file yourself and work out from the `blocks.txt` which blocks have been called. It would not be hard to make another version of this which reads the `blocks.txt` file and prints strings instead. Or to build a program to do that conversion after the fact. It would be better to write the trace in binary.

### `libdumb-hist.a`
The second implementation of `__debug_trace`, `libdumb-hist.a`, prints a histogram of all the `bbid` from calls to `__debug_trace`. The file can set by an environment variable `DUMB_TRACE_PATH`. If that isn't set, then it prints to the standard output.

So, given `foo.o`, built like above, you could build the executable like this:

    clang foo.o libdumb-hist.a -o foo

If you want to run it and have the trace recorded in `foo-hist.txt`, do this:

    DUMB_TRACE_PATH=foo-hist.txt ./foo 

If that has `fish` and `badger` functions like above, then `foo-hist.txt` will have this in it:

    0=1
    1=2
    3=1
    2=1
 
That file will be appended to, so if you run that command twice then `foo-hist.txt` will contain two copies of the histogram.

Note that this file will not contain zero counts.

### Compressing traces
The traces may be very large.   

If the traces get out of hand then you can use named pipes. E.g.:

    mkfifo trace.fifo                        # Make a named pipe
    DUMB_TRACE_PATH=trace.fifo ./foo-trace & # Trace to the pipe (background)
    cat trace.fifo | gzip -9 > trace.gz      # Zip to trace.gz
    rm trace.fifo                            # Delete pipe (or reuse it next time)
    gunzip -c trace.gz                       # Unzip the trace

## Warning
This is not well tested and probably has lots of bugs. It is not well documented. I don't stand by it at all :-)