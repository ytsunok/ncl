#include <stdio.h>
#include <math.h>
#include "wrapper.h"

extern void NGCALLF(ddrveof,DDRVEOF)(double *,int *,int *,int *,int *,
                                     double *,int *,double *, double *,
                                     float*,double *,int *,int *,double*,
                                     long *, double *,int *,double *,int *,
                                     int *,int *,int *,int *);

extern void NGCALLF(dncldrv,DNCLDRV)(double *,double *,int *,int *,int *,
                                     int *,double *,int *,double *,double *,
                                     float *,double *,int *,int *,double *,
                                     double *,double *,long *,double *, 
                                     int *,double *,int *,int *,int *,int *,
                                     int*);

extern void NGCALLF(deofts7,DEOFTS7)(double *,int *,int *,int *,int *,
                                     double *,int *, double *,int *, int *,
                                     double *,double *,double *,double *,
                                     int *);

extern void NGCALLF(deoftsca,DEOFTSCA)(double *,int *,int *,int *,int *,
                                       double *,int *,double *,int *, int*,
                                       double *,double *,int *,double *,
                                       double *);

extern void NGCALLF(deof2data,DEOF2DATA)(int *,int *,int *,double *,
                                         double *, double *, double *);

NhlErrorTypes eofcov_W( void )
{
/*
 * Input array variables
 */
  void *x;
  double *dx;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  NclScalar missing_x, missing_rx, missing_dx;
  NclBasicDataTypes type_x;
  int nrow, ncol, nobs, msta, total_size_x;
  int *neval, iopt = 0, jopt = 0, i, ier = 0;
/*
 * Work array variables.
 */
  double *cssm, *work, *weval;
  int   *iwork, *ifail;
  int lwork, liwork, lifail;
  long lcssm;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
  int *eof_function;
  double *trace, *eval;
  float *pcvar;
  float *rtrace, *reval;
/*
 * Output array variables
 */
  double *evec;
  float *revec;
  int total_size_evec, dsizes_evec[NCL_MAX_DIMENSIONS];
/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           2,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
/*
 * Get number of eigenvalues and eigen vectors to be computed.
 */
  neval = (int *)NclGetArgValue(
            1,
            2, 
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            2);
/*
 * The grid coming in must be at least 2-dimensional.
 */
  if( ndims_x < 2 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: The input array must be at least 2-dimensional");
    return(NhlFATAL);
  }
/*
 * Check dimension sizes.
 */
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) msta *= dsizes_x[i];
  ncol = msta;
  nobs = nrow = dsizes_x[ndims_x-1];

  total_size_x = ncol * nrow;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
/*
 * Coerce x to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  if( dx == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: Unable to allocate memory for coercing x array to double precision");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec[0] = *neval;
  for( i = 0; i <= ndims_x-2; i++ ) dsizes_evec[i+1] = dsizes_x[i];

  total_size_evec = *neval * ncol;

  evec = (double *)calloc(total_size_evec,sizeof(double));
  if( evec == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Allocate memory for attributes.
 */
  trace = (double *)calloc(1,sizeof(double));
  eval =  (double *)calloc(*neval,sizeof(double));
  pcvar = (float *)calloc(*neval,sizeof(float));
  if( trace == NULL || pcvar == NULL || eval == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: Unable to allocate memory for attribute arrays");
    return(NhlFATAL);
  }
/*
 * Create a few more work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lcssm  = (long)msta*((long)msta+1)/2;
  lwork  = 8*msta;
  liwork = 5*msta;
  lifail = msta;
  cssm   = (double *)calloc(lcssm,sizeof(double));
  work   = (double *)calloc(lwork,sizeof(double));
  weval  = (double *)calloc(lifail,sizeof(double));
  iwork  =   (int *)calloc(liwork,sizeof(int));
  ifail  =   (int *)calloc(lifail,sizeof(int));
  if( cssm == NULL || work == NULL || weval == NULL || iwork == NULL || 
      ifail == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(ddrveof,DDRVEOF)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                           neval,eval,evec,pcvar,trace,&iopt,&jopt,
                           cssm,&lcssm,work,&lwork,weval,iwork,&liwork,
                           ifail,&lifail,&ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx != x) NclFree(dx);
  NclFree(work);
  NclFree(cssm);
  NclFree(weval);
  NclFree(iwork);
  NclFree(ifail);
/*
 * Return values. 
 */
  if(type_x != NCL_double) {
/*
 * Copy double values to float values.
 */
    revec = (float*)calloc(total_size_evec,sizeof(float));
    if( revec == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < total_size_evec; i++ ) revec[i] = (float)evec[i];

/*
 * Free up double precision array.
 */
    NclFree(evec);
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec,
                              &missing_rx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);
/*
 * Coerce eval to float.
 */
    reval = (float *)calloc(*neval,sizeof(float));
    for( i = 0; i < *neval; i++ ) reval[i] = (float)eval[i];
/*
 * Free double precision eval.
 */
    NclFree(eval);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)reval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );

/*
 * pcvar is returned as float no matter what. 
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

/*
 * Coerce trace to float.
 */
    rtrace = (float *)calloc(1,sizeof(float));
    *rtrace = (float)(*trace);
    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rtrace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                                                   );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
  else {
/*
 *  Return doubles.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec,
                              &missing_dx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );

    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)eval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );
/*
 * pcvar is returned as float no matter what.
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)trace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }

/*
 * eof_function is returned to indicate which function was used.
 */
  eof_function = (int *)calloc(1,sizeof(int));
  *eof_function = 0;
  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         (void*)eof_function,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)nclTypeintClass
                         );
  _NclAddAtt(
             att_id,
             "eof_function",
             att_md,
             NULL
             );


  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcor_W( void )
{
/*
 * Input array variables
 */
  void *x;
  double *dx;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  NclScalar missing_x, missing_rx, missing_dx;
  NclBasicDataTypes type_x;
  int nrow, ncol, nobs, msta, total_size_x;
  int *neval, iopt = 0, jopt = 1, i, ier = 0;
/*
 * Work array variables.
 */
  double *cssm, *work, *weval;
  int   *iwork, *ifail;
  int lwork, liwork, lifail;
  long lcssm;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
  int *eof_function;
  double *trace, *eval;
  float *pcvar;
  float *rtrace, *reval;
/*
 * Output array variables
 */
  double *evec;
  float *revec;
  int total_size_evec, dsizes_evec[NCL_MAX_DIMENSIONS];
/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           2,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
/*
 * Get number of eigenvalues and eigen vectors to be computed.
 */
  neval = (int *)NclGetArgValue(
            1,
            2, 
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            2);
/*
 * The grid coming in must be at least 2-dimensional.
 */
  if( ndims_x < 2 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: The input array must be at least 2-dimensional");
    return(NhlFATAL);
  }
/*
 * Check dimension sizes.
 */
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) msta *= dsizes_x[i];
  ncol = msta;
  nobs = nrow = dsizes_x[ndims_x-1];

  total_size_x = ncol * nrow;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
