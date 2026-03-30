#include "HSCAN_3_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAN_3_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxMethodDecl(
            isVirtual(),
            unless(isExpansionInSystemHeader())
        ).bind("method"),
        this
    );
}

void HSCAN_3_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
    if (!method) return;

    if (!method->hasAttr<OverrideAttr>() && !method->isVirtualAsWritten()) {
        diag(method->getLocation(),
             "Virtual function should explicitly use 'override'");
    }
}

}
}