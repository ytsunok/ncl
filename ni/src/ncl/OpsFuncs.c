#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <ncarg/hlu/hluP.h>
#include <data_objs/NclMultiDValdoubleData.h>
#include <data_objs/NclMultiDValfloatData.h>
#include <data_objs/NclMultiDVallongData.h>
#include <data_objs/NclMultiDValintData.h>
#include <data_objs/NclMultiDValshortData.h>
#include <data_objs/NclMultiDValstringData.h>
#include <data_objs/NclMultiDValHLUObjData.h>
#include <data_objs/NclMultiDVallogicalData.h>
#include <data_objs/NclHLUObj.h>
#include <defs.h>
#include <Symbol.h>
#include <errno.h>
#include <OpsList.h>
#include <Machine.h>
#include <Execute.h>
#include <OpsFuncs.h>
#include <data_objs/NclVar.h>
#include <data_objs/DataSupport.h>
#include <y.tab.h>

NhlErrorTypes _NclIAny
#if __STDC__
(void)
#else
()
#endif
{
/*
* Guarenteed to be a logical
*/
	NclStackEntry data;	
	NclStackEntry data_out;	
	NclMultiDValData tmp_md = NULL;
	int i,dim_size = 1;
	logical *tmp_val;
	data = _NclGetArg(0,1);
	if(data.kind == NclStk_VAR) {
		if(data.u.data_var != NULL) {	
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
	} else {
		NhlPError(NhlWARNING, NhlEUNKNOWN,"any: incorrect type of object passed to any");
		return(NhlWARNING);
	}
	if(tmp_md == NULL) {
		data_out.kind = NclStk_NOVAL;
		data_out.u.data_obj = NULL;
		_NclPlaceReturn(data_out);
		return(NhlFATAL);
	}

	if(tmp_md->multidval.kind == SCALAR) {
		_NclPlaceReturn(data);
	} else if(!tmp_md->multidval.missing_value.has_missing) {
		tmp_val = (logical*)tmp_md->multidval.val;
		i = 0;
		while(!(*tmp_val)) {
			tmp_val++;
			i++;
			if(i == tmp_md->multidval.totalelements) {
				tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
				*tmp_val = 0;
				_NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
			}
		}
		tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
		*tmp_val = 1;
		data_out.kind = NclStk_VAL;
		data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
		_NclPlaceReturn(data_out);
	} else {
		tmp_val = (logical*)tmp_md->multidval.val;
		i = 0;
		while(i<tmp_md->multidval.totalelements) {
			if((*tmp_val != tmp_md->multidval.missing_value.value.logicalval) &&(*tmp_val) ) {
				break;
			}
			tmp_val++;
			i++;
		}
		if(i >= tmp_md->multidval.totalelements) {
			tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
			*tmp_val = 0;
			data_out.kind = NclStk_VAL;
			data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
			_NclPlaceReturn(data_out);
		} else {
			tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
			*tmp_val = 1;
			data_out.kind = NclStk_VAL;
			data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
			_NclPlaceReturn(data_out);
		}
	}
	return(NhlNOERROR);
}
NhlErrorTypes _NclIAll
#if __STDC__
(void)
#else
()
#endif
{
/*
* Guarenteed to be a logical
*/
	NclStackEntry data;	
	NclStackEntry data_out;	
	NclMultiDValData tmp_md = NULL;
	int i,dim_size = 1;
	logical *tmp_val;
	data = _NclGetArg(0,1);
	if(data.kind == NclStk_VAR) {
		if(data.u.data_var != NULL) {	
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
	} else {
		NhlPError(NhlWARNING, NhlEUNKNOWN,"any: incorrect type of object passed to any");
		return(NhlWARNING);
	}
	if(tmp_md == NULL) {
		data_out.kind = NclStk_NOVAL;
		data_out.u.data_obj = NULL;
		_NclPlaceReturn(data_out);
		return(NhlFATAL);
	}

	if(tmp_md->multidval.kind == SCALAR) {
		_NclPlaceReturn(data);
	} else if(!tmp_md->multidval.missing_value.has_missing) {
		tmp_val = (logical*)tmp_md->multidval.val;
		i = 0;
		while((*tmp_val)) {
			tmp_val++;
			i++;
			if(i >= tmp_md->multidval.totalelements) {
				tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
				*tmp_val = 1;
				data_out.kind = NclStk_VAL;
				data_out.u.data_obj =_NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
				_NclPlaceReturn(data_out);
				
			}
		}
		tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
		*tmp_val = 0;
		data_out.kind = NclStk_VAL;
		data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
		_NclPlaceReturn(data_out);
	} else {
		tmp_val = (logical*)tmp_md->multidval.val;
		i = 0;
		while(i<tmp_md->multidval.totalelements) {
			if((*tmp_val != tmp_md->multidval.missing_value.value.logicalval) &&!(*tmp_val) ) {
				break;
			}
			tmp_val++;
			i++;
		}
		if(i >= tmp_md->multidval.totalelements) {
			tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
			*tmp_val = 1;
			data_out.kind = NclStk_VAL;
			data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
			_NclPlaceReturn(data_out);
		} else {
			tmp_val = (logical*)NclMalloc((unsigned)_NclSizeOf(NCL_logical));
			*tmp_val = 0;
			data_out.kind = NclStk_VAL;
			data_out.u.data_obj = _NclMultiDVallogicalCreate(NULL,NULL,Ncl_MultiDVallogicalData,0,tmp_val,NULL,1,&dim_size,TEMPORARY,NULL);
			_NclPlaceReturn(data_out);
		}
	}
	return(NhlNOERROR);
}

NhlErrorTypes _NclISizeOf
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;	
	NclStackEntry data_out;	
	NclMultiDValData tmp_md = NULL;
	int *size;
	int dim_size = 1;

	data = _NclGetArg(0,1);
	if(data.kind == NclStk_VAR) {
		if(data.u.data_var != NULL) {	
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
	} else {
		NhlPError(NhlWARNING, NhlEUNKNOWN,"sizeof: incorrect type of object passed to sizeof");
		return(NhlWARNING);
	}
	if(tmp_md != NULL) {
		data_out.kind = NclStk_VAL;
		size = NclMalloc(sizeof(int));
		*size = _NclSizeOf(tmp_md->multidval.data_type)*tmp_md->multidval.totalelements;
		data_out.u.data_obj = _NclMultiDValintCreate(
			NULL,
			NULL,
			Ncl_MultiDValintData,
			0,
			(void*)size,
			NULL,
			1,
			&dim_size,
			TEMPORARY,
			NULL
		);
		if(data_out.u.data_obj != NULL) {
			_NclPlaceReturn(data_out);
			return(NhlNOERROR);
		} else {
			return(NhlFATAL);
		}
	} else {
		return(NhlFATAL);
	}
}

NhlErrorTypes _NclIDimSizes
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;	
	NclStackEntry data_out;	
	NclMultiDValData tmp_md = NULL;
	int *size;
	int dim_size,i;

	data = _NclGetArg(0,1);
	if(data.kind == NclStk_VAR) {
		if(data.u.data_var != NULL) {	
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
	} else {
		NhlPError(NhlWARNING, NhlEUNKNOWN,"sizeof: incorrect type of object passed to sizeof");
		return(NhlWARNING);
	}
	if(tmp_md != NULL) {
		data_out.kind = NclStk_VAL;
		size = NclMalloc(sizeof(int)*tmp_md->multidval.n_dims);
		for(i = 0; i< tmp_md->multidval.n_dims; i++) {
			size[i] = tmp_md->multidval.dim_sizes[i];
		}
		dim_size = tmp_md->multidval.n_dims;
		data_out.u.data_obj = _NclMultiDValintCreate(
			NULL,
			NULL,
			Ncl_MultiDValintData,
			0,
			(void*)size,
			NULL,
			1,
			&dim_size,
			TEMPORARY,
			NULL
		);
		if(data_out.u.data_obj != NULL ) {
			_NclPlaceReturn(data_out);
			return(NhlNOERROR);
		} else {
			return(NhlFATAL);
		}
	} else {
		return(NhlFATAL);
	}
}

NhlErrorTypes _NclIDumpStk
#if  __STDC__
(void)
#else
()
#endif
{
	FILE *fp = NULL;
	NclMultiDValData tmp_md,tmp1_md;
	NclStackEntry data;
	char *fname = NULL;
	NhlErrorTypes ret = NhlNOERROR;
	data = _NclGetArg(0,1);
	if(data.kind == NclStk_VAR) {
		if(data.u.data_var != NULL) {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
	} else {
		NhlPError(NhlWARNING, NhlEUNKNOWN,"dump: incorrect type of object, defaulting to stdout");
		fp =  stdout;
		ret = NhlWARNING;
	}
	if(tmp_md->obj.obj_type_mask & Ncl_MultiDValstringData) {
		if(tmp_md->multidval.kind != SCALAR) {
			NhlPError(NhlWARNING,NhlEUNKNOWN,"dump: multiple file names passed to dump, using the first one");
			ret = NhlWARNING;
		}
		fname = NrmQuarkToString(*(int*)tmp_md->multidval.val);
	} else {
		tmp1_md = _NclCoerceData(tmp_md,Ncl_MultiDValstringData,NULL);
		if(tmp1_md == NULL) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"dump: Unable to covert parameter to string representation for output filename");
			fp = NULL;
			return(NhlFATAL);
		} else {
			if(tmp_md->obj.status != PERMANENT) {
				_NclDestroyObj((NclObj)tmp_md);
			}
			tmp_md = tmp1_md;
			if(tmp_md->multidval.kind != SCALAR) {
				NhlPError(NhlWARNING,NhlEUNKNOWN,"dump: multiple file names passed to dump, using the first one");
				ret = NhlWARNING;
			}
			fname = NrmQuarkToString(*(int*)tmp_md->multidval.val); 
		}
	}
	if((fname != NULL)&&(strcmp(fname,"stdout"))) {
		fp = fopen(fname,"a");
	} else {
		fp = stdout;
	}
	if(fp != NULL) {
		_NclDumpStack(fp,6);
		if(fp != stdout)
			fclose(fp);
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"dump: Unable to open output stream or file");
		return(NhlFATAL);
	}
	return(ret);
}

