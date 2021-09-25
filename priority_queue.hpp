#pragma once

template<typename T, typename Container>
class priority_queue {
	Container _container;
	
	/**
	 * Возвращает индекс левого ребёнка по индексу родителя
	 * 2*i + 1
	 */
	int _leftChildIndex(int parentIndex);
	
	/**
	 * Возвращает индекс правого ребёнка по индексу родителя
	 * 2*i + 2
	 */
	int _rightChildIndex(int parentIndex);
	
	/**
	 * Возвращает индекс родителя по индексу ребёнка
	 * (int)(0.5 * i + 0.5) - 1
	 */
	int _parentIndex(int childIndex);
	
	/**
	 * "Просеивание" вверх
	 */
	void _siftUp(int index);
	
	/**
	 * "Просеивание" вниз
	 */
	void _siftDown(int index);
	
public:
	/**
	 * Добавление элемента в очередь
	 * Реализуется через siftUp
	 */
	void push(const T& value);
	
	/**
	 * Возвращает верхний элемент очереди,
	 * НЕ удаляя его
	 *
	 * Возвращает первый элемент
	 */
	T top() const;
	
	/**
	 * Возвращает верхний элемент очереди,
	 * удаляя его
	 * 
	 * Возвращает первый элемент, удаляет его, делает siftDown
	 */
	T pop();
	
	/**
	 * Проверяет, пустая очередь или нет
	 */
	bool empty() const;
};


template<typename T, typename Container>
int priority_queue<T, Container>::_leftChildIndex(int parentIndex) {
	return parentIndex * 2 + 1; // TODO validate returning value
}

template<typename T, typename Container>
int priority_queue<T, Container>::_rightChildIndex(int parentIndex) {
	return parentIndex * 2 + 2; // TODO validate returning value
}

template<typename T, typename Container>
int priority_queue<T, Container>::_parentIndex(int childIndex) {
	return (int)(0.5 * childIndex + 0.5) - 1; // TODO validate returning value
}


template<typename T, typename Container>
void priority_queue<T, Container>::_siftUp(int index) {
	// случай если элемент уже в корне
	if (index == 0) {
		return;
	}
	int parent = 0; // индекс, по которому «поднимаемся» для дальнейшего рекурсивного просеивания вверх
	if (_container[index] > _container[_parentIndex(index)]) {
		parent = _parentIndex(index);
	}
	else {
		return;
	}
	std::swap(_container[index], _container[parent]);
	_siftUp(parent);
}


template<typename T, typename Container>
void priority_queue<T, Container>::_siftDown(int index) {
	// случай если элемент уже внизу
	if (index == _container.size()-1) {
		return;
	}
	int child = 0; // индекс, по которому «спустимся» для дальнейшего рекурсивного просеивания вниз
	// TODO refactoring
	if (_leftChildIndex(index) < _container.size() && _rightChildIndex(index) < _container.size()) {
		if (_container[_leftChildIndex(index)] >= _container[_rightChildIndex(index)]) {
			child = _leftChildIndex(index);
		}
		else {
			child = _rightChildIndex(index);
		}
	}
	else if (_leftChildIndex(index) < _container.size() && _container[index] <= _container[_leftChildIndex(index)]) {
		child = _leftChildIndex(index);
	}
	/*
	else if (_rightChildIndex(index) < _container.size() && _container[index] <= _container[_rightChildIndex(index)]) {
		child = _rightChildIndex(index);
	}
	*/
	else {
		return;
	}
	std::swap(_container[index], _container[child]);
	_siftDown(child);
}


template<typename T, typename Container>
void priority_queue<T, Container>::push(const T& value) {
	_container.push_back(value); // пушим, куда пушается
	if (_container.size() != 1) {
		_siftUp(_container.size() - 1);
	}
}

template<typename T, typename Container>
T priority_queue<T, Container>::top() const {
	return _container[0];
}


template<typename T, typename Container>
T priority_queue<T, Container>::pop() {
	T topValue = top();
	
	// если контейнер из одного элемента, то смысла свопать нет
	if (_container.size() != 1) {
		std::swap(_container[0], _container[_container.size() - 1]);
	}
	_container.pop_back();
	if (!empty()) {
		_siftDown(0);
	}
	return topValue;
}

template<typename T, typename Container>
bool priority_queue<T, Container>::empty() const {
	return _container.empty();
}