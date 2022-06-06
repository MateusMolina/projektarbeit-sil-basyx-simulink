
#define S_FUNCTION_NAME  PropertySAConnectorBlock
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

#include <cstdio>
#include <string>
#include <memory>
#include <urlhandler/urlHandler.hpp>
#include <httpclient/curlHttpConnection.hpp>
#include <basyxconnector/components.hpp>
#include <basyxconnector/registryServerConnector.hpp>
#include <basyxconnector/aasServerConnector.hpp>

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
    ssSetNumSFcnParams(S, 4);  /* Number of expected parameters */
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
    ssSetNumPWork(S, 0);
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
    ssSetSampleTime(S, 0, 1.0);
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

std::unique_ptr<RegistryServerConnector> regCon;
std::unique_ptr<AasServerConnector> aasCon;
std::unique_ptr<CurlHttpConnection> httpCon;
std::unique_ptr<Aas> aas_;
std::unique_ptr<Submodel> sm_;
std::unique_ptr<SubmodelElement> se_;
//  typedef HRESULT(CALLBACK* proc_api_init)(std::string);
//  typedef HRESULT(CALLBACK* proc_call_api)(double&, double&);
//  HINSTANCE hDLL;               // Handle to DLL
//  HINSTANCE altDLL;
//  proc_api_init api_init;    // Function pointer
//  proc_call_api callAPI;    // Function pointer


static string getPar(SimStruct *S, int n){
  return std::string(mxArrayToString(ssGetSFcnParam(S,n)));
}

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
	  //Parameter #1: API web address
	  // const mxArray* pArrayValue = ssGetSFcnParam(S, 0);
	  // const char* apiCharArray = mxArrayToString(pArrayValue);
	  // std::string apiAddress(apiCharArray);

	  // //Dynamically load DLL files required for REST client
	  // altDLL = LoadLibrary("include\\cpprest_2_10.dll");
	  // hDLL = LoadLibrary("include\\example_api.dll");
    //   if (hDLL) {
		//   api_init = (proc_api_init)GetProcAddress(hDLL, "initializeAPI");
		//   callAPI = (proc_call_api)GetProcAddress(hDLL, "callAPI");

		//   if (api_init) {
		// 	  api_init(apiAddress);
		//   }
	  // }
	  // else {
		//   api_init = NULL;
		//   callAPI = NULL;
	  // }
    string regUrlStr, aasId, smIdShort, seIdShort;
    regUrlStr = getPar(S,0);
    aasId = getPar(S,1);
    smIdShort = getPar(S,2);
    seIdShort = getPar(S,3);
    try{
      Url urlStr = Url(regUrlStr);
      httpCon = std::make_unique<CurlHttpConnection>();
      regCon = std::make_unique<RegistryServerConnector>(std::move(urlStr), *httpCon);
      aas_ =  std::make_unique<Aas>(regCon->fetchAAS(aasId));
      aasCon = std::make_unique<AasServerConnector>(*aas_, *httpCon);
      sm_ = std::make_unique<Submodel>(*aas_,smIdShort);
      se_ = std::make_unique<SubmodelElement>(*sm_,seIdShort);
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
}



#define MDL_UPDATE  /* Change to #undef to remove function */
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
    double inputValue;
    double outputValue;
    double       *y = ssGetOutputPortRealSignal(S,0);
	  const double* u = (const double*)ssGetInputPortRealSignal(S, 0);
	  inputValue = u[0];

	  //Call web API each time step, if it's available
	  // if ssIsSampleHit(S, 0, tid) {
		//   if (callAPI) {
		// 	  callAPI(inputValue, outputValue);
		//   }
		//   else {
		// 	  outputValue = 0.0;
		//   }
	  // }


    aasCon->updateSeValue(*se_,std::to_string(u[0])); 

    outputValue = std::stod(aasCon->getSeValue(*se_));

    y[0] = outputValue;
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
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
  //   FreeLibrary(hDLL);
	// FreeLibrary(altDLL);
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