NhlErrorTypes _NclIFrame
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclMultiDValData tmp_md;
	NhlErrorTypes ret = NhlNOERROR;
	NclHLUObj hlu_ptr;
	int *obj_ids,i;

	data = _NclGetArg(0,1);

	if(data.kind == NclStk_VAR) {
		if(!(_NclGetVarRepValue(data.u.data_var) & NCL_HLU_MASK) ) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Non-object passed to frame, ignoring request");
			return(NhlFATAL);
		} else {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(tmp_md->obj.obj_type_mask & NCL_HLU_MASK) {
				obj_ids = (int*)tmp_md->multidval.val;
				for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
					hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
					if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
						ret = NhlFrame(hlu_ptr->hlu.hlu_id);
					}
				}
			}
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
		if(data.u.data_obj->obj.obj_type_mask && NCL_HLU_MASK) {
			obj_ids = (int*)tmp_md->multidval.val;
			for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
				hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
				if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
					ret = NhlFrame(hlu_ptr->hlu.hlu_id);
				}
			}
		}
	}
	return(ret);
}
NhlErrorTypes _NclIClear
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclMultiDValData tmp_md;
	NclHLUObj hlu_ptr;
	int *obj_ids,i;

	data = _NclGetArg(0,1);

	if(data.kind == NclStk_VAR) {
		if(!(_NclGetVarRepValue(data.u.data_var) & NCL_HLU_MASK) ) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Non-object passed to clear, ignoring request");
			return(NhlFATAL);
		} else {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(tmp_md->obj.obj_type_mask & NCL_HLU_MASK) {
				obj_ids = (int*)tmp_md->multidval.val;
				for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
					hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
					if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
						NhlClearWorkstation(hlu_ptr->hlu.hlu_id);
					}
				}
			}
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
		if(data.u.data_obj->obj.obj_type_mask && NCL_HLU_MASK) {
			obj_ids = (int*)tmp_md->multidval.val;
			for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
				hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
				if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
					NhlClearWorkstation(hlu_ptr->hlu.hlu_id);
				}
			}
		}
	}
	return(NhlNOERROR);
}

NhlErrorTypes _NclIDestroy
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclMultiDValData tmp_md;
	NclSymbol *thesym;
	NclStackEntry *var;
	int *obj_ids,i;

	data = _NclGetArg(0,1);

	if(data.kind == NclStk_VAR) {
		if(!(_NclGetVarRepValue(data.u.data_var) & NCL_HLU_MASK)) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Non-object passed to update, ignoring request");
	
			return(NhlFATAL);
		} else {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(tmp_md->obj.obj_type_mask & NCL_HLU_MASK) {
				obj_ids = (int*)tmp_md->multidval.val;
				for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
					NhlDestroy(obj_ids[i]);
				}
			}
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
		if(data.u.data_obj->obj.obj_type_mask && NCL_HLU_MASK) {
			obj_ids = (int*)tmp_md->multidval.val;
			for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
				NhlDestroy(obj_ids[i]);
			}
		}
	} else {
		return(NhlFATAL);
	}
	switch(data.kind) {
	case NclStk_VAL:
		_NclDestroyObj((NclObj)data.u.data_obj);
		break;
	case NclStk_VAR:
		if((data.u.data_var != NULL)&&(data.u.data_var->var.thesym != NULL)) {
			var = _NclRetrieveRec(data.u.data_var->var.thesym,DONT_CARE);
			thesym = data.u.data_var->var.thesym;
			if(data.u.data_var->var.var_type == NORMAL) {
/*
* Can't destroy symbol since it may be referenced from the instruction
* sequence. Changing it to UNDEF should do the trick though
*/
				_NclChangeSymbolType(thesym,UNDEF);
			}
		} else {
			var = NULL;
		}
		_NclDestroyObj((NclObj)data.u.data_var);
		if(var != NULL) {
			var->u.data_var = NULL;
			var->kind = NclStk_NOVAL;
		}
		break;
	default:
		break;
	}
	data.kind = NclStk_NOVAL;
	data.u.data_obj = NULL;
	_NclPutArg(data,0,1);
	return(NhlNOERROR);
}
NhlErrorTypes _NclIUpdate
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclMultiDValData tmp_md;
	NclHLUObj hlu_ptr;
	int *obj_ids,i;

	data = _NclGetArg(0,1);

	if(data.kind == NclStk_VAR) {
		if(!(_NclGetVarRepValue(data.u.data_var) & NCL_HLU_MASK)) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Non-object passed to update, ignoring request");
	
			return(NhlFATAL);
		} else {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(tmp_md->obj.obj_type_mask & NCL_HLU_MASK) {
				obj_ids = (int*)tmp_md->multidval.val;
				for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
					hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
					if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
						NhlUpdateWorkstation(hlu_ptr->hlu.hlu_id);
					}
				}
			}
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
		if(data.u.data_obj->obj.obj_type_mask && NCL_HLU_MASK) {
			obj_ids = (int*)tmp_md->multidval.val;
			for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
				hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);

				if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
					NhlUpdateWorkstation(hlu_ptr->hlu.hlu_id);
				}
			}
		}
	} else {
		return(NhlFATAL);
	}
	return(NhlNOERROR);
}

