#include "HSCAV_6_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAV_6_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxNewExpr(
            unless(isExpansionInSystemHeader())
        ).bind("new"),
        this
    );
}

void HSCAV_6_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *newExpr = Result.Nodes.getNodeAs<CXXNewExpr>("new");
    if (!newExpr) return;

    diag(newExpr->getExprLoc(),
         "Memory allocated with new may leak if not deleted");
}

}
}