#include "HSCAA_2_4_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAA_2_4_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        expr(unless(anyOf(
            callExpr(),
            binaryOperator(),
            unaryOperator()
        ))).bind("expr"),
        this
    );
}

void HSCAA_2_4_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *exprNode = Result.Nodes.getNodeAs<Expr>("expr");
    if (!exprNode) return;

    diag(exprNode->getExprLoc(), "Unused expression");
}

} 
}