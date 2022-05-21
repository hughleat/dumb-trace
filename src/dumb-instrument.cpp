#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/InitializePasses.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"

using namespace llvm;

/// Input LLVM module file name.
cl::opt<std::string> InputFilename(
    cl::Positional, 
    cl::desc("Specify input filename"),
    cl::value_desc("filename"), 
    cl::init("-")
);
    
/// Output LLVM module file name.
cl::opt<std::string> OutputFilename(
    "o", 
    cl::desc("Specify output filename"),
    cl::value_desc("filename"), 
    cl::init("-")
);

/// Prefix for the instrumentation messages
cl::opt<std::string> Prefix(
    "p", 
    cl::desc("Prefix for messages"),
    cl::init("")
);


namespace llvm {
    // The INITIALIZE_PASS_XXX macros put the initialiser in the llvm namespace.
    void initializeDumbInstrumentPass(PassRegistry &Registry);
}

// All the work is done here
class DumbInstrument : public llvm::FunctionPass {
public:
    static char ID;
    DumbInstrument() : FunctionPass(ID) {}

    bool runOnFunction(llvm::Function &F) override {
        // Only instrument definitions.
        if (F.isDeclaration()) {
            return false;
        }
        
        auto &M = *F.getParent();
        auto &C = M.getContext();

        // Get __dumb_trace(const char* msg, unsigned bb)
        auto *VoidTy = Type::getVoidTy(C);
        auto *CharPtrTy = Type::getInt8PtrTy(C);
        auto *UnsignedTy = Type::getInt32Ty(C);
        static constexpr const char *Symbol__dumb_trace = "__dumb_trace";
        auto DumbTrace = M.getOrInsertFunction(Symbol__dumb_trace, VoidTy, CharPtrTy, UnsignedTy);

        // Add a global for the msg
        auto msg = (Prefix == "" ? "" : Prefix + ".") + F.getName() + ".";
        auto *IntTy = Type::getInt32Ty(C);
        auto *Zero = ConstantInt::getSigned(IntTy, 0);
        auto *MsgData = ConstantDataArray::getString(C, msg.str(), true);
        auto *MsgGlobal = new GlobalVariable(M, MsgData->getType(), true, GlobalValue::PrivateLinkage, MsgData);
        auto *MsgAccess = ConstantExpr::getInBoundsGetElementPtr(MsgData->getType(), MsgGlobal, ArrayRef<Constant*>({Zero, Zero}));
        
        unsigned i = 0;
        for (auto &BB: F) {
            IRBuilder<> Builder(&BB, BB.getFirstInsertionPt());
            Builder.CreateCall(DumbTrace, {MsgAccess, ConstantInt::get(UnsignedTy, i, true)});
            i++;
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

    // Run the pass
    initializeDumbInstrumentPass(*PassRegistry::getPassRegistry());
    legacy::PassManager PM;
    DumbInstrument* Instrument = new DumbInstrument();
    PM.add(Instrument);
    PM.run(*Module);

    if (verifyModule(*Module, &errs()))
      return 1;

    Module->print(Out.os(), nullptr, false);

    Out.keep();
    return 0;
}