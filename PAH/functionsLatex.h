#ifndef _FUNCTIONS_LATEX_H
#define _FUNCTIONS_LATEX_H

#include "LinkedList/linkedlist.h"

void endLatexTag(LinkedList l);
void beginBoldLatex(LinkedList l);
void beginItalicLatex(LinkedList l);
void beginUnderlineLatex(LinkedList l);
void beginTitleLatex(LinkedList l, int level);
void addCloseTagLatex(LinkedList l);
void addIndexLatex();

#endif