/*
 * Coerce x to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  if( dx == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: Unable to allocate memory for coercing x array to double precision");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec[0] = *neval;
  for( i = 0; i <= ndims_x-2; i++ ) dsizes_evec[i+1] = dsizes_x[i];

  total_size_evec = *neval * ncol;

  evec = (double *)calloc(total_size_evec,sizeof(double));
  if( evec == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Allocate memory for attributes.
 */
  trace = (double *)calloc(1,sizeof(double));
  eval =  (double *)calloc(*neval,sizeof(double));
  pcvar = (float *)calloc(*neval,sizeof(float));
  if( trace == NULL || pcvar == NULL || eval == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: Unable to allocate memory for attribute arrays");
    return(NhlFATAL);
  }
/*
 * Create a few more work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lcssm  = (long)msta*((long)msta+1)/2;
  lwork  = 8*msta;
  liwork = 5*msta;
  lifail = msta;
  cssm   = (double *)calloc(lcssm,sizeof(double));
  work   = (double *)calloc(lwork,sizeof(double));
  weval  = (double *)calloc(lifail,sizeof(double));
  iwork  =   (int *)calloc(liwork,sizeof(int));
  ifail  =   (int *)calloc(lifail,sizeof(int));
  if( cssm == NULL || work == NULL || weval == NULL || iwork == NULL || 
      ifail == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(ddrveof,DDRVEOF)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                           neval,eval,evec,pcvar,trace,&iopt,&jopt,
                           cssm,&lcssm,work,&lwork,weval,iwork,&liwork,
                           ifail,&lifail,&ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx != x) NclFree(dx);
  NclFree(work);
  NclFree(cssm);
  NclFree(weval);
  NclFree(iwork);
  NclFree(ifail);
/*
 * Return values. 
 */
  if(type_x != NCL_double) {
/*
 * Copy double values to float values.
 */
    revec = (float*)calloc(total_size_evec,sizeof(float));
    if( revec == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < total_size_evec; i++ ) revec[i] = (float)evec[i];

/*
 * Free up double precision array.
 */
    NclFree(evec);
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec,
                              &missing_rx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);
/*
 * Coerce eval to float.
 */
    reval = (float *)calloc(*neval,sizeof(float));
    for( i = 0; i < *neval; i++ ) reval[i] = (float)eval[i];
/*
 * Free double precision eval.
 */
    NclFree(eval);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)reval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );

/*
 * pcvar is returned as float no matter what. 
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

/*
 * Coerce trace to float.
 */
    rtrace = (float *)calloc(1,sizeof(float));
    *rtrace = (float)(*trace);
    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rtrace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                                                   );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
  else {
/*
 *  Return doubles.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec,
                              &missing_dx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );

    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)eval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );
/*
 * pcvar is returned as float no matter what.
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)trace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
/*
 * eof_function is returned to indicate which function was used.
 */
  eof_function = (int *)calloc(1,sizeof(int));
  *eof_function = 1;
  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         (void*)eof_function,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)nclTypeintClass
                         );
  _NclAddAtt(
             att_id,
             "eof_function",
             att_md,
             NULL
             );


  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcov_pcmsg_W( void )
{
/*
 * Input array variables
 */
  void *x, *pcmsg;
  double *dx, *dpcmsg;
  float *rpcmsg;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  NclScalar missing_x, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_pcmsg;
  int nrow, ncol, nobs, msta, total_size_x;
  int *neval, iopt = 0, jopt = 0, i, ier = 0;
/*
 * Work array variables.
 */
  double *tmp_x, *cssm, *work, *weval, *evecx;
  int   *iwork, *ifail;
  int lwork, liwork, lifail;
  long lcssm, total_mem;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
  int *eof_function;
  double *trace, *eval;
  float *pcvar;
  float *rtrace, *reval;
/*
 * Output array variables
 */
  double *evec;
  float *revec;
  int total_size_evec, dsizes_evec[NCL_MAX_DIMENSIONS];
/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
/*
 * Get number of eigenvalues and eigen vectors to be computed.
 */
  neval = (int *)NclGetArgValue(
            1,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            2);

  pcmsg = (void *)NclGetArgValue(
            2,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            &type_pcmsg,
            2);
/*
 * The grid coming in must be at least 2-dimensional.
 */
  if( ndims_x < 2 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: The input array must be at least 2-dimensional");
    return(NhlFATAL);
  }
/*
 * Check dimension sizes.
 */
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) msta *= dsizes_x[i];
  ncol = msta;
  nobs = nrow = dsizes_x[ndims_x-1];

  total_size_x = ncol * nrow;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
/*
 * Coerce x to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  if(dx == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: Unable to allocate memory for coercing input to double precision");
    return(NhlFATAL);
  }
/*  
 * Go ahead and make a separate copy of pcmsg, even if it is already 
 * double, because we'll need to return that double later. We
 * don't want to return it as a pointer to the original double
 * value.
 */
  if(type_pcmsg != NCL_double) {
    dpcmsg = coerce_input_double(pcmsg,type_pcmsg,1,0,NULL,NULL);
  }
  else {
    dpcmsg  = (double*)calloc(1,sizeof(double));
    *dpcmsg = ((double*)pcmsg)[0];
  }
