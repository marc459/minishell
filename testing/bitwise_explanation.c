#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// La manera de proceder es muy sencilla, usamos constantes para trabajar con cada flag.
// Si te das cuenta, cada valor es justamente el doble del anterior para conseguir el
// efecto deseado en binario; que solo afecte a un bit específico y no se repita.
// De esta forma, cada flag representa un solo bit.
// En c no existe la manera de trabajar directamente con bits y por eso se tiene
// que recurrir a esta técnica.

//									hex			   dec		   bin
#define token_empty				0x00001			//	 1 : 000000001
#define token_string			0x00002			//	 2 : 000000010
#define token_file				0x00004			//	 4 : 000000100
#define token_pipe				0x00008			//	 8 : 000001000
#define token_in_redir1			0x00010			//	16 : 000010000
#define token_in_redir2			0x00020			//	32 : 000100000
#define token_out_redir1		0x00040			//	64 : 001000000
#define token_out_redir2		0x00080			// 128 : 010000000
#define token_end				0x00100			// 256 : 100000000


// Y ahora podemos agrupar "cosas", para no tener que insertar una parrafada en medio del código
// Imagina que queremos trabajar con el concepto de "cualquier redirección" en minishell.
// O simplemente, cualquier operador "| < << < >> ;"
// Bastará con sumar las posiciones binarias y quedará asi:

#define token_in_redir			0x00030			//  48 : 000110000
#define token_out_redir			0x000D0			// 208 : 011000000
#define token_redir				0x000F0			// 240 : 011110000
#define token_operator			0x001F8			// 504 : 111111000

// Si no usásemos este método, la estructura resultante sería algo así:
#ifdef WITHOUT_FLAGS

// Esto era lo que te expliqué el otro día, la alineación de la memoria
// el tipo _Bool solo admite 0 o 1 y el compilador se te debería quejar si tratas de asignar otros
// valores pero no deja de ser un char porque es el espacio mínimo asignable en memoria.
// ¿Por qué usar _Bool si es un char? Simplemente es una forma muy gráfica de saber qué objetivo tiene
// esa variable, no tienes que imaginartelo ni leer el código donde entre en uso.
//
// Dicho lo cual, esta estructura está compuesta por 9 chars, 1 puntero y un int. Si nos ponemos
// a hacer cuentas, podremos entender que la estructura ocupa 9 + 8 + 4 = 21 pero en realidad ocupa 24.
// La memoria está alineada en múltiplos de 8 bytes, por lo que si algo ocupa 21, se le añadiran 3 bytes
// de relleno para lograr la tan deseada alineación.
//
// Ojo! mucho cuidado en cómo se colocan las diferentes variables dentro de la estructura.
// Si los tipos de datos no están agrupados, puede dar como resultado un tamaño más grande.
//
// El ejemplo lo tienes con struct s_test, los he desagrupado y esa estructura es enorme para lo que contiene.
typedef struct s_token
{
        char	*string;
        int		flags;          //Esto lo añado por compatibilidad, que nos conocemos...
        _Bool	is_empty;
        _Bool	is_string;
        _Bool	is_file;
        _Bool	is_pipe;
        _Bool	is_in_redir1;
        _Bool	is_in_redir2;
        _Bool	is_out_redir1;
        _Bool	is_out_redir2;
        _Bool	is_end;
}			t_token;

#else

typedef struct s_token
{
        char	*string;
        int		flags;
}				t_token;

#endif

typedef struct s_test
{
        char	str;
        int		nb;
        char	str1;
        char	*ptr;
        char	str2;
}				t_test;

// funcion recursiva para imprimir la conversión binaria de un numero decimal.
// nb:  numero decimal a imprimir
// len: cantidad de digitos binarios a imprimir (para que esteticamente quede bien)
void	ft_putbin(int nb, int len)
{
		if (!len)
			return;
		ft_putbin(nb / 2, --len);
		printf("%i", nb % 2);
}

