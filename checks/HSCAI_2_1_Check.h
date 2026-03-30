#pragma once

#include "clang-tidy/ClangTidyCheck.h"

namespace clang {
namespace tidy {

class HSCAI_2_1_Check : public ClangTidyCheck {
public:
    HSCAI_2_1_Check(StringRef Name, ClangTidyContext *Context)
        : ClangTidyCheck(Name, Context) {}

    void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
    bool isVirtualBaseToDerived(const CXXRecordDecl *from,
                               const CXXRecordDecl *to);
};

} // namespace tidy
} // namespace clang