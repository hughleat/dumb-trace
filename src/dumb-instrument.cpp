#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

#include "llvm/Bitcode/BitcodeWriterPass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SystemUtils.h"
#include "llvm/Support/ToolOutputFile.h"

using namespace llvm;

/// Input LLVM module file name.
static cl::opt<std::string> InputFilename(
    cl::Positional, 
    cl::desc("Specify input file name"),
    cl::value_desc("filename"), 
    cl::init("-")
);
    
/// Output LLVM module file name.
static cl::opt<std::string> OutputFilename(
    "o", 
    cl::desc("Specify output file name (default stdout)"),
    cl::value_desc("filename"), 
    cl::init("-")
);

/// Output block list file namee
static cl::opt<std::string> BlockListName(
    "b", 
    cl::desc("Block list filename (default stderr)"),
    cl::value_desc("filename"), 
    cl::init("-")
);

/// Include list file name
static cl::opt<std::string> IncludeFilename(
    "i", 
    cl::desc("Include list file name (default none)"),
    cl::value_desc("filename"), 
    cl::init("")
);

/// Options to control output
static cl::opt<bool> Force(
    "f", 
    cl::desc("Enable binary output on terminals")
);

static cl::opt<bool> OutputAssembly(
    "S", 
    cl::desc("Write output as LLVM assembly"), 
    cl::Hidden
);

static cl::opt<bool> PreserveBitcodeUseListOrder(
    "preserve-bc-uselistorder", 
    cl::desc("Preserve use-list order when writing LLVM bitcode."), 
    cl::init(true), 
    cl::Hidden
);

static cl::opt<bool> PreserveAssemblyUseListOrder(
    "preserve-ll-uselistorder", 
    cl::desc("Preserve use-list order when writing LLVM assembly."), 
    cl::init(false), 
    cl::Hidden
);

/// Where to write the blocks
static std::ostream* Blocks = nullptr;
/// Next block id
static unsigned NextBBID = 0;

/// Includes
static std::unordered_set<std::string> Includes;

namespace llvm {
    // The INITIALIZE_PASS_XXX macros put the initialiser in the llvm namespace.
    void initializeDumbInstrumentPass(PassRegistry &Registry);
}

// All the work is done here
class DumbInstrument : public llvm::ModulePass {
public:
    static char ID;
    DumbInstrument() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
        bool changed = false;
        unsigned fid = 0;
        for (auto &F: M) {
            // Only instrument definitions.
            if (!F.isDeclaration()) {
                changed |= runOnFunction(F, fid++);
            }            
        }
        return changed;
    }

    bool runOnFunction(Function &F, unsigned fid) {        
        auto &M = *F.getParent();
        auto &C = M.getContext();

        std::string FID = M.getName().str() + ":" + F.getName().str();

        // See if this function is included
        if (IncludeFilename != "") {
            if (Includes.find(FID) == Includes.end()) {
                return false;
            }
        }

        // Get __dumb_trace(const char* msg, unsigned bb)
        auto *VoidTy = Type::getVoidTy(C);
        auto *UnsignedTy = Type::getInt32Ty(C);
        static constexpr const char *Symbol__dumb_trace = "__dumb_trace";
        auto DumbTrace = M.getOrInsertFunction(Symbol__dumb_trace, VoidTy, UnsignedTy);
        
        for (auto &BB: F) {
            // Write out the block
            *Blocks << FID << ":" << NextBBID << std::endl;
            IRBuilder<> Builder(&BB, BB.getFirstInsertionPt());
            Builder.CreateCall(DumbTrace, {ConstantInt::get(UnsignedTy, NextBBID++, true)});
        }

        return true;
    }
};

// Initialise the pass. We have to declare the dependencies we use.
char DumbInstrument::ID = 0;
INITIALIZE_PASS(DumbInstrument, "dumb-instrument", "Dumb instrumentation", false, false)

/// Reads a module from a file.
/// On error, messages are written to stderr and null is returned.
///
/// \param Context LLVM Context for the module.
/// \param Name Input file name.
static std::unique_ptr<Module> readModule(LLVMContext& Context, StringRef Name) {
  SMDiagnostic Diag;
  std::unique_ptr<Module> Module = parseIRFile(Name, Diag, Context);

  if (!Module)
    Diag.print("dumb-instrument", errs());

  return Module;
}

int main(int argc, char** argv) {
    cl::ParseCommandLineOptions(argc, argv,
                                " Dumb-Instrument\n\n"
                                " Add stupid instrumentation to a bitcode file.\n");

    LLVMContext Context;
    SMDiagnostic Err;
    SourceMgr SM;
    std::error_code EC;

    ToolOutputFile Out(OutputFilename, EC, sys::fs::OF_None);
    if (EC) {
        Err = SMDiagnostic(OutputFilename, SourceMgr::DK_Error, "Could not open output file: " + EC.message());
        Err.print(argv[0], errs());
        return 1;
    }

    std::unique_ptr<Module> Module = readModule(Context, InputFilename);

    if (!Module)
        return 1;

    // Load the includes
    // TODO: errors
    if (IncludeFilename != "") {
        std::ifstream IFS(IncludeFilename);
        std::string Line;
        while (std::getline(IFS, Line)) {
            Includes.insert(Line);
        }
    }

    // Load the block list, if not stderr
    // Init the blockId to the number of blocks already written
    // TODO: errors
    if (BlockListName != "-") {
        std::ifstream IFS(BlockListName);
        std::string Line;
        while (std::getline(IFS, Line)) {
            NextBBID++;
        }        
    }
    // Set up the blocks output file
    if (BlockListName != "-") {
        Blocks = new std::ofstream(BlockListName, std::ios_base::app);
    } else {
        Blocks = &std::cerr;
    }

    // Run the pass
    initializeDumbInstrumentPass(*PassRegistry::getPassRegistry());
    legacy::PassManager PM;
    DumbInstrument* Instrument = new DumbInstrument();
    PM.add(Instrument);

    if (OutputAssembly) {
      PM.add(createPrintModulePass(Out.os(), "", PreserveAssemblyUseListOrder));
    } else if (Force || !CheckBitcodeOutputToConsole(Out.os())) {
      PM.add(createBitcodeWriterPass(Out.os(), PreserveBitcodeUseListOrder));
    }
    PM.run(*Module);

    // Close the block stream
    if (BlockListName != "-") {
        dynamic_cast<std::ofstream*>(Blocks)->close();
        delete Blocks;
    }       

    Out.keep();
    
    if (verifyModule(*Module, &errs())) return 1;
    return 0;
}