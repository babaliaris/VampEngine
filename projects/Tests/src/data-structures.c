#include <VampTest/VampTest.h>
#include <data-structures/list.h>


typedef struct TestData
{
    int __number__;
}
TestData;


VAMP_TEST(VampList, CreateAndDestroyTest)
{
    VampList *list = VampNewList();

    VampDestroyList(list, NULL);
}


VAMP_TEST(VampList, IsEmptyTest)
{
    VampList *list = VampNewList();

    VAMP_EXPECT( list->IsEmpty(list), "The list should be empty at this point." );
    VAMP_EXPECT( list->GetLength(list) == 0, "The length of the list should be 0." );

    VampDestroyList(list, NULL);
}


VAMP_TEST(VampList, AppendDataTest)
{
    VampList *list = VampNewList();

    TestData data0, data1, data2, data3, data4;
    data0.__number__ = 0;
    data1.__number__ = 1;
    data2.__number__ = 2;
    data3.__number__ = 3;
    data4.__number__ = 4;

    list->Append(list, (void *)&data0);
    list->Append(list, (void *)&data1);
    list->Append(list, (void *)&data2);
    list->Append(list, (void *)&data3);
    list->Append(list, (void *)&data4);

    VAMP_EXPECT( !list->IsEmpty(list), "The list should NOT be empty." );
    VAMP_EXPECT( list->GetLength(list) == 5, "There must be 5 elements in the list.")

    VampDestroyList(list, NULL);
}


VAMP_TEST(VampList, GetAtTest)
{
    VampList *list = VampNewList();

    TestData data0, data1, data2, data3, data4;
    data0.__number__ = 0;
    data1.__number__ = 1;
    data2.__number__ = 2;
    data3.__number__ = 3;
    data4.__number__ = 4;

    list->Append(list, (void *)&data0);
    list->Append(list, (void *)&data1);
    list->Append(list, (void *)&data2);
    list->Append(list, (void *)&data3);
    list->Append(list, (void *)&data4);

    

    VAMP_EXPECT( !list->IsEmpty(list), "The list should NOT be empty." );
    VAMP_EXPECT( list->GetLength(list) == 5, "There must be 5 elements in the list.")

    VAMP_EXPECT( ((TestData *)list->GetAt(list, 0))->__number__ == 0, "The number should be 0." );
    VAMP_EXPECT( ((TestData *)list->GetAt(list, 1))->__number__ == 1, "The number should be 1." );
    VAMP_EXPECT( ((TestData *)list->GetAt(list, 2))->__number__ == 2, "The number should be 2." );
    VAMP_EXPECT( ((TestData *)list->GetAt(list, 3))->__number__ == 3, "The number should be 3." );
    VAMP_EXPECT( ((TestData *)list->GetAt(list, 4))->__number__ == 4, "The number should be 4." );

    VampDestroyList(list, NULL);
}


VAMP_TEST(VampList, RemoveAtTest)
{
    VampList *list = VampNewList();

    TestData data0, data1, data2, data3, data4;
    data0.__number__ = 0; //Third to be removed
    data1.__number__ = 1; //Last to be removed
    data2.__number__ = 2; //Third to be removed
    data3.__number__ = 3; //First to be removed
    data4.__number__ = 4; //Second to be reomoved

    list->Append(list, (void *)&data0);
    list->Append(list, (void *)&data1);
    list->Append(list, (void *)&data2);
    list->Append(list, (void *)&data3);
    list->Append(list, (void *)&data4);

    //5 elements on the list: 0,1,2,3,4
    void *d3 = list->RemoveAt(list, 3);
    VAMP_EXPECT( ((TestData *)d3)->__number__ == 3, "The number should be 3" );
    VAMP_EXPECT( list->GetLength(list) == 4 , "The length should be 4" );

    //4 elements on the list: 0,1,2,3
    void *d4 = list->RemoveAt(list, 3);
    VAMP_EXPECT( ((TestData *)d4)->__number__ == 4, "The number should be 4" );
    VAMP_EXPECT( list->GetLength(list) == 3 , "The length should be 3" );


    //3 elements on the list: 0,1,2
    void *d0 = list->RemoveAt(list, 0);
    VAMP_EXPECT( ((TestData *)d0)->__number__ == 0, "The number should be 0" );
    VAMP_EXPECT( list->GetLength(list) == 2 , "The length should be 2" );

    //2 elements on the list: 0,1
    void *d2 = list->RemoveAt(list, 1);
    VAMP_EXPECT( ((TestData *)d2)->__number__ == 2, "The number should be 2" );
    VAMP_EXPECT( list->GetLength(list) == 1 , "The length should be 1" );

    //2 element on the list: 0
    void *d1 = list->RemoveAt(list, 0);
    VAMP_EXPECT( ((TestData *)d1)->__number__ == 1, "The number should be 1" );
    VAMP_EXPECT( list->GetLength(list) == 0 , "The length should be 0" );

    VAMP_EXPECT( list->IsEmpty(list), "The list should be empty." );

    VampDestroyList(list, NULL);
}


