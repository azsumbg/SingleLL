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
		NODE<T>* next_node{ nullptr };

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
			mPtr = nullptr;
		};
		LIST(T data)
		{
			mPtr = new NODE<T>{};

			mPtr->data = data;
			mPtr->next_node = nullptr;

			++mSize;
		}
		LIST(LIST& other)
		{
			if (other.mPtr == nullptr)
			{
				mPtr = nullptr;
				mSize = 0;
			}
			else
			{
				mSize = other.mSize;

				NODE<T>* from{ other.mPtr };
				NODE<T>* to{ mPtr };

				NODE<T> first_node{ new NODE<T> };
				first_node.data = from->data;

				to = first_node;

				while (from->next_node != nullptr)
				{
					from = from->next_node;

					NODE<T>* temp{ new NODE<T> };

					temp->data = from->data;
					to->next_node = temp; 

					to = to->next_node;
				}
			}
		}
		LIST(LIST&& other)
		{
			if (other.mPtr == nullptr)
			{
				mPtr = nullptr;
				mSize = 0;
			}
			else
			{
				mSize = other.mSize;
				mPtr = other.mPtr;
				other.mPtr = nullptr;
			}
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
					next = current->next_node;
					delete current;
				}
			}
		}
		
		LIST<T>& operator = (LIST<T>& other)
		{
			if (other.mPtr == nullptr || mPtr == other.mPtr)
			{
				if (mPtr)
				{
					NODE<T>* current{ mPtr };
					NODE<T>* next{ nullptr };

					while (next != nullptr)
					{
						next = current->next_node;
						delete current;
					}
				}
				
				mPtr = nullptr;
				mSize = 0;
			}
			else
			{
				mSize = other.mSize;

				NODE<T>* copy_from{ other.mPtr };
				
				NODE<T>* first_node = new NODE<T>;
				first_node->data = copy_from->data;
				mPtr = first_node;

				NODE<T>* current{ mPtr };

				while (copy_from->next_node != nullptr)
				{
					copy_from = copy_from->next_node;

					NODE<T>* temp = new NODE<T>;

					temp->data = copy_from->data;
					
					current->next_node = temp;

					current = current->next_node;
				}
			}

			return *this;
		}

		LIST<T>& operator = (LIST<T>&& other)
		{
			if (other.mPtr == nullptr || mPtr == other.mPtr)
			{
				if (mPtr)
				{
					NODE<T>* current{ mPtr };
					NODE<T>* next{ nullptr };

					while (next != nullptr)
					{
						next = current->next_node;
						delete current;
					}
				}

				mPtr = nullptr;
				mSize = 0;
			}
			else
			{
				mSize = other.mSize;
				mPtr = other.mPtr;

				other.mPtr = nullptr;
			}

			return *this;
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
					next = current->next_node;
					delete current;
				}
			}

			mPtr = new NODE<T>{};

			mSize = 0;
		}

		T& front()
		{
			return mPtr->data;
		}
		T& back()
		{
			NODE<T>* traverser = mPtr;

			while (traverser->next_node != nullptr)traverser = traverser->next_node;
			
			return traverser->data;
		}

		T& operator[](size_t pos)
		{
			if (pos >= mSize)return back();

			NODE<T>* temp = mPtr;

			for (size_t i = 0; i < pos; ++i)temp = temp->next_node;

			return temp->data;
		}

		void push_back(T what)
		{
		
			if (mPtr == nullptr)
			{
				NODE<T>* new_node = new NODE<T>{};
				new_node->data = what;
				mPtr = new_node;
			}
			else
			{
				NODE<T>* find_pos = mPtr;
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
			if (mPtr == nullptr)
			{
				NODE<T>* new_node = new NODE<T>{};

				mPtr->data = what;
				mPtr->next_node = new_node;
			}
			else
			{
				NODE<T>* old_first_node = mPtr;
				NODE<T>* new_first_node = new NODE<T>{};

				new_first_node->data = what;
				new_first_node->next_node = old_first_node;

				mPtr = new_first_node;
			}

			++mSize;
		}

		bool insert(T what, size_t pos)
		{
			if (pos > mSize || mPtr == nullptr)return false;

			NODE<T>* find_pos = mPtr;
			NODE<T>* prev_node = nullptr;
			NODE<T>* new_node = new NODE<T>{};

			if (pos == 0)
			{
				new_node->next_node = mPtr;
				new_node->data = what;

				mPtr = new_node;
			}
			else
			{
				for (size_t i = 0; i < pos; ++i)
				{
					if (i == pos - 1)prev_node = find_pos;
					find_pos = find_pos->next_node;
				}

				new_node->data = what;
				new_node->next_node = find_pos;

				prev_node->next_node = new_node;
			}

			++mSize;

			return true;
		}
		bool erase(size_t pos)
		{
			if (pos > mSize)return false;

			NODE<T>* temp = mPtr;
			NODE<T>* old = nullptr;

			if (pos == 0)
			{
				mPtr = mPtr->next_node;
				delete temp;
			}
			else
			{
				for (size_t i = 0; i < pos; ++i)
				{
					if (i == pos - 1)old = temp;
					temp = temp->next_node;
				}
								
				old->next_node = temp->next_node;
				delete temp;
			}

			--mSize;
			return true;
		}
	};
}