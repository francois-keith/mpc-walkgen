#ifndef _LSSOL_H
#define _LSSOL_H

////////////////////////////////////////////////////////////////////////////////
///
///\file	lssol.h
///\brief The header for the QP solver LSSOL
///\author	Lafaye Jory
///\version	1.0
///\date	19/08/2011
///
////////////////////////////////////////////////////////////////////////////////

extern "C"
{
int lsoptn_(char *string, short string_len);
	
int lssol_(int *mm, int *n, int *nclin, int *
	lda, int *ldr, double *a, double *bl, double *bu, 
	double *cvec, int *istate, int *kx, double *x, 
	double *r__, double *b, int *inform__, int *iter, 
	double *obj, double *clamda, int *iw, int *leniw, 
	double *w, int *lenw);
}
void sendOption(const std::string & option){
	short len = static_cast<short> (option.length());
	char truc[200];
	option.copy(truc, len);
	lsoptn_(truc , len);	
}


#endif
