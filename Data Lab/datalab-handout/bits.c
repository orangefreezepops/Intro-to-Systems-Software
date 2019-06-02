/* 
 * CS:APP Data Lab 
 * 
 * Keegan Fouse kdf11@pitt.edu
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code 
must conform to the following style:

int Funct(arg1, arg2, ...) {
	/* brief description of how your implementation works */
	int var1 = Expr1;
	...
		int varM = ExprM;

	varJ = ExprJ;
	...
		varN = ExprN;
	return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting if the shift amount
is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	int result = (1 << x);
	result += 4;
	return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
	the coding rules are less strict.  You are allowed to use looping and
	conditional control.  You are allowed to use both ints and unsigneds.
	You can use arbitrary integer and unsigned constants. You can use any arithmetic,
	logical, or comparison operations on int or unsigned data.

	You are expressly forbidden to:
	1. Define or use any macros.
	2. Define any additional functions in this file.
	3. Call any functions.
	4. Use any form of casting.
	5. Use any data type other than int or unsigned.  This means that you
	cannot use arrays, structs, or unions.
	6. Use any floating point data types, operations, or constants.


	NOTES:
	1. Use the dlc (data lab checker) compiler (described in the handout) to 
	check the legality of your solutions.
	2. Each function has a maximum number of operations (integer, logical,
			or comparison) that you are allowed to use for your implementation
	of the function.  The max operator count is checked by dlc.
	Note that assignment ('=') is not counted; you may use as many of
	these as you want without penalty.
	3. Use the btest test harness to check your functions for correctness.
	4. Use the BDD checker to formally verify your functions
	5. The maximum number of ops for each function is given in the
	header comment for each function. If there are any inconsistencies 
	between the maximum ops in the writeup and in this file, consider
	this file the authoritative source.

	/*
	 * STEP 2: Modify the following functions according the coding rules.
	 * 
	 *   IMPORTANT. TO AVOID GRADING SURPRISES:
	 *   1. Use the dlc compiler to check that your solutions conform
	 *      to the coding rules.
	 *   2. Use the BDD checker to formally verify that your solutions produce 
	 *      the correct answers.
	 */


#endif
	//1
	/* 
	 * bitXor - x^y using only ~ and & 
	 *   Example: bitXor(4, 5) = 1
	 *   Legal ops: ~ &
	 *   Max ops: 14
	 *   Rating: 1
	 */
int bitXor(int x, int y) {
	/*using 447 notes and demorgans laws i found that a
	 *combination of ~x&y and x&~y isolated each of the interior bits needed
	 *for XOR functions and then continued to plug them into '&' operations
	 *and negating them too to finally arrive at the XOR
	 */
	int first, second, result;
	first = (~x & y);
	second = (x & ~y);
	result = ~(~first & ~second);
	return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/*
	 *left shift the 1 bit all the way to the very last position.
	 *since its signed think of its positive... 0x7FFFFFFF, the very last integer
	 *to begin with a 0, the next integer would make it negative, so because its 
	 *the last positive number, its twos complement is the most negative number.
	 */
	return 1 << 31;
}
//2
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/*
	 *created the number 0xAAAAAAAA (all odd positions are 1) by loading the higher bits
	 *AND'd that number with x to see if the odd numbered bits corresponded.
	 *XOR'd that number with the original 0xAAAAAAAA to check that the odd bits
	 *are in fact 1's (everything would come out zero if they were) and then
	 *negated the whole operation... so, if all odd bits were 1 (!0 = 1 = true)
	 *otherwise it would result in an integer which would be negated to zero (!x = 0)
	 */
	int reference;
	reference = (0xAA << 8) + 0xAA;
	reference = (reference << 16) + reference;
	return !((x & reference) ^ reference);
}
//3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/*
	 *first you need to get x into a true/false form of 1 or 0
	 *double negating it will put it in that form, !!0 = 0, !!1 = 1
	 *then you can AND both of the outcomes with,
	 *(~x + 1) (all 1's or all 0's) for y, or its complement ~(~x + 1) for z   
	 *The AND-ing of y and z with all 1's or 0's will give you
	 *the answer of which one is true, you then just OR the two options
	 *and return that
	 */
	int ytrue, ztrue;
	x = !!x;
	ytrue = y & (~x + 1);
	ztrue = z & (~(~x + 1));
	return ytrue | ztrue;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/*
	 *(x | -x) will always be 1 unless x is 0, so do the operation
	 *then shift the sign bit all the way to the right producing 
	 *either all 1's or 0. Add 1 and youll either create a positive 
	 *or set it to zero
	 */
	int neg, signbit;
	neg = ~x + 1;
	signbit = (x | neg);
	x = signbit >> 31;
	return x + 1;
}
//float
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/*
	 *isolate the sign bit, exponent bits, fraction bits, bias and e value get them into
	 *signed integers by AND-ing them with all 1's. 
	 *If the exponent value is all 1's return 0x80000000u bc those are special cases
	 *if the exponent value is less than the bias return 0 - denormalized cases 
	 *for the normalized cases first get the E value then check for overflow
	 *if the E value is greater than the number of bits in the fraction portion
         *shift the bits left by the difference of E and 23. if its less shift right
	 *by the difference of 23 and E this corresponds to positive and negative 
	 *integers respectively. add 1 and shift for the normalized case. if the sign bit  
	 *is negative change it, then return the result.
	 */
	 unsigned sign, exponent, fraction, bias, result, e;
	 sign = uf >> 31;
	 exponent = (uf >> 23) & 0xFF;
	 fraction = (uf & 0x7FFFFF);
	 bias = 0x7f;
	 result = fraction;

	 if (exponent == 0xFF){
		 //special out of bounds cases
		 return 0x80000000u;
	 }

	 if (exponent < bias){
		 //denormalized cases
		 return 0x0;
	 }
	 //for normalized cases
	 e = exponent - bias;
	 if (e >= 31){
		 //to protect overflow
		 return 0x80000000u;
	 }

	 if (e >= 22){
		 result = fraction << (e - 23);
	 } else {
		 result = fraction >> (23 - e);
	 }

	 result = (result + 1) << e;

	 if (sign){
		 result = - result;
	 }
	 return result;

}
