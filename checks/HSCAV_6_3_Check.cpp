#include "HSCAV_6_3_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAV_6_3_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        ifStmt(
            unless(isExpansionInSystemHeader()),
            hasThen(
                hasDescendant(
                    cxxDeleteExpr()
                )
            )
        ).bind("if"),
        this
    );
}

void HSCAV_6_3_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *ifStmtNode = Result.Nodes.getNodeAs<IfStmt>("if");
    if (!ifStmtNode) return;

    diag(ifStmtNode->getIfLoc(),
         "Unnecessary null check before delete");
}

} // namespace tidy
} // namespace clang