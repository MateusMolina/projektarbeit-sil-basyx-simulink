
#define S_FUNCTION_NAME  PropertySAConnectorBlock
#define S_FUNCTION_LEVEL 2

// List of parameters
#define PAR_BM          0
#define PAR_SR          1
#define PAR_REGURLSTR   2
#define PAR_AASURLSTR   3
#define PAR_AASID       4
#define PAR_SMIDSHORT   5
#define PAR_SEIDSHORT   6
#define PAR_COUNT       7       // Number of parameters

// List of PVectors
#define P_AAS           0
#define P_SM            1
#define P_SE            2

#include "simstruc.h"

#include <cstdio>
#include <string>
#include <memory>
#include <urlhandler/urlHandler.hpp>
#include <httpclient/curlHttpConnection.hpp>
#include <basyxconnector/components.hpp>
#include <basyxconnector/registryServerConnector.hpp>
#include <basyxconnector/aasServerConnector.hpp>


std::unique_ptr<CurlHttpConnection> httpCon;

// Common Methods
// Def
static string getStrPar(SimStruct *S, int n){
  return std::string(mxArrayToString(ssGetSFcnParam(S,n)));
}

static double getNumPar(SimStruct *S, int n){
  return *mxGetPr(ssGetSFcnParam(S,n));
}

static void updateSE(SimStruct *S, double inputValue){
  Aas* aas = (Aas*) ssGetPWorkValue(S,P_AAS);
  SubmodelElement* se =(SubmodelElement*) ssGetPWorkValue(S,P_SE);
  AasServerConnector aasCon = AasServerConnector(*aas, *httpCon);
  aasCon.updateSeValue(*se,std::to_string(inputValue)); 
}

static double readSE(SimStruct *S){
  Aas* aas = (Aas*) ssGetPWorkValue(S,P_AAS);
  SubmodelElement* se =(SubmodelElement*) ssGetPWorkValue(S,P_SE);
  AasServerConnector aasCon = AasServerConnector(*aas, *httpCon);
  return  std::stod(aasCon.getSeValue(*se));
}

static void initializePVectors(SimStruct *S){
  string regUrlStr, aasUrlStr, aasId, smIdShort, seIdShort;
  regUrlStr = getStrPar(S,PAR_REGURLSTR);
  aasUrlStr = getStrPar(S,PAR_AASURLSTR);
  aasId = getStrPar(S,PAR_AASID);
  smIdShort = getStrPar(S,PAR_SMIDSHORT);
  seIdShort = getStrPar(S,PAR_SEIDSHORT);

  // Create AAS based on whether user has provided an AasUrlStr or not
  Aas* aas;
  if(aasUrlStr == ""){
    Url urlStr = Url(regUrlStr);
    RegistryServerConnector regCon = RegistryServerConnector(std::move(urlStr), *httpCon);
    aas = new Aas(regCon.fetchAAS(aasId));
  }else{
    Url urlStr= Url(aasUrlStr);
    aas = new Aas(urlStr, aasId);
  }

  Submodel* sm = new Submodel(*aas,smIdShort);
  SubmodelElement* se = new SubmodelElement(*sm,seIdShort);

  void **PWork = ssGetPWork(S);
  PWork[P_AAS] = aas;
  PWork[P_SM] = sm;
  PWork[P_SE] = se;
}

static double getLocalSeValue(SimStruct *S){
  SubmodelElement* se =(SubmodelElement*) ssGetPWorkValue(S,P_SE);
  return std::stod(se->getValue());
}

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, PAR_COUNT);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 4);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the operating point save/restore compliance to be same as a 
     * built-in block */
    ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, getNumPar(S, PAR_SR));
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
  }
#endif /* MDL_INITIALIZE_CONDITIONS */


#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */


  // TODO Make it work when providing directly the URL for the AAS
  static void mdlStart(SimStruct *S)
  {
    try{
      httpCon = std::make_unique<CurlHttpConnection>();
      initializePVectors(S);
      // Case snapshot mode
      if(getNumPar(S,PAR_BM)==0){
        readSE(S);
      } 
    }catch (const std::exception& e){
      ssSetErrorStatus(S,e.what());
      return;
    }
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{   
  
  const double* u = (const double*)ssGetInputPortRealSignal(S, 0);
  double       *y = ssGetOutputPortRealSignal(S,0);
  try{
    // Case snapshot mode
    if(getNumPar(S,PAR_BM)==0){
      y[0] = getLocalSeValue(S);
    }// case real-time mode
    else{ 
      if (ssGetInputPortConnected(S,0)) updateSE(S,u[0]);      
      if (ssGetOutputPortConnected(S,0)) y[0] = readSE(S);
    }
  }catch (const std::exception& e){
      ssSetErrorStatus(S,e.what());
      return;
  }
}

#undef MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {

  }
#endif /* MDL_UPDATE */



#undef MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
  // Case snapshot mode
  try{
    if(getNumPar(S,PAR_BM)==0){
      const double* u = (const double*)ssGetInputPortRealSignal(S, 0);
      if (ssGetInputPortConnected(S,0)) updateSE(S,u[0]);
    }
  }catch (const std::exception& e){
      ssSetErrorStatus(S,e.what());
      return;
  }
  if (ssGetPWork(S) != NULL) {
    SubmodelElement *se;
    se = (SubmodelElement *) ssGetPWorkValue(S,P_SE);
    if (se != NULL) {
      delete se;
    }
    ssSetPWorkValue(S,P_SE,NULL);

    Submodel *sm;
    sm = (Submodel *) ssGetPWorkValue(S,P_SM);
    if (sm != NULL) {
      delete sm;
    }
    ssSetPWorkValue(S,P_SM,NULL);

    Aas *aas;
    aas = (Aas *) ssGetPWorkValue(S,P_AAS);
    if (aas != NULL) {
      delete aas;
    }
    ssSetPWorkValue(S,P_AAS,NULL);
  }

  delete httpCon.release();
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
