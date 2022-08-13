/*
 * BPointExpr.h
 *
 *  Created on: Jun 12, 2021
 *      Author: jsymolon
 */

#ifndef BPOINTEXPR_H_
#define BPOINTEXPR_H_

#include "BPoint.h"
#include <string>

class BPointExpr {

public:
	BPointExpr();
	~BPointExpr();
	int getId();
	void setId(int);
	void setPostfixExpr(int*, int);
	void getPostfixExpr(int*, int&);
	void setInfixExpr(int*, int);
	void getInfixExpr(int*, int&);
	std::string getExprString();
	void setExprString(std::string);
	int getCount();
	void setCount(int);
	bool isBreak();
	bool isEnabled();
	void isEnabled(bool);

private:
	int id;		// Uniquely identifies breakpoint expression.
	int postfix_expr[MAX_LB_NODES];
	int infix_expr[MAX_LB_NODES];
	int p_count; // Number of valid postfix_expr elements
	int i_count;
	std::string expr;    // Expression is stored linearly for display.
	int count;	    // Specifies a count for the number of times the other
					// expression conditions must be met before isBrk is true.
	bool isBrk;	    // Flag whether or not the condition to break has been met.
	bool isEnab;	// Flag whether or not the expression is being tested.
};
#endif /* BPOINTEXPR_H_ */
