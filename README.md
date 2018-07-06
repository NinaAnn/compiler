# compiler
Proj of the compiler course of Alain
Explication des choix fait :
Mon compilateur a les fonctions :
¬	Les opérations fondamentales : 
Plus +, moins -, multiplication *, division /, égalité = Tous INT -› INT
¬	dup (n – n n) ANY -› ANY, ANY, 
¬	drop (n - ) ANY -› void
¬	swap (n1 n2 – n2 n1) ANY1 ANY2 -› ANY2 ANY1 (Probème)
¬	. (e - ) INT -› void
¬	count type CHAIN -› void
¬	recurse void -› void: cette fonction peut seulement fonctionner quand il est dans ‘if else then’ .
¬	calculate CHAIN -› INT
¬	if ( else ) then : ‘if’ et ‘else’ peuvent avoir le même ‘input’ et ‘output’
¬	read : CHAIN -› void compiler les documents
