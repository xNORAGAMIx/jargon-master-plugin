#include "HSCAA_2_1_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAA_2_1_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        varDecl(hasLocalStorage()).bind("var"),
        this
    );
}

void HSCAA_2_1_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *var = Result.Nodes.getNodeAs<VarDecl>("var");
    if (!var) return;

    if (var->isUsed()) return;

    diag(var->getLocation(), "Unused variable");
}

} // namespace tidy
} // namespace clang