/*
 * Check dpcmsg
 */
  if(*dpcmsg < 0. || *dpcmsg > 100.) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: pcmsg must be between 0 and 100 inclusive");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec[0] = *neval;
  for( i = 0; i <= ndims_x-2; i++ ) dsizes_evec[i+1] = dsizes_x[i];

  total_size_evec = *neval * ncol;

  evec  = (double *)calloc(total_size_evec,sizeof(double));
  if( evec == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Allocate memory for attributes.
 */
  trace = (double *)calloc(1,sizeof(double));
  eval  =  (double *)calloc(*neval,sizeof(double));
  pcvar = (float *)calloc(*neval,sizeof(float));
  if( trace == NULL || pcvar == NULL || eval == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: Unable to allocate memory for attribute arrays");
    return(NhlFATAL);
  }
/*
 * Create a few more work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lcssm  = (long)msta*((long)msta+1)/2;
  lwork  = 8*msta;
  liwork = 5*msta;
  lifail = msta;
  cssm   = (double *)calloc(lcssm,sizeof(double));
  work   = (double *)calloc(lwork,sizeof(double));
  weval  = (double *)calloc(lifail,sizeof(double));
  iwork  =    (int *)calloc(liwork,sizeof(int));
  ifail  =    (int *)calloc(lifail,sizeof(int));
  tmp_x  = (double *)calloc(total_size_x,sizeof(double));
  evecx  =  (double *)calloc(total_size_evec,sizeof(double));
  total_mem = 8*(lcssm+(long)lwork+(long)lifail+(long)total_size_x+(long)total_size_evec)+4*((long)liwork+(long)lifail);
  if(  cssm == NULL ||  work == NULL || weval == NULL || iwork == NULL || 
      ifail == NULL || tmp_x == NULL || evecx == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: Unable to allocate memory for work arrays. A total of %d bytes need to be allocated",total_mem);
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(dncldrv,DNCLDRV)(dx,tmp_x,&nrow,&ncol,&nobs,&msta,
                           &missing_dx.doubleval,neval,eval,evec,pcvar,
                           trace,&iopt,&jopt,dpcmsg,evecx,cssm,&lcssm,
                           work,&lwork,weval,iwork,&liwork,ifail,&lifail,&ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_pcmsg: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_pcmsg: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_pcmsg: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_pcmsg: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx     != x)     NclFree(dx);
  NclFree(work);
  NclFree(cssm);
  NclFree(weval);
  NclFree(iwork);
  NclFree(ifail);
  NclFree(tmp_x);
  NclFree(evecx);
/*
 * Return values. 
 */
  if(type_x != NCL_double) {
/*
 * Copy double values to float values.
 */
    revec = (float*)calloc(total_size_evec,sizeof(float));
    if( revec == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_pcmsg: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < total_size_evec; i++ ) revec[i] = (float)evec[i];

/*
 * Free up double precision array.
 */
    NclFree(evec);
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec,
                              &missing_rx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);
/*
 * Coerce eval to float.
 */
    reval = (float *)calloc(*neval,sizeof(float));
    for( i = 0; i < *neval; i++ ) reval[i] = (float)eval[i];
/*
 * Free double precision eval.
 */
    NclFree(eval);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)reval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );

/*
 * pcvar is returned as float no matter what. 
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

/*
 * Coerce trace to float.
 */
    rtrace = (float *)calloc(1,sizeof(float));
    *rtrace = (float)(*trace);
    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rtrace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                                                   );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
  else {
/*
 *  Return doubles.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec,
                              &missing_dx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );

    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)eval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );
/*
 * pcvar is returned as float no matter what.
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)trace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }

/*
 * Return pcmsg as an attribute "pcrit" of type float or double.
 */
  dsizes[0] = 1;
  if(type_pcmsg != NCL_double) {
    NclFree(dpcmsg);
    if(type_pcmsg != NCL_float) {
      rpcmsg = coerce_input_float(pcmsg,type_pcmsg,1,0,NULL,NULL);
    }
    else {
      rpcmsg  = (float*)calloc(1,sizeof(float));
      *rpcmsg = ((float*)pcmsg)[0];
    }
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rpcmsg,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
  }
  else {
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)dpcmsg,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
  }
  _NclAddAtt(
             att_id,
             "pcrit",
             att_md,
             NULL
             );
/*
 * eof_function is returned to indicate which function was used.
 */
  eof_function = (int *)calloc(1,sizeof(int));
  *eof_function = 2;
  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         (void*)eof_function,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)nclTypeintClass
                         );
  _NclAddAtt(
             att_id,
             "eof_function",
             att_md,
             NULL
             );


  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcor_pcmsg_W( void )
{
/*
 * Input array variables
 */
  void *x, *pcmsg;
  double *dx, *dpcmsg;
  float *rpcmsg;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  NclScalar missing_x, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_pcmsg;
  int nrow, ncol, nobs, msta, total_size_x;
  int *neval, iopt = 0, jopt = 1, i, ier = 0;
/*
 * Work array variables.
 */
  double *tmp_x, *cssm, *work, *weval, *evecx;
  int    *iwork, *ifail;
  int lwork, liwork, lifail;
  long lcssm, total_mem;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
  int *eof_function;
  double *trace, *eval;
  float *pcvar;
  float *rtrace, *reval;
/*
 * Output array variables
 */
  double *evec;
  float *revec;
  int total_size_evec, dsizes_evec[NCL_MAX_DIMENSIONS];
/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
/*
 * Get number of eigenvalues and eigen vectors to be computed.
 */
  neval = (int *)NclGetArgValue(
            1,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            2);

  pcmsg = (void *)NclGetArgValue(
            2,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            &type_pcmsg,
            2);
/*
 * The grid coming in must be at least 2-dimensional.
 */
  if( ndims_x < 2 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: The input array must be at least 2-dimensional");
    return(NhlFATAL);
  }
/*
 * Check dimension sizes.
 */
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) msta *= dsizes_x[i];
  ncol = msta;
  nobs = nrow = dsizes_x[ndims_x-1];

  total_size_x = ncol * nrow;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
