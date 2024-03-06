//
// File: functions.h
//
// @author Alex A Denny aad7700@g.rit.edu
//
//////////////////////////////////////////////

#ifndef FUNC_H
#define FUNC_H

/// The definition of the Result Structur
typedef struct {
    int* integer;	//int array that hold each element of the base 2 and base 10 numbers
    int index;		//int for nummber of elemnts in corresponding base 2 and 10 array
} Result;

/// tenToTwo()
///	   converts a given int from base 10 to base 2
///
/// args -
///	   int num: number to be converted
Result tenToTwo(int num);

/// twoToTen()
///        converts a given int from base 2 to base 10
///
/// args -
///        int num: number to be converted
Result twoToTen(int num);

/// relation()
///        uses Result structure's integer and index components
///	   to create a relationshi[ phrase (father's mother etc.)
///
/// args -
///        Result res: result structure to be used
void relation(Result res);

/// gens_back()
///	   uses Result structure's index to determine
///	   the generations bacl
///
/// args -
///        Result res: result structure to be used
int gens_back(Result res);

/// num_cmdTwo()
///	   user selected two as their command
///
/// args -
///        int num: number user given as base 10
void num_cmdTwo(int num);

/// num_cmdThree()
///        user selected three as their command
///
/// args -
///        int num: number user given as base 2
void num_cmdThree(int num);

/// num_cmdFour()
///        user selected four as their command
///
/// args -
///        Result res: result generated in main with user input
//		to be used in command
//	   int num: int generated in main with user input
//	   	to be used in command
void num_cmdFour(Result res, int num);

#endif //FUNC_H
