
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_HDEF static const CMLIlluminationType rgbSpaceIlluminations[CML_RGB_COUNT] = {
  CML_ILLUMINATION_D65,     // CML_RGB_ADOBE_98
  CML_ILLUMINATION_D65,     // CML_RGB_APPLE
  CML_ILLUMINATION_D50,     // CML_RGB_BEST
  CML_ILLUMINATION_D50,     // CML_RGB_BETA
  CML_ILLUMINATION_D65,     // CML_RGB_BRUCE
  CML_ILLUMINATION_E,       // CML_RGB_CIE
  CML_ILLUMINATION_D50,     // CML_RGB_COLORMATCH
  CML_ILLUMINATION_D50,     // CML_RGB_DON4
  CML_ILLUMINATION_D50,     // CML_RGB_EBU_MONITOR
  CML_ILLUMINATION_D50,     // CML_RGB_ECI
  CML_ILLUMINATION_D50,     // CML_RGB_EKTA_SPACE_PS5
  CML_ILLUMINATION_D65,     // CML_RGB_HDTV
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_601_525
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_601_625
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_709
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_2020
  CML_ILLUMINATION_D50,     // CML_RGB_KODAK_DC
  CML_ILLUMINATION_C,       // CML_RGB_NTSC_53
  CML_ILLUMINATION_D65,     // CML_RGB_PAL_SECAM_EBU
  CML_ILLUMINATION_D50,     // CML_RGB_ROMM_PROPHOTO
  CML_ILLUMINATION_D65,     // CML_RGB_SMPTE_C
  CML_ILLUMINATION_D65,     // CML_RGB_SRGB
  CML_ILLUMINATION_D50,     // CML_RGB_WIDE_GAMUT
  CML_ILLUMINATION_D65,     // CML_RGB_CUSTOM
};

CML_HDEF static const CMLResponseCurveType rgbSpaceResponseTypes[CML_RGB_COUNT] = {
  CML_RESPONSE_GAMMA_ADOBE_98,             // CML_RGB_ADOBE_98
  CML_RESPONSE_GAMMA_1_8,                  // CML_RGB_APPLE
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_BEST
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_BETA
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_BRUCE
  CML_RESPONSE_LINEAR,                     // CML_RGB_CIE
  CML_RESPONSE_GAMMA_1_8,                  // CML_RGB_COLORMATCH
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_DON4
  CML_RESPONSE_GAMMA_1_9,                  // CML_RGB_EBU_MONITOR
  CML_RESPONSE_GAMMA_1_8,                  // CML_RGB_ECI
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_EKTA_SPACE_PS5
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_HDTV
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,  // CML_RGB_REC_BT_601_525
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,  // CML_RGB_REC_BT_601_625
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,  // CML_RGB_REC_BT_709
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT,  // CML_RGB_REC_BT_2020
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_KODAK_DC
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_NTSC_53
  CML_RESPONSE_SRGB,                       // CML_RGB_PAL_SECAM_EBU
  CML_RESPONSE_GAMMA_1_8,                  // CML_RGB_ROMM_PROPHOTO
  CML_RESPONSE_SRGB,                       // CML_RGB_SMPTE_C
  CML_RESPONSE_SRGB,                       // CML_RGB_SRGB
  CML_RESPONSE_GAMMA_2_2,                  // CML_RGB_WIDE_GAMUT
  CML_RESPONSE_UNDEFINED,                  // CML_RGB_CUSTOM
};

