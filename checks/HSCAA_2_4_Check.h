#pragma once

#include "clang-tidy/ClangTidyCheck.h"

namespace clang {
namespace tidy {

class HSCAA_2_4_Check : public ClangTidyCheck {
public:
    HSCAA_2_4_Check(StringRef Name, ClangTidyContext *Context)
        : ClangTidyCheck(Name, Context) {}

    void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} 
}