#include "HSCAI_2_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAI_2_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cStyleCastExpr(
            unless(isExpansionInSystemHeader())
        ).bind("cast"),
        this
    );
}

void HSCAI_2_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *castExpr = Result.Nodes.getNodeAs<CStyleCastExpr>("cast");
    if (!castExpr) return;

    diag(castExpr->getExprLoc(),
         "Avoid C-style casts; use static_cast or dynamic_cast instead");
}

} 
}