// array ordering: {xr, yr, xg, yg, xb, yb}
CML_HDEF static const float rgbSpaceprimaries[CML_RGB_COUNT][6] = {
  {0.6400f,   0.3300f,   0.2100f,   0.7100f,   0.1500f,   0.0600f},   // CML_RGB_ADOBE_98
  {0.6250f,   0.3400f,   0.2800f,   0.5950f,   0.1550f,   0.0700f},   // CML_RGB_APPLE
  {0.7347f,   0.2653f,   0.2150f,   0.7750f,   0.1300f,   0.0350f},   // CML_RGB_BEST
  {0.6888f,   0.3112f,   0.1986f,   0.7551f,   0.1265f,   0.0352f},   // CML_RGB_BETA
  {0.6400f,   0.3300f,   0.2800f,   0.6500f,   0.1500f,   0.0600f},   // CML_RGB_BRUCE
  {0.734690f, 0.265310f, 0.272958f, 0.718062f, 0.166446f, 0.008964f}, // CML_RGB_CIE
  {0.6300f,   0.3400f,   0.2950f,   0.6050f,   0.1500f,   0.0750f},   // CML_RGB_COLORMATCH
  {0.6960f,   0.3000f,   0.2150f,   0.7650f,   0.1300f,   0.0350f},   // CML_RGB_DON4
  {0.6314f,   0.3391f,   0.2809f,   0.5971f,   0.1487f,   0.0645f},   // CML_RGB_EBU_MONITOR
  {0.6700f,   0.3300f,   0.2100f,   0.7100f,   0.1400f,   0.0800f},   // CML_RGB_ECI
  {0.6950f,   0.3050f,   0.2600f,   0.7000f,   0.1100f,   0.0050f},   // CML_RGB_EKTA_SPACE_PS5
  {0.6400f,   0.3300f,   0.3297f,   0.6593f,   0.1500f,   0.0600f},   // CML_RGB_HDTV
  {0.6300f,   0.3400f,   0.3100f,   0.5950f,   0.1550f,   0.0700f},   // CML_RGB_REC_BT_601_525
  {0.6400f,   0.3300f,   0.2900f,   0.6000f,   0.1500f,   0.0600f},   // CML_RGB_REC_BT_601_625
  {0.6400f,   0.3300f,   0.3000f,   0.6000f,   0.1500f,   0.0600f},   // CML_RGB_REC_BT_709
  {0.7080f,   0.2920f,   0.1700f,   0.7970f,   0.1310f,   0.0460f},   // CML_RGB_REC_BT_2020
  {0.6492f,   0.3314f,   0.3219f,   0.5997f,   0.1548f,   0.0646f},   // CML_RGB_KODAK_DC
  {0.6700f,   0.3300f,   0.2100f,   0.7100f,   0.1400f,   0.0800f},   // CML_RGB_NTSC_53
  {0.6400f,   0.3300f,   0.2900f,   0.6000f,   0.1500f,   0.0600f},   // CML_RGB_PAL_SECAM_EBU
  {0.7347f,   0.2653f,   0.1596f,   0.8404f,   0.0366f,   0.0001f},   // CML_RGB_ROMM_PROPHOTO
  {0.6300f,   0.3400f,   0.3100f,   0.5950f,   0.1550f,   0.0700f},   // CML_RGB_SMPTE_C
  {0.6400f,   0.3300f,   0.3000f,   0.6000f,   0.1500f,   0.0600f},   // CML_RGB_SRGB
  {0.734690f, 0.265310f, 0.114161f, 0.826207f, 0.156641f, 0.017705f}, // CML_RGB_WIDE_GAMUT
  {0.6400f,   0.3300f,   0.3000f,   0.6000f,   0.1500f,   0.0600f}    // CML_RGB_CUSTOM
};



CML_HDEF void cml_recomputeRGBResponses(CMLColorMachine* cm){
  if(cm->recomputationLockCount){cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES; return;}
  
  if(cm->rgbSpace.type != CML_RGB_CUSTOM){
    CMLResponseCurve responseR;
    CMLResponseCurve responseG;
    CMLResponseCurve responseB;
    cmlInitResponseCurveWithType(&responseR, rgbSpaceResponseTypes[cm->rgbSpace.type]);
    cmlInitResponseCurveWithType(&responseG, rgbSpaceResponseTypes[cm->rgbSpace.type]);
    cmlInitResponseCurveWithType(&responseB, rgbSpaceResponseTypes[cm->rgbSpace.type]);
    cmlSetResponseR(cm, &responseR);
    cmlSetResponseG(cm, &responseG);
    cmlSetResponseB(cm, &responseB);
    cmlClearResponseCurve(&responseR);
    cmlClearResponseCurve(&responseG);
    cmlClearResponseCurve(&responseB);
  }
}