NhlErrorTypes _NclIDraw
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclMultiDValData tmp_md;
	int *obj_ids,i;
	NclHLUObj hlu_ptr;

	data = _NclGetArg(0,1);

	if(data.kind == NclStk_VAR) {
		if(!(_NclGetVarRepValue(data.u.data_var) & NCL_HLU_MASK)) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Non-object passed to draw, ignoring request");
			return(NhlFATAL);
		} else {
			tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(tmp_md->obj.obj_type_mask & NCL_HLU_MASK) {
				obj_ids = (int*)tmp_md->multidval.val;
				for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
					hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
					if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
						NhlDraw(hlu_ptr->hlu.hlu_id);
					}
				}
			}
		}
	} else if(data.kind == NclStk_VAL) {
		tmp_md = data.u.data_obj;
		if(data.u.data_obj->obj.obj_type_mask && NCL_HLU_MASK) {
			obj_ids = (int*)tmp_md->multidval.val;
			for(i = 0; i < tmp_md->multidval.totalelements; i++ ) {
				hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
				if((hlu_ptr != NULL)&&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
					NhlDraw(hlu_ptr->hlu.hlu_id);
				}
			}
		}
	} else {
		return(NhlFATAL);
	}
	return(NhlNOERROR);
}

NhlErrorTypes _NclIPrint
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	FILE *fp;
	

	data = _NclGetArg(0,1);
	fp = stdout;
/*_NclGetOutputStream();*/

	switch(data.kind) {
	case NclStk_VAL:
		_NclPrint((NclObj)data.u.data_obj,fp);
		break;
	case NclStk_VAR:
		_NclPrint((NclObj)data.u.data_var,fp);
		break;
	default:
		break;
	}
	return(NhlNOERROR);
}

NhlErrorTypes _NclIDelete
#if  __STDC__
(void)
#else
()
#endif
{
	NclStackEntry data;
	NclStackEntry* var;
	NclSymbol *thesym;
	int sub_sel = 0;

	data = _NclGetArg(0,1);

	switch(data.kind) {
	case NclStk_VAL:
		_NclDestroyObj((NclObj)data.u.data_obj);
		break;
	case NclStk_VAR:
		if(data.u.data_var != NULL) {
			switch(data.u.data_var->var.var_type) {
				case VARSUBSEL:
				case COORDSUBSEL:
				case FILEVARSUBSEL:
					sub_sel = 1;
					break;
				case NORMAL:
				case COORD:
				case FILEVAR: 
				case PARAM:
				case RETURNVAR:
				case HLUOBJ :
				default:
					sub_sel = 0;
					break;
			}
		}
		if((data.u.data_var != NULL)&&(data.u.data_var->var.thesym != NULL)&&(!sub_sel)) {
			var = _NclRetrieveRec(data.u.data_var->var.thesym,DONT_CARE);
			thesym = data.u.data_var->var.thesym;
			if(data.u.data_var->var.var_type == NORMAL) {
/*
* Can't destroy symbol since it may be referenced from the instruction
* sequence. Changing it to UNDEF should do the trick though
*/
				_NclChangeSymbolType(thesym,UNDEF);
			}
		} else {
			var = NULL;
		}
		_NclDestroyObj((NclObj)data.u.data_var);
		if(var != NULL) {
			var->u.data_var = NULL;
			var->kind = NclStk_NOVAL;
		}
		break;
	default:
		break;
	}
	data.kind = NclStk_NOVAL;
	data.u.data_obj = NULL;
	_NclPutArg(data,0,1);
	
	return(NhlNOERROR);
}
NhlErrorTypes _NclDualOp
#if  __STDC__
(NclStackEntry lhs, NclStackEntry rhs,NclStackEntry *result,int operation)
#else
(lhs, rhs,result,operation)
NclStackEntry lhs;
NclStackEntry rhs;
NclStackEntry *result;
int operation;
#endif
{
	NclMultiDValData lhs_data_obj = NULL;
	NclMultiDValData rhs_data_obj = NULL;
	NclMultiDValData coerce_res = NULL;
	NhlErrorTypes ret = NhlNOERROR;
	int lhs_type;
	int rhs_type;


	if(lhs.kind == NclStk_VAL) {
		lhs_type = lhs.u.data_obj->obj.obj_type_mask & NCL_VAL_TYPE_MASK;
	} else if(lhs.kind == NclStk_VAR) {
		lhs_type = _NclGetVarRepValue(lhs.u.data_var);
	} else {
		return(NhlFATAL);
	}

	if(rhs.kind == NclStk_VAL) {
		rhs_type = rhs.u.data_obj->obj.obj_type_mask & NCL_VAL_TYPE_MASK;
	} else if(rhs.kind == NclStk_VAR) {
		rhs_type = _NclGetVarRepValue(rhs.u.data_var);
	} else {
		return(NhlFATAL);
	}

	if(lhs_type != rhs_type) {

		if(rhs.kind == NclStk_VAL) {
/*
* No need to pass in missing value since it will be used appropriately
* by the operator's function
*/
			coerce_res = _NclCoerceData(rhs.u.data_obj,
					lhs_type,NULL);
		} else {
/*
* No need to pass in missing value since it will be used appropriately
* by the operator's function
*/
			coerce_res = _NclCoerceVar(rhs.u.data_var,lhs_type,NULL);
		}
		if(coerce_res == NULL) {
			if(lhs.kind == NclStk_VAL) {
/*
* No need to pass in missing value since it will be used appropriately
* by the operator's function
*/
			coerce_res = _NclCoerceData(lhs.u.data_obj,
				rhs_type & NCL_VAL_TYPE_MASK,NULL);
			} else {
/*
* No need to pass in missing value since it will be used appropriately
* by the operator's function
*/
			coerce_res = _NclCoerceVar(lhs.u.data_var,
				rhs_type,NULL);
			}
			if(coerce_res == NULL) {
/*
* Error message needed
*/
				return(NhlFATAL);
			} else {
				if(lhs.u.data_obj->obj.status != PERMANENT) {
					_NclDestroyObj((NclObj)lhs.u.data_obj);
				}
				lhs_data_obj = coerce_res;
				if(rhs.kind == NclStk_VAL) {
					rhs_data_obj = rhs.u.data_obj;
				} else {
					rhs_data_obj = _NclVarValueRead(rhs.u.data_var,NULL,NULL);
				}

			}
		} else {
			if(rhs.u.data_obj->obj.status != PERMANENT) {
				_NclDestroyObj((NclObj)rhs.u.data_obj);
			}
			rhs_data_obj = coerce_res;
			if(lhs.kind == NclStk_VAL) {
				lhs_data_obj = lhs.u.data_obj;
			} else {
				lhs_data_obj = _NclVarValueRead(lhs.u.data_var,NULL,NULL);
			}
		}
	} else {
		if(lhs.kind == NclStk_VAL) {
			lhs_data_obj = lhs.u.data_obj;
		} else {
			lhs_data_obj = _NclVarValueRead(lhs.u.data_var,NULL,NULL);
		}
		if(rhs.kind == NclStk_VAL) {
			rhs_data_obj = rhs.u.data_obj;
		} else {
			rhs_data_obj = _NclVarValueRead(rhs.u.data_var,NULL,NULL);
		}
	}
	if((lhs_data_obj != NULL)&&(rhs_data_obj != NULL)) {
		ret = _NclCallDualOp(lhs_data_obj,rhs_data_obj,operation,result);
	} else {
		return(NhlFATAL);
	}
        if((lhs.kind == NclStk_VAL)&&(lhs_data_obj->obj.status != PERMANENT)) {
		_NclDestroyObj((NclObj)lhs_data_obj);
        } else if((lhs.kind == NclStk_VAR)&&(lhs.u.data_var->obj.status != PERMANENT)) {
		_NclDestroyObj((NclObj)lhs.u.data_var);
        } 
        if((rhs.kind == NclStk_VAL)&&(rhs_data_obj->obj.status != PERMANENT)) {
		_NclDestroyObj((NclObj)rhs_data_obj);
        } else if((rhs.kind == NclStk_VAR)&&(rhs.u.data_var->obj.status != PERMANENT)) {
		_NclDestroyObj((NclObj)rhs.u.data_var);
        } 


	return(ret);
}


