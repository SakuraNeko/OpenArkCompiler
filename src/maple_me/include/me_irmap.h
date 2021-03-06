/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MAPLE_ME_INCLUDE_ME_IRMAP_H
#define MAPLE_ME_INCLUDE_ME_IRMAP_H
#include "ssa_tab.h"
#include "me_function.h"
#include "irmap.h"

constexpr int kHmapHashLength = 5107;

namespace maple {
class MeIRMap : public IRMap {
 public:
  MeIRMap(MeFunction &f, Dominance &dom, MemPool &memPool, MemPool &tmpMemPool)
      : IRMap(*f.GetMeSSATab(), dom, memPool, tmpMemPool, kHmapHashLength), func(f) {
    SetDumpStmtNum(MeOption::stmtNum);
  }

  ~MeIRMap() = default;

  BB *GetBB(BBId id) override {
    return func.GetBBFromID(id);
  }

  BB *GetBBForLabIdx(LabelIdx lidx, PUIdx pidx = 0) override {
    return func.GetLabelBBAt(lidx);
  }

  void DumpBB(const BB &bb);
  void Dump() override;
  void EmitBB(const BB&, BlockNode&);
  void EmitBBStmts(const BB&, BlockNode&);

  MeFunction &GetFunc() {
    return func;
  }

  std::string PhaseName() const {
    return "irmap";
  }
 private:
  MeFunction &func;
};

class MeDoIRMap : public MeFuncPhase {
 public:
  explicit MeDoIRMap(MePhaseID id) : MeFuncPhase(id) {}

  ~MeDoIRMap() = default;

  AnalysisResult *Run(MeFunction *func, MeFuncResultMgr *m, ModuleResultMgr *mrm) override;
  std::string PhaseName() const override {
    return "irmap";
  }
};
}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_IRMAP_H