/*
 * Coerce x to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  if(dx == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: Unable to allocate memory for coercing input to double precision");
    return(NhlFATAL);
  }
/*  
 * Go ahead and make a separate copy of pcmsg, even if it is already 
 * double, because we'll need to return that double later. We
 * don't want to return it as a pointer to the original double
 * value.
 */
  if(type_pcmsg != NCL_double) {
    dpcmsg = coerce_input_double(pcmsg,type_pcmsg,1,0,NULL,NULL);
  }
  else {
    dpcmsg  = (double*)calloc(1,sizeof(double));
    *dpcmsg = ((double*)pcmsg)[0];
  }
/*
 * Check dpcmsg
 */
  if(*dpcmsg < 0. || *dpcmsg > 100.) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: pcmsg must be between 0 and 100 inclusive");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec[0] = *neval;
  for( i = 0; i <= ndims_x-2; i++ ) dsizes_evec[i+1] = dsizes_x[i];

  total_size_evec = *neval * ncol;

  evec = (double *)calloc(total_size_evec,sizeof(double));
  if( evec == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Allocate memory for attributes.
 */
  trace = (double *)calloc(1,sizeof(double));
  eval  =  (double *)calloc(*neval,sizeof(double));
  pcvar = (float *)calloc(*neval,sizeof(float));
  if( trace == NULL || pcvar == NULL || eval == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: Unable to allocate memory for attribute arrays");
    return(NhlFATAL);
  }
/*
 * Create a few more work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lcssm  = (long)msta*((long)msta+1)/2;
  lwork  = 8*msta;
  liwork = 5*msta;
  lifail = msta;
  cssm   = (double *)calloc(lcssm,sizeof(double));
  work   = (double *)calloc(lwork,sizeof(double));
  weval  = (double *)calloc(lifail,sizeof(double));
  iwork  =    (int *)calloc(liwork,sizeof(int));
  ifail  =    (int *)calloc(lifail,sizeof(int));
  tmp_x  = (double *)calloc(total_size_x,sizeof(double));
  evecx  =  (double *)calloc(total_size_evec,sizeof(double));
  total_mem = 8*(lcssm+lwork+lifail+total_size_x+total_size_evec)+4*(liwork+lifail);
  if(  cssm == NULL ||  work == NULL || weval == NULL || iwork == NULL || 
      ifail == NULL || tmp_x == NULL || evecx == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: Unable to allocate memory for work arrays. A total of %d bytes need to be allocated",total_mem);
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(dncldrv,DNCLDRV)(dx,tmp_x,&nrow,&ncol,&nobs,&msta,
                           &missing_dx.doubleval,neval,eval,evec,pcvar,
                           trace,&iopt,&jopt,dpcmsg,evecx,cssm,&lcssm,
                           work,&lwork,weval,iwork,&liwork,ifail,&lifail,&ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_pcmsg: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_pcmsg: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_pcmsg: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_pcmsg: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx != x) NclFree(dx);
  NclFree(work);
  NclFree(cssm);
  NclFree(weval);
  NclFree(iwork);
  NclFree(ifail);
  NclFree(tmp_x);
  NclFree(evecx);
/*
 * Return values. 
 */
  if(type_x != NCL_double) {
/*
 * Copy double values to float values.
 */
    revec = (float*)calloc(total_size_evec,sizeof(float));
    if( revec == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_pcmsg: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < total_size_evec; i++ ) revec[i] = (float)evec[i];

/*
 * Free up double precision array.
 */
    NclFree(evec);
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec,
                              &missing_rx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);
/*
 * Coerce eval to float.
 */
    reval = (float *)calloc(*neval,sizeof(float));
    for( i = 0; i < *neval; i++ ) reval[i] = (float)eval[i];
/*
 * Free double precision eval.
 */
    NclFree(eval);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)reval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );

/*
 * pcvar is returned as float no matter what. 
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

/*
 * Coerce trace to float.
 */
    rtrace = (float *)calloc(1,sizeof(float));
    *rtrace = (float)(*trace);
    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rtrace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                                                   );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
  else {
/*
 *  Return doubles.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec,
                              &missing_dx,
                              ndims_x,
                              dsizes_evec,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );

    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

    dsizes[0] = *neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)eval,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "eval",
               att_md,
               NULL
               );
/*
 * pcvar is returned as float no matter what.
 */
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)pcvar,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "pcvar",
               att_md,
               NULL
               );

    dsizes[0] = 1;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)trace,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "trace",
               att_md,
               NULL
               );
  }
/*
 * Return pcmsg as an attribute "pcrit" of type float or double.
 */
  dsizes[0] = 1;
  if(type_pcmsg != NCL_double) {
    NclFree(dpcmsg);
    if(type_pcmsg != NCL_float) {
      rpcmsg = coerce_input_float(pcmsg,type_pcmsg,1,0,NULL,NULL);
    }
    else {
      rpcmsg  = (float*)calloc(1,sizeof(float));
      *rpcmsg = ((float*)pcmsg)[0];
    }
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)rpcmsg,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
  }
  else {
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)dpcmsg,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
  }
  _NclAddAtt(
             att_id,
             "pcrit",
             att_md,
             NULL
             );