NhlErrorTypes _NclMonoOp
#if  __STDC__
(NclStackEntry operand, NclStackEntry *result, int operation)
#else
(operand, result,operation)
NclStackEntry operand;
NclStackEntry *result;
int operation;
#endif
{
	NclMultiDValData operand_md;
	NhlErrorTypes ret = NhlNOERROR;
	
	
        if(operand.kind == NclStk_VAL) {
		operand_md = operand.u.data_obj;
	} else if(operand.kind == NclStk_VAR) {
		operand_md = _NclVarValueRead(operand.u.data_var,NULL,NULL);
        } else {
                return(NhlFATAL);
        }

	ret = _NclCallMonoOp(operand_md,result,operation);

	if(operand_md->obj.status != PERMANENT) {
		_NclDestroyObj((NclObj)operand_md);
	} else if((operand.kind == NclStk_VAR)&&(operand.u.data_var->obj.status != PERMANENT)) {
		_NclDestroyObj((NclObj)operand_md);
	}

        return(ret);
}


NhlErrorTypes _NclBuildArray
#if __STDC__
(int n_items,NclStackEntry *result)
#else
(n_items,result)
	int n_items;
	NclStackEntry *result;
#endif
{
	NclStackEntry data;
	int partsize;
	int items_left = n_items;
	void *value;
	char *ptr;
	int dim_sizes[NCL_MAX_DIMENSIONS];
	NclMultiDValData theobj,coerce_res;
	NclStackEntry *data_ptr;
	NclObjTypes result_type ;
	int obj_type ;
	int must_be_numeric = 1,i,j;
	int ndims;
	NclScalar *mis_ptr = NULL,themissing;
	int still_no_missing = 1;

	

/*
* First element determines whether the type of the result array is numerci
* or textual
*/
	data_ptr = _NclPeek(0);
	if(data_ptr->kind == NclStk_VAL) {	
		obj_type = data_ptr->u.data_obj->obj.obj_type_mask;
		ndims = data_ptr->u.data_obj->multidval.n_dims;
		for(i = 0; i < ndims; i++ ) {
			dim_sizes[i] = data_ptr->u.data_obj->multidval.dim_sizes[i];
		} 
	} else if(data_ptr->kind == NclStk_VAR) {
		obj_type = _NclGetVarRepValue(data_ptr->u.data_var);
		ndims = data_ptr->u.data_var->var.n_dims;
		for(i = 0; i < ndims; i++ ) {
			dim_sizes[i] = data_ptr->u.data_var->var.dim_info[i].dim_size;
		} 
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: attempt to build array out of illegal data type, can't continue");
		_NclCleanUpStack(n_items);
		return(NhlFATAL);
	}
	if(obj_type & NCL_VAL_NUMERIC_MASK) {
		must_be_numeric =1;
		result_type = obj_type & NCL_VAL_NUMERIC_MASK;
	} else if(obj_type & NCL_VAL_CHARSTR_MASK) {
		must_be_numeric =0;
		result_type = obj_type & NCL_VAL_CHARSTR_MASK;
	} else if(obj_type & NCL_HLU_MASK) {
		must_be_numeric =-1;
		result_type = obj_type & NCL_HLU_MASK;
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: attempt to build array out of illegal data type or undefined element, can't continue");
		_NclCleanUpStack(n_items);
		return(NhlFATAL);
	}

/*
* The following loop figures out what the final type of the result array
* should be so the appropriate space can be allocated and the elements not
* of this type can be coerced into the correct type
*/	
	for(i = 1; i< n_items; i++) {
		data_ptr = _NclPeek(i);
		if(data_ptr->kind == NclStk_VAL) {	
			obj_type = data_ptr->u.data_obj->obj.obj_type_mask;
			if(ndims == data_ptr->u.data_obj->multidval.n_dims) {
				for(j = 0; j < ndims; j++) {
					if(dim_sizes[j] != data_ptr->u.data_obj->multidval.dim_sizes[j]) {
						NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: each element of a literal array must have the same dimension sizes, at least one item doesn't");
						_NclCleanUpStack(n_items);
						return(NhlFATAL);
					}
				}
			} else {
				NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: each element of a literal array must have the same number of dimensions");
				_NclCleanUpStack(n_items);
				return(NhlFATAL);
			}
		} else if(data_ptr->kind == NclStk_VAR) {
			obj_type = _NclGetVarRepValue(data_ptr->u.data_var);
			if(ndims == data_ptr->u.data_var->var.n_dims) {
				for(j = 0; j < ndims; j++) {
					if(dim_sizes[j] != data_ptr->u.data_var->var.dim_info[j].dim_size) {
						NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: each element of a literal array must have the same dimension sizes, at least one item doesn't");
						_NclCleanUpStack(n_items);
						return(NhlFATAL);
					}
				}
			} else {
				NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: each element of a literal array must have the same number of dimensions");
				_NclCleanUpStack(n_items);
				return(NhlFATAL);
			}
		} else {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: attempt to build array out of illegal data type, can't continue");
			_NclCleanUpStack(n_items);
			return(NhlFATAL);
		}
		if((must_be_numeric==1)&&
			( obj_type &NCL_VAL_NUMERIC_MASK)) {
			if(result_type > (obj_type & NCL_VAL_NUMERIC_MASK)) {
				result_type = (obj_type & NCL_VAL_NUMERIC_MASK);
			}
		} else if((must_be_numeric == 0)&&
			(obj_type & NCL_VAL_CHARSTR_MASK)) {
			if(result_type > (obj_type & NCL_VAL_CHARSTR_MASK)) {
				result_type = (obj_type & NCL_VAL_CHARSTR_MASK);
			}
		} else if((must_be_numeric == -1)&&
			(obj_type & NCL_HLU_MASK)) {
			if(result_type > (obj_type & NCL_HLU_MASK)) {
				result_type = (obj_type & NCL_HLU_MASK);
			}
		} else {
/*
* May need to say something different now that objects are done in this
* way too
*/
			NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: can not combine character or string types with numeric types, can't continue");
			_NclCleanUpStack(n_items);
			return(NhlFATAL);
		}
	}
/*
* By the time you get here you know the stack is guarenteed to contain either 
* numeric values that can be coerced or textual values that can be coerced. 
* Still the  possibility that dimensions numbers and sizes of elements don't 
* match
*/

	data = _NclPop();
	items_left--;
	if(data.kind == NclStk_VAL) {
		theobj = (NclMultiDValData)data.u.data_obj;
		if(!(theobj->obj.obj_type_mask & result_type)) {
			coerce_res = _NclCoerceData(theobj,result_type,NULL);
			if(coerce_res == NULL) {
/*
* This should not happen because the beginning loops assure that all elements
* are coercible to result_type.
*/
				NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
			} else if(coerce_res->multidval.missing_value.has_missing) {
				still_no_missing = 0;
/*
* I do this so I can just pass mis_ptr in regardless later on. It
* will be NULL if none of the input has missing values. other wise
* it will be set to the correct missing value.
*/
				mis_ptr = &themissing;
				themissing = coerce_res->multidval.missing_value.value;
			}
			if(theobj->obj.status != PERMANENT) {
				_NclDestroyObj((NclObj)theobj);
			}
			theobj = coerce_res;
		} else if(theobj->multidval.missing_value.has_missing) {
			still_no_missing = 0;
			mis_ptr = &themissing;
			themissing = theobj->multidval.missing_value.value;
		}
	} else if(data.kind == NclStk_VAR){
		obj_type = _NclGetVarRepValue(data.u.data_var);	
		if(!(obj_type & result_type)) {
			theobj = _NclCoerceVar(data.u.data_var,result_type,NULL);
			if(theobj == NULL) {
/*
* This should not happen because the beginning loops assure that all elements
* are coercible to result_type.
*/
				NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
				_NclCleanUpStack(items_left);
				return(NhlFATAL);
			} else if(theobj->multidval.missing_value.has_missing){
				still_no_missing = 0;
/*
* I do this so I can just pass mis_ptr in regardless later on. It
* will be NULL if none of the input has missing values. other wise
* it will be set to the correct missing value.
*/
				mis_ptr = &themissing;
				themissing = theobj->multidval.missing_value.value;
			}
			if(data.u.data_var->obj.status != PERMANENT) {
				_NclDestroyObj((NclObj)data.u.data_var);
			}
		} else {
			theobj = _NclVarValueRead(data.u.data_var,NULL,NULL);
			if(theobj == NULL) {
				NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
				_NclCleanUpStack(items_left);
				return(NhlFATAL);
			} else if(theobj->multidval.missing_value.has_missing){
/*
* I do this so I can just pass mis_ptr in regardless later on. It
* will be NULL if none of the input has missing values. other wise
* it will be set to the correct missing value.
*/
				still_no_missing = 0;
				mis_ptr = &themissing;
				themissing = theobj->multidval.missing_value.value;
			}
		}
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: unknown stack data type");
		_NclCleanUpStack(items_left);
		return(NhlFATAL);
	}


	partsize = theobj->multidval.totalsize;

/*
* ------------->Need check for exceeding maximum dimensions <----------
*/
	for(i =0; i< theobj->multidval.n_dims; i++) {
/*
* -------------> Also need to rearrage dimension info <---------------
*/
		dim_sizes[i+1] = theobj->multidval.dim_sizes[i];
	}
	dim_sizes[0] = n_items;
	if(theobj->multidval.kind == MULTID) {
		ndims = theobj->multidval.n_dims +1;
	} else {
		ndims = 1;
	}
	value = (void*)NclMalloc((unsigned)partsize*n_items);
	if(value == NULL) {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray : Memory allocation failure\n");
		result->kind = NclStk_NOVAL;
		result->u.data_obj = NULL; 
		NclFree(value);
		_NclCleanUpStack(items_left);
		return(NhlFATAL);
	}
	ptr = (char*)value;
	memcpy(ptr,(char*)theobj->multidval.val,partsize);
	ptr += partsize;
	if(theobj->obj.status != PERMANENT) {
		_NclDestroyObj((NclObj)theobj);
	}


	while(items_left) {
		data = _NclPop();
		items_left--;
		if(data.kind == NclStk_VAL) {
			theobj = (NclMultiDValData)data.u.data_obj;
			if(!(theobj->obj.obj_type_mask & result_type)) {
				coerce_res = _NclCoerceData(theobj,result_type,mis_ptr);
				if(coerce_res == NULL) {
/*
* This should not happen because the beginning loops assure that all elements
* are coercible to result_type.
*/
					NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
					_NclCleanUpStack(items_left);
					NclFree(value);
					return(NhlFATAL);
				} else if((still_no_missing)	
					&&(coerce_res->multidval.missing_value.has_missing)) {
					still_no_missing = 0;
					mis_ptr = &themissing;
					themissing = theobj->multidval.missing_value.value;
				}
				if(theobj->obj.status != PERMANENT) {
					_NclDestroyObj((NclObj)theobj);
				}
				theobj = coerce_res;
			} else if((theobj->multidval.missing_value.has_missing)&&(still_no_missing)) {
				still_no_missing = 0;
				mis_ptr = &themissing;
				themissing = theobj->multidval.missing_value.value;
			} else if((theobj->multidval.missing_value.has_missing)&&(!still_no_missing)){
/*
* This is the case where the object is already the correct type but
* needs to have the missing value reset. ResetMissingValue should only be
* called if the object is TEMPORARY otherwise CoerceData Needs to be
* used to convert the missing values.
*/
				if(theobj->obj.status != TEMPORARY) {
/*
* Since theobj is not TEMPORARY then it is referenced somewhere else and the
* following will not cause the pointer to be lost.
*/
					coerce_res = _NclCopyVal(theobj,mis_ptr);
					if(theobj->obj.status != PERMANENT) {
						_NclDestroyObj((NclObj)theobj);
					}
					theobj = coerce_res;
				} else {
					_NclResetMissingValue(theobj,mis_ptr);
				}
			}
		} else if(data.kind == NclStk_VAR){
			obj_type = _NclGetVarRepValue(data.u.data_var);	
			if(!(obj_type & result_type)) {
				theobj = _NclCoerceVar(data.u.data_var,result_type,mis_ptr);
				if(theobj == NULL) {
/*
* This should not happen because the beginning loops assure that all elements
* are coercible to result_type.
*/
					NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
					_NclCleanUpStack(items_left);
					NclFree(value);
					return(NhlFATAL);
				} else if((still_no_missing)&&
					(theobj->multidval.missing_value.has_missing)) {
					still_no_missing = 0;
					mis_ptr = &themissing;
					themissing = theobj->multidval.missing_value.value;
				}
				if(data.u.data_var->obj.status != PERMANENT) {
					_NclDestroyObj((NclObj)data.u.data_var);
				}
			} else {
				theobj = _NclVarValueRead(data.u.data_var,NULL,NULL);
				if(theobj == NULL) {
					NhlPError(NhlFATAL,NhlEUNKNOWN,"An Error occured that should not have happend");
					_NclCleanUpStack(items_left);
					NclFree(value);
					return(NhlFATAL);
				} else if((still_no_missing)&&
					(theobj->multidval.missing_value.has_missing)) {
					still_no_missing = 0;
					mis_ptr = &themissing;
					themissing = theobj->multidval.missing_value.value;
				} else if((theobj->multidval.missing_value.has_missing)&&(!still_no_missing)) {
					if(theobj->obj.status == TEMPORARY) {
						_NclResetMissingValue(theobj,mis_ptr);
					} else {
						coerce_res = _NclCopyVal(theobj,mis_ptr);
						if(theobj->obj.status != PERMANENT) {
							_NclDestroyObj((NclObj)theobj);
						}
						theobj = coerce_res;
					}
				}
			}
		} else {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclBuildArray: unknown stack data type");
			_NclCleanUpStack(items_left);
			NclFree(value);
			return(NhlFATAL);
		}
		memcpy(ptr,(char*)theobj->multidval.val,partsize);
		ptr += partsize;
		if(theobj->obj.status != PERMANENT) {
			_NclDestroyObj((NclObj)theobj);
		}
	}
	result->kind = NclStk_VAL;
/*
*
* ------------> stilll need to handle dim info
*/
	result->u.data_obj = _NclCreateVal(NULL,NULL,result_type,0,value,NULL,ndims,dim_sizes,TEMPORARY,NULL);
	if(result->u.data_obj != NULL) 
		return(NhlNOERROR);
	else 
		return(NhlFATAL);
}

