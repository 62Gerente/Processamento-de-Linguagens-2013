#ifndef _FUNCTIONS_HTML_
#define _FUNCTIONS_HTML_

#include "LinkedList/linkedlist.h"

LinkedList closeTags ;

void beginBoldHtml();
void beginItalicHtml();
void beginUnderlineHtml();

void beginOrderListHtml();
void beginUnorderListHtml();
void beginDictionaryHtml();
void beginItemHtml();
void beginDictionaryTitleHtml();
void beginDictionaryItemHtml();

void beginTitleHtml(int level);

void endTagHtml();
void endItemHtml();

/*void endBoldHtml();
void endItalicHtml();
void endUnderlineHtml();*/

#endif