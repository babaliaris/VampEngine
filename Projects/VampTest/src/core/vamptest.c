#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>

VampUnitTest *vampCreateTest(const char *pSuiteName, const char *pTestName, const char *pFullName, VampTestCallback testFunc)
{
    //Check if they passed a testFunc callback.
    if (!testFunc)
    {
        VAMP_WARN("Parameter VampTestCallback testFunc should not be NULL.");
        return NULL;
    }

    //Allocate memory.
    VampUnitTest *new_test = (VampUnitTest *)vampMalloc(VAMP_SIZEOF(VampUnitTest));

    //Check if the allocation succeeded.
    if (!new_test)
    {
        VAMP_WARN("Failed to vampCreateTest(). Reason: OUT OF MEMORY.");
        return NULL;
    }

    //Initialize the new object.
    new_test->m_failed      = 0;
    new_test->m_suite_name  = pSuiteName;
    new_test->m_test_name   = pTestName;
    new_test->m_full_name   = pFullName;
    new_test->run           = testFunc;

    return new_test;
}

char vampDestroyTest(VampUnitTest **pThis)
{
    if (!pThis || !(*pThis))
    {
        VAMP_WARN("You called vampDestroyTest(NULL) or with a **pointer pointing to NULL.");
        return 0;
    }

    vampFree(*pThis);

    *pThis = NULL;

    return 1;
}


static void runAllTestsImpl(VampTestApplication *pThis)
{
    if (!pThis)
    {
        VAMP_WARN("You called runAllTestsImpl(NULL).");
        return;
    }

    for (VAMP_SIZE_T i = 0; i < pThis->m_total_registered_tests; i++)
    {
        VampUnitTest *test = pThis->m_tests[i];

        VAMP_ASSERT(test == NULL);

        test->run(test);

        pThis->m_total_run++;
        if (test->m_failed) pThis->m_total_failed++;
    }
}


static void registerTestImpl(VampTestApplication *pThis, VampUnitTest *pTest)
{
    if (!pThis || !pTest)
    {
        VAMP_WARN("You called registerTestImpl() with a NULL value.");
        return;
    }

    if (pThis->m_total_registered_tests >= VAMPTEST_TOTAL_NUMBER_OF_TESTS)
    {
        VAMP_ERROR("VAMPTEST_TOTAL_NUMBER_OF_TESTS exceeded. Please update its value to a higher number.");
        return;
    }

    pThis->m_tests[pThis->m_total_registered_tests] = pTest;
    pThis->m_total_registered_tests++;
}


VampTestApplication *vampCreateTestApplication()
{
    VampTestApplication *new_app = (VampTestApplication *)vampMalloc(VAMP_SIZEOF(VampTestApplication));

    //Check if the allocation succeeded.
    if (!new_app)
    {
        VAMP_WARN("Failed to vampCreateTestApplication(). Reason: OUT OF MEMORY.");
        return NULL;
    }

    new_app->m_total_registered_tests   = 0;
    new_app->m_total_run                = 0;
    new_app->m_total_failed             = 0;
    new_app->m_tests                    = (VampUnitTest **)vampMalloc( VAMP_SIZEOF(VampUnitTest *) * VAMPTEST_TOTAL_NUMBER_OF_TESTS );

    new_app->registerTest   = registerTestImpl;
    new_app->runAllTests    = runAllTestsImpl;

    return new_app;
}


char vampDestroyTestApplication(VampTestApplication **pThis)
{
    if (!pThis || !(*pThis))
    {
        VAMP_WARN("You called vampDestroyTestApplication(NULL) or with a **pointer pointing to NULL.");
        return 0;
    }

    //Destroy all the tests.
    for (VAMP_SIZE_T i = 0; i < (*pThis)->m_total_registered_tests; i++)
    {
        VAMP_ASSERT( (*pThis)->m_tests[i] != NULL);
        vampDestroyTest(&(*pThis)->m_tests[i]);
    }

    vampFree((*pThis)->m_tests);

    vampFree(*pThis);

    *pThis = NULL;

    return 1;
}
