#include "HSCAI_2_1_Check.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

bool HSCAI_2_1_Check::isVirtualBaseToDerived(
    const CXXRecordDecl *from,
    const CXXRecordDecl *to) {

    if (!from || !to) return false;

    for (const auto &base : from->bases()) {
        if (const auto *baseDecl = base.getType()->getAsCXXRecordDecl()) {
            if (base.isVirtual() && baseDecl == to)
                return true;

            if (isVirtualBaseToDerived(baseDecl, to))
                return true;
        }
    }
    return false;
}

void HSCAI_2_1_Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        cxxStaticCastExpr().bind("cast"),
        this
    );
}

void HSCAI_2_1_Check::check(const MatchFinder::MatchResult &Result) {

    const auto *castExpr =
        Result.Nodes.getNodeAs<CXXStaticCastExpr>("cast");

    if (!castExpr) return;

    const auto *fromDecl =
        castExpr->getSubExpr()->getType()->getAsCXXRecordDecl();

    const auto *toDecl =
        castExpr->getType()->getAsCXXRecordDecl();

    if (!fromDecl || !toDecl) return;

    if (isVirtualBaseToDerived(fromDecl, toDecl)) {
        diag(castExpr->getExprLoc(),
             "Unsafe cast across virtual inheritance");
    }
}

} // namespace tidy
} // namespace clang