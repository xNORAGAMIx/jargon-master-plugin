#include "HSCAN_3_1_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAN_3_1_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxMethodDecl(
            isOverride(),
            unless(isExpansionInSystemHeader())
        ).bind("method"),
        this
    );
}

void HSCAN_3_1_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
    if (!method) return;

    if (!method->hasAttr<OverrideAttr>()) {
        diag(method->getLocation(),
             "Overriding method should be marked with 'override'");
    }
}

}
}