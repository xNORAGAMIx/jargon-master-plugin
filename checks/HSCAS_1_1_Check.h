#pragma once

#include "clang-tidy/ClangTidyCheck.h"

namespace clang {
namespace tidy {

class HSCAS_1_1_Check : public ClangTidyCheck {
public:
    HSCAS_1_1_Check(StringRef Name, ClangTidyContext *Context)
        : ClangTidyCheck(Name, Context) {}

    void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

}
}