/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ModelMockup
 *
 */
#ifndef MODELMOCKUP_H
#define MODELMOCKUP_H

// Includes:
#include <string>

class ModelMockup
{
public:
    ModelMockup(): m_sValue(""){}
    //~ModelMockup(){}

    // Getters:
    std::string value(){return m_sValue;}
    // Setters:
    void setValue(std::string sValue){m_sValue = sValue;}
    // Methods:

private:
    // Methods:

    // Members:
    std::string m_sValue;

};

#endif // MODELMOCKUP_H
