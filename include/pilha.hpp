#include <iostream>

namespace sc
{
	template <typename T>

	class stack
	{
		private:

		T *storage; //armazena os dados
		size_t m_size; //tamanho de armazenamento
		size_t m_topo; //indice do topo

		void double_storage(void)
		{
			//criar nova area de armazenamento
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

			explicit stack(void) : storage(new T[1]), m_size(1), m_topo(0) //lista inicializadora!!
			{ }
			~stack(void)
			{
				delete [] storage;
			}


		void push(const T& value) //insere um elemento na pilha
		{
			//se esta cheio aloca mais memoria
			if(m_size == m_topo)
			{
				double_storage();
			}

			//armazena 
			storage[m_topo++] = value;
				
		}
		void pop() //remove o primeiro elemento da pilha
		{
			if( empty() )
				throw std::runtime_error("pew pop");

			--m_topo;
		}
		T top(void ) const//retorna o elemento do m_topo da pilha
		{
			if( empty())
				throw std::runtime_error("pew top");

			return storage[m_topo-1];
		}
		bool empty(void ) const //verifica se a pilha esta vazia
		{
			return m_topo == 0;
		}
		size_t size(void ) const //retorna o tamanho da pilha
		{
			return m_topo;
		}
		void clear(void ) // limpa a pilha
		{
			m_topo = 0;
		}


	};
}