/*
 * eof_function is returned to indicate which function was used.
 */
  eof_function = (int *)calloc(1,sizeof(int));
  *eof_function = 3;
  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         (void*)eof_function,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)nclTypeintClass
                         );
  _NclAddAtt(
             att_id,
             "eof_function",
             att_md,
             NULL
             );


  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcov_ts_W( void )
{
/*
 * Input array variables
 */
  void *x, *evec;
  double *dx, *devec;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  int ndims_evec, dsizes_evec[NCL_MAX_DIMENSIONS], has_missing_evec;
  NclScalar missing_x, missing_evec, missing_devec, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_evec;
  int nrow, ncol, nobs, msta, total_size_x, total_size_evec;
  int neval, ntime, iflag = 0, jopt = 0, i, ier = 0;
/*
 * Work array variables.
 */
  double *wrk, *wx;
  int lwrk, lwx;
/*
 * Output array variables
 */
  double *evec_ts, *evtsav;
  float *revec_ts, *revtsav;      
  int dsizes_evec_ts[2];
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;


/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           2,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
  evec = (void*)NclGetArgValue(
           1,
           2,
           &ndims_evec, 
           dsizes_evec,
           &missing_evec,
           &has_missing_evec,
           &type_evec,
           2);
/*
 * Check the input grids.  They both must be at least two dimensional and
 * have the same number of dimensions.  All but the last dimension of the
 * first input array must be the same as all the but first dimension of
 * the second input array.
 */
  if( ndims_x < 2 || ndims_x != ndims_evec ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: The input arrays must be at least 2-dimensional and have the same number of dimensions");
    return(NhlFATAL);
  }
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) {
    if( dsizes_x[i] != dsizes_evec[i+1] ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: All but the last dimension of the first input array must be the same as all but the first dimension of the second input array");
      return(NhlFATAL);
    }
    msta *= dsizes_x[i];
  }
  ncol = msta;
  nobs = nrow = ntime = dsizes_x[ndims_x-1];
  neval = dsizes_evec[0];

  total_size_x    = ncol * nrow;
  total_size_evec = msta * neval;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
  coerce_missing(type_evec,has_missing_evec,&missing_evec,
                 &missing_devec,NULL);
/*
 * Coerce x/evec to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  devec = coerce_input_double(evec,type_evec,total_size_evec,
                              has_missing_evec,&missing_evec,&missing_devec);
  if(dx == NULL || devec == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: Unable to allocate memory for coercing input arrays to double precision");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variables.
 */
  dsizes_evec_ts[0] = neval;
  dsizes_evec_ts[1] = ntime;
  evec_ts = (double *)calloc(ntime*neval,sizeof(double));
  evtsav  = (double *)calloc(neval,sizeof(double));
  if( evec_ts == NULL || evtsav == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: Unable to allocate memory for output arrays");
    return(NhlFATAL);
  }
/*
 * Create a couple of work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lwrk = nobs;
  lwx  = nrow*ncol;
  wrk  = (double *)calloc(lwrk,sizeof(double));
  wx   = (double *)calloc(lwx,sizeof(double));
  if( wrk == NULL || wx == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(deofts7,DEOFTS7)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                           &neval,devec,&jopt,&iflag,wx,wrk,evec_ts,evtsav,
                           &ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) { 
       NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx != x) NclFree(dx);
  if((void*)devec != evec) NclFree(devec);
  NclFree(wx);
  NclFree(wrk);
/*
 * Return values. 
 */
  if(type_x != NCL_double && type_evec != NCL_double) {
/*
 * Neither input array is double, so return float values.
 *
 * First copy double values to float values.
 */
    revec_ts = (float *)calloc(ntime*neval,sizeof(float));
    revtsav  = (float *)calloc(neval,sizeof(float));
    if( revec_ts == NULL || revtsav == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts: Unable to allocate memory for output arrays");
      return(NhlFATAL);
    }
    for( i = 0; i < ntime*neval; i++ ) revec_ts[i] = (float)evec_ts[i];
    for( i = 0; i < neval; i++ )       revtsav[i]  = (float)evtsav[i];
/*
 * Free up double precision arrays.
 */
    NclFree(evec_ts);
    NclFree(evtsav);
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec_ts,
                              &missing_rx,
                              2,
                              dsizes_evec_ts,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

/*
 * Attribute "ts_mean".
 */
    dsizes[0] = neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)revtsav,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "ts_mean",
               att_md,
               NULL
               );

  }
  else {
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec_ts,
                              &missing_dx,
                              2,
                              dsizes_evec_ts,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

/*
 * Attribute "ts_mean".
 */
    dsizes[0] = neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)evtsav,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "ts_mean",
               att_md,
               NULL
               );
  }
  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcor_ts_W( void )
{
/*
 * Input array variables
 */
  void *x, *evec;
  double *dx, *devec;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  int ndims_evec, dsizes_evec[NCL_MAX_DIMENSIONS], has_missing_evec;
  NclScalar missing_x, missing_evec, missing_devec, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_evec;
  int nrow, ncol, nobs, msta, total_size_x, total_size_evec;
  int neval, ntime, iflag = 0, jopt = 1, i, ier = 0;
/*
 * Work array variables.
 */
  double *wrk, *wx;
  int lwrk, lwx;
/*
 * Output array variables
 */
  double *evec_ts, *evtsav;
  float *revec_ts, *revtsav;      
  int dsizes_evec_ts[2];

/*
 * Attribute variables
 */
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;

/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           2,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
  evec = (void*)NclGetArgValue(
           1,
           2,
           &ndims_evec, 
           dsizes_evec,
           &missing_evec,
           &has_missing_evec,
           &type_evec,
           2);
/*
 * Check the input grids.  They both must be at least two dimensional and
 * have the same number of dimensions.  All but the last dimension of the
 * first input array must be the same as all the but first dimension of
 * the second input array.
 */
  if( ndims_x < 2 || ndims_x != ndims_evec ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: The input arrays must be at least 2-dimensional and have the same number of dimensions");
    return(NhlFATAL);
  }
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) {
    if( dsizes_x[i] != dsizes_evec[i+1] ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: All but the last dimension of the first input array must be the same as all but the first dimension of the second input array");
      return(NhlFATAL);
    }
    msta *= dsizes_x[i];
  }
  ncol = msta;
  nobs = nrow = ntime = dsizes_x[ndims_x-1];
  neval = dsizes_evec[0];

  total_size_x    = ncol * nrow;
  total_size_evec = msta * neval;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
  coerce_missing(type_evec,has_missing_evec,&missing_evec,
                 &missing_devec,NULL);
