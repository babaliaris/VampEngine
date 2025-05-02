#ifndef VAMP_TEST_H
#define VAMP_TEST_H
#include <VampEngine/core/vamp_std.h>
#include <VampEngine/debug/vamp_logger.h>

#define VAMPTEST_MAX_NUM_OF_TESTS 10000

typedef struct VampUnitTest
{

    char m_failed;
    const char *m_suite_name;
    const char *m_test_name;
    const char *m_full_name;

    void (*run)(struct VampUnitTest *pThis);

}VampUnitTest;



typedef void (*VampTestFunc)(VampUnitTest *pVamptestThis);



typedef struct VampTestApplication
{

    VAMP_SIZE_T m_total_tests;
    VAMP_SIZE_T m_total_run;
    VAMP_SIZE_T m_total_failed;

    VampUnitTest **m_tests_list;

    void (*registerTest)(struct VampTestApplication *pThis, VampUnitTest *pTest);
    void (*runAllTests)(struct VampTestApplication *pThis);

}VampTestApplication;



VampUnitTest *vampCreateUnitTest(const char *pSuiteName, const char *pTestName, const char *pFullName, VampTestFunc pTestFunc);
char vampDestroyTest(VampUnitTest **pThis);

VampTestApplication *vampCreateTestApplication();
char vampDestroyTestApplication(VampTestApplication **pThis);


#define VAMPTEST_START()\
    VampTestApplication *vamptest_application = vampCreateTestApplication()

#define VAMPTEST_END()\
    vamptest_application->runAllTests(vamptest_application);\
    VAMPTEST_PRINT_TOTAL_RESULTS();\
    vampDestroyTestApplication(&vamptest_application)

#define VAMPTEST_PRINT_TOTAL_RESULTS()\
    vampPrintf("\n%sTotal Tests:%s %ld\n%sTotal Run:%s %ld\n%sTotal Failed:%s %ld\n%sTotal Passed:%s %ld\n",\
        VAMP_COLOR_CYAN, VAMP_COLOR_DEFAULT, vamptest_application->m_total_tests,\
        VAMP_COLOR_CYAN, VAMP_COLOR_DEFAULT, vamptest_application->m_total_run,\
        VAMP_COLOR_RED, VAMP_COLOR_DEFAULT, vamptest_application->m_total_failed,\
        VAMP_COLOR_GREEN, VAMP_COLOR_DEFAULT, vamptest_application->m_total_run - vamptest_application->m_total_failed\
    )

#define VAMPTEST_CREATE_TEST_FUNC_NAME(suite_name, test_name) suite_name##_##test_name

#define VAMPTEST_TEST(suite_name, test_name)\
    void VAMPTEST_CREATE_TEST_FUNC_NAME(suite_name, test_name)(VampUnitTest *pVamptestThis)

#define VAMPTEST_REGISTER(suite_name, test_name)\
    vamptest_application->registerTest(vamptest_application, vampCreateUnitTest(\
        #suite_name,\
        #test_name,\
        #suite_name ":" #test_name,\
        VAMPTEST_CREATE_TEST_FUNC_NAME(suite_name, test_name)\
    ))

#define VAMPTEST_ASSERT(cond)\
    if ( !(cond) )\
    {\
        vampPrintf("[%sFAILED%s] {%s%s%s} %s:%ld:%s%s%s() %sREASON%s: %s%s%s\n",\
            VAMP_COLOR_RED, VAMP_COLOR_DEFAULT, VAMP_COLOR_GREEN, pVamptestThis->m_full_name,\
            VAMP_COLOR_DEFAULT, __FILE__, __LINE__, VAMP_COLOR_MAGENTA, __func__, VAMP_COLOR_DEFAULT,\
            VAMP_COLOR_GREEN, VAMP_COLOR_DEFAULT, VAMP_COLOR_CYAN, #cond, VAMP_COLOR_DEFAULT\
        );\
        \
        pVamptestThis->m_failed = 1;\
    }


#endif
