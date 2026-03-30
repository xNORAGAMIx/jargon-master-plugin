#include "HSCAA_2_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAA_2_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        parmVarDecl().bind("param"),
        this
    );
}

void HSCAA_2_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *param = Result.Nodes.getNodeAs<ParmVarDecl>("param");
    if (!param) return;

    if (param->isUsed()) return;

    diag(param->getLocation(), "Unused function parameter");
}

} // namespace tidy
} // namespace clang