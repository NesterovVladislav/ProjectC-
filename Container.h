#ifndef __Container_H_
#define __Container_H_

#include <stdexcept>

template< class T > struct Node{
	explicit Node< T >( T const & iData )
		: m_data( iData )
		, m_next()
		, m_previous()
	{}
	~Node(){}
	T  m_data;
	Node<T> * m_next;
	Node<T> * m_previous;
};

template< class T > class Container{
public:
	Container()
		: m_head( NULL )
		, m_tail( NULL )
		, tmp( NULL )
		, m_size( 0 )
	{}
	~Container(){
		while ( m_size > 0 ){
			try{
				RemoveBack();
			}
			catch ( std::invalid_argument & except )
			{
				std::cerr << except.what() << std::endl;
			}
		}
	}
	void PushFront( T const &  iData ){
		Node< T > * newHead = new Node< T >( iData );
		if ( m_size == 0 ){
			m_tail = newHead;
		}
		else{
			m_head->m_previous = newHead;
			newHead->m_next = m_head;
		}
		m_head = newHead;
		++m_size;
	}
	int RemoveFront(){
		if ( m_size == 0 ){
			throw std::invalid_argument( "Deleting of an empty list." ); 
		}
		else if ( m_size == 1 ){
			delete m_head;
			m_tail = NULL;
			tmp = NULL;
			--m_size;
		}
		else{
			tmp = m_head->m_next;
			tmp->m_previous = NULL;
			delete m_head;
			m_head = tmp;
			--m_size;
		}
		return 1;
	}
	void PushBack( T const & iData ){
		Node< T > * newTail = new Node< T >( iData );
		newTail->m_data = iData;
		if ( m_size == 0 ){
			m_head = newTail;
		}
		else{
			m_tail->m_next = newTail;
			newTail->m_previous = m_tail;
		}
		m_tail = newTail;
		++m_size;
	}
	int RemoveBack(){
		if ( m_size == 0 ){
			throw std::invalid_argument( "Deleting of an empty list." ); 
		}
		else if ( m_size == 1 ){
			delete m_tail;
			m_head = NULL;
			tmp = NULL;
			--m_size;
		}
		else{
			tmp = m_tail->m_previous;
			tmp->m_next = NULL;
			delete m_tail;
			m_tail = tmp;
			--m_size;
		}
		return 1;
	}
	T const * GetElement( size_t iIndex ){
		if ( m_size < iIndex ){
			throw std::invalid_argument( "Going beyond the list." );
		}
		else{
			Node< T > * getElem = m_head;
			while ( iIndex > 0 ){
				getElem = getElem->m_next;
				--iIndex;
			}
			return & getElem->m_data;
		}
	}
	T const * GetHead() const {
		return & m_head->m_data;
	}
	T const * GetTail() const {
		return & m_tail->m_data;
	}
	size_t GetSize() const {
		return m_size;
	}
	bool Emty() const {
		return m_size == 0 ? false : true;
	}
private:
	Node< T > * m_head;
	Node< T > * m_tail;
	Node< T > * tmp;
	size_t m_size;

};

#endif // __Container_H_