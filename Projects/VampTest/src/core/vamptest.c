#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>


static void registerTestImpl(VampTestApplication *pThis, VampUnitTest *pTest)
{   
    //Neiter must be NULL.
    VAMP_ASSERT(pThis != NULL);
    VAMP_ASSERT(pTest != NULL);

    pThis->m_tests_list[pThis->m_total_tests] = pTest;

    pThis->m_total_tests++;
}



static void runAllTestsImpl(VampTestApplication *pThis)
{
    VAMP_ASSERT(pThis != NULL);
    VAMP_ASSERT(pThis->m_total_tests < VAMPTEST_MAX_NUM_OF_TESTS);

    for (VAMP_SIZE_T i = 0; i < pThis->m_total_tests; i++)
    {
        VampUnitTest *test = pThis->m_tests_list[i];

        VAMP_ASSERT(test != NULL);

        test->run(test);

        pThis->m_total_run++;

        if (test->m_failed) pThis->m_total_failed++;
    }
}


VampUnitTest *vampCreateUnitTest(const char *pSuiteName, const char *pTestName, const char *pFullName, VampTestFunc pTestFunc)
{
    VampUnitTest *new_test = (VampUnitTest *)vampMalloc(VAMP_SIZEOF(VampUnitTest));

    if (!new_test)
    {
        VAMP_WARN("Run out of memory!");
        return NULL;
    }

    //The test funcion MUST be provided!
    VAMP_ASSERT(pTestFunc != NULL);

    new_test->m_failed      = 0;
    new_test->m_suite_name  = pSuiteName;
    new_test->m_test_name   = pTestName;
    new_test->m_full_name   = pFullName;
    new_test->run           = pTestFunc;

    return new_test;
}



char vampDestroyTest(VampUnitTest **pThis)
{
    if (!pThis || !(*pThis))
    {
        VAMP_WARN("pThis or *pThis is NULL.");
        return 0;
    }

    vampFree(*pThis);

    *pThis = NULL;

    return 1;
}



VampTestApplication *vampCreateTestApplication()
{
    VampTestApplication *new_app = (VampTestApplication *)vampMalloc(VAMP_SIZEOF(VampTestApplication));

    if (!new_app)
    {
        VAMP_WARN("Out of memory!");
        return NULL;
    }

    new_app->m_total_tests  = 0;
    new_app->m_total_run    = 0;
    new_app->m_total_failed = 0;

    new_app->m_tests_list   = (VampUnitTest **)vampMalloc(VAMP_SIZEOF(VampUnitTest *));

    new_app->registerTest   = registerTestImpl;
    new_app->runAllTests    = runAllTestsImpl;

    return new_app;
}



char vampDestroyTestApplication(VampTestApplication **pThis)
{
    if (!pThis || !(*pThis))
    {
        VAMP_WARN("pThis or *pThis is NULL.");
        return 0;
    }

    VAMP_ASSERT( (*pThis)->m_total_tests < VAMPTEST_MAX_NUM_OF_TESTS );

    //Destroy all the tests in the list.
    for (VAMP_SIZE_T i = 0; i < (*pThis)->m_total_tests; i++)
        vampDestroyTest( &(*pThis)->m_tests_list[i] );

    vampFree(*pThis);

    *pThis = NULL;

    return 1;
}
