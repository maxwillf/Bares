#include "../include/parser.h"
#include <iterator>
#include <algorithm>

/// Converts the input character c_ into its corresponding terminal symbol code.
Parser::terminal_symbol_t  Parser::lexer( char c_ ) const
{
    switch( c_ )
    {
        case '+':  return terminal_symbol_t::TS_PLUS;
        case '-':  return terminal_symbol_t::TS_MINUS;
        case ' ':  return terminal_symbol_t::TS_WS;
        case   9:  return terminal_symbol_t::TS_TAB;
        case '0':  return terminal_symbol_t::TS_ZERO;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':  return terminal_symbol_t::TS_NON_ZERO_DIGIT;
        case '\0': return terminal_symbol_t::TS_EOS; // end of string: the $ terminal symbol
    }
    return terminal_symbol_t::TS_INVALID;
}


/// Consumes a valid character from the input source expression.
void Parser::next_symbol( void )
{
    // Advances iterator to the next valid symbol for processing
    std::advance( it_curr_symb, 1 );
}

/// Checks whether we reached the end of the input expression string.
bool Parser::end_input( void ) const
{
    // "Fim de entrada" ocorre quando o iterador chega ao
    // fim da string que guarda a expressão.
    return it_curr_symb == expr.end();
}

/// Returns the result of trying to match the current character with c_, **without** consuming the current character from the input expression.
bool Parser::peek( terminal_symbol_t c_ ) const
{
    // Checks whether the input symbol is equal to the argument symbol.
    return ( not end_input() and
             lexer( *it_curr_symb ) == c_ );
}

/// Returns the result of trying to match (peek()) and consume the current character with c_.
/*!
 * If the match is not successful, the current character (from the input) **is not consumed**.
 * @param c_ the current character from the input source expression we wish to parse.
 * @see peek().
 * @return true if we got a successful match; false otherwise.
 */
bool Parser::accept( terminal_symbol_t c_ )
{
    // If we have a match, we consume the character from the input source expression.
    // caractere da entrada.
    if ( peek( c_ ) )
    {
        next_symbol();
        return true;
    }

    return false;
}

/// Skips all white spaces and tries to accept() the next valid character. @see accept().
bool Parser::expect( terminal_symbol_t c_ )
{
    // Skip all white spaces first.
    skip_ws();
    return accept( c_ );
}


/// Ignores any white space or tabs in the expression until reach a valid character or end of input.
void Parser::skip_ws( void )
{
    // Skip white spaces, while at the same time, check for end of string.
    while ( not end_input() and
            ( lexer( *it_curr_symb ) == Parser::terminal_symbol_t::TS_WS  or
              lexer( *it_curr_symb ) == Parser::terminal_symbol_t::TS_TAB ) )
    {
        next_symbol();
    }
}


//=== Non Terminal Symbols (NTS) methods.

/// Validates (i.e. returns true or false) and consumes an expression from the input string.
/*! This method parses a valid expression from the input and, at the same time, it tokenizes its components.
 *
 * Production rule is:
 * ```
 *  <expr> := <term>,{ ("+"|"-"),<term> };
 * ```
 * An expression might be just a term or one or more terms with '+'/'-' between them.
 */
Parser::ResultType Parser::expression()
{
    // tentamos processar um termo.

    // enquanto der certo, tente processar outros termos.

}

/// Validates (i.e. returns true or false) and consumes a term from the input string.
/*! This method parses a valid term from the input.
 *
 * Production rule is:
 * ```
 *  <term> := <integer>;
 * ```
 * A term is made of a single integer.
 *
 * @return true if a term has been successfuly parsed from the input; false otherwise.
 */
Parser::ResultType Parser::term()
{
    skip_ws();
    // Guarda o início do termo no input, para possíveis mensagens de erro.
    // Processe um inteiro.
    // Vamos tokenizar o inteiro, se ele for bem formado.
        // Copiar a substring correspondente para uma variável string.
        // Tentar realizar a conversão de string para inteiro (usar stoll()).
        // Recebemos um inteiro válido, resta saber se está dentro da faixa.
            // Fora da faixa, reportar erro.
        // Coloca o novo token na nossa lista de tokens.
}

