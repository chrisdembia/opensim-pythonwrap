/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id: FloatDatatypeValidator.cpp,v 1.9 2003/11/12 20:32:03 peiyongz Exp $
 * $Log: FloatDatatypeValidator.cpp,v $
 * Revision 1.9  2003/11/12 20:32:03  peiyongz
 * Statless Grammar: ValidationContext
 *
 * Revision 1.8  2003/11/06 15:30:07  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.7  2003/10/02 19:21:06  peiyongz
 * Implementation of Serialization/Deserialization
 *
 * Revision 1.6  2003/05/18 14:02:07  knoaman
 * Memory manager implementation: pass per instance manager.
 *
 * Revision 1.5  2003/05/16 06:01:57  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.4  2003/05/15 18:53:26  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.3  2002/12/18 14:17:55  gareth
 * Fix to bug #13438. When you eant a vector that calls delete[] on its members you should use RefArrayVectorOf.
 *
 * Revision 1.2  2002/11/04 14:53:28  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:41  peiyongz
 * sane_include
 *
 * Revision 1.6  2001/10/02 18:59:29  peiyongz
 * Invalid_Facet_Tag to display the tag name
 *
 * Revision 1.5  2001/10/01 21:03:55  peiyongz
 * DTV Reorganization:derived from AbstractNumericValidator
 *
 * Revision 1.4  2001/09/20 13:11:42  knoaman
 * Regx  + misc. fixes
 *
 * Revision 1.3  2001/08/21 18:42:53  peiyongz
 * Bugzilla# 2816: cleanUp() declared with external linkage and called
 *                          before defined as inline
 *
 * Revision 1.2  2001/08/15 18:08:44  peiyongz
 * Fix to potential leakage in strEnumeration
 *
 * Revision 1.1  2001/07/26 20:42:16  peiyongz
 * FloatDatatypeValidator
 *
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/datatype/FloatDatatypeValidator.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeFacetException.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeValueException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
FloatDatatypeValidator::FloatDatatypeValidator(MemoryManager* const manager)
:AbstractNumericValidator(0, 0, 0, DatatypeValidator::Float, manager)
{
    setOrdered(XSSimpleTypeDefinition::ORDERED_PARTIAL);
    setBounded(true);
    setFinite(true);
    setNumeric(true);
}

FloatDatatypeValidator::FloatDatatypeValidator(
                          DatatypeValidator*            const baseValidator
                        , RefHashTableOf<KVStringPair>* const facets
                        , RefArrayVectorOf<XMLCh>*      const enums
                        , const int                           finalSet
                        , MemoryManager* const                manager)
:AbstractNumericValidator(baseValidator, facets, finalSet, DatatypeValidator::Float, manager)
{
    init(enums);
}

FloatDatatypeValidator::~FloatDatatypeValidator()
{}

// -----------------------------------------------------------------------
// Compare methods
// -----------------------------------------------------------------------
int FloatDatatypeValidator::compare(const XMLCh* const lValue
                                  , const XMLCh* const rValue)
{
    XMLFloat lObj(lValue, fMemoryManager);
    XMLFloat rObj(rValue, fMemoryManager);

    return compareValues(&lObj, &rObj);
}

DatatypeValidator* FloatDatatypeValidator::newInstance
(
      RefHashTableOf<KVStringPair>* const facets
    , RefArrayVectorOf<XMLCh>* const      enums
    , const int                           finalSet
    , MemoryManager* const                manager
)
{
    return (DatatypeValidator*) new (manager) FloatDatatypeValidator(this, facets, enums, finalSet, manager);
}

// -----------------------------------------------------------------------
// ctor provided to be used by derived classes
// -----------------------------------------------------------------------
FloatDatatypeValidator::FloatDatatypeValidator(DatatypeValidator*            const baseValidator
                                             , RefHashTableOf<KVStringPair>* const facets
                                             , const int                           finalSet
                                             , const ValidatorType                 type
                                             , MemoryManager* const                manager)
:AbstractNumericValidator(baseValidator, facets, finalSet, type, manager)
{
    //do not invoke init here !!!
}

void FloatDatatypeValidator::assignAdditionalFacet(const XMLCh* const key
                                                 , const XMLCh* const)
{
    ThrowXML1(InvalidDatatypeFacetException
            , XMLExcepts::FACET_Invalid_Tag
            , key);
}

void FloatDatatypeValidator::inheritAdditionalFacet()
{}

void FloatDatatypeValidator::checkAdditionalFacetConstraints() const
{}

void FloatDatatypeValidator::checkAdditionalFacetConstraintsBase() const
{}

int  FloatDatatypeValidator::compareValues(const XMLNumber* const lValue
                                         , const XMLNumber* const rValue)
{
    return XMLFloat::compareValues((XMLFloat*) lValue, (XMLFloat*) rValue);
}

