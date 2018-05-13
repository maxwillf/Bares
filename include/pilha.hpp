#include <iostream>

namespace sc
{
	template <typename T>

	class stack
	{
		private:

		T *storage; //< armazena os dados
		size_t m_size; //tamanho de armazenamento
		size_t m_topo; //indice do topo

		/*! Allocates twice the current amount of memory */
		void double_storage(void)
		{
			T* temp = new T[2*m_size];
			
			//copiar os dados para nova area
			for( auto i(0u); i < m_topo; i++)
			{
				temp[i] = storage[i];
			}
			
			//liberar area antiga
			delete [] storage;

			//redirecionar o ponteiro para nova area
			storage = temp;

			//dobra o tamanho
			m_size *= 2;

		}
		public:
			/*! Constructor */
			explicit stack(void) : storage(new T[1]), m_size(1), m_topo(0) //lista inicializadora!!
			{ }
			~stack(void)
			{
				delete [] storage;
			}

		/*! Inserts a new element at the top of the stack */
		void push(const T& value) 
		{
			//se esta cheio aloca mais memoria
			if(m_size == m_topo)
			{
				double_storage();
			}

			//armazena 
			storage[m_topo++] = value;
				
		}
		/*! Removes the element at the top of the stack*/
		void pop() //remove o primeiro elemento da pilha
		{
			if( empty() )
				throw std::runtime_error("pew pop");

			--m_topo;
		}
		/*! Returns the element at the top of the stack*/
		T top(void ) const//retorna o elemento do m_topo da pilha
		{
			if( empty())
				throw std::runtime_error("pew top");

			return storage[m_topo-1];
		}
		/*! Checks if the stack is empty */
		bool empty(void ) const //verifica se a pilha esta vazia
		{
			return m_topo == 0;
		}
		/*! Returns the size of the stack */
		size_t size(void ) const //retorna o tamanho da pilha
		{
			return m_topo;
		}

		/*! Deletes all elements from the stack*/
		void clear(void ) // limpa a pilha
		{
			m_topo = 0;
		}


	};
}
