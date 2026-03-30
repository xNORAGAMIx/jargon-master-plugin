#include "HSCBC_6_3_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCBC_6_3_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        callExpr(
            callee(functionDecl(hasName("std::move")))
        ).bind("move"),
        this
    );
}

void HSCBC_6_3_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *call = Result.Nodes.getNodeAs<CallExpr>("move");
    if (!call) return;

    diag(call->getExprLoc(),
         "Object moved using std::move; ensure it is not used afterward");
}

}
}