char RemoveByConditionFunc(void *data, void *cond)
{
    TestData *d = (TestData *)data;
    TestData *c = (TestData *)cond;

    return (d->__number__ == c->__number__);
}


VAMP_TEST(VampList, RemoveByConditionTest)
{
    VampList *list = VampNewList();

    TestData data0, data1, data2, data3, data4;
    data0.__number__ = 0; //Third to be removed
    data1.__number__ = 1; //Last to be removed
    data2.__number__ = 2; //Third to be removed
    data3.__number__ = 3; //First to be removed
    data4.__number__ = 4; //Second to be reomoved

    list->Append(list, (void *)&data0);
    list->Append(list, (void *)&data1);
    list->Append(list, (void *)&data2);
    list->Append(list, (void *)&data3);
    list->Append(list, (void *)&data4);

    //5 elements on the list: 0,1,2,3,4
    void *d3 = list->RemoveByCondition(list, RemoveByConditionFunc, &data3);
    VAMP_EXPECT( ((TestData *)d3)->__number__ == 3, "The number should be 3" );
    VAMP_EXPECT( list->GetLength(list) == 4 , "The length should be 4" );

    //4 elements on the list: 0,1,2,3
    void *d4 = list->RemoveByCondition(list, RemoveByConditionFunc, &data4);
    VAMP_EXPECT( ((TestData *)d4)->__number__ == 4, "The number should be 4" );
    VAMP_EXPECT( list->GetLength(list) == 3 , "The length should be 3" );


    //3 elements on the list: 0,1,2
    void *d0 = list->RemoveByCondition(list, RemoveByConditionFunc, &data0);
    VAMP_EXPECT( ((TestData *)d0)->__number__ == 0, "The number should be 0" );
    VAMP_EXPECT( list->GetLength(list) == 2 , "The length should be 2" );

    //2 elements on the list: 0,1
    void *d2 = list->RemoveByCondition(list, RemoveByConditionFunc, &data2);
    VAMP_EXPECT( ((TestData *)d2)->__number__ == 2, "The number should be 2" );
    VAMP_EXPECT( list->GetLength(list) == 1 , "The length should be 1" );

    //2 element on the list: 0
    void *d1 = list->RemoveByCondition(list, RemoveByConditionFunc, &data1);
    VAMP_EXPECT( ((TestData *)d1)->__number__ == 1, "The number should be 1" );
    VAMP_EXPECT( list->GetLength(list) == 0 , "The length should be 0" );

    VAMP_EXPECT( list->IsEmpty(list), "The list should be empty." );


    VampDestroyList(list, NULL);
}






char GetByConditionFunc(void *data, void *cond)
{
    TestData *d = (TestData *)data;
    TestData *c = (TestData *)cond;

    return (d->__number__ == c->__number__);
}


VAMP_TEST(VampList, GetByConditionTest)
{
    VampList *list = VampNewList();

    TestData data0, data1, data2, data3, data4;
    data0.__number__ = 0;
    data1.__number__ = 1;
    data2.__number__ = 2;
    data3.__number__ = 3;
    data4.__number__ = 4;

    list->Append(list, (void *)&data0);
    list->Append(list, (void *)&data1);
    list->Append(list, (void *)&data2);
    list->Append(list, (void *)&data3);
    list->Append(list, (void *)&data4);

    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, &data0))->__number__ == 0, "The number should be 0.");
    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, &data1))->__number__ == 1, "The number should be 1.");
    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, &data2))->__number__ == 2, "The number should be 2.");
    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, &data3))->__number__ == 3, "The number should be 3.");
    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, &data4))->__number__ == 4, "The number should be 4.");

    VampDestroyList(list, NULL);
}





void VampListDestroyClb(void *data)
{
    TestData* d = (TestData *)data;
    free(d);
}


VAMP_TEST(VampList, DestroyListAndClearUserData)
{
    VampList *list = VampNewList();

    TestData *data0 = (TestData *)malloc(sizeof(TestData));
    TestData *data1 = (TestData *)malloc(sizeof(TestData));

    data0->__number__ = 0;
    data1->__number__ = 1;

    list->Append(list, data0);
    list->Append(list, data1);

    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, data0))->__number__ == 0, "The number should be 0.");
    VAMP_EXPECT( ((TestData *)list->GetByCondition(list, GetByConditionFunc, data1))->__number__ == 1, "The number should be 1.");

    VampDestroyList(list, VampListDestroyClb);
}