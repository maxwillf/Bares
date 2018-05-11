#include <iostream>
#include <iomanip>
#include <vector>
#include "pilha.hpp"
#include <cassert>
#include "../include/parser.h"
#define debug false
sc::vector<std::string> expressions =
{
"10000000 - 2",
"2+          ",
"3 * d       ",
"2 = 3       ",
"2.3 + 4     ",
"2 * 3 4     ",
"2 ** 3      ",
"%5 * 10     ",
"*5 * 10     ",
"(2+3)*/(1-4)",
"(-3*4)(10*5)",
"2 - 4)      ",
"2) - 4      ",
")2 - 4      ",
"((2%3) * 8  ",
//"3/(1-1)     ",
//"10/(3*3^-2) ",
"20*20000    ",
    "10",
    "    12    +    4   8",
    "32767 - 32768 + 3",
    "5 + -32766",
    "5 + -32769",
    "12 + 3",
    "-3+-5+-6",
    "12 + 3     -3 + -34 ",
    "+12",
    "1.3 * 4",
    "a + 4",
    "       ",
    "  123 *  548",
	"5 / 2 " ,
	" 7 ^3 +2", 
	" 3+(5+2) ",
	"(2*3+(5-2))",
	"(2*3+(5-2)",
"25 / 5+4 *8",
"(2+3) * 8",
"5 % 2 ^4",
"(5 % 3) ^4",
"-----3",
"2^3^2"
};

void print_error_msg( const Parser::ResultType & result, std::string str )
{
    std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    error_indicator[result.at_col] = '^';
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << ">>> Unexpected end of input at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << ">>> Ill formed integer at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << ">>> Missing <term> at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << ">>> Extraneous symbol after valid expression found at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << ">>> Integer constant out of range beginning at column (" << result.at_col+1 << ")!\n";
            break;
        default:
            std::cout << ">>> Unhandled error found!\n";
            break;
    }

    std::cout << "\"" << str << "\"\n";
    std::cout << " " << error_indicator << std::endl;
}

sc::vector<Token> infix_to_postfix(sc::vector < Token > lista)
{
	sc::vector <Token> posfix;
	sc::stack <Token> s;

	for (const auto &c : lista) {
		if (c.type == Token::token_t::OPERAND) {
			posfix.push_back( c);
		}	
		else if (c.value == "(") {
			s.push(c);	
		}
		else if (c.value == ")") {
	
			while(not s.empty() and s.top().value != "(" ){
				
				posfix.push_back( s.top());
				s.pop();
				}
			s.pop();
		}
		else if ( c.type == Token::token_t::OPERATOR) {
		std::cout << "Operator: " << c.value << " Precendence: " << c.precedence << std::endl;
			while(not s.empty() and (s.top().precedence >= c.precedence)
					and s.top().precedence < 3){ //op1 != ^
					
			posfix.push_back( s.top());
			s.pop();
			}

			s.push(c);

		}
	}
	
	while(not s.empty())
	{

		posfix.push_back(s.top());
		s.pop();
	}

	if(debug){
		for (auto i = posfix.begin(); i != posfix.end(); ++i) {
			std::cout << *i << std::endl;
		}	
	}

	return posfix; 
}
int execute_operator(int op1, int op2, char c)
{
	switch( c )
	{
		case '^': return pow(op1,op2);
		case '*': return op1*op2;
		case '/': if (op2 == 0) throw std::runtime_error("Division by zero");
					  return op1/op2;
		case '%': if (op2 == 0) throw std::runtime_error("Division by zero");
					  return op1%op2;
		case '+' : return op1+op2;
		case '-' : return op1-op2;
		default  : assert( false );


	}
}

int evaluate_postfix(sc::vector <Token> postfix)
{
	sc::stack<int> s;
	/*	while(not postfix.empty()){
			std::cout << "Stack values(up to bottom) " <<  c.value << std::endl;
			postfix.pop(); } */
	int result = 0;
	if(postfix.size() == 1) return std::stoll(postfix[0].value);
	for(const auto & c: postfix)
	{
		if(  c.type == Token::token_t::OPERAND  ){
			s.push(  std::stoll(c.value ) );
		}
		else if (not postfix.empty() and
				c.type == Token::token_t::OPERATOR ) {
			auto op2(s.top() ); s.pop();	
			auto op1(s.top() ); s.pop();	

			s.push( execute_operator(op1,op2,c.value[0]));
			result = s.top();
		}
		else assert(false);
	}
	return result;
}





int main()
{
    Parser my_parser; // Instancia um parser.
    // Tentar analisar cada expressão da lista.
    for( const auto & expr : expressions )
    {
        // Fazer o parsing desta expressão.
        auto result = my_parser.parse( expr );
        // Preparar cabeçalho da saida.
        std::cout << std::setfill('=') << std::setw(80) << "\n";
        std::cout << std::setfill(' ') << ">>> Parsing \"" << expr << "\"\n";
        // Se deu pau, imprimir a mensagem adequada.
        if ( result.type != Parser::ResultType::OK )
            print_error_msg( result, expr );
        else
            std::cout << ">>> Expression SUCCESSFULLY parsed!\n";

         // Recuperar a lista de tokens.
        auto lista = my_parser.get_tokens();
        std::cout << ">>> Tokens: { ";
        sc::copy( lista.begin(), lista.end(),
                std::ostream_iterator< Token >(std::cout, " ") );
        std::cout << "}\n";
		if(result.type != Parser::ResultType::OK) continue;
		sc::vector<Token> postfix = infix_to_postfix(lista);
	
		long op_result = evaluate_postfix(postfix);
	
		if(op_result > 32767 or op_result < -32768){
			std::cout << "Numeric overflow error!" << std::endl;
		}
		
		else{
			std::cout << "Resultado: " << op_result << std::endl;
		}
    }



    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}
