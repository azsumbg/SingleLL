#pragma once

#ifdef SINGLELL_EXPORTS
#define SINGLELL_API __declspec(dllexport)
#else 
#define SINGLELL_API __declspec(dllimport)
#endif 

namespace sll
{
	template<typename T>struct NODE
	{
		NODE* next_node{ nullptr };

		T data{};
	};
	template<typename T>class LIST
	{
	private:
		NODE<T>* mPtr{ nullptr };

		size_t mSize{ 0 };

	public:

		LIST() 
		{
			mPtr = new NODE<T>{};
		};
		LIST(T data)
		{
			mPtr = new NODE<T>{};
			
			NODE* next_final_node = new NODE<T>{};

			mPtr->data = data;
			mPtr->next_node = next_final_node;

			++size;
		}
		~LIST()
		{
			if (mSize == 1)delete mPtr;
			else
			{
				NODE<T>* next = mPtr;

				while (next != nullptr)
				{
					NODE<T>* current = next;
					next = current->next;
					delete current;
				}
			}
		}
		
		size_t size()const
		{
			return mSize;
		}

		bool empty()const
		{
			return (mSize == 0);
		}

		void clear()
		{
			if (mSize == 1)delete mPtr;
			else
			{
				NODE<T>* next = mPtr;

				while (next != nullptr)
				{
					NODE<T>* current = next;
					next = current->next;
					delete current;
				}
			}

			mPtr = new NODE<T>{};

			mSize = 0;
		}

		NODE<T>& front()
		{
			return *mPtr;
		}
		NODE<T>& back()
		{
			NODE<T>* current = mPtr;

			while (current->next_node != nullptr)current = current->next_node;
			
			return *current;
		}

		void push_back(T what)
		{
			if (mPtr->next_node == nullptr)
			{
				mPtr->data = what;

				NODE<T>* new_node = new NODE{};

				mPtr->next_node = new_node;
			}
			else
			{
				NODE<T>* find_pos = mPtr->next_node;
				NODE<T>* new_node = new NODE<T>{};

				new_node->data = what;
				new_node->next_node = nullptr;

				while (find_pos->next_node != nullptr)find_pos = find_pos->next_node;

				find_pos->next_node = new_node;
			}

			++mSize;
		}
		void push_front(T what)
		{
			if (mPtr->next_node == nullptr)
			{
				NODE<T>* new_node = new NODE<T>{};

				mPtr->data = what;
				mPtr->next_node = new_node;
			}
			else
			{
				NODE<T>* old_first_node = mPtr;
				NODE<T>* new_first_node = new NODE{};

				new_first_node->data = what;
				new_first_node->next_node = old_first_node;

				mPtr = new_first_node;
			}

			++mSize;
		}

		bool insert(T what, size_t pos)
		{
			if (pos > mSize)return false;

			NODE<T>* find_pos = mPtr;
			NODE<T>* new_node = new NODE{};

			for (size_t i = 0; i < pos; ++i)find_pos = find_pos->next_node;

			new_node->data = what;
			new_node->next_node = find_pos->next_node;

			find_pos->next_node = new_node;

			++mSize;

			return true;
		}

	};
}