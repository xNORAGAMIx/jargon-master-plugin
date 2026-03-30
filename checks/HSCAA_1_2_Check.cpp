#include "HSCAA_1_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAA_1_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        callExpr(unless(isExpansionInSystemHeader())).bind("call"),
        this
    );
}

void HSCAA_1_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *call = Result.Nodes.getNodeAs<CallExpr>("call");
    if (!call) return;

    if (call->getType()->isVoidType()) return;

    const auto &parents = Result.Context->getParents(*call);
    if (parents.empty()) return;

    const Stmt *parent = parents[0].get<Stmt>();
    if (!parent) return;

    if (isa<ExprWithCleanups>(parent) || isa<CompoundStmt>(parent)) {
        diag(call->getExprLoc(), "Return value is ignored");
    }
}

} // namespace tidy
} // namespace clang