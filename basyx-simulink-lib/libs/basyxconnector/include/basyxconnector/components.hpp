#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

/**
 * @file components.hpp
 * @author @MateusMolina
 * @brief containers for AAS, Submodel and SubmodelElements 
 * @version 0.1
 * 
 */

#include<urlhandler/urlHandler.hpp>
#include<string>

using std::string;

struct Aas{
    Url aasUrl;
    string aasId;

    Aas() = delete;
    Aas(Url aasUrl, string aasId) : aasUrl(aasUrl), aasId(aasId) {};
};

struct Submodel{
    Aas aas;
    string submodelIdShort;

    Submodel() = delete;
    Submodel(Aas &aas, string submodelIdshort) : aas(aas), submodelIdShort(submodelIdshort)  {}
};

struct SubmodelElement{
    private:
        string currentValue;
    public:
        Submodel submodel;
        string seIdShort;

        SubmodelElement() = delete;
        SubmodelElement(Submodel &sm, string seIdShort) : submodel(sm), seIdShort(seIdShort) {}
       
        void updateValue(string newValue) {currentValue=newValue;}
        string getValue(string newValue) {return currentValue;}
};


#endif // __COMPONENTS_H__