/// Validates (i.e. returns true or false) and consumes an integer from the input string.
/*! This method parses a valid integer from the input and, at the same time, add the integer to the token list.
 *
 * Production rule is:
 * ```
 * <integer> := 0 | ["-"],<natural_number>;
 * ```
 * A integer might be a zero or a natural number, which, in turn, might begin with an unary minus.
 *
 * @return true if an integer has been successfuly parsed from the input; false otherwise.
 */
Parser::ResultType Parser::integer()
{
    // Se aceitarmos um zero, então o inteiro acabou aqui.

    // Vamos tentar aceitar o '-'.
    // Vamos processar um número natural.
}

/// Validates (i.e. returns true or false) and consumes a natural number from the input string.
/*! This method parses a valid natural number from the input.
 *
 * Production rule is:
 * ```
 * <natural_number> := <digit_excl_zero>,{<digit>};
 * ```
 *
 * @return true if a natural number has been successfuly parsed from the input; false otherwise.
 */
Parser::ResultType Parser::natural_number()
{
    // Tem que vir um número que não seja zero! (de acordo com a definição), senão é erro.
    // Cosumir os demais dígitos, se existirem...
}

/// Validates (i.e. returns true or false) and consumes a non-zero digit from the input string.
/*! This method parses a single valid non-zero digit from the input.
 *
 * Production rule is:
 * ```
 * <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
 * ```
 *
 * @return true if a non-zero digit has been successfuly parsed from the input; false otherwise.
 */
bool Parser::digit_excl_zero()
{
    // aceitar qualquer charactere que seja um dígito não zero.
}

/// Validates (i.e. returns true or false) and consumes a zero digit from the input string.
/*! This method parses a single valid digit from the input.
 *
 * Production rule is:
 * ```
 * <digit> := "0"| <digit_excl_zero>;
 * ```
 *
 * @return true if a digit has been successfuly parsed from the input; false otherwise.
 */
bool Parser::digit()
{
    // dá certo se aceitarmos zero ou processarmos um dígito que não seja zero.
}

/*!
 * This is the parser's entry point.
 * This method tries to (recursivelly) validate an expression.
 * During this process, we also store the tokens into a container.
 *
 * \param e_ The string with the expression to parse.
 * \return The parsing result.
 *
 * @see ResultType
 */
Parser::ResultType  Parser::parse( std::string e_ )
{
    expr = e_; //  Guarda a expressão no membro correspondente.
    it_curr_symb = expr.begin(); // Define o simbolo inicial a ser processado.
    ResultType result; // By default it's OK.

    // Sempre limpamos a lista de tokens da rodada anterior.
    token_list.clear();

    // Vamos verificar se recebemos uma  Let us ignore any leading white spaces.
    skip_ws();
    if ( end_input() ) // Premature end?
    {
        result =  ResultType( ResultType::UNEXPECTED_END_OF_EXPRESSION,
                std::distance( expr.begin(), it_curr_symb ) );
    }
    else
    {
        // chamada regular para expressão.
        result = expression();

        // Verificar se ainda sobrou algo na expressão.
        if ( result.type == ResultType::OK )
        {
            // Neste momento não deveria ter nada sobrando na string, a não ser
            // espaços em branco.
            skip_ws(); // Vamos "consumir" os espaços em branco, se existirem....
            if ( not end_input() ) // Se estiver tudo ok, deveríamos estar no final da string.
            {
                return ResultType( ResultType::EXTRANEOUS_SYMBOL, std::distance( expr.begin(), it_curr_symb ) );
            }
        }
    }

    return result;

}


/// Return the list of tokens, which is the by-product created during the syntax analysis.
std::vector< Token >
Parser::get_tokens( void ) const
{
    return token_list;
}



//==========================[ End of parse.cpp ]==========================//