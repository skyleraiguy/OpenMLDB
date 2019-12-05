/*
 * op_generator.h
 * Copyright (C) 4paradigm.com 2019 wangtaize <wangtaize@4paradigm.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_VM_OP_GENERATOR_H_
#define SRC_VM_OP_GENERATOR_H_

#include <string>
#include <vector>
#include "base/status.h"
#include "llvm/IR/Module.h"
#include "node/plan_node.h"
#include "node/sql_node.h"
#include "vm/op.h"
#include "vm/table_mgr.h"

namespace fesql {
namespace vm {
using ::fesql::base::Status;  // NOLINT
struct OpVector {
    std::string sql;
    // TOD(wangtaize) add free logic
    std::vector<OpNode*> ops;
};

class OpGenerator {
 public:
    explicit OpGenerator(TableMgr* table_mgr);
    ~OpGenerator();

    bool Gen(const ::fesql::node::PlanNodeList& trees, const std::string& db,
             ::llvm::Module* module, OpVector* ops,
             base::Status& status);  // NOLINT

 private:
    bool GenFnDef(::llvm::Module* module,
                  const ::fesql::node::FuncDefPlanNode* plan);

    bool GenSQL(const ::fesql::node::SelectPlanNode* node,
                const std::string& db, ::llvm::Module* module,
                OpVector* ops,          // NOLINT
                base::Status& status);  // NOLINT

    OpNode* GenProject(const ::fesql::node::ProjectListPlanNode* node,
                       const std::string& db, ::llvm::Module* module,
                       Status& status);  // NOLINT

    OpNode* GenScan(const ::fesql::node::ScanPlanNode* node,
                    const std::string& db, ::llvm::Module* module,
                    Status& status);  // NOLINT

    OpNode* GenLimit(const ::fesql::node::LimitPlanNode* node,
                     const std::string& db, ::llvm::Module* module,
                     Status& status);  // NOLINT
    OpNode* GenMerge(const ::fesql::node::MergePlanNode* node,
                     ::llvm::Module* module,
                     Status& status);  // NOLINT

    OpNode* RoutingNode(const ::fesql::node::PlanNode* node,
                        const std::string& db, ::llvm::Module* module,
                        std::map<const std::string, OpNode*>& ops_map,
                        OpVector* ops,
                        Status& status);  // NOLINT

 private:
    TableMgr* table_mgr_;
};

}  // namespace vm
}  // namespace fesql

#endif  // SRC_VM_OP_GENERATOR_H_
