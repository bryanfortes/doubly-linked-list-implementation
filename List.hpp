/*
	const_iterator member functions
								*/
template<typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} //textbook
{}

template<typename T>
const T & List<T>::const_iterator::operator*() const { return retrieve(); } //textbook

template<typename T>
typename List<T>::const_iterator & List <T>::const_iterator::operator++() { //textbook
	current = current->next;
	return *this;
}

template<typename T>
typename List<T>::const_iterator List <T>::const_iterator::operator++(int){ //textbook
	auto old = *this;
	current = current->next;
	return old;
}

template<typename T>
typename List<T>::const_iterator & List <T>::const_iterator::operator--(){
	current = current->prev;
	return *this;
}

template<typename T>
typename List<T>::const_iterator List <T>::const_iterator::operator--(int){ 
	auto old = *this;
	current = current->prev;
	return old;
}

template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{return current == rhs.current;}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{return !(*this == rhs);}

template<typename T>
T & List<T>::const_iterator::retrieve()const //textbook
{return current->data;}

template<typename T>
List<T>::const_iterator::const_iterator(typename List<T>::Node* p) : current{p} //textbook
{}

/*
	iterator member functions
							*/
							
template<typename T>
List<T>::iterator::iterator(){} //textbook

template<typename T>
T & List<T>::iterator::operator*() 
{return this->current->data;}

template<typename T>
const T & List<T>::iterator::operator*()const
{return this-> retrieve();}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++(){ //textbook
	this->current = this-> current->next;
	return *this;
}
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){ //textbook
	auto old = *this;
	this->current = this->current->next;
	return old;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--(){
	this->current = this-> current->prev;
	return *this;
}
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
	auto old = *this;
	this->current = this->current->prev;
	return old;
}
template<typename T>
List<T>::iterator::iterator(typename List<T>::Node* p)  : List<T>::const_iterator{p} //textbook
{}

/***************************
*	List member functions	*
****************************/
						


template<typename T>
List<T>::List() {init();} //textbook

template<typename T> //copy constructor
List<T>::List(const List<T> & rhs) { //textbook
	init();
	for(auto itr = rhs.begin(); itr != rhs.end(); ++itr)
		push_back(*itr);
}

template<typename T> //move construotor 
List<T>::List(List<T> && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} { //textbook
	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template<typename T>
List<T>::List(int num, const T & val){
	init();
	for(int i =0; i < num; i++)
		push_back(val);
}

template<typename T>
List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end){ //textbook
	init();
	for(auto itr = start; itr != end; ++itr)
		push_back(*itr);
}

template<typename T>
List<T>::List(typename std::initializer_list<T> iList){
	init();
	for(auto itr = iList.begin(); itr != iList.end(); ++itr)
		push_back(*itr);
}

template<typename T>
List<T>::~List(){ //textbook
	clear();
	delete head;
	delete tail;
}

template<typename T>
const List<T> & List<T>::operator=(const List<T> & rhs) { //textbook
	auto copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename T>
List<T> & List<T>::operator=(List<T> && rhs){
	init();
	*this = std::move(rhs);
	return *this;
}

template<typename T>
List<T> & List<T>::operator=(typename std::initializer_list<T> iList){
	init();
	for(auto itr = iList.begin(); itr != iList.end(); ++itr)
		push_back(*itr);
	return *this;
}

template<typename T>
int List<T>::size() const{return theSize;} //textbook

template<typename T>
bool List<T>::empty() const{return size()==0;} //textbook

template<typename T> 
void List<T>::clear(){ //textbook
	while(!empty())
		pop_back();
}

template<typename T>
void List<T>::reverse(){
	if(!empty()){
		auto ptr = head;
		while(ptr != nullptr){ //swaps next and prev pointers
			std::swap(ptr->next, ptr->prev);
			ptr = ptr->prev; //this points to the swapped "next" pointer
		}
	}
	std::swap(head, tail);
}
template<typename T>
T & List<T>::front() {return *begin();} //textbook

template<typename T>
const T & List<T>::front() const{return *begin();} //textbook

template<typename T>
T & List<T>::back(){return *(--end());} //textbook

template<typename T>
const T & List<T>::back()const{return *(--end());} //textbook

template<typename T>
void List<T>::push_front(const T & val){insert(begin(), val);} //textbook

template<typename T>
void List<T>::push_front(T && val){insert(begin(), std::move(val));} //textbook

template<typename T>
void List<T>::push_back(const T & val){insert(end(), val);} //textbook

template<typename T>
void List<T>::push_back(T && val){insert(end(), std::move(val));} //textbook

template<typename T>
void List<T>::pop_front(){erase(begin());} //textbook

template<typename T>
void List<T>::pop_back(){erase(--end());} //textbook

template<typename T>
void List<T>::remove(const T & val){ 
	for( auto itr = begin(); itr != end(); ++itr)
		if(*itr == val)
			erase(itr);
}

template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
	for(auto itr= begin(); itr != end(); ++itr)
		if(pred(*itr))
			erase(itr);
}

template<typename T>
void List<T>::print(std::ostream & os, char ofc) const{
	for(auto itr = begin(); itr != end(); ++itr)
		os << *itr << ofc; 
}

template<typename T>
typename List<T>::iterator List<T>::begin(){ //textbook
	typename List<T>::iterator itr{head->next}; 
	return itr;
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const{ //textbook
	typename List<T>::const_iterator const_itr{head->next};
	return const_itr;
}
template<typename T>
typename List<T>::iterator List<T>::end(){ //textbook
	typename List<T>::iterator itr{tail};
	return itr;
}
template<typename T>
typename List<T>::const_iterator List<T>::end() const{ //textbook
	typename List<T>::const_iterator const_itr{tail};
	return const_itr;
}

template<typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T & val){
	auto* p = itr.current;
	theSize++;
	auto* p2 = new List<T>::Node{val, p->prev, p};
	p->prev->next = p2;
	p->prev = p2;
	typename List<T>::iterator temp{p2};
	return temp;
}

template<typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, T && val){
	auto* p = itr.current;
	theSize++;
	auto* p2 = new List<T>::Node{std::move(val), p->prev, p};
	p->prev->next = p2;
	p->prev = p2;
	typename List<T>::iterator temp{p2};
	return temp;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr){
	auto* p = itr.current;
	typename List<T>::iterator retVal{ p->next };
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	return retVal;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator start, typename List<T>::iterator end){ //textbook
	for(auto itr = start; itr != end;)
		itr = erase(itr);
	return end;
}

template<typename T>
void List<T>::init(){ //textbook
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

template<typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs){
	if(lhs.size() == rhs.size()){ //compare sizes
		auto right = rhs.begin(); //create dummy rhs itr
		for(auto left = lhs.begin(); left != lhs.end(); ++left){ //create and iterate through lhs itr
			if(*left != *right) //if elements are different return false
				return false;
			else 
				++right; //else iterate rhs dummy
		}
		return true; //return true when complete
	}
	else
		return false; //return false if size are !=
}

template<typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs){return !(lhs == rhs);}

template<typename T>
std::ostream & operator<<( std::ostream & os, const List<T> & l){
	l.print(os);
	return os;
}
