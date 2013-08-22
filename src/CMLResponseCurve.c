
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLInternal.h"


CMLHIDDEN CMLResponseCurve* cmlCreateResponseCurve(CMLResponseCurve* curve){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  curve->forwardfunc = NULL;
  curve->backwardfunc = NULL;
  return curve;
}


CMLAPI CMLResponseCurve* cmlCreateResponseCurveCopy(CMLResponseCurve* dstcurve, CMLResponseCurve* srccurve){
  if(!dstcurve){dstcurve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  dstcurve->forwardfunc = CMLduplicateFunction(srccurve->forwardfunc);
  dstcurve->backwardfunc = CMLduplicateFunction(srccurve->backwardfunc);
  dstcurve->functiontype = srccurve->functiontype;
  return dstcurve;
}


CMLAPI CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                        CMLResponseCurve* curve,
                                   CMLResponseCurvePreset preset){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
//  curve->type = type;
//  curve->param0 = param0;
//  curve->param1 = param1;
//  curve->param2 = param2;
//  curve->param3 = param3;

//  cmlReleaseFunction(curve->func);
//  cmlReleaseFunction(curve->invfunc);

  switch(preset){
  case CML_RESPONSE_LINEAR:
    curve->forwardfunc  = CMLcreateLinearResponse();
    curve->backwardfunc = CMLcreateLinearResponse();
    curve->functiontype = CML_FUNCTION_LINEAR;
    break;
  case CML_RESPONSE_SQRT:
    curve->forwardfunc  = CMLcreateGammaResponse(.5f); // todo: create functions
    curve->backwardfunc = CMLcreateGammaResponse(2.f); // for that.
    curve->functiontype = CML_FUNCTION_SQRT;
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    curve->forwardfunc  = CMLcreateGammaResponse(cmlInverse(2.f + 51.f / 256.f));
    curve->backwardfunc = CMLcreateGammaResponse(2.f + 51.f / 256.f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_8:
    curve->forwardfunc  = CMLcreateGammaResponse(cmlInverse(1.8f));
    curve->backwardfunc = CMLcreateGammaResponse(1.8f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_9:
    curve->forwardfunc  = CMLcreateGammaResponse(cmlInverse(1.9f));
    curve->backwardfunc = CMLcreateGammaResponse(1.9f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_2_2:
    curve->forwardfunc  = CMLcreateGammaResponse(cmlInverse(2.2f));
    curve->backwardfunc = CMLcreateGammaResponse(2.2f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    curve->forwardfunc  = CMLcreateGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->backwardfunc = CMLcreateInverseGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    curve->forwardfunc  = CMLcreateGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->backwardfunc = CMLcreateInverseGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_SRGB:
    curve->forwardfunc  = CMLcreateXYZTosRGBResponse();
    curve->backwardfunc = CMLcreatesRGBToXYZResponse();
    curve->functiontype = CML_FUNCTION_SRGB;
    break;
  case CML_RESPONSE_LSTAR:
    curve->forwardfunc  = CMLcreateYToLStarResponse();
    curve->backwardfunc = CMLcreateLStarToYResponse();
    curve->functiontype = CML_FUNCTION_LSTAR;
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    curve->forwardfunc  = CMLcreateYToLStarStandardResponse();
    curve->backwardfunc = CMLcreateLStarToYStandardResponse();
    curve->functiontype = CML_FUNCTION_LSTAR_STANDARD;
    break;
  default:
    #ifndef NDEBUG
      curve->forwardfunc  = CMLcreateLinearResponse();
      curve->backwardfunc = CMLcreateLinearResponse();
      cmlError("cmlCreateResponseCurveWithPreset", "Response preset unknown.");
    #endif
    break;
  }

  return curve;
}

CMLAPI CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                         CMLResponseCurve* curve,
//                                           CMLFunctionType type,
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
  curve->forwardfunc  = CMLcreateGammaLinearResponse(param0, param1, param2, param3);
  curve->backwardfunc = CMLcreateInverseGammaLinearResponse(param0, param1, param2, param3);
  return curve;
}



CMLAPI void CMLclearResponseCurve(CMLResponseCurve* curve){
  cmlReleaseFunction(curve->backwardfunc);
  cmlReleaseFunction(curve->forwardfunc);
}

CMLAPI void CMLdestroyResponseCurve(CMLResponseCurve* curve){
  CMLclearResponseCurve(curve);
  free(curve);
}



CMLAPI CMLFunction* CMLgetResponseCurveFunc(const CMLResponseCurve* curve){
  return curve->backwardfunc;
}
CMLAPI CMLFunction* CMLgetResponseCurveInvFunc(const CMLResponseCurve* curve){
  return curve->forwardfunc;
}
//CMLAPI CMLFunctionType CMLgetResponseCurveFunctionType(const CMLResponseCurve* curve){
//  return curve->type;
//}
CMLAPI float CMLgetResponseCurveParam0(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 2.0f; break;
  case CML_FUNCTION_GAMMA: return CMLgetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_GAMMA_LINEAR: return CMLgetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_SRGB: return 2.4f; break;
  case CML_FUNCTION_LSTAR: return 3.0f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 3.0f; break;
  default:
    #ifndef NDEBUG
      cmlError("CMLgetResponseCurveParam0", "Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CMLAPI float CMLgetResponseCurveParam1(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 0.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return CMLgetFunctionParameter(curve->backwardfunc, 1); break;
  case CML_FUNCTION_SRGB: return 0.055f; break;
  case CML_FUNCTION_LSTAR: return 0.16f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.16f; break;
  default:
    #ifndef NDEBUG
      cmlError("CMLgetResponseCurveParam1", "Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}
CMLAPI float CMLgetResponseCurveParam2(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 1.0f; break;
  case CML_FUNCTION_GAMMA: return 1.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return CMLgetFunctionParameter(curve->backwardfunc, 2); break;
  case CML_FUNCTION_SRGB: return 12.92f; break;
  case CML_FUNCTION_LSTAR: return 9.03296296296296296f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 9.033f; break;
  default:
    #ifndef NDEBUG
      cmlError("CMLgetResponseCurveParam2", "Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CMLAPI float CMLgetResponseCurveParam3(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return CMLgetFunctionParameter(curve->backwardfunc, 3); break;
  case CML_FUNCTION_SRGB: return 0.0031306684425f; break;
  case CML_FUNCTION_LSTAR: return 0.008856451679036f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.008856f; break;
  default:
    #ifndef NDEBUG
      cmlError("CMLgetResponseCurveParam3", "Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}

