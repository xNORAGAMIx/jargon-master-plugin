#include "HSCAG_4_2_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAG_4_2_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxMethodDecl(
            unless(isExpansionInSystemHeader())
        ).bind("method"),
        this
    );
}

void HSCAG_4_2_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
    if (!method) return;

    const auto *parent = method->getParent();
    if (!parent) return;

    std::string methodName = method->getNameAsString();

    for (const auto &base : parent->bases()) {

        const auto *baseDecl = base.getType()->getAsCXXRecordDecl();
        if (!baseDecl) continue;

        for (const auto *baseMethod : baseDecl->methods()) {

            if (baseMethod->getNameAsString() == methodName) {

                diag(method->getLocation(),
                     "Method hides base class method");
                return;
            }
        }
    }
}

} // namespace tidy
} // namespace clang