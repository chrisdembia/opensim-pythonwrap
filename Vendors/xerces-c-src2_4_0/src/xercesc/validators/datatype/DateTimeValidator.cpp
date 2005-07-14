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
 * $Id: DateTimeValidator.cpp,v 1.11 2003/11/12 20:32:03 peiyongz Exp $
 * $Log: DateTimeValidator.cpp,v $
 * Revision 1.11  2003/11/12 20:32:03  peiyongz
 * Statless Grammar: ValidationContext
 *
 * Revision 1.10  2003/10/02 19:21:06  peiyongz
 * Implementation of Serialization/Deserialization
 *
 * Revision 1.9  2003/10/01 16:32:41  neilg
 * improve handling of out of memory conditions, bug #23415.  Thanks to David Cargill.
 *
 * Revision 1.8  2003/08/14 03:00:11  knoaman
 * Code refactoring to improve performance of validation.
 *
 * Revision 1.7  2003/05/18 14:02:07  knoaman
 * Memory manager implementation: pass per instance manager.
 *
 * Revision 1.6  2003/05/16 06:01:57  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.5  2003/05/15 18:53:26  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.4  2003/01/30 21:56:22  tng
 * Performance: call getRawData instead of toString
 *
 * Revision 1.3  2002/11/27 21:26:55  peiyongz
 * Schema Errat E2-24 Duration 'T': allow SchemaDateTimeException be
 * propogated to client.
 *
 * Revision 1.2  2002/11/04 14:53:28  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:41  peiyongz
 * sane_include
 *
 * Revision 1.2  2001/11/12 20:37:57  peiyongz
 * SchemaDateTimeException defined
 *
 * Revision 1.1  2001/11/07 19:18:52  peiyongz
 * DateTime Port
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/datatype/DateTimeValidator.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeFacetException.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeValueException.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

static const int BUF_LEN = 64;
static XMLCh value1[BUF_LEN+1];
static XMLCh value2[BUF_LEN+1];

// ---------------------------------------------------------------------------
//  Macro
// ---------------------------------------------------------------------------
#define  REPORT_VALUE_ERROR(val1, val2, except_code)    \
  ThrowXML2(InvalidDatatypeValueException               \
          , except_code                                 \
          , val1->getRawData()                          \
          , val2->getRawData());

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
DateTimeValidator::~DateTimeValidator()
{
    if (fDateTime)
        delete fDateTime;
}

DateTimeValidator::DateTimeValidator(
                          DatatypeValidator*            const baseValidator
                        , RefHashTableOf<KVStringPair>* const facets
                        , const int                           finalSet
                        , const ValidatorType                 type
                        , MemoryManager* const                manager)
:AbstractNumericFacetValidator(baseValidator, facets, finalSet, type, manager)
, fDateTime(0)
{
    //do not invoke init() here !!!
}

void DateTimeValidator::validate(const XMLCh*             const content
                               ,       ValidationContext* const context)
{
    checkContent(content, context, false);
}

