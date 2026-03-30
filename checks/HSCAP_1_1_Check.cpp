#include "HSCAP_1_1_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAP_1_1_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxConstructorDecl().bind("ctor"),
        this
    );
}

void HSCAP_1_1_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *ctor = Result.Nodes.getNodeAs<CXXConstructorDecl>("ctor");
    if (!ctor) return;

    // Skip copy/move constructors (optional but better)
    if (ctor->isCopyOrMoveConstructor()) return;

    if (!ctor->isExplicit()) {
        diag(ctor->getLocation(),
             "Constructor should be marked explicit");
    }
}

} // namespace tidy
} // namespace clang