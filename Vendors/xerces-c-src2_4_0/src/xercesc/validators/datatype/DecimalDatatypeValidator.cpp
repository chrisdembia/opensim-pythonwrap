/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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
 * $Log: DecimalDatatypeValidator.cpp,v $
 * Revision 1.17  2003/11/28 18:53:07  peiyongz
 * Support for getCanonicalRepresentation
 *
 * Revision 1.16  2003/11/12 20:32:03  peiyongz
 * Statless Grammar: ValidationContext
 *
 * Revision 1.15  2003/11/06 15:30:07  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.14  2003/10/31 22:16:58  peiyongz
 * to serialize/deserialize data member
 *
 * Revision 1.13  2003/10/02 19:21:06  peiyongz
 * Implementation of Serialization/Deserialization
 *
 * Revision 1.12  2003/08/14 03:00:11  knoaman
 * Code refactoring to improve performance of validation.
 *
 * Revision 1.11  2003/05/18 14:02:07  knoaman
 * Memory manager implementation: pass per instance manager.
 *
 * Revision 1.10  2003/05/16 06:01:57  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.9  2003/05/15 18:53:26  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.8  2003/03/01 20:59:06  peiyongz
 * TotalDigits value must be a positiveInteger
 *
 * Revision 1.7  2003/02/25 17:24:37  peiyongz
 * Schema Errata: E2-44 totalDigits/fractDigits
 *
 * Revision 1.6  2003/01/30 21:56:22  tng
 * Performance: call getRawData instead of toString
 *
 * Revision 1.5  2002/12/18 14:17:55  gareth
 * Fix to bug #13438. When you eant a vector that calls delete[] on its members you should use RefArrayVectorOf.
 *
 * Revision 1.4  2002/11/04 14:53:28  tng
 * C++ Namespace Support.
 *
 * Revision 1.3  2002/09/24 19:44:40  tng
 * Performance: use XMLString::equals instead of XMLString::compareString
 *
 * Revision 1.2  2002/04/01 20:17:46  peiyongz
 * Bug#7551: Exceptions are caught by value, rather than by reference
 *
 * Revision 1.1.1.1  2002/02/01 22:22:41  peiyongz
 * sane_include
 *
 * Revision 1.19  2001/10/09 20:53:22  peiyongz
 * Optimization: save get***() to temp var
 *
 * Revision 1.18  2001/10/02 18:59:29  peiyongz
 * Invalid_Facet_Tag to display the tag name
 *
 * Revision 1.17  2001/10/01 21:04:40  peiyongz
 * DTV Reorganization:fix to memory leak in compare() method.
 *
 * Revision 1.16  2001/10/01 16:16:38  peiyongz
 * DTV Reorganization:derived from AbstractNumericValidator
 *
 * Revision 1.15  2001/09/20 13:11:42  knoaman
 * Regx  + misc. fixes
 *
 * Revision 1.14  2001/08/22 18:28:01  peiyongz
 * Memory leak: delete the bufffer allocated by ::toString()
 *
 * Revision 1.13  2001/08/21 18:42:53  peiyongz
 * Bugzilla# 2816: cleanUp() declared with external linkage and called
 *                          before defined as inline
 *
 * Revision 1.12  2001/08/15 18:08:44  peiyongz
 * Fix to potential leakage in strEnumeration
 *
 * Revision 1.11  2001/07/17 21:30:12  peiyongz
 * bug fix: numBase->getMinInclusive()->toString()
 *
 * Revision 1.10  2001/06/20 17:56:32  peiyongz
 * support for "fixed" option on constrainning facets
 *
 * Revision 1.8  2001/05/29 19:49:34  tng
 * Schema: Constraint Checking Fix in datatypeValidators.  By Pei Yong Zhang.
 *
 * Revision 1.7  2001/05/28 21:11:18  tng
 * Schema: Various DatatypeValidator fix.  By Pei Yong Zhang
 *
 * Revision 1.6  2001/05/18 20:18:02  tng
 * Schema: More exception messages in XMLBigDecimal/XMLBigInteger/DecimalDatatypeValidator.  By Pei Yong Zhang.
 *
 * Revision 1.5  2001/05/18 13:36:45  tng
 * Schema: Catch RegularExpression exception and NumberFormatException
 *
 * Revision 1.4  2001/05/18 13:23:46  tng
 * Schema: Exception messages in DatatypeValidator.  By Pei Yong Zhang.
 *
 * Revision 1.3  2001/05/11 17:17:23  tng
 * Schema: DatatypeValidator fixes.  By Pei Yong Zhang.
 *
 * Revision 1.2  2001/05/11 13:27:28  tng
 * Copyright update.
 *
 * Revision 1.1  2001/05/10 20:51:29  tng
 * Schema: Add DecimalDatatypeValidator and XMLBigDecimal, XMLBigInteger.  By Pei Yong Zhang.
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/datatype/DecimalDatatypeValidator.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeFacetException.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeValueException.hpp>
#include <xercesc/util/NumberFormatException.hpp>
#include <xercesc/util/XMLBigDecimal.hpp>

XERCES_CPP_NAMESPACE_BEGIN

static const int BUF_LEN = 64;
static XMLCh value1[BUF_LEN+1];
static XMLCh value2[BUF_LEN+1];

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
DecimalDatatypeValidator::DecimalDatatypeValidator(MemoryManager* const manager)
:AbstractNumericValidator(0, 0, 0, DatatypeValidator::Decimal, manager)
, fTotalDigits(0)
, fFractionDigits(0)
, fCompareData(0)
{
    setOrdered(XSSimpleTypeDefinition::ORDERED_TOTAL);
    setNumeric(true);
}

DecimalDatatypeValidator::DecimalDatatypeValidator(
                          DatatypeValidator*            const baseValidator
                        , RefHashTableOf<KVStringPair>* const facets
                        , RefArrayVectorOf<XMLCh>*           const enums
                        , const int                           finalSet
                        , MemoryManager* const manager)
:AbstractNumericValidator(baseValidator, facets, finalSet, DatatypeValidator::Decimal, manager)
, fTotalDigits(0)
, fFractionDigits(0)
, fCompareData(0)
{
    init(enums);
}

DecimalDatatypeValidator::~DecimalDatatypeValidator()
{
    if (fCompareData)
        delete fCompareData;
}

// -----------------------------------------------------------------------
// Compare methods
// -----------------------------------------------------------------------
int DecimalDatatypeValidator::compare(const XMLCh* const lValue
                                    , const XMLCh* const rValue)
{
    XMLBigDecimal lObj(lValue, fMemoryManager);
    XMLBigDecimal rObj(rValue, fMemoryManager);

    return compareValues(&lObj, &rObj);
}

DatatypeValidator* DecimalDatatypeValidator::newInstance
(
      RefHashTableOf<KVStringPair>* const facets
    , RefArrayVectorOf<XMLCh>* const      enums
    , const int                           finalSet
    , MemoryManager* const                manager
)
{
    return (DatatypeValidator*) new (manager) DecimalDatatypeValidator(this, facets, enums, finalSet, manager);
}

// -----------------------------------------------------------------------
// ctor provided to be used by derived classes
// -----------------------------------------------------------------------
DecimalDatatypeValidator::DecimalDatatypeValidator(DatatypeValidator*            const baseValidator
                                                 , RefHashTableOf<KVStringPair>* const facets
                                                 , const int                           finalSet
                                                 , const ValidatorType                 type
                                                 , MemoryManager* const                manager)
:AbstractNumericValidator(baseValidator, facets, finalSet, type, manager)
, fTotalDigits(0)
, fFractionDigits(0)
{
    //do not invoke init here !!!
}

void DecimalDatatypeValidator::assignAdditionalFacet(const XMLCh* const key
                                                   , const XMLCh* const value)
{
    if (XMLString::equals(key, SchemaSymbols::fgELT_TOTALDIGITS))
    {
        int val;
        try
        {
            val = XMLString::parseInt(value);
        }
        catch (NumberFormatException&)
        {
            ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::FACET_Invalid_TotalDigit, value);
        }

        // check 4.3.11.c0 must: totalDigits > 0
        if ( val <= 0 )
            ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::FACET_PosInt_TotalDigit, value);

        setTotalDigits(val);
        setFacetsDefined(DatatypeValidator::FACET_TOTALDIGITS);
    }
    else if (XMLString::equals(key, SchemaSymbols::fgELT_FRACTIONDIGITS))
    {
        int val;
        try
        {
            val = XMLString::parseInt(value);
        }
        catch (NumberFormatException&)
        {
            ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::FACET_Invalid_FractDigit, value);
        }

        // check 4.3.12.c0 must: fractionDigits > 0
        if ( val < 0 )
            ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::FACET_NonNeg_FractDigit, value);

        setFractionDigits(val);
        setFacetsDefined(DatatypeValidator::FACET_FRACTIONDIGITS);
    }
    else
    {
        ThrowXML1(InvalidDatatypeFacetException
                , XMLExcepts::FACET_Invalid_Tag
                , key);
    }
}

void DecimalDatatypeValidator::inheritAdditionalFacet()
{

    DecimalDatatypeValidator *numBase = (DecimalDatatypeValidator*) getBaseValidator();

    if (!numBase)
        return;

    int thisFacetsDefined = getFacetsDefined();
    int baseFacetsDefined = numBase->getFacetsDefined();

    // inherit totalDigits
    if ((( baseFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0) &&
        (( thisFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) == 0) )
    {
        setTotalDigits(numBase->fTotalDigits);
        setFacetsDefined(DatatypeValidator::FACET_TOTALDIGITS);
    }

    // inherit fractionDigits
    if ((( baseFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0) &&
        (( thisFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) == 0) )
    {
        setFractionDigits(numBase->fFractionDigits);
        setFacetsDefined(DatatypeValidator::FACET_FRACTIONDIGITS);
    }
}

void DecimalDatatypeValidator::checkAdditionalFacetConstraints() const
{
    int thisFacetsDefined = getFacetsDefined();

    // check 4.3.12.c1 must: fractionDigits <= totalDigits
    if ( ((thisFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0) &&
         ((thisFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0) )
    {
        if ( fFractionDigits > fTotalDigits )
        {
            XMLString::binToText(getFractionDigits(), value1, BUF_LEN, 10);
            XMLString::binToText(getTotalDigits(), value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_TotDigit_FractDigit
                                 , value2
                                 , value1);
        }
    }

}

void DecimalDatatypeValidator::checkAdditionalFacetConstraintsBase() const
{

    DecimalDatatypeValidator *numBase = (DecimalDatatypeValidator*) getBaseValidator();

    if (!numBase)
        return;

    int thisFacetsDefined = getFacetsDefined();
    int baseFacetsDefined = numBase->getFacetsDefined();

    // check 4.3.11.c1 error: totalDigits > base.totalDigits
    // totalDigits != base.totalDigits if (base.fixed)
    if (( thisFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0)
    {
        if ( (( baseFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0) &&
            ( fTotalDigits > numBase->fTotalDigits ))
        {
            XMLString::binToText(fTotalDigits, value1, BUF_LEN, 10);
            XMLString::binToText(numBase->fTotalDigits, value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_totalDigit_base_totalDigit
                                 , value1
                                 , value2);
        }

        if ( (( baseFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0) &&
            (( numBase->getFixed() & DatatypeValidator::FACET_TOTALDIGITS) != 0) &&
            ( fTotalDigits != numBase->fTotalDigits ))
        {
            XMLString::binToText(fTotalDigits, value1, BUF_LEN, 10);
            XMLString::binToText(numBase->fTotalDigits, value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_totalDigit_base_fixed
                                 , value1
                                 , value2);
        }
    }

    if (( thisFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0)
    {
        // check question error: fractionDigits > base.fractionDigits ???
        if ( (( baseFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0) &&
            ( fFractionDigits > numBase->fFractionDigits ))
        {
            XMLString::binToText(fFractionDigits, value1, BUF_LEN, 10);
            XMLString::binToText(numBase->fFractionDigits, value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_fractDigit_base_fractDigit
                                 , value1
                                 , value2);
                        }

        // check question error: fractionDigits > base.totalDigits ???
        if ( (( baseFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0) &&
            ( fFractionDigits > numBase->fTotalDigits ))
        {
            XMLString::binToText(fFractionDigits, value1, BUF_LEN, 10);
            XMLString::binToText(numBase->fTotalDigits, value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_fractDigit_base_totalDigit
                                 , value1
                                 , value2);
        }

        // fractionDigits != base.fractionDigits if (base.fixed)
        if ( (( baseFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0) &&
            (( numBase->getFixed() & DatatypeValidator::FACET_FRACTIONDIGITS) != 0) &&
            ( fFractionDigits != numBase->fFractionDigits ))
        {
            XMLString::binToText(fFractionDigits, value1, BUF_LEN, 10);
            XMLString::binToText(numBase->fFractionDigits, value2, BUF_LEN, 10);
            ThrowXML2(InvalidDatatypeFacetException
                                 , XMLExcepts::FACET_fractDigit_base_fixed
                                 , value1
                                 , value2);
        }
    }

}

int  DecimalDatatypeValidator::compareValues(const XMLNumber* const lValue
                                           , const XMLNumber* const rValue)
{
    return XMLBigDecimal::compareValues((XMLBigDecimal*) lValue, (XMLBigDecimal*) rValue);
}

void  DecimalDatatypeValidator::setMaxInclusive(const XMLCh* const value)
{
    fMaxInclusive = new (fMemoryManager) XMLBigDecimal(value, fMemoryManager);
}

void  DecimalDatatypeValidator::setMaxExclusive(const XMLCh* const value)
{
    fMaxExclusive = new (fMemoryManager) XMLBigDecimal(value, fMemoryManager);
}

void  DecimalDatatypeValidator::setMinInclusive(const XMLCh* const value)
{
    fMinInclusive = new (fMemoryManager) XMLBigDecimal(value, fMemoryManager);
}

void  DecimalDatatypeValidator::setMinExclusive(const XMLCh* const value)
{
    fMinExclusive = new (fMemoryManager) XMLBigDecimal(value, fMemoryManager);
}

void DecimalDatatypeValidator::setEnumeration()
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

    DecimalDatatypeValidator *numBase = (DecimalDatatypeValidator*) getBaseValidator();
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

    fEnumeration = new (fMemoryManager) RefVectorOf<XMLNumber>(enumLength, true, fMemoryManager);
    fEnumerationInherited = false;

    for ( i = 0; i < enumLength; i++)
    {
        fEnumeration->insertElementAt(new (fMemoryManager) XMLBigDecimal(fStrEnumeration->elementAt(i), fMemoryManager), i);
    }

}

// -----------------------------------------------------------------------
// Abstract interface from AbstractNumericValidator
// -----------------------------------------------------------------------
void DecimalDatatypeValidator::checkContent(const XMLCh*             const content
                                           ,      ValidationContext* const context
                                           ,      bool                     asBase)
{

    //validate against base validator if any
    DecimalDatatypeValidator *pBase = (DecimalDatatypeValidator*) this->getBaseValidator();
    if (pBase)
        pBase->checkContent(content, context, true);

    int thisFacetsDefined = getFacetsDefined();

    // we check pattern first
    if ( (thisFacetsDefined & DatatypeValidator::FACET_PATTERN ) != 0 )
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
        if (fCompareData)
            fCompareData->setDecimalValue(content);
        else
            fCompareData = new (fMemoryManager) XMLBigDecimal(content, fMemoryManager);

        if (getEnumeration())
        {
            int i=0;
            int enumLength = getEnumeration()->size();
            for ( ; i < enumLength; i++)
            {
                if (compareValues(fCompareData, (XMLBigDecimal*) getEnumeration()->elementAt(i)) ==0 )
                    break;
            }

            if (i == enumLength)
                ThrowXML1(InvalidDatatypeValueException, XMLExcepts::VALUE_NotIn_Enumeration, content);
        }

        boundsCheck(fCompareData);

        if ( (thisFacetsDefined & DatatypeValidator::FACET_FRACTIONDIGITS) != 0 )
        {
            if ( fCompareData->getScale() > fFractionDigits )
            {                
                XMLString::binToText(fCompareData->getScale(), value1, BUF_LEN, 10);
                XMLString::binToText(fFractionDigits, value2, BUF_LEN, 10);
                ThrowXML3(InvalidDatatypeFacetException
                                 , XMLExcepts::VALUE_exceed_fractDigit
                                 , fCompareData->getRawData()
                                 , value1
                                 , value2);
            }
        }

        if ( (thisFacetsDefined & DatatypeValidator::FACET_TOTALDIGITS) != 0 )
        {
            if ( fCompareData->getTotalDigit() > fTotalDigits )
            {                
                XMLString::binToText(fCompareData->getTotalDigit(), value1, BUF_LEN, 10);
                XMLString::binToText(fTotalDigits, value2, BUF_LEN, 10);
                ThrowXML3(InvalidDatatypeFacetException
                                 , XMLExcepts::VALUE_exceed_totalDigit
                                 , fCompareData->getRawData()
                                 , value1
                                 , value2);
            }

            /***
             E2-44 totalDigits

             ... by restricting it to numbers that are expressible as i � 10^-n
             where i and n are integers such that |i| < 10^totalDigits and 0 <= n <= totalDigits.
            ***/

            if ( fCompareData->getScale() > fTotalDigits )  
            {                
                XMLString::binToText(fCompareData->getScale(), value1, BUF_LEN, 10);
                XMLString::binToText(fTotalDigits, value2, BUF_LEN, 10);
                ThrowXML3(InvalidDatatypeFacetException
                                 , XMLExcepts::VALUE_exceed_totalDigit
                                 , fCompareData->getRawData()
                                 , value1
                                 , value2);
            }
        
        }

    }
    catch (XMLException &e)
    {
       ThrowXML1(InvalidDatatypeFacetException, XMLExcepts::RethrowError, e.getMessage());
    }

}

/***
 * 3.2.3 decimal  
 *
 * . the preceding optional "+" sign is prohibited. 
 * . The decimal point is required. 
 * . Leading and trailing zeroes are prohibited subject to the following: 
 *   there must be at least one digit to the right and to the left of the decimal point which may be a zero.
 *
 *
 *  3.3.13 integer
 *  3.3.16 long
 *  3.3.17 int
 *  3.3.18 short 
 *  3.3.19 byte
 *  3.3.20 nonNegativeInteger
 *  3.3.25 positiveInteger
 *
 *   . the preceding optional "+" sign is prohibited and
 *   . leading zeroes are prohibited.
 *   
 *  3.3.14 nonPositiveInteger
 *
 *  . the negative sign ("-") is required with the token "0" and 
 *  . leading zeroes are prohibited.
 *  
 *  3.3.15 negativeInteger
 *  3.3.21 unsignedLong
 *  3.3.22 unsignedInt
 *  3.3.23 unsignedShort
 *  3.3.24 unsignedByte
 *
 *  . leading zeroes are prohibited.
 *  
 *  todo:
 *    In order to implement this method, this class shall have a way to tell if itself
 *    is an 'int', or 'unsignedLong', or something list above, not merely 'Decimal'.
 *
 *    Thus we need to extend DatatypeValidator::ValidatorType to include these
 *    'new' dv types. And assign them the value the way that once AND with mask
 *    it would be 'Decimal', and all the existing dv type would remain what they
 *    are.
 *
 *    eg. 'String' & mask = 'String'
 *        'AnyURI' & mask = 'AnyURI',
 *
 *        'int'    & mask = 'Decimal'
 *        'long'   & mask = 'long'
 *    
 *    thus, when deserialize, we can create 'Decimal'dv even they are 'int',
 *    'long'.
 *
 *    All dv' ctor need to carry an extra field DatatypeValidator::ValidatorType
 *    to specify who it is rather than merely relying on the c++ object itself.
 *
 ***/
const XMLCh* DecimalDatatypeValidator::getCanonicalRepresentation(const XMLCh*         const rawData
                                                                 ,      MemoryManager* const memMgr) const
{
    DecimalDatatypeValidator* temp = (DecimalDatatypeValidator*) this;
    temp->checkContent(rawData, 0, false);

    MemoryManager* toUse = memMgr? memMgr : fMemoryManager;
    //todo: change behaviour later
    return XMLString::replicate(rawData, toUse);
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_TOCREATE(DecimalDatatypeValidator)

void DecimalDatatypeValidator::serialize(XSerializeEngine& serEng)
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
        serEng<<(int) (XMLNumber::BigDecimal);
    }

    AbstractNumericValidator::serialize(serEng);

    //don't serialize XMLBigDecimal*       
    if (serEng.isStoring())
    {
        serEng<<fTotalDigits;
        serEng<<fFractionDigits;
    }
    else
    {
        serEng>>fTotalDigits;
        serEng>>fFractionDigits;
    }

}

XERCES_CPP_NAMESPACE_END

/**
  * End of file DecimalDatatypeValidator::cpp
  */