NhlErrorTypes _NclProcCallOp
#if __STDC__
(NclSymbol *proc,int caller_level)
#else
(proc,caller_level)
	NclSymbol *proc;
	int caller_level;
#endif
{
	NhlErrorTypes ret = NhlNOERROR;
	NclExecuteReturnStatus eret;
	NclStackEntry data;
	void* previous_fp = NULL;
	int i;

/*
* By the time you get here all of the arguments should've been checked against
* the templates and converted to the appropriate type and the sizes checked
*/
	if(proc->u.procfunc== NULL) {
		return(NhlFATAL);
	}
	
	_NclPushMachine(proc->u.procfunc->mach_rec_ptr);
	eret = _NclExecute(0);
	switch(eret) {
	case Ncl_ERRORS:
		ret = NhlFATAL;
		break;
	case Ncl_STOPS:
	case Ncl_BREAKS:
	case Ncl_CONTINUES:
	default:
		ret = NhlNOERROR;
		break;
	}
	(void)_NclPopMachine();
	previous_fp = _NclLeaveFrame(caller_level);
/*
* Temporary stack management code
*/
	if(ret != NhlFATAL) {
		_NclRemapParameters(proc->u.procfunc->nargs,proc->u.procfunc->thescope->cur_offset,previous_fp,PROC_CALL_OP);
	} else {
		for(i = 0; i<proc->u.procfunc->thescope->cur_offset; i++) {
			data = _NclPop();
			switch(data.kind) {
			case NclStk_VAL: {
				_NclDestroyObj((NclObj)data.u.data_obj);
			}
				break;
			case NclStk_VAR: {
				_NclDestroyObj((NclObj)data.u.data_var);
			}
				break;
			default:
				break;
			}
		}
	}
	
	_NclPopFrame(PROC_CALL_OP);
	return(ret);
}
NhlErrorTypes _NclFuncCallOp
#if __STDC__
(NclSymbol *func,int caller_level)
#else
(func,caller_level)
	NclSymbol *func;
	int caller_level;
