#include "clang-tidy/ClangTidy.h"
#include "clang-tidy/ClangTidyModuleRegistry.h"

#include "checks/HSCAA_1_2_Check.h"
#include "checks/HSCAA_2_1_Check.h"
#include "checks/HSCAI_2_1_Check.h"
#include "checks/HSCAA_2_2_Check.h"
#include "checks/HSCAP_1_1_Check.h"
#include "checks/HSCAA_2_3_Check.h"
#include "checks/HSCAA_2_4_Check.h"
#include "checks/HSCAG_4_2_Check.h"
#include "checks/HSCAS_1_1_Check.h"
#include "checks/HSCAV_6_2_Check.h"
#include "checks/HSCAV_6_3_Check.h"
#include "checks/HSCBC_6_3_Check.h"
#include "checks/HSCAI_2_2_Check.h"
#include "checks/HSCAI_2_3_Check.h"
#include "checks/HSCAN_3_1_Check.h"
#include "checks/HSCAN_3_2_Check.h"

using namespace clang::tidy;

namespace {

class MyModule : public ClangTidyModule {
public:
    void addCheckFactories(ClangTidyCheckFactories &Factories) override {

        Factories.registerCheck<HSCAA_1_2_Check>("hscaa-1-2");
        Factories.registerCheck<HSCAA_2_1_Check>("hscaa-2-1");
        Factories.registerCheck<HSCAI_2_1_Check>("hscai-2-1");
        Factories.registerCheck<HSCAA_2_2_Check>("hscaa-2-2");
        Factories.registerCheck<HSCAP_1_1_Check>("hscap-1-1");
        Factories.registerCheck<HSCAA_2_3_Check>("hscaa-2-3");
        Factories.registerCheck<HSCAA_2_4_Check>("hscaa-2-4");
        Factories.registerCheck<HSCAG_4_2_Check>("hscag-4-2");
        Factories.registerCheck<HSCAS_1_1_Check>("hscas-1-1");
        Factories.registerCheck<HSCAV_6_2_Check>("hscav-6-2");
        Factories.registerCheck<HSCAV_6_3_Check>("hscav-6-3");
        Factories.registerCheck<HSCBC_6_3_Check>("hscbc-6-3");
        Factories.registerCheck<HSCAI_2_2_Check>("hscai-2-2");
        Factories.registerCheck<HSCAI_2_3_Check>("hscai-2-3");
        Factories.registerCheck<HSCAN_3_1_Check>("hscan-3-1");
        Factories.registerCheck<HSCAN_3_2_Check>("hscan-3-2");
        
    }
};

} // namespace

static ClangTidyModuleRegistry::Add<MyModule>
X("hscaa-module", "My custom static analysis checks");

volatile int MyModuleAnchorSource = 0;