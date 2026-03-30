#include "HSCAI_2_3_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAI_2_3_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxReinterpretCastExpr(
            unless(isExpansionInSystemHeader())
        ).bind("cast"),
        this
    );
}

void HSCAI_2_3_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *castExpr = Result.Nodes.getNodeAs<CXXReinterpretCastExpr>("cast");
    if (!castExpr) return;

    diag(castExpr->getExprLoc(),
         "Avoid reinterpret_cast; it is unsafe");
}

} 
}