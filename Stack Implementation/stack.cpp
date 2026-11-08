#include "stack.h"

Stack::Stack(int n)
{
	num = n;
	array = new int[num];
	top = -1;
}

Stack::~Stack()
{
	delete[] array;
}

void Stack::Push(int n)
{
	/*try
	{
		if (IsFull()) throw StackFull();
		top++;
		array[top] = n;
	}
	catch (StackFull)
	{
		Resize(n);
	}*/
	if (IsFull()) Resize(n);
	else
	{
		top++;
		array[top] = n;
	}
}

void Stack::Pop()
{
	if (IsEmpty()) throw StackEmpty();
	else top--;
}

bool Stack::IsEmpty() const
{
	return (top == -1);
}

bool Stack::IsFull() const
{
	return (top == (num - 1));
}

void Stack::MakeEmpty()
{
	top = -1;
}

int Stack::Top() const
{
	if (IsEmpty()) throw StackEmpty();
	else return array[top];
}

int Stack::Size() const
{
	return top + 1;
}

int Stack::Max() const
{
	if (IsEmpty()) throw StackEmpty();
	else
	{
		int max = array[0];
		for (int i = 0; i < top+1; i++)
		{
			if (array[i] > max) max = array[i];
		}
		return max;
	}
}

int Stack::Min() const
{
	if (IsEmpty()) throw StackEmpty();
	else
	{
		int min = array[0];
		for (int i = 0; i < top+1; i++)
		{
			if (array[i] < min) min = array[i];
		}
		return min;
	}
}

int Stack::Peek(unsigned int n) const
{
	if (top < static_cast<int>(n)) throw StackInvalidPeek();
	return array[top - n];
}

int Stack::Capacity() const
{
	return num ;
}

void Stack::Resize(int n)
{
	try
	{
		int newnum = 2 * num;
		int* temp = new int[newnum];

		for (int i = 0; i < top+1; i++)
		{
			temp[i] = array[i];
		}

		delete[] array;
		array = temp;
		num = newnum;

		top++;
		array[top] = n;
	}
	catch(bad_alloc&)
	{
		throw StackFull();
	}
}