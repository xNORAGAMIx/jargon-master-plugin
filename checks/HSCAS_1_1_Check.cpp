#include "HSCAS_1_1_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void HSCAS_1_1_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxCatchStmt().bind("catch"),
        this
    );
}

void HSCAS_1_1_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *catchStmt = Result.Nodes.getNodeAs<CXXCatchStmt>("catch");
    if (!catchStmt) return;

    const VarDecl *exceptionDecl = catchStmt->getExceptionDecl();
    if (!exceptionDecl) return;

    if (!exceptionDecl->getType()->isReferenceType()) {
        diag(exceptionDecl->getLocation(),
             "Exception should be caught by reference");
    }
}

}
}