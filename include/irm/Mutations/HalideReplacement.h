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

#pragma once

#include "irm/ConstValues/ConstValueConstructor.h"
#include "irm/IRMutation.h"
#include <llvm/IR/Type.h>
#include <memory>
#include <vector>
#include <string>
#include <utility>

namespace irm {

class HalideReplacement : public IRMutation {
public:
  using ReplacementMapping = std::vector<std::pair<std::string, std::string>>;
  explicit HalideReplacement(ReplacementMapping mappings);
  
  bool canMutate(llvm::Instruction *instruction) override;
  void mutate(llvm::Instruction *instruction) override;

private:
  ReplacementMapping mappings;
};

// TODO add mutators

class Halide_AddToMul : public HalideReplacement {
public:
  explicit Halide_AddToMul() : HalideReplacement({{"Halidepl", "Halideml"}}) {}
};

class Halide_AddToSub : public HalideReplacement {
public:
  explicit Halide_AddToSub() : HalideReplacement({{"Halidepl", "Halidemi"}}) {}
};

class Halide_AddToDiv : public HalideReplacement {
public:
  explicit Halide_AddToDiv() : HalideReplacement({{"Halidepl", "Halidedv"}}) {}
};

class Halide_SubToMul : public HalideReplacement {
public:
  explicit Halide_SubToMul() : HalideReplacement({{"Halidemi", "Halideml"}}) {}
};

class Halide_SubToAdd : public HalideReplacement {
public:
  explicit Halide_SubToAdd() : HalideReplacement({{"Halidemi", "Halidepl"}}) {}
};

class Halide_SubToDiv : public HalideReplacement {
public:
  explicit Halide_SubToDiv() : HalideReplacement({{"Halidemi", "Halidedv"}}) {}
};

class Halide_MulToAdd : public HalideReplacement {
public:
  explicit Halide_MulToAdd() : HalideReplacement({{"Halideml", "Halidepl"}}) {}
};

class Halide_MulToSub : public HalideReplacement {
public:
  explicit Halide_MulToSub() : HalideReplacement({{"Halideml", "Halidemi"}}) {}
};

class Halide_MulToDiv : public HalideReplacement {
public:
  explicit Halide_MulToDiv() : HalideReplacement({{"Halideml", "Halidedv"}}) {}
};

class Halide_DivToMul : public HalideReplacement {
public:
  explicit Halide_DivToMul() : HalideReplacement({{"Halidedv", "Halideml"}}) {}
};

class Halide_DivToAdd : public HalideReplacement {
public:
  explicit Halide_DivToAdd() : HalideReplacement({{"Halidedv", "Halidepl"}}) {}
};

class Halide_DivToSub : public HalideReplacement {
public:
  explicit Halide_DivToSub() : HalideReplacement({{"Halidedv", "Halidemi"}}) {}
};

class Halide_add_assign_to_sub_assign : public HalideReplacement {
public:
  explicit Halide_add_assign_to_sub_assign() : HalideReplacement({
    {"_ZN6Halide9float16_tpL", "_ZN6Halide9float16_tmi"},
  {"_ZN6Halide10bfloat16_tpL", "_ZN6Halide10bfloat16_tmI"},
  {"_ZN6HalidepIERNS_4Expr", "_ZN6HalidemIERNS_4Expr"},
  {"_ZN6Halide19FuncTupleElementRefpLERKNS_4Expr", "_ZN6Halide19FuncTupleElementRefmIERKNS_4Expr"},
  {"_ZN6Halide7FuncRefpLE", "_ZN6Halide7FuncRefmI"}}) {}
};

} // namespace irm
