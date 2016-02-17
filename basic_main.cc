#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <stdio.h>
#include <string>

using namespace llvm;
using namespace std;
static std::unique_ptr<Module> TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value *> NamedValues;
int main(int argc, char const* argv[])
{
    TheModule = llvm::make_unique<Module>("main", getGlobalContext());
    // Make the function type:  int (int,char**) etc.
    std::vector<Type*> args;
    args.push_back(Type::getInt32Ty(getGlobalContext()));
    PointerType* x = Type::getInt8PtrTy(getGlobalContext());
    PointerType* p = PointerType::get(x, 0);
    args.push_back(p);
    FunctionType *FT = FunctionType::get(Type::getInt32Ty(getGlobalContext()), args, false);

    //Function *F = Function::Create(FT, GlobalValue::InternalLinkage, "main", TheModule.get());
    Function *F = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());
    Function::arg_iterator argit = F->arg_begin();
    Value *arg_0 = argit++;
    arg_0->setName("argc");
    Value *arg_1 = argit++;
    arg_1->setName("argv");

    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    Builder.SetInsertPoint(BB);
    AllocaInst *alloc = new AllocaInst(Type::getInt32Ty(getGlobalContext()), "Im_a_var", BB);
    Value *xxx = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 1000, true);
    Builder.CreateStore(xxx, alloc);
    Value *RetVal = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
    Builder.CreateRet(RetVal);
    TheModule->dump();
    return 0;
}
