run: test
	
foo.bc: foo.c
	clang -c -emit-llvm -O0 -g0 foo.c

foo.ll: foo.c
	clang -S -emit-llvm -O0 -g0 foo.c

foo-instr.bc: foo.bc
	../build/dumb-instrument foo.bc -o foo-instr.bc

foo-instr.ll: foo.ll
	../build/dumb-instrument foo.ll -o foo-instr.ll

foo-trace: foo-instr.bc
	clang++ -O3 foo-instr.bc ../build/libdumb-trace.a -o foo-trace
	
foo-hist: foo-instr.bc
	clang++ -O3 foo-instr.bc ../build/libdumb-hist.a -o foo-hist
	

test: foo-trace foo-hist
	echo Trace
	DUMB_TRACE_PATH=foo-trace.txt ./foo-trace
	cat foo-trace.txt
	echo

	echo Hist
	DUMB_TRACE_PATH=foo-hist.txt ./foo-hist
	cat foo-hist.txt

clean:
	rm -rf *.bc *.ll foo-*