#include "HSCAA_2_3_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAA_2_3_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        callExpr().bind("call"),
        this
    );
}

void HSCAA_2_3_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *call = Result.Nodes.getNodeAs<CallExpr>("call");
    if (!call) return;

    if (!call->getType()->isVoidType()) {
        diag(call->getExprLoc(),
             "Return value should not be ignored (HSCAA_2_3)");
    }
}

} // namespace tidy
} // namespace clang