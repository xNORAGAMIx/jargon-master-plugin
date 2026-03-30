#include "clang-tidy/ClangTidy.h"
#include "clang-tidy/ClangTidyModuleRegistry.h"

#include "checks/HSCAA_1_2_Check.h"
#include "checks/HSCAA_2_1_Check.h"
#include "checks/HSCAI_2_1_Check.h"

using namespace clang::tidy;

namespace {

class MyModule : public ClangTidyModule {
public:
    void addCheckFactories(ClangTidyCheckFactories &Factories) override {

        Factories.registerCheck<HSCAA_1_2_Check>("hscaa-1-2");
        Factories.registerCheck<HSCAA_2_1_Check>("hscaa-2-1");
        Factories.registerCheck<HSCAI_2_1_Check>("hscai-2-1");
    }
};

} // namespace

static ClangTidyModuleRegistry::Add<MyModule>
X("hscaa-module", "My custom static analysis checks");

volatile int MyModuleAnchorSource = 0;