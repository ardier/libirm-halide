//
//  Copyright 2019 Mull Project
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "irm/Mutations/HalideReplacement.h"
#include <iostream>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

using namespace irm;

HalideReplacement::HalideReplacement(std::string functionPrefix, std::string replaceFunctionPrefix)
    : functionPrefix(functionPrefix), replaceFunctionPrefix(replaceFunctionPrefix) {}

bool HalideReplacement::canMutate(llvm::Instruction *instruction) {

  assert(instruction);
  std::string instructionStr;
  llvm::raw_string_ostream rso(instructionStr);
  instruction->print(rso);
  rso.flush();

  // if instruction does not inclucde "Halidepl" return false
  if (instructionStr.find(functionPrefix) == std::string::npos) {
    return false;
  }

  return true;
}

void HalideReplacement::mutate(llvm::Instruction *instruction) {
  assert(instruction);

  // get invoke instruction
  llvm::InvokeInst *invokeInst = llvm::dyn_cast<llvm::InvokeInst>(instruction);

  // get the function
  llvm::Function *function = invokeInst->getCalledFunction();

  std::string functionName = function->getName().str();
  std::string newFunctionName = functionName;
  newFunctionName.replace(
      newFunctionName.find(functionPrefix), functionPrefix.length(), replaceFunctionPrefix);

  llvm::Module *module = function->getParent();
  llvm::Function *newFunction = module->getFunction(newFunctionName);
  invokeInst->setCalledFunction(newFunction);
}