CML_HDEF void cml_recomputeRGBColorSpace(CMLColorMachine* cm){
  if(cm->recomputationLockCount){cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_RGB; return;}

  if(cmlGetReferenceIlluminationType(cm) != rgbSpaceIlluminations[cm->rgbSpace.type]){
    cm->rgbSpace.type = CML_RGB_CUSTOM;
  }

  CMLVec3 normedWhitePointYxy;
  cmlCpy3(normedWhitePointYxy, cmlGetReferenceWhitePointYxy(cm));
//  if(!cm->observer.radiometric){
//    normedWhitePointYxy[0] = 1.f;
//  }
  
  cmlFillRGBToXYZMatrix(cm->rgbSpace.matrix, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[1], cm->rgbSpace.primariesYxy[2], normedWhitePointYxy);
  cmlInvertMat33(cm->rgbSpace.matrixInv, cm->rgbSpace.matrix);
  
  cml_recomputeRGBResponses(cm);
}



CML_DEF CMLRGBColorSpaceType cmlGetRGBColorSpaceType(const CMLColorMachine* cm){
  return cm->rgbSpace.type;
}


CML_DEF void cmlSetRGBColorSpaceType(CMLColorMachine* cm, CMLRGBColorSpaceType type){
  // Multiple changes need to be made. (Illumination and RGBSpace)
  cmlLockRecomputation(cm);
  
  cm->rgbSpace.type = type;
  if(cm->rgbSpace.type != CML_RGB_CUSTOM){
    cmlGetRGBColorSpacePrimaries(type, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[1], cm->rgbSpace.primariesYxy[2]);
    cmlSetIlluminationType(cm, rgbSpaceIlluminations[cm->rgbSpace.type]);
  }
  cml_recomputeRGBColorSpace(cm);
  
  cmlReleaseRecomputation(cm);
}


CML_DEF void cmlGetRGBPrimariesYxy(const CMLColorMachine* cm, CMLVec3 primaries[3]){
  cmlCpy3(primaries[0], cm->rgbSpace.primariesYxy[0]);
  cmlCpy3(primaries[1], cm->rgbSpace.primariesYxy[1]);
  cmlCpy3(primaries[2], cm->rgbSpace.primariesYxy[2]);
}


CML_DEF void cmlSetRGBPrimariesYxy(CMLColorMachine* cm, CMLVec3 primaries[3]){
  cm->rgbSpace.type = CML_RGB_CUSTOM;
  cm->rgbSpace.primariesYxy[0][1] = primaries[0][1];
  cm->rgbSpace.primariesYxy[0][2] = primaries[0][2];
  cm->rgbSpace.primariesYxy[1][1] = primaries[1][1];
  cm->rgbSpace.primariesYxy[1][2] = primaries[1][2];
  cm->rgbSpace.primariesYxy[2][1] = primaries[2][1];
  cm->rgbSpace.primariesYxy[2][2] = primaries[2][2];
  cml_recomputeRGBColorSpace(cm);
}



CML_DEF void cmlSetResponseRGB(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlSetResponseR(cm, response);
  cmlSetResponseG(cm, response);
  cmlSetResponseB(cm, response);
}

CML_DEF void cmlSetCustomGammaLinearParametersRGB(CMLColorMachine* cm, const GammaLinearInputParameters* parameters){
  cm->rgbSpace.customParametersR = *parameters;
  cm->rgbSpace.customParametersG = *parameters;
  cm->rgbSpace.customParametersB = *parameters;
}

CML_DEF const CMLResponseCurve* cmlGetResponseR(CMLColorMachine* cm){
  return &(cm->rgbSpace.responseR);
}
CML_DEF const CMLResponseCurve* cmlGetResponseG(CMLColorMachine* cm){
  return &(cm->rgbSpace.responseG);
}
CML_DEF const CMLResponseCurve* cmlGetResponseB(CMLColorMachine* cm){
  return &(cm->rgbSpace.responseB);
}

CML_DEF const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersR(const CMLColorMachine* cm){
  return &cm->rgbSpace.customParametersR;
}

CML_DEF const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersG(const CMLColorMachine* cm){
  return &cm->rgbSpace.customParametersG;
}

CML_DEF const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersB(const CMLColorMachine* cm){
  return &cm->rgbSpace.customParametersB;
}

CML_DEF void cmlSetResponseR(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlClearResponseCurve(&(cm->rgbSpace.responseR));
  cmlInitResponseCurveWithCopy((&cm->rgbSpace.responseR), response);
}