// Imprime el contenido de un token
void	print_token(t_token *token)
{
		printf("token->str = \"%s\"\n", token->string);
		printf("flags = ");
		ft_putbin(token->flags, 9);
		printf("\nflags =");
		// & se utiliza como operador lógico "AND". Verificará bit a bit en cada posición si ambos son 1 y nos devolverá un numero resultante
		// En este if, supongamos que token->flags tiene el numero 11 : 000001011 y token_empty 1 : 000000001
		//
		// Sabemos que la tabla de la verdad de AND es:
		// 0 : 0 = 0
		// 0 : 1 = 0
		// 1 : 0 = 0
		// 1 : 1 = 1
		//
		// token_flags  token_empty
		//      000001101       000000001
		// Solo hay una posición donde en ambos numeros hay un 1:
		// 000000001
		// Como el número resultante es mayor de 0 el if lo dará como verdadero e imprimirá " empty"
		if (token->flags & token_empty)
			printf(" empty");
		// El caso se vuelve a repetir, ahora el 1 está en la posición 2, token_string 2 : 000000010
		// Al realizar la operación determinamos que en ambos numeros, la posición 2 es un 1, por tanto entrará en el if
		if (token->flags & token_string)
			printf(" string");
		// Aquí no entrará porque flags 11 : 000001011 y token_file 4 : 000000100 en la posicion 3 no tienen ambos un 1.
		if (token->flags & token_file)
			printf(" file");
		// Aquí si
		if (token->flags & token_pipe)
			printf(" pipe");
		// Y ya no volverá a mostrar nada más.
		if (token->flags & token_in_redir1)
			printf(" in_redir1");
		if (token->flags & token_in_redir2)
			printf(" in_redir2");
		if (token->flags & token_out_redir1)
			printf(" out_redir1");
		if (token->flags & token_out_redir2)
			printf(" out_redir2");
		if (token->flags & token_end)
			printf(" end");
		printf("\n");
}

int		main(void)
{
		t_token token;

		bzero(&token, sizeof(t_token));

		// Vamos a imprimir el tamaño del tipo t_token;
		// Si compilas añadiendo -DWITHOUT_FLAGS verás la diferencia.
		printf("Tamaño de t_token = %lu\n", sizeof(t_token));
		printf("Tamaño de t_test = %lu\n", sizeof(t_test));

		// con esto añadiremos tantos flags como queramos, siempre que usemos el operador lógico "OR".
		// OR se usa para "sumar" (aunque no exactamente). Si tenemos 001001011 y 000100100 nos lo transforma a 001101111
		// Tabla de la verdad de OR
		// 0 : 0 = 0
		// 1 : 0 = 1
		// 0 : 1 = 1
		// 1 : 1 = 1
		//
		// Como sabemos que token.flags no contiene nada porque se ha usado bzero podemos hacer una asignación directa sin usar ningún
		// operador lógico en la asignación. La buena práctica es usar siempre |= para evitar sobreescribir ningún valor que pudiera contener.
		printf("añadimos token_file y token_end\n");
		token.flags = token_file | token_end;
		print_token(&token);

		// "token.flags |=" es lo mismo que usar "token.flags = token.flags | ..." y respeta el valor que pudiera contener previamente.
		printf("añadimos token_in_redir1\n");
		token.flags |= token_in_redir1;
		print_token(&token);

		// Ahora imagina que queremos eliminar un flag de la lista sin tocar el resto. En este caso se hará algo muy inteligente,
		// negaremos binariamente el flag que queramos eliminar:
		//  token_end = 256 : 100000000
		// ~token_end = 255 : 011111111
		// De esta forma lo que aplicaremos es un AND lógico y lograremos el efecto deseado:
		// Dado que el primer bit de ~token_end es 0 y el resto es 1, la resultante será cualquier número quedando el primer bit a 0, que
		// era lo que se buscaba.
		printf("eliminamos token_end\n");
		token.flags &= ~token_end;
		print_token(&token);

		// lo bueno de este sistema es que si tratamos de eliminar un flags que no existe, no pasa nada. Todo funciona correctamente.
		printf("eliminamos token_pipe\n");
		token.flags &= ~token_pipe;
		print_token(&token);

		// esto es lo más interesante de este método. Si quisiéramos saber si tiene algún operador de los posibles, tendríamos
		// que hacer una de estas 4 cosas:
		//
		// if ((token.flags & token_pipe) || (token.flags & token_in_redir1) || (token.flags & token_in_redir2) || (...))
		//
		// o en su lugar:
		//
		// if (token.flags & (token_pipe | token_in_redir1 | token_in_redir2 | token_out_redir1 | ... ))
		//
		// o en su lugar:
		//
		// if (token.is_pipe || token.is_in_redir1 || token.is_in_redir2 || token.is_out_redir1 || ...)
		//
		// o simplemente, usaremos algo muy muy simple:
		//
		// if (token.flags & token_operator)
		//
		// Mucho más fácil de leer y de entender.
		//
		// (vale, si, otro método es encapsularlo en una función que devuelva el tercer caso anterior, algo así como...)
		//
		// _Bool token_is_operator(t_token *token)
		// {
		//              return (token->is_pipe || token->is_redir1 || ...);
		// }
		//
		// if (token_is_operator(&token))
		//
		printf("Tomemos una decisión...\n Si tenemos algun 'operator', le vamos a añadir token_pipe y eliminaremos token_end\n");
		if (token.flags & token_operator)
		{
			token.flags |= token_pipe;
			token.flags &= ~token_end;
		}
		print_token(&token);
		printf("Por último, vamos a añadir manualmente cualquier numero y mostramos los flags que contiene:\n");
		token.flags = 492;
		print_token(&token);
		return (0);
}