/*
 * Coerce x/evec to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  devec = coerce_input_double(evec,type_evec,total_size_evec,
                              has_missing_evec,&missing_evec,&missing_devec);
  if(dx == NULL || devec == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: Unable to allocate memory for coercing input arrays to double precision");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variables.
 */
  dsizes_evec_ts[0] = neval;
  dsizes_evec_ts[1] = ntime;
  evec_ts = (double *)calloc(ntime*neval,sizeof(double));
  evtsav  = (double *)calloc(neval,sizeof(double));
  if( evec_ts == NULL || evtsav == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: Unable to allocate memory for output arrays");
    return(NhlFATAL);
  }
/*
 * Create a couple of work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lwrk = nobs;
  lwx  = nrow*ncol;
  wrk  = (double *)calloc(lwrk,sizeof(double));
  wx   = (double *)calloc(lwx,sizeof(double));
  if( wrk == NULL || wx == NULL ) {
        NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(deofts7,DEOFTS7)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                           &neval,devec,&jopt,&iflag,wx,wrk,evec_ts,evtsav,
                           &ier);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx != x) NclFree(dx);
  if((void*)devec != evec) NclFree(devec);
  NclFree(wx);
  NclFree(wrk);
/*
 * Return values. 
 */
  if(type_x != NCL_double && type_evec != NCL_double) {
/*
 * Neither input array is double, so return float values.
 *
 * First copy double values to float values.
 */
    revec_ts = (float *)calloc(ntime*neval,sizeof(float));
    revtsav  = (float *)calloc(neval,sizeof(float));
    if( revec_ts == NULL || revtsav == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts: Unable to allocate memory for output arrays");
      return(NhlFATAL);
    }
    for( i = 0; i < ntime*neval; i++ ) revec_ts[i] = (float)evec_ts[i];
    for( i = 0; i < neval; i++ )       revtsav[i]  = (float)evtsav[i];
/*
 * Free up double precision arrays.
 */
    NclFree(evec_ts);
    NclFree(evtsav);

/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)revec_ts,
                              &missing_rx,
                              2,
                              dsizes_evec_ts,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypefloatClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

/*
 * Attribute "ts_mean".
 */
    dsizes[0] = neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)revtsav,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypefloatClass
                           );
    _NclAddAtt(
               att_id,
               "ts_mean",
               att_md,
               NULL
               );

  }
  else {
/*
 * Set up return value.
 */
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              (void*)evec_ts,
                              &missing_dx,
                              2,
                              dsizes_evec_ts,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)nclTypedoubleClass
                              );
/*
 * Set up attributes to return.
 */
    att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

/*
 * Attribute "ts_mean".
 */
    dsizes[0] = neval;
    att_md = _NclCreateVal(
                           NULL,
                           NULL,
                           Ncl_MultiDValData,
                           0,
                           (void*)evtsav,
                           NULL,
                           1,
                           dsizes,
                           TEMPORARY,
                           NULL,
                           (NclObjClass)nclTypedoubleClass
                           );
    _NclAddAtt(
               att_id,
               "ts_mean",
               att_md,
               NULL
               );
  }
  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes eofcov_ts_pcmsg_W( void )
{
/*
 * Input array variables
 */
  void *x, *evec, *pcmsg;
  double *dx, *devec, *dpcmsg;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  int ndims_evec, dsizes_evec[NCL_MAX_DIMENSIONS], has_missing_evec;
  NclScalar missing_x, missing_evec, missing_devec, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_evec, type_pcmsg;
  int nrow, ncol, nobs, msta, total_size_x, total_size_evec;
  int neval, ntime, iflag = 0, jopt = 0, i, ier = 0;
/*
 * Work array variables.
 */
  double *wrk, *wx;
  int lwrk, lwx;
/*
 * Output array variables
 */
  double *evec_ts;
  float *revec_ts;      
  int dsizes_evec_ts[2];

/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
  evec = (void*)NclGetArgValue(
           1,
           3,
           &ndims_evec, 
           dsizes_evec,
           &missing_evec,
           &has_missing_evec,
           &type_evec,
           2);
  pcmsg = (void *)NclGetArgValue(
            2,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            &type_pcmsg,
            2);
/*
 * Check the input grids.  They both must be at least two dimensional and
 * have the same number of dimensions.  All but the last dimension of the
 * first input array must be the same as all the but first dimension of
 * the second input array.
 */
  if( ndims_x < 2 || ndims_x != ndims_evec ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: The input arrays must be at least 2-dimensional and have the same number of dimensions");
    return(NhlFATAL);
  }
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) {
    if( dsizes_x[i] != dsizes_evec[i+1] ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: All but the last dimension of the first input array must be the same as all but the first dimension of the second input array");
      return(NhlFATAL);
    }
    msta *= dsizes_x[i];
  }
  ncol = msta;
  nobs = nrow = ntime = dsizes_x[ndims_x-1];
  neval = dsizes_evec[0];

  total_size_x    = ncol * nrow;
  total_size_evec = msta * neval;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
  coerce_missing(type_evec,has_missing_evec,&missing_evec,
                 &missing_devec,NULL);
/*
 * Coerce x, evec, pcmsg to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  devec = coerce_input_double(evec,type_evec,total_size_evec,
                              has_missing_evec,&missing_evec,&missing_devec);
  dpcmsg = coerce_input_double(pcmsg,type_pcmsg,1,0,NULL,NULL);

  if(dx == NULL || devec == NULL || dpcmsg == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: Unable to allocate memory for coercing input to double precision");
    return(NhlFATAL);
  }
/*
 * Check dpcmsg
 */
  if(*dpcmsg < 0. || *dpcmsg > 100.) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: pcmsg must be between 0 and 100 inclusive");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec_ts[0] = neval;
  dsizes_evec_ts[1] = ntime;
  evec_ts = (double *)calloc(ntime*neval,sizeof(double));
  if( evec_ts == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Create a couple of work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lwrk = nobs;
  lwx  = nrow*ncol;
  wrk  = (double *)calloc(lwrk,sizeof(double));
  wx   = (double *)calloc(lwx,sizeof(double));
  if( wrk == NULL || wx == NULL ) {
        NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(deoftsca,DEOFTSCA)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                             &neval,devec,&jopt,&iflag,evec_ts,dpcmsg,&ier,wx,wrk);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts_pcmsg: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts_pcmsg: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts_pcmsg: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcov_ts_pcmsg: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx     != x)     NclFree(dx);
  if((void*)dpcmsg != pcmsg) NclFree(dpcmsg);
  if((void*)devec  != evec)  NclFree(devec);
  NclFree(wx);
  NclFree(wrk);