CML_DEF void cmlSetResponseG(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlClearResponseCurve(&(cm->rgbSpace.responseG));
  cmlInitResponseCurveWithCopy((&cm->rgbSpace.responseG), response);
}


CML_DEF void cmlSetResponseB(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlClearResponseCurve(&(cm->rgbSpace.responseB));
  cmlInitResponseCurveWithCopy((&cm->rgbSpace.responseB), response);
}



CML_DEF uint8 cmlGetRGBLUTSize(const CMLColorMachine* cm){
  return cm->rgbSpace.lutSize;
}


CML_DEF void cmlSetRGBLUTSize(CMLColorMachine* cm, uint8 bits){
  if((bits < 1) || (bits > 16)){bits = 32;}
  cm->rgbSpace.lutSize = bits;
  cml_recomputeRGBResponses(cm);
}


CML_DEF void cmlGetRGBColorSpacePrimaries(CMLRGBColorSpaceType type, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy){
  if(type < CML_RGB_CUSTOM){
    primaryRYxy[0] = 1.f;
    primaryRYxy[1]  = rgbSpaceprimaries[type][0];
    primaryRYxy[2]  = rgbSpaceprimaries[type][1];
    primaryGYxy[0] = 1.f;
    primaryGYxy[1]  = rgbSpaceprimaries[type][2];
    primaryGYxy[2]  = rgbSpaceprimaries[type][3];
    primaryBYxy[0] = 1.f;
    primaryBYxy[1]  = rgbSpaceprimaries[type][4];
    primaryBYxy[2]  = rgbSpaceprimaries[type][5];
  }else{
    #if CML_DEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
  }
}


CML_DEF CMLIlluminationType cmlGetRGBColorSpaceIlluminationType(CMLRGBColorSpaceType type){
  if(type < CML_RGB_CUSTOM){
    return rgbSpaceIlluminations[type];
  }else{
    #if CML_DEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
    return CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  }
}

CML_DEF CMLResponseCurveType cmlGetRGBColorSpaceResponseCurveType(CMLRGBColorSpaceType type){
  if(type < CML_RGB_CUSTOM){
    return rgbSpaceResponseTypes[type];
  }else{
    #if CML_DEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
    return CML_RESPONSE_LINEAR;
  }
}

CML_DEF void cmlFillRGBToXYZMatrix(CMLMat33 rgbToXyzMatrix, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy, const CMLVec3 whitePointYxy){
  CMLVec3 redXYZ;
  CMLVec3 greenXYZ;
  CMLVec3 blueXYZ;

  float xr = primaryRYxy[1];
  float yr = primaryRYxy[2];
  float xg = primaryGYxy[1];
  float yg = primaryGYxy[2];
  float xb = primaryBYxy[1];
  float yb = primaryBYxy[2];
  float Yw = whitePointYxy[0];
  float xw = whitePointYxy[1];
  float yw = whitePointYxy[2];

  // Computation of the matrix
  float ybxg = yb*xg;
  float ygxb = yg*xb;
  float yrxb = yr*xb;
  float xryb = xr*yb;
  float yrxg = yr*xg;
  float xryg = xr*yg;
  float diff1 = ybxg-ygxb;
  float diff2 = xryb-yrxb;
  float diff3 = xryg-yrxg;
  float div1 = diff3-diff2+diff1;
  float zw = 1.f - xw - yw;
  float div2 = div1 * yw;
  
  primaryRYxy[0] = Yw * yr*(+(yg-yb+diff1)*xw/div2+(xb-xg+diff1)/div1+diff1*zw/div2);
  primaryGYxy[0] = Yw * yg*(-(yr-yb+diff2)*xw/div2-(xb-xr+diff2)/div1-diff2*zw/div2);
  primaryBYxy[0] = Yw * yb*(+(yr-yg+diff3)*xw/div2+(xg-xr+diff3)/div1+diff3*zw/div2);

  // todo: can the whitePoint be used?
  cml_YxyToXYZ(redXYZ, primaryRYxy, CML_NULL, 1);
  cml_YxyToXYZ(greenXYZ, primaryGYxy, CML_NULL, 1);
  cml_YxyToXYZ(blueXYZ, primaryBYxy, CML_NULL, 1);

  cmlSetMat33Vec3(rgbToXyzMatrix, redXYZ, greenXYZ, blueXYZ);
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>
