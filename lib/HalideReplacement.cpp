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
#include <iostream>
using namespace irm;
using std::cout;
using std::endl;

HalideReplacement::HalideReplacement(std::vector<std::pair<std::string, std::string>> mappings)
    : mappings(std::move(mappings)) {}

bool HalideReplacement::canMutate(llvm::Instruction *instruction) {
    assert(instruction);
    std::string instructionStr;
    llvm::raw_string_ostream rso(instructionStr);
    instruction->print(rso);
    rso.flush();

    // Iterate through all mappings to see if any function prefix matches the instruction string.
    for (const auto& mapping : mappings) {
        if (instructionStr.find(mapping.first) != std::string::npos) {
            return true; // Found a match, can mutate
        }
    }
    return false; // No matches found
}

void HalideReplacement::mutate(llvm::Instruction *instruction) {
    assert(instruction);

    // This example mutation logic might need to be significantly updated depending on your needs
    // Particularly since you now have multiple possible replacements

    // Attempting a simplistic approach: replace the first match found
    for (const auto& mapping : mappings) {
        std::string instructionStr;
        llvm::raw_string_ostream rso(instructionStr);
        instruction->print(rso);
        rso.flush();

        size_t pos = instructionStr.find(mapping.first);
        if (pos != std::string::npos) {
            // Logic to replace instruction based on the specific mapping found
            // This is highly dependent on what the mutation entails and the specifics of your use case
            // For example, changing function calls, operands, etc., requires detailed LLVM IR manipulation
            // Below is a very simplified and likely incorrect example just to illustrate handling the found mapping

            // Get invoke instruction (if it's indeed an invoke instruction; similar checks needed for other types)
            if (llvm::InvokeInst *invokeInst = llvm::dyn_cast<llvm::InvokeInst>(instruction)) {
                llvm::Function *function = invokeInst->getCalledFunction();
                if (function) {
                    std::string functionName = function->getName().str();
                    std::string newFunctionName = functionName.replace(pos, mapping.first.length(), mapping.second);

                    llvm::Module *module = function->getParent();
                    llvm::Function *newFunction = module->getFunction(newFunctionName);
                    if (newFunction) {
                        invokeInst->setCalledFunction(newFunction);
                    }
                }
            }
            break; // Assuming only one mutation per instruction for this example
        }
    }
}