/*
 * Return values. 
 */
  if(type_x != NCL_double && type_evec != NCL_double) {
/*
 * Neither input array is double, so return float values.
 *
 * First copy double values to float values.
 */
    revec_ts = (float *)calloc(ntime*neval,sizeof(float));
    if( revec_ts == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcov_ts_pcmsg: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < ntime*neval; i++ ) revec_ts[i] = (float)evec_ts[i];
/*
 * Free up double precision array.
 */
    NclFree(evec_ts);

/*
 * Return float values. 
 */
    return(NclReturnValue((void*)revec_ts,2,dsizes_evec_ts,&missing_rx,
                          NCL_float,0));
  }
  else {
/*
 * Return double values. 
 */
    return(NclReturnValue((void*)evec_ts,2,dsizes_evec_ts,&missing_dx,
                          NCL_double,0));
  }
}


NhlErrorTypes eofcor_ts_pcmsg_W( void )
{
/*
 * Input array variables
 */
  void *x, *evec, *pcmsg;
  double *dx, *devec, *dpcmsg;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS], has_missing_x;
  int ndims_evec, dsizes_evec[NCL_MAX_DIMENSIONS], has_missing_evec;
  NclScalar missing_x, missing_evec, missing_devec, missing_rx, missing_dx;
  NclBasicDataTypes type_x, type_evec, type_pcmsg;
  int nrow, ncol, nobs, msta, total_size_x, total_size_evec;
  int neval, ntime, iflag = 0, jopt = 1, i, ier = 0;
/*
 * Work array variables.
 */
  double *wrk, *wx;
  int lwrk, lwx;
/*
 * Output array variables
 */
  double *evec_ts;
  float *revec_ts;      
  int dsizes_evec_ts[2];

/*
 * Retrieve parameters
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);
  evec = (void*)NclGetArgValue(
           1,
           3,
           &ndims_evec, 
           dsizes_evec,
           &missing_evec,
           &has_missing_evec,
           &type_evec,
           2);
  pcmsg = (void *)NclGetArgValue(
            2,
            3, 
            NULL,
            NULL,
            NULL,
            NULL,
            &type_pcmsg,
            2);
/*
 * Check the input grids.  They both must be at least two dimensional and
 * have the same number of dimensions.  All but the last dimension of the
 * first input array must be the same as all the but first dimension of
 * the second input array.
 */
  if( ndims_x < 2 || ndims_x != ndims_evec ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: The input arrays must be at least 2-dimensional and have the same number of dimensions");
    return(NhlFATAL);
  }
  msta = 1;
  for( i = 0; i <= ndims_x-2; i++ ) {
    if( dsizes_x[i] != dsizes_evec[i+1] ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: All but the last dimension of the first input array must be the same as all but the first dimension of the second input array");
      return(NhlFATAL);
    }
    msta *= dsizes_x[i];
  }
  ncol = msta;
  nobs = nrow = ntime = dsizes_x[ndims_x-1];
  neval = dsizes_evec[0];

  total_size_x    = ncol * nrow;
  total_size_evec = msta * neval;

  if( msta < 1 || nobs < 1 ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: The dimensions of the input array must both be at least 1");
    return(NhlFATAL);
  }
/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
  coerce_missing(type_evec,has_missing_evec,&missing_evec,
                 &missing_devec,NULL);
/*
 * Coerce x, evec, pcmsg to double if necessary.
 */
  dx = coerce_input_double(x,type_x,total_size_x,has_missing_x,&missing_x,
                           &missing_dx);
  devec = coerce_input_double(evec,type_evec,total_size_evec,
                              has_missing_evec,&missing_evec,&missing_devec);
  dpcmsg = coerce_input_double(pcmsg,type_pcmsg,1,0,NULL,NULL);

  if(dx == NULL || devec == NULL || dpcmsg == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: Unable to allocate memory for coercing input to double precision");
    return(NhlFATAL);
  }
/*
 * Check dpcmsg
 */
  if(*dpcmsg < 0. || *dpcmsg > 100.) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: pcmsg must be between 0 and 100 inclusive");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_evec_ts[0] = neval;
  dsizes_evec_ts[1] = ntime;
  evec_ts = (double *)calloc(ntime*neval,sizeof(double));
  if( evec_ts == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: Unable to allocate memory for output array");
    return(NhlFATAL);
  }
/*
 * Create a couple of work arrays.  This is necessary to avoid having
 * these arrays created dynamically in the Fortran file (which makes
 * it Fortran 90, and unportable to some systems. 
 */
  lwrk = nobs;
  lwx  = nrow*ncol;
  wrk  = (double *)calloc(lwrk,sizeof(double));
  wx   = (double *)calloc(lwx,sizeof(double));
  if( wrk == NULL || wx == NULL ) {
        NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: Unable to allocate memory for work arrays");
    return(NhlFATAL);
  }
/*
 * Call the Fortran 77 version of 'drveof' with the full argument list.
 */
  NGCALLF(deoftsca,DEOFTSCA)(dx,&nrow,&ncol,&nobs,&msta,&missing_dx.doubleval,
                             &neval,devec,&jopt,&iflag,evec_ts,dpcmsg,&ier,wx,wrk);
/*
 * Check various possible error messages.
 */
  if (ier != 0) {
    if (ier == -1) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts_pcmsg: cssm contains one or more missing values\n" );
    }
    else if (ier == -88) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts_pcmsg: trace is equal to zero\n" );
    }
    else if (ier < 0) {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts_pcmsg: The %d-th argument had an illegal value\n", abs(ier) );
    }
    else {
      NhlPError(NhlWARNING,NhlEUNKNOWN,"eofcor_ts_pcmsg: %d eigenvectors failed to converge\n",ier);
    }
  }
