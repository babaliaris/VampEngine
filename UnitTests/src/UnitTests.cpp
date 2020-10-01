#define VAMP_TEST_ENTRY
#include <VampTest.h>
#include <VampEngine.h>


VAMP_TEST(heap_sort, create)
{
	VampEngine::DataStructs::HeapSort<int, int> h(7);

	h.Push(1, 1);		//Root  => 0
	h.Push(8, 8);		//Inner => 1
	h.Push(2, 2);		//Inner => 2
	h.Push(4, 4);		//Leaf  => 3
	h.Push(10, 10);		//Leaf  => 4
	h.Push(6, 6);		//Leaf  => 5
	h.Push(12, 12);		//Leaf  => 6

	VAMP_TEST_NOTEQUAL(true, h.empty());
}


VAMP_TEST(heap_sort, one_item)
{
	VampEngine::DataStructs::HeapSort<int, int> h(1);

	h.Push(1, 1); //Root  => 0

	VAMP_TEST_EQUAL(1, h.Pop());

	VAMP_TEST_EQUAL(true, h.empty());
}



VAMP_TEST(heap_sort, two_items)
{
	VampEngine::DataStructs::HeapSort<int, int> h(2);

	h.Push(1, 1); //Root  => 0
	h.Push(2, 2); //Root  => 0

	h.Sort();

	VAMP_TEST_EQUAL(2, h.Pop());
	VAMP_TEST_EQUAL(1, h.Pop());

	VAMP_TEST_EQUAL(true, h.empty());
}


VAMP_TEST(heap_sort, leaf)
{
	VampEngine::DataStructs::HeapSort<int, int> h(7);

	h.Push(1, 1);		//Root  => 0
	h.Push(8, 8);		//Full  => 1
	h.Push(2, 2);		//Full  => 2
	h.Push(4, 4);		//Leaf  => 3
	h.Push(10, 10);		//Leaf  => 4
	h.Push(6, 6);		//Leaf  => 5
	h.Push(12, 12);		//Leaf  => 6

	VAMP_TEST_NOTEQUAL(true, h.empty());

	VAMP_TEST_EQUAL(true, h.IsLeaf(3));
	VAMP_TEST_EQUAL(true, h.IsLeaf(4));
	VAMP_TEST_EQUAL(true, h.IsLeaf(5));
	VAMP_TEST_EQUAL(true, h.IsLeaf(6));


}


VAMP_TEST(heap_sort, inner)
{
	VampEngine::DataStructs::HeapSort<int, int> h(7);

	h.Push(1, 1);		//Root  => 0
	h.Push(8, 8);		//Full  => 1
	h.Push(2, 2);		//Full  => 2
	h.Push(4, 4);		//Leaf  => 3
	h.Push(10, 10);		//Leaf  => 4
	h.Push(6, 6);		//Leaf  => 5
	h.Push(12, 12);		//Leaf  => 6

	VAMP_TEST_EQUAL(false, h.IsInner(1));
	VAMP_TEST_EQUAL(false, h.IsInner(2));
}


VAMP_TEST(heap_sort, sort_and_pop1)
{
	VampEngine::DataStructs::HeapSort<int, int> h(7);

	h.Push(1, 1);		//Root  => 0
	h.Push(8, 8);		//Full  => 1
	h.Push(2, 2);		//Full  => 2
	h.Push(4, 4);		//Leaf  => 3
	h.Push(10, 10);		//Leaf  => 4
	h.Push(6, 6);		//Leaf  => 5
	h.Push(12, 12);		//Leaf  => 6

	h.Sort();

	VAMP_TEST_EQUAL(12, h.Pop());
	VAMP_TEST_EQUAL(10, h.Pop());
	VAMP_TEST_EQUAL(8, h.Pop());
	VAMP_TEST_EQUAL(6, h.Pop());
	VAMP_TEST_EQUAL(4, h.Pop());
	VAMP_TEST_EQUAL(2, h.Pop());
	VAMP_TEST_EQUAL(1, h.Pop());

	VAMP_TEST_EQUAL(true, h.empty());
}




VAMP_TEST(heap_sort, sort_and_pop2)
{
	VampEngine::DataStructs::HeapSort<int, int> h(10);

	h.Push(20, 20);
	h.Push(15, 15);
	h.Push(2, 2);
	h.Push(6, 6);
	h.Push(30, 30);
	h.Push(1, 1);	
	h.Push(45, 45);	
	h.Push(0, 0);
	h.Push(2, 2);
	h.Push(20, 20);

	h.Sort();

	VAMP_TEST_EQUAL(45, h.Pop());
	VAMP_TEST_EQUAL(30, h.Pop());
	VAMP_TEST_EQUAL(20, h.Pop());
	VAMP_TEST_EQUAL(20, h.Pop());
	VAMP_TEST_EQUAL(15, h.Pop());
	VAMP_TEST_EQUAL(6, h.Pop());
	VAMP_TEST_EQUAL(2, h.Pop());
	VAMP_TEST_EQUAL(2, h.Pop());
	VAMP_TEST_EQUAL(1, h.Pop());
	VAMP_TEST_EQUAL(0, h.Pop());

	VAMP_TEST_EQUAL(true, h.empty());
}



VAMP_TEST(heap_sort, sorted_push)
{
	VampEngine::DataStructs::HeapSort<int, int> h(10);

	h.Push(1, 1);
	h.Push(8, 8);
	h.Push(2, 2);
	h.Push(4, 4);
	h.Push(10, 10);
	h.Push(6, 6);
	h.Push(12, 12);	

	h.Sort();

	h.Push(14, 14); 
	h.Push(20, 20);
	h.Push(16, 16);

	VAMP_TEST_EQUAL(20, h.Pop());
	VAMP_TEST_EQUAL(16, h.Pop());
	VAMP_TEST_EQUAL(14, h.Pop());
	VAMP_TEST_EQUAL(12, h.Pop());
	VAMP_TEST_EQUAL(10, h.Pop());
	VAMP_TEST_EQUAL(8, h.Pop());
	VAMP_TEST_EQUAL(6, h.Pop());
	VAMP_TEST_EQUAL(4, h.Pop());
	VAMP_TEST_EQUAL(2, h.Pop());
	VAMP_TEST_EQUAL(1, h.Pop());

	VAMP_TEST_EQUAL(true, h.empty());
}