void  FloatDatatypeValidator::setMaxInclusive(const XMLCh* const value)
{
    fMaxInclusive = new (fMemoryManager) XMLFloat(value, fMemoryManager);
}

void  FloatDatatypeValidator::setMaxExclusive(const XMLCh* const value)
{
    fMaxExclusive = new (fMemoryManager) XMLFloat(value, fMemoryManager);
}

void  FloatDatatypeValidator::setMinInclusive(const XMLCh* const value)
{
    fMinInclusive = new (fMemoryManager) XMLFloat(value, fMemoryManager);
}

void  FloatDatatypeValidator::setMinExclusive(const XMLCh* const value)
{
    fMinExclusive = new (fMemoryManager) XMLFloat(value, fMemoryManager);
}

void  FloatDatatypeValidator::setEnumeration()
{
    // check 4.3.5.c0 must: enumeration values from the value space of base
    //
    // 1. shall be from base value space
    // 2. shall be from current value space as well ( shall go through boundsCheck() )
    //
    if (!fStrEnumeration)
        return;

    int i = 0;
    int enumLength = fStrEnumeration->size();

    FloatDatatypeValidator *numBase = (FloatDatatypeValidator*) getBaseValidator();
    if (numBase)
    {
        try
        {
            for ( i = 0; i < enumLength; i++)
            {
                numBase->checkContent(fStrEnumeration->elementAt(i), (ValidationContext*)0, false);
            }
        }
        catch (XMLException&)
        {
            ThrowXML1(InvalidDatatypeFacetException
                , XMLExcepts::FACET_enum_base
                , fStrEnumeration->elementAt(i));

        }
    }

    // We put the this->checkContent in a separate loop
    // to not block original message with in that method.
    //
    for ( i = 0; i < enumLength; i++)
    {
        checkContent(fStrEnumeration->elementAt(i), (ValidationContext*)0, false);
    }

    fEnumeration = new (fMemoryManager) RefVectorOf<XMLNumber>(enumLength, true,  fMemoryManager);
    fEnumerationInherited = false;

    for ( i = 0; i < enumLength; i++)
    {
        fEnumeration->insertElementAt(new (fMemoryManager) XMLFloat(fStrEnumeration->elementAt(i), fMemoryManager), i);
    }
}

// -----------------------------------------------------------------------
// Abstract interface from AbstractNumericValidator
// -----------------------------------------------------------------------
void FloatDatatypeValidator::checkContent(const XMLCh*             const content
                                         ,      ValidationContext* const context
                                         ,      bool                     asBase)
{

    //validate against base validator if any
    FloatDatatypeValidator *pBase = (FloatDatatypeValidator*) this->getBaseValidator();
    if (pBase)
        pBase->checkContent(content, context, true);

    // we check pattern first
    if ( (getFacetsDefined() & DatatypeValidator::FACET_PATTERN ) != 0 )
    {
        // lazy construction
        if (getRegex() ==0) {
            try {
                setRegex(new (fMemoryManager) RegularExpression(getPattern(), SchemaSymbols::fgRegEx_XOption, fMemoryManager));
            }
            catch (XMLException &e)
            {
                ThrowXML1(InvalidDatatypeValueException, XMLExcepts::RethrowError, e.getMessage());
            }
        }

        if (getRegex()->matches(content) ==false)
        {
            ThrowXML2(InvalidDatatypeValueException
                    , XMLExcepts::VALUE_NotMatch_Pattern
                    , content
                    , getPattern());
        }
    }

    // if this is a base validator, we only need to check pattern facet
    // all other facet were inherited by the derived type
    if (asBase)
        return;

    try {
        XMLFloat theValue(content, fMemoryManager);
        XMLFloat *theData = &theValue;

        if (getEnumeration() != 0)
        {
            int i=0;
            int enumLength = getEnumeration()->size();
            for ( ; i < enumLength; i++)
            {
                if (compareValues(theData, (XMLFloat*) getEnumeration()->elementAt(i))==0)
                    break;
            }

            if (i == enumLength)
                ThrowXML1(InvalidDatatypeValueException, XMLExcepts::VALUE_NotIn_Enumeration, content);
        }

        boundsCheck(theData);
    }
    catch (XMLException &e)
    {
       ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::RethrowError, e.getMessage());
    }

}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_TOCREATE(FloatDatatypeValidator)

void FloatDatatypeValidator::serialize(XSerializeEngine& serEng)
{
    /***
     * Note: 
     *
     *     During storing, we need write the specific number
     *     type info before calling base::serialize().
     *
     *     While loading, we do nothing here
     ***/

    if (serEng.isStoring())
    {
        serEng<<(int) (XMLNumber::Float);
    }

    AbstractNumericValidator::serialize(serEng);

}

XERCES_CPP_NAMESPACE_END

/**
  * End of file FloatDatatypeValidator::cpp
  */