/*
 * Free unneeded memory.
 */
  if((void*)dx     != x)     NclFree(dx);
  if((void*)dpcmsg != pcmsg) NclFree(dpcmsg);
  if((void*)devec  != evec)  NclFree(devec);
  NclFree(wx);
  NclFree(wrk);
/*
 * Return values. 
 */
  if(type_x != NCL_double && type_evec != NCL_double) {
/*
 * Neither input array is double, so return float values.
 *
 * First copy double values to float values.
 */
    revec_ts = (float *)calloc(ntime*neval,sizeof(float));
    if( revec_ts == NULL ) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"eofcor_ts_pcmsg: Unable to allocate memory for output array");
      return(NhlFATAL);
    }
    for( i = 0; i < ntime*neval; i++ ) revec_ts[i] = (float)evec_ts[i];
/*
 * Free up double precision array.
 */
    NclFree(evec_ts);

/*
 * Return float values. 
 */
    return(NclReturnValue((void*)revec_ts,2,dsizes_evec_ts,&missing_rx,
                          NCL_float,0));
  }
  else {
/*
 * Return double values. 
 */
    return(NclReturnValue((void*)evec_ts,2,dsizes_evec_ts,&missing_dx,
                          NCL_double,0));
  }
}


NhlErrorTypes eof2data_W( void )
{
/*
 * Input array variables
 */
  void *evec, *evects;
  double *devec, *devects;
  int ndims_evec, dsizes_evec[NCL_MAX_DIMENSIONS], has_missing_evec;
  int dsizes_evects[2], has_missing_evects;
  NclScalar missing_evec, missing_devec, missing_revec;
  NclBasicDataTypes type_evec, type_evects;
  int nrow, ncol, nobs, msta, total_size_evec, total_size_evects;
  int neval, npts, ntim, i;
/*
 * Output array variables
 */
  void *x;
  double *dx;
  float *rx;      
  int *dsizes_x, total_size_x;
  NclBasicDataTypes type_x;

/*
 * Retrieve parameters
 */
  evec = (void*)NclGetArgValue(
           0,
           2,
           &ndims_evec, 
           dsizes_evec,
           &missing_evec,
           &has_missing_evec,
           &type_evec,
           2);
  evects = (void*)NclGetArgValue(
           1,
           2,
           NULL,
           dsizes_evects,
           NULL,
           NULL,
           &type_evects,
           2);
/*
 * Check the input grids. The first one can be any dimension, but it must
 * be at least 2 dimensions.  The first dimension of both input arrays
 * must be the same (neval).
 */
  if(ndims_evec < 2) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eof2data: The first input array must be at least 2-dimensional");
    return(NhlFATAL);
  }

  if( dsizes_evec[0] != dsizes_evects[0] ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eof2data: The leftmost dimension of both input arrays must be the same");
    return(NhlFATAL);
  }

  neval = dsizes_evec[0];
  ntim  = dsizes_evects[1];

  npts  = 1;
  for( i = 1; i < ndims_evec; i++ ) npts *= dsizes_evec[i];

  total_size_evec   = neval * npts;
  total_size_evects = neval * ntim;
  total_size_x      = npts  * ntim;

/*
 * Coerce missing values, if any.
 */
  coerce_missing(type_evec,has_missing_evec,&missing_evec,&missing_devec,
                 &missing_revec);
/*
 * Coerce evec/evects to double if necessary.
 */
  devec = coerce_input_double(evec,type_evec,total_size_evec,
                              has_missing_evec,&missing_evec,
                              &missing_devec);
  devects = coerce_input_double(evects,type_evects,total_size_evects,
                                0,NULL,NULL);
  if(devec == NULL || devects == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eof2data: Unable to allocate memory for coercing input arrays to double precision");
    return(NhlFATAL);
  }
/*
 * Allocate memory for return variable.
 */
  dsizes_x = (int*)calloc(ndims_evec, sizeof(int));
  
  if(type_evec == NCL_double || type_evects == NCL_double) {
    type_x = NCL_double;
    x      = (double *)calloc(total_size_x,sizeof(double));
    dx     = (double*)x;
  }
  else {
    type_x = NCL_float;
    x      = (float *)calloc(total_size_x,sizeof(float));
    dx     = (double *)calloc(total_size_x,sizeof(double));
  }
  if(x == NULL || dx == NULL || dsizes_x == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"eof2data: Unable to allocate memory for output array");
    return(NhlFATAL);
  }

  dsizes_x[ndims_evec-1] = ntim;
  for(i=0; i <= ndims_evec-2; i++) dsizes_x[i] = dsizes_evec[i+1];

/*
 * Call the Fortran 77 version of 'deof2data' with the full argument list.
 */
  NGCALLF(deof2data,DEOF2DATA)(&neval,&npts,&ntim,devec,devects,dx,
                               &missing_devec.doubleval);
/*
 * Free unneeded memory.
 */
  if((void*)devec   != evec)   NclFree(devec);
  if((void*)devects != evects) NclFree(devects);
/*
 * Return values. 
 */
  if(type_x == NCL_float) {
/*
 * Coerce double values to float and free up double precision array.
 */
    coerce_output_float_only(x,dx,total_size_x,0);
    NclFree(dx);

    if(has_missing_evec) {
      return(NclReturnValue(x,ndims_evec,dsizes_x,&missing_revec,type_x,0));
    }
    else {
      return(NclReturnValue(x,ndims_evec,dsizes_x,NULL,type_x,0));
    }
  }
  else {
/*
 * Return double values. 
 */
    if(has_missing_evec) {
      return(NclReturnValue(x,ndims_evec,dsizes_x,&missing_devec,type_x,0));
    }
    else {
      return(NclReturnValue(x,ndims_evec,dsizes_x,NULL,type_x,0));
    }
  }
}