#endif
{
	NhlErrorTypes ret = NhlNOERROR;
	NclStackEntry data;
	NclExecuteReturnStatus eret;
	void *previous_fp= NULL;
	
	int i;

/*
* By the time you get here all of the arguments should've been checked against
* the templates and converted to the appropriate type and the sizes checked
*/
	if(func->u.procfunc == NULL) {
		return(NhlFATAL);
	}
	
	_NclPushMachine(func->u.procfunc->mach_rec_ptr);
	eret = _NclExecute(0);
	switch(eret) {
	case Ncl_ERRORS:
		ret = NhlFATAL;
		break;
	case Ncl_STOPS:
	case Ncl_BREAKS:
	case Ncl_CONTINUES:
	default:
		ret = NhlNOERROR;
		break;
	}
	(void)_NclPopMachine();
	previous_fp = _NclLeaveFrame(caller_level);

	if(ret != NhlFATAL) {
		_NclRemapParameters(func->u.procfunc->nargs,func->u.procfunc->thescope->cur_offset,previous_fp,FUNC_CALL_OP);
	} else {
		for(i = 0; i<func->u.procfunc->thescope->cur_offset; i++) {
			data = _NclPop();
			switch(data.kind) {
			case NclStk_VAL: {
				_NclDestroyObj((NclObj)data.u.data_obj);
			}
				break;
			case NclStk_VAR: {
				_NclDestroyObj((NclObj)data.u.data_var);
			}
				break;
			default:
				break;
			}
		}
	}
	_NclPopFrame(FUNC_CALL_OP);
/*
* Doesn't leave return value on stack if an error has occured. Probably
* should check it to see if it needs to be freed
*/
	if(ret < NhlWARNING) {
		(void)_NclPop();
	}

	return(ret);
}

