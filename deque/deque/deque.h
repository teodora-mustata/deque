#include <iostream>
#include <vector>
#include <array>

template<typename T>
class deque
{
private:
	static const int block_size = 8;
	std::vector<std::array<T, block_size>*> blocks;
	int numElements;
	int frontBlock, backBlock, frontElement, backElement;
	int blockCnt = 0;
public:
	deque(); //constructor
	~deque(); //destructor
	void push_back(const T& element);
	void push_front(const T& element);
	int size();
	T& operator[](int index);
	std::vector<std::array<T, 8>*> vector();
	int blocksize();
	T& front();
	T& back();
	bool empty();
	void clear();
	void pop_back();
	void pop_front();
	void insert(const T& element, int poz);
	void delete_element(int poz);
	void display();
	void resetblockCnt();
};

//constructor
template<typename T>
deque<T>::deque() 
{
	numElements = 0;
	frontBlock = backBlock = frontElement = backElement = 0;
}

//destructor
template<typename T>
deque<T>::~deque() 
{
	for (auto block : blocks) 
		{
			delete block;
		}
}

template<typename T>
inline void deque<T>::push_back(const T& element)
{
	if (numElements == 0) //nu există elemente
	{
		blocks.push_back(new std::array<T, block_size>);
		(*blocks[0])[0] = element;
		backBlock = 0;
		backElement = 0;
		frontBlock = 0;
		frontElement = 0;
	}
	else {
		if (backElement == block_size - 1) // nu este loc de inserare la dreapta
		{
			blocks.push_back(new std::array<T, block_size>);
			backBlock++;
			backElement = 0;
		}
		else //blocul nu este plin
		{
			backElement++;
		}
		(*blocks[backBlock])[backElement] = element;
	}
	numElements++;
}

template<typename T>
inline void deque<T>::push_front(const T& element)
{
	if (numElements == 0) // nu există elemente
	{
		blocks.push_back(new std::array<T, block_size>);
		(*blocks[0])[block_size-1] = element;
		backBlock = 0;
		backElement = block_size - 1;
		frontBlock = 0;
		frontElement = block_size-1;
	}
	else {
		if (frontElement == 0) // nu este loc de inserare la stanga
		{
			blocks.insert(blocks.begin(), new std::array<T, block_size>);
			frontBlock = 0;
			frontElement = block_size - 1;
			backBlock++;
		}
		else // primul bloc nu este plin
		{
			frontElement--;
		}
		(*blocks[frontBlock])[frontElement] = element;
	}
	numElements++;
}

template<typename T>
inline int deque<T>::size()
{
	return numElements;
}

template<typename T>
inline T& deque<T>::operator[](int index)
{
	if (index < 0 || index >= numElements)
	{
		throw std::out_of_range("Index out of range");
	}

	int blockIndex = (frontBlock + index / block_size) % blocks.size() + blockCnt;
	int elementIndex = (frontElement + index % block_size) % block_size;
	int nextElementIndex = (frontElement + (index + 1) % block_size) % block_size;

	T result = (*blocks[blockIndex])[elementIndex];

	if (nextElementIndex == 0 && index < numElements - 1) {
		blockCnt++;
	}

	return result;
}

template<typename T>
inline std::vector<std::array<T, 8>*> deque<T>::vector()
{
	return blocks;
}

template<typename T>
inline int deque<T>::blocksize()
{
	return block_size;
}

template<typename T>
inline T& deque<T>::front() 
{
	if (numElements == 0) 
	{
		throw std::out_of_range("Deque is empty");
	}
	return (*blocks[frontBlock])[frontElement];
}

template<typename T>
inline T& deque<T>::back()
{
	if (numElements == 0)
	{
		throw std::out_of_range("Deque is empty");
	}
	return (*blocks[backBlock])[backElement];
}

template<typename T>
inline bool deque<T>::empty()
{
	return numElements == 0;
}

template<typename T>
inline void deque<T>::clear()
{
	for (auto block : blocks) {
		delete block;
	}
	blocks.clear();
	numElements = 0;
	frontBlock = backBlock = frontElement = backElement = 0;
}

template<typename T>
inline void deque<T>::pop_back()
{
	if (numElements == 0) {
		throw std::out_of_range("Deque is empty.");
	}
	if (backElement == 0) //suntem la inceputul blocului, trebuie sa eliminam blocul
	{
		delete blocks[backBlock];
		blocks.pop_back();
		backBlock--;
		backElement = block_size - 1;
	}
	else {
		backElement--;
	}
	numElements--;
}

template<typename T>
inline void deque<T>::pop_front()
{
	if (numElements == 0) {
		throw std::out_of_range("Deque is empty.");
	}
	if (frontElement == block_size - 1) //suntem la sfarsitul blocului, trebuie sa eliminam blocul
	{
		delete blocks[frontBlock];
		blocks.erase(blocks.begin());
		frontBlock=0;
		frontElement = 0;
	}
	else {
		frontElement++;
	}

	numElements--;
}

template<typename T>
inline void deque<T>::insert(const T& element, int poz)
{
	if (poz < 0 || poz > numElements)
	{
		throw std::out_of_range("Index out of range");
	}

	if (poz == 0)
	{
		push_front(element);
	}
	else if (poz == numElements)
	{
		push_back(element);
	}
	else
	{
		if (numElements % block_size == 0) //blocurile sunt pline
		{
			blocks.push_back(new std::array<T, block_size>);
			backElement = 0;
			backBlock++;
		}
		numElements++;
		for (int i = numElements-1; i > poz; --i)
		{
			(*this)[i] = (*this)[i - 1];
		}

		(*this)[poz] = element;
	}
}

template<typename T>
inline void deque<T>::delete_element(int poz)
{
	if (poz < 0 || poz >= numElements)
	{
		throw std::out_of_range("Index out of range");
	}

	if (numElements == 1)
	{
		clear();
		return;
	}

	if (poz == 0)
	{
		pop_front();
		return;
	}

	if (poz == numElements - 1)
	{
		pop_back();
		return;
	}

	for (int i = poz; i < numElements - 1; ++i)
	{
		(*this)[i] = (*this)[i + 1];
	}

	numElements--;
	if (backElement == 0)
	{
		backBlock--;
		backElement = block_size - 1;
	}
	else
	{
		backElement--;
	}
}

template<typename T>
inline void deque<T>::display()
{
	if (numElements == 0) {
		std::cout << "Deque is empty.\n";
		return;
	}

	std::cout << "Deque elements: ";
	for (int i = 0; i < numElements; i++)
		std::cout << (*this)[i] << " ";
	std::cout << "\n";
}

template<typename T>
inline void deque<T>::resetblockCnt()
{
	blockCnt = 0;
}

