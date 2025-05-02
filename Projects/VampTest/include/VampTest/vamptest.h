#ifndef VAMP_TEST_H
#define VAMP_TEST_H
#include <VampEngine/core/vamp_std.h>
#include <VampEngine/debug/vamp_logger.h>



#define VAMPTEST_TOTAL_NUMBER_OF_TESTS 10000



typedef struct VampUnitTest
{
    char            m_failed;
    const char     *m_test_name;
    const char     *m_suite_name;
    const char     *m_full_name;

    void (*run)(struct VampUnitTest *pThis);

}VampUnitTest;



typedef struct VampTestApplication
{
    VAMP_SIZE_T m_total_registered_tests;
    VAMP_SIZE_T m_total_run;
    VAMP_SIZE_T m_total_failed;

    VampUnitTest **m_tests;

    void (*registerTest)(struct VampTestApplication *pThis, VampUnitTest *pTest);
    void (*runAllTests)(struct VampTestApplication *pThis);

}VampTestApplication;



typedef void (*VampTestCallback)(VampUnitTest *__pVampTest__);



VampUnitTest *vampCreateTest(const char *pSuiteName, const char *pTestName, const char *pFullName, VampTestCallback testFunc);
char vampDestroyTest(VampUnitTest **pThis);



VampTestApplication *vampCreateTestApplication();
char vampDestroyTestApplication(VampTestApplication **pThis);



#define VAMPTEST_START()\
    VampTestApplication *__vamp_test_application__ = vampCreateTestApplication();\


#define VAMPTEST_PRINT_RESULTS()\
    vampPrintf("\n%sTotal Registered: %ld\nTotal Run: %ld\n%sTotal Failed: %ld\n%s",\
        VAMP_COLOR_GREEN,\
        __vamp_test_application__->m_total_registered_tests,\
        __vamp_test_application__->m_total_run,\
        VAMP_COLOR_RED,\
        __vamp_test_application__->m_total_failed,\
        VAMP_COLOR_DEFAULT\
    );




#define VAMPTEST_END()\
    __vamp_test_application__->runAllTests(__vamp_test_application__);\
    VAMPTEST_PRINT_RESULTS();\
    vampDestroyTestApplication(&__vamp_test_application__);



#define VAMPTEST_CREATE_TEST_NAME(suite_name, test_name) suite_name##_##test_name



#define VAMPTEST_TEST(suite_name, test_name)\
    void VAMPTEST_CREATE_TEST_NAME(suite_name, test_name)(VampUnitTest *__pVampTest__)



#define VAMPTEST_REGISTER_TEST(suite_name, test_name)\
    __vamp_test_application__->registerTest(__vamp_test_application__, vampCreateTest(\
        #suite_name,\
        #test_name,\
        #suite_name ":" #test_name,\
        VAMPTEST_CREATE_TEST_NAME(suite_name, test_name)\
    ))



#define VAMPTEST_TEST_ASSERT(cond, fmt, ...)\
    if ( !(cond) )\
    {\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_RED, "FAILED", __pVampTest__->m_full_name, __FILE__, __LINE__, fmt, ##__VA_ARGS__);\
        __pVampTest__->m_failed = 1;\
        return;\
    }

#endif