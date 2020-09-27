#pragma once
#include "VampAssert.h"
#include <vector>
#include <type_traits>

namespace VampEngine
{

	namespace DataStructs
	{

		template<typename key, typename data>
		class HeapSort
		{
			//Public Methods.
			public:

				//Constructor.
				HeapSort()
				{
					VAMP_ASSERT( (std::is_same_v<int, key> || std::is_same_v<float, key> || std::is_same_v<double, key>) , 
						"HeapSort only supports int, float and double as the key!");
				}

				//Deconstructor.
				~HeapSort()
				{
					//Delete all the nodes.
					for (HeapNode* node : m_list)
						delete node;
				}

				//Push Method.
				inline void Push(key key, data data)
				{

					//Push a new item into the list.
					if (!m_isOrdered) m_list.push_back(new HeapNode(key, data));
					else this->PushOrdered(key, data);
				}


				//Pop Method.
				inline data Pop()
				{
					return this->PopItem();
				}


				//Sort Method.
				inline void Sort()
				{
					//If there are at least 2 items in the list.
					if (m_list.size() > 1)
					{
						//End of list, points to the index of the last item.
						for (unsigned int i = 1; i < m_list.size(); i++)
							this->SortHeap(i);
					}

					//Now the heap is ordered.
					m_isOrdered = true;
				}



				//Empty Method.
				inline bool empty()
				{
					return m_list.empty();
				}

				//Is Leaf Method.
				inline bool IsLeaf(unsigned int index)
				{
					unsigned int left = this->GetLeft(index);
					unsigned int right = this->GetRight(index);

					return left >= m_list.size() && right >= m_list.size();
				}


				//Is Inner Node Method.
				inline bool IsInner(unsigned int index)
				{
					unsigned int left  = this->GetLeft(index);
					unsigned int right = this->GetRight(index);

					return left >= m_list.size() || right >= m_list.size();
				}


			//Private Members.
			private:

				//Heap Node.
				struct HeapNode
				{
					//Node Data.
					key	 m_key;
					data m_data;

					//Constructor.
					HeapNode(key key, data data)
						: m_key(key), m_data(data)
					{}
				};

				//The heap list.
				std::vector<HeapNode *> m_list;

				//Is this heap ordered?
				bool m_isOrdered = false;



			//Private Methods.
			private:


				//Push Ordered Item.
				void PushOrdered(key key, data data)
				{
					//Push the new item at the end of the list.
					m_list.push_back(new HeapNode(key, data));

					//Sort it.
					this->SortOnPush( (unsigned int)m_list.size() - 1);
				}

				//Pop An Item.
				#pragma warning( push )
				#pragma warning( disable: 4715 )
				data PopItem()
				{

					//One item in the list.
					if (m_list.size() == 1)
					{
						data extracted_data = m_list.back()->m_data;
						m_list.pop_back();

						return extracted_data;
					}

					//2 or more items.
					else if (m_list.size() > 1)
					{
						//Swap the root with the last item.
						this->Swap(0, (unsigned int)m_list.size() - 1);

						//Pop the last item.
						data extracted_data = m_list.back()->m_data;
						m_list.pop_back();

						//Sort On Pop.
						this->SortOnPop(0);

						//Return the poped data.
						return extracted_data;
					}

					//It is best to not reach this point, because the rest return statements
					//could cause problems!!!
					VAMP_ASSERT(0, "Make sure you don't pop when the list is empty!!!");
				}
				#pragma warning( pop )

				//Sort The Heap.
				void SortHeap(unsigned int index)
				{
					//If this is the root, don't do anything.
					if (index == 0)
						return;

					//Get the parent node.
					unsigned int parent = this->GetParent(index);

					//If this is greater than the parents key.
					if (m_list[index]->m_key > m_list[parent]->m_key)
					{
						this->Swap(index, parent);
						this->SortHeap(parent);
					}
				}


				//Sort On Pop.
				void SortOnPop(unsigned int index)
				{
					unsigned int left  = this->GetLeft(index);
					unsigned int right = this->GetRight(index);

					//If this is a leaf, just return.
					if (this->IsLeaf(index))
						return;

					//If this contains only one child.
					else if (this->IsInner(index))
					{

						//It's the left child.
						if (left < m_list.size() && m_list[left]->m_key > m_list[index]->m_key)
						{
							this->Swap(left, index);
							this->SortOnPop(left);
						}

						//It's the right child.
						else if (right < m_list.size() && m_list[right]->m_key > m_list[index]->m_key)
						{
							this->Swap(right, index);
							this->SortOnPop(right);
						}

					}


					//This is a full node.
					else
					{
						//The left child's key is greater.
						if (m_list[left]->m_key > m_list[right]->m_key && m_list[left]->m_key > m_list[index]->m_key)
						{
							this->Swap(left, index);
							this->SortOnPop(left);
						}

						//The right child's key is greater.
						else if (m_list[right]->m_key > m_list[index]->m_key)
						{
							this->Swap(right, index);
							this->SortOnPop(right);
						}
					}
				}



				//Sort On Pop.
				void SortOnPush(unsigned int index)
				{
					//If this is the root element.
					if (index == 0)
						return;

					//Get the parent.
					unsigned int parent = this->GetParent(index);

					//If this key is greater than the parent's.
					if (m_list[index]->m_key > m_list[parent]->m_key)
					{
						this->Swap(index, parent);
						this->SortOnPush(parent);
					}
				}



				//Get Parent Method.
				inline unsigned int GetParent(unsigned int index) const
				{
					VAMP_ASSERT(index > 0, "Index should be greater than zero.");
					return (index - 1) / 2;
				}

				//Get Left Method.
				inline unsigned int GetLeft(unsigned int index) const
				{
					return 2 * index + 1;
				}

				//Get Right Method.
				inline unsigned int GetRight(unsigned int index) const
				{
					return 2 * index + 2;
				}

				//Swap the content of two Nodes.
				inline void Swap(unsigned int index1, unsigned int index2)
				{
					key key_1   = m_list[index1]->m_key;
					data data_1 = m_list[index1]->m_data;

					m_list[index1]->m_key  = m_list[index2]->m_key;
					m_list[index1]->m_data = m_list[index2]->m_data;

					m_list[index2]->m_key  = key_1;
					m_list[index2]->m_data = data_1;
				}
		};
	}
}