NclStackEntry _NclCreateHLUObjOp
#if __STDC__
(int nres,char *the_hlu_obj, NclSymbol *the_hlu_obj_class, NclMultiDValData parent)
#else
(nres,the_hlu_obj, the_hlu_obj_class, parent)
	int nres;
	NclSymbol *the_hlu_obj;
	NclSymbol *the_hlu_obj_class;
	NclMultiDValData parent;
#endif
{
	int i;
	NclStackEntry *data,*resname;
	NclStackEntry data_out;
	int rl_list;
	NhlGenArray *gen_array;
	NclMultiDValData tmp_md = NULL;
	NclHLUObj tmp_ho = NULL;
	int *tmp_id = NULL,tmp_ho_id;
	int dim_size = 1;
	int parent_id = -1;

	if(parent != NULL) 	 {
		if(parent->multidval.totalelements > 1) {
			NhlPError(NhlWARNING,NhlEUNKNOWN,"Objects only accept one object as their parent, a multi-element of array objects, using the first element");
		}
		tmp_ho = (NclHLUObj)_NclGetObj(*(int*)parent->multidval.val);
		if((tmp_ho != NULL)&&(tmp_ho->obj.obj_type_mask & Ncl_HLUObj)) {
			parent_id = tmp_ho->hlu.hlu_id;
		} else {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"_NclCreateHLUObjOp: Parent value is not an hlu object or is undefined");
			_NclCleanUpStack(2*nres);
			data_out.kind = NclStk_NOVAL;
			data_out.u.data_obj = NULL;
			return(data_out);
		}
	}


	rl_list = NhlRLCreate(NhlSETRL);	
	gen_array = NclMalloc((unsigned)sizeof(NhlGenArray)*nres);
	for(i = 0; i < nres; i++) {
/*
* Need to peek because I have to keep the stack values arround until after
* the Create call
*/
		data = _NclPeek(2*i);
		resname = _NclPeek(2*i+1);
		if(((data->kind != NclStk_VAL)&&(data->kind != NclStk_VAR))||(resname->kind != NclStk_VAL)) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Error in resource list. type mismatch, resource names must be strings and \nresource values must be either file variables, variables or expression results.\n");

			_NclCleanUpStack(2*nres);
			data_out.kind = NclStk_NOVAL;
			data_out.u.data_obj = NULL;
			return(data_out);
		}
		switch(data->kind) {
		case NclStk_VAL:
			tmp_md = (NclMultiDValData)data->u.data_obj;
		break;
		case NclStk_VAR:
			tmp_md = _NclVarValueRead(data->u.data_var,NULL,NULL);
		break;
		}
		if(tmp_md->multidval.hlu_type_rep != NULL) {
			gen_array[i] = _NhlCreateGenArray(
					(NhlPointer)tmp_md->multidval.val,
					tmp_md->multidval.hlu_type_rep,
					(int)(tmp_md->multidval.totalsize/tmp_md->multidval.totalelements),
					tmp_md->multidval.n_dims,
					tmp_md->multidval.dim_sizes,
					0);
			NhlRLSet(rl_list,NrmQuarkToString(
				*(int*)(((NclMultiDValData)resname->u.data_obj)->multidval.val)),
				NhlTGenArray,
				gen_array[i]);
		}
/*
*-----> Need to deal with NULL hlu_type_rep
*/
	}

	tmp_id = (int*)NclMalloc((unsigned)sizeof(int));

	NhlCreate(&tmp_ho_id,the_hlu_obj,the_hlu_obj_class->u.obj_class_ptr,(parent_id == -1? NhlNOPARENT:parent_id),rl_list);
	tmp_ho = _NclHLUObjCreate(NULL,nclHLUObjClass,Ncl_HLUObj,0,TEMPORARY,tmp_ho_id); 
	*tmp_id = tmp_ho->obj.id;
	tmp_md = _NclMultiDValHLUObjDataCreate(
		NULL,
		NULL,
		Ncl_MultiDValHLUObjData,
		0,
		tmp_id,
		NULL,
		1,
		&dim_size,
		TEMPORARY,
		NULL
	); 
	if(tmp_md != NULL) {
		data_out.u.data_obj = tmp_md;
		data_out.kind = NclStk_VAL;
	} else {
		data_out.u.data_obj = NULL;
		data_out.kind = NclStk_NOVAL;
	}
	for(i = 0; i < nres; i++) {
		NhlFreeGenArray(gen_array[i]);
	}
	NclFree(gen_array);
	NhlRLDestroy(rl_list);
	_NclCleanUpStack(2*nres);
	return(data_out);
}

NhlErrorTypes _NclSetHLUObjOp
#if __STDC__
(NclMultiDValData the_hlu_data_obj, int nres)
#else
(the_hlu_data_obj,nres)
NclMultiDValData the_hlu_data_obj;
int nres;
#endif
{
	int i;
	NclStackEntry *data,*resname;
	int rl_list;
	NhlGenArray *gen_array;
	NclMultiDValData tmp_md = NULL;
	int *obj_ids = NULL;
	NclHLUObj hlu_ptr;


	rl_list = NhlRLCreate(NhlSETRL);	
	gen_array = NclMalloc((unsigned)sizeof(NhlGenArray)*nres);
	for(i = 0; i < nres; i++) {
/*
* Need to peek because I have to keep the stack values arround until after
* the Create call
*/
		data = _NclPeek(2*i);
		resname = _NclPeek(2*i+1);
		if(((data->kind != NclStk_VAL)&&(data->kind != NclStk_VAR))||(resname->kind != NclStk_VAL)) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"Error in resource list. type mismatch, resource names must be strings and \nresource values must be either file variables, variables or expression results.\n");

			_NclCleanUpStack(2*nres);
			return(NhlFATAL);
		}
		switch(data->kind) {
		case NclStk_VAL:
			tmp_md = (NclMultiDValData)data->u.data_obj;
		break;
		case NclStk_VAR:
			tmp_md = _NclVarValueRead(data->u.data_var,NULL,NULL);
		break;
		}
		gen_array[i] = _NhlCreateGenArray(
				(NhlPointer)tmp_md->multidval.val,
				tmp_md->multidval.hlu_type_rep,
				(int)(tmp_md->multidval.totalsize/tmp_md->multidval.totalelements),
				tmp_md->multidval.n_dims,
				tmp_md->multidval.dim_sizes,
				0);
		NhlRLSet(rl_list,NrmQuarkToString(
			*(int*)(((NclMultiDValData)resname->u.data_obj)->multidval.val)),
			NhlTGenArray,
			gen_array[i]);
	}


