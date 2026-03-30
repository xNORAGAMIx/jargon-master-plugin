#pragma once

#include "clang-tidy/ClangTidyCheck.h"

namespace clang {
namespace tidy {

class HSCAN_3_1_Check : public ClangTidyCheck {
public:
    HSCAN_3_1_Check(StringRef Name, ClangTidyContext *Context)
        : ClangTidyCheck(Name, Context) {}

    void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

}
}