int DateTimeValidator::compare(const XMLCh* const value1
                             , const XMLCh* const value2)
{
    try
    {
        XMLDateTime *pDate1 = parse(value1);
        Janitor<XMLDateTime> jName1(pDate1);
        XMLDateTime *pDate2 = parse(value2);
        Janitor<XMLDateTime> jName2(pDate2);
        int result = compareDates(pDate1, pDate2, true);
        return (result==INDETERMINATE)? -1 : result;
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch (...) // RuntimeException e
    {
        return -1; // revisit after implement compareDates()
    }

}

void DateTimeValidator::assignAdditionalFacet( const XMLCh* const key
                                             , const XMLCh* const)
{
    ThrowXML1(InvalidDatatypeFacetException
            , XMLExcepts::FACET_Invalid_Tag
            , key);
}

void DateTimeValidator::inheritAdditionalFacet()
{}

void DateTimeValidator::checkAdditionalFacetConstraints() const
{}

void DateTimeValidator::checkAdditionalFacetConstraintsBase() const
{}

void DateTimeValidator::checkContent(const XMLCh*             const content
                                   ,       ValidationContext* const context
                                   ,       bool                     asBase)
{

    //validate against base validator if any
    DateTimeValidator *pBaseValidator = (DateTimeValidator*) this->getBaseValidator();
    if (pBaseValidator)
        pBaseValidator->checkContent(content, context, true);

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

    // the derived classes' parse() method constructs an
    // XMLDateTime object anc invokes appropriate XMLDateTime's
    // parser to parse the content.
    if (fDateTime)
        fDateTime->setBuffer(content);
    else
        fDateTime = new (fMemoryManager) XMLDateTime(content, fMemoryManager);

    parse(fDateTime);

    // must be < MaxExclusive
    if ((thisFacetsDefined & DatatypeValidator::FACET_MAXEXCLUSIVE) != 0)
    {
        if (compareValues(fDateTime, getMaxExclusive()) != XMLDateTime::LESS_THAN)
        {
            REPORT_VALUE_ERROR( fDateTime
                              , getMaxExclusive()
                              , XMLExcepts::VALUE_exceed_maxExcl)
        }
    } 	

    // must be <= MaxInclusive
    if ((thisFacetsDefined & DatatypeValidator::FACET_MAXINCLUSIVE) != 0)
    {
        int result = compareValues(fDateTime, getMaxInclusive());
        if ( result == XMLDateTime::GREATER_THAN || result == XMLDateTime::INDETERMINATE )
        {
            REPORT_VALUE_ERROR( fDateTime
                              , getMaxInclusive()
                              , XMLExcepts::VALUE_exceed_maxIncl)
        }
    }

    // must be >= MinInclusive
    if ((thisFacetsDefined & DatatypeValidator::FACET_MININCLUSIVE) != 0)
    {
        int result = compareValues(fDateTime, getMinInclusive());
        if (result == XMLDateTime::LESS_THAN || result == XMLDateTime::INDETERMINATE)
        {
            REPORT_VALUE_ERROR( fDateTime
                              , getMinInclusive()
                              , XMLExcepts::VALUE_exceed_minIncl)
        }
    }

    // must be > MinExclusive
    if ( (thisFacetsDefined & DatatypeValidator::FACET_MINEXCLUSIVE) != 0 )
    {
        if (compareValues(fDateTime, getMinExclusive()) != XMLDateTime::GREATER_THAN)
        {
            REPORT_VALUE_ERROR( fDateTime
                              , getMinExclusive()
                              , XMLExcepts::VALUE_exceed_minExcl)
        }
    }

    if ((thisFacetsDefined & DatatypeValidator::FACET_ENUMERATION) != 0 &&
        (getEnumeration() != 0))
    {
        int i=0;
        int enumLength = getEnumeration()->size();
        for ( ; i < enumLength; i++)
        {
            if (compareValues(fDateTime, getEnumeration()->elementAt(i)) == XMLDateTime::EQUAL)
                break;
        }

        if (i == enumLength)
            ThrowXML1(InvalidDatatypeValueException, XMLExcepts::VALUE_NotIn_Enumeration, content);
    }
}

//
// Comparision methods
//
int DateTimeValidator::compareValues(const XMLNumber* const lValue
                                   , const XMLNumber* const rValue)
{
    return compareDates((XMLDateTime*) lValue, (XMLDateTime*) rValue, true);
}

/**
 * Compare algorithm described in dateDime (3.2.7).
 * Duration datatype overwrites this method
 *
 * @param date1  normalized date representation of the first value
 * @param date2  normalized date representation of the second value
 * @param strict
 * @return less, greater, less_equal, greater_equal, equal
 */
int DateTimeValidator::compareDates(const XMLDateTime* const date1
                                  , const XMLDateTime* const date2
                                  , bool                     strict)
{
    return XMLDateTime::compare(date1, date2);
}

//
// In fact, the proper way of the following set*() shall be
// {
// if (fMaxInclusive)
//     delete fMaxInclusive;
//
//    fMaxInclusive = parse(value);
//
// }
//
// But we know this function is invoked once and only once
// since there is no duplicated facet passed in, therefore
// fMaxInclusive is alwasy zero before, so for the
// sake of performance, we do not do the checking/delete.
//

void DateTimeValidator::setMaxInclusive(const XMLCh* const value)
{
    fMaxInclusive = parse(value);
}

void DateTimeValidator::setMaxExclusive(const XMLCh* const value)
{
    fMaxExclusive = parse(value);
}

void DateTimeValidator::setMinInclusive(const XMLCh* const value)
{
    fMinInclusive = parse(value);
}

void DateTimeValidator::setMinExclusive(const XMLCh* const value)
{
    fMinExclusive = parse(value);
}

void DateTimeValidator::setEnumeration()
{
// to do: do we need to check against base value space???

    if (!fStrEnumeration)
        return;

    int enumLength = fStrEnumeration->size();
    fEnumeration = new (fMemoryManager) RefVectorOf<XMLNumber>(enumLength, true, fMemoryManager);
    fEnumerationInherited = false;

    for ( int i = 0; i < enumLength; i++)
        fEnumeration->insertElementAt(parse(fStrEnumeration->elementAt(i)), i);

}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_NOCREATE(DateTimeValidator)

void DateTimeValidator::serialize(XSerializeEngine& serEng)
{
    /***
     *
     * Note: All its derivatives share the same number type, that is
     *       XMLNumber::DateTime, so this class would write it.
     ***/

    if (serEng.isStoring())
    {
        serEng<<(int) XMLNumber::DateTime;
    }

    AbstractNumericFacetValidator::serialize(serEng);

    //fDateTime can be instantiated during checkContent(), so don't serialize it.
}

XERCES_CPP_NAMESPACE_END

/**
  * End of file DateTimeValidator::cpp
  */