/* 
* stuff like this makes me think that NclMultiDValHLUObjData.c should have 
* methods added to the HLUObj to perform HLU specific functions.
*/
	obj_ids = (int*)the_hlu_data_obj->multidval.val;
	for(i = 0; i < the_hlu_data_obj->multidval.totalelements; i++ ) {
		hlu_ptr = (NclHLUObj)_NclGetObj(obj_ids[i]);
		if((hlu_ptr != NULL) &&(hlu_ptr->obj.obj_type_mask & Ncl_HLUObj)) {
			NhlSetValues(hlu_ptr->hlu.hlu_id,rl_list);
		}
	}
	for(i = 0; i < nres; i++) {
		NhlFreeGenArray(gen_array[i]);
	}
	NclFree(gen_array);
	NhlRLDestroy(rl_list);
	_NclCleanUpStack(2*nres);
	return(NhlNOERROR);
}

NhlErrorTypes _NclNewOp
#if  __STDC__
(NclSymbol*  data_type, NclStackEntry size_expr, NclStackEntry missing_expr)
#else
(data_type, size_expr, missing_expr)
NclSymbol*  data_type;
NclStackEntry size_expr;
NclStackEntry missing_expr;
#endif  
{
	unsigned int the_obj_type;
	NclStackEntry data;
	NclBasicDataTypes the_type;
	unsigned int allowed_types = (NCL_VAL_NUMERIC_MASK | NCL_VAL_CHARSTR_MASK | NCL_HLU_MASK);
	NclScalar missing_val;
	NclMultiDValData missing_md,tmp_md,size_md,tmp1_md;
	void *tmp_val;
	int dim_sizes[NCL_MAX_DIMENSIONS];
	int tmp_missing = NCL_DEFAULT_MISSING_VALUE;
	long *dim_size_list,total;
	int i;
	NhlErrorTypes ret = NhlNOERROR;
	

	the_type = _NclKeywordToDataType(data_type);
	the_obj_type = _NclKeywordToObjType(data_type);
	if(the_obj_type == NCL_VAL_NUMERIC_MASK) {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Keyword numeric is too general, can't determine the size of data");
		return(NhlFATAL);
	} else if(the_obj_type == Ncl_Var) {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Can not make arrays of vars without values and variable names");
		return(NhlFATAL);
	}

	if((missing_expr.kind == NclStk_VAL)||(missing_expr.kind == NclStk_VAR)) {
		if(missing_expr.kind == NclStk_VAL) {
			missing_md = missing_expr.u.data_obj;
		} else {
			missing_md = _NclVarValueRead(missing_expr.u.data_var,NULL,NULL);
		}
		if(missing_md->multidval.kind != SCALAR) {
			NhlPError(NhlWARNING,NhlEUNKNOWN,"New: the missing value provided has more than one element, using the first one as the _FillValue");
			ret = NhlWARNING;
		}
		if(missing_md->obj.obj_type != the_obj_type) {
			tmp_md = _NclCoerceData(missing_md,the_obj_type,NULL);
			if(tmp_md == NULL) {
				NhlPError(NhlWARNING,NhlEUNKNOWN,"New: Could not coerce missing value parameter into appropriate type, using default");

				if(the_type != NCL_int) {
					tmp_val = (void*)NclMalloc((unsigned)_NclSizeOf(the_type));
					dim_sizes[0] = 1;
					if(_NclScalarCoerce(&tmp_missing,NCL_int,tmp_val,the_type)) {
						memcpy((void*)&missing_val,(void*)tmp_val,_NclSizeOf(the_type));
						NclFree(tmp_val);
					} else {
						NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Could not coerce default missing value into appropriate type");
						return(NhlFATAL);
					}
				} else {	
						missing_val.intval = tmp_missing;
				}
				ret = NhlWARNING;
			} else {
				if(missing_md->obj.status != PERMANENT) {
					_NclDestroyObj((NclObj)missing_md);
				}
				missing_md = tmp_md;
			}
		} 
		memcpy((void*)&missing_val,(void*)missing_md->multidval.val,_NclSizeOf(the_type));
	} else {
		if(the_type != NCL_int) {
			tmp_val = (void*)NclMalloc((unsigned)_NclSizeOf(the_type));
			dim_sizes[0] = 1;
			if(_NclScalarCoerce(&tmp_missing,NCL_int,tmp_val,the_type)) {
				memcpy((void*)&missing_val,(void*)tmp_val,_NclSizeOf(the_type));
				NclFree(tmp_val);
			} else {
				NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Could not coerce missing value into requested type");
				return(NhlFATAL);
			}
		} else {	
				missing_val.intval = tmp_missing;
		}
	}
	if(size_expr.kind == NclStk_VAL) {
		size_md = size_expr.u.data_obj;
	} else if(size_expr.kind == NclStk_VAR) {
		size_md = _NclVarValueRead(size_expr.u.data_var,NULL,NULL);
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Incorrect type passed as dimension size array");
		return(NhlFATAL);

	}
	if(size_md != NULL) {
		if(size_md->multidval.missing_value.has_missing) {
			NhlPError(NhlFATAL,NhlEUNKNOWN,"New: The dimension size list contains missing values, can't determine size");
			return(NhlFATAL);
		}
		if(!(size_md->obj.obj_type_mask & Ncl_MultiDVallongData)) {
			tmp1_md = _NclCoerceData(size_md,Ncl_MultiDVallongData,NULL);
			if(tmp1_md == NULL) {
				NhlPError(NhlFATAL,NhlEUNKNOWN,"New: the dimension size parameter is the wrong type an integer value was expected");
				return(NhlFATAL);
			}
		} else {
			tmp1_md = size_md;
		}
		dim_size_list = (long*)tmp1_md->multidval.val;
		total = 1;
		for(i = 0; i< tmp1_md->multidval.dim_sizes[0]; i++) {
			if(dim_size_list[i] < 1) {	
				NhlPError(NhlFATAL,NhlEUNKNOWN,"New: a zero or negative value has been passed in in the dimension size parameter");
				return(NhlFATAL);
			}
			total *= dim_size_list[i];
			dim_sizes[i] = (int)dim_size_list[i];
		}
		tmp_val = (void*)NclMalloc((unsigned int)total*_NclSizeOf(the_type));
		for(i = 0; i< total*_NclSizeOf(the_type); i+=_NclSizeOf(the_type)) {
			memcpy((void*)&(((char*)tmp_val)[i]),(void*)&missing_val,_NclSizeOf(the_type));
			
		}
		tmp_md = _NclCreateVal(NULL,NULL,the_obj_type,0,tmp_val,&missing_val,tmp1_md->multidval.totalelements,dim_sizes,TEMPORARY,NULL);
		if(tmp1_md != size_md) {
			_NclDestroyObj((NclObj)tmp1_md);
		}
		if(tmp_md != NULL) {
			data.kind = NclStk_VAL;
			data.u.data_obj = tmp_md;
			_NclPush(data);
			return(ret);
		} else{
			NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Could not create new array");
			return(NhlFATAL);
		}
	} else {
		NhlPError(NhlFATAL,NhlEUNKNOWN,"New: Could not create new array");
		return(NhlFATAL);
	}
}


#ifdef __cplusplus
}
#endif
