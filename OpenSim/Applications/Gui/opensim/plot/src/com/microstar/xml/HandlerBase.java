// HandlerBase.java: Simple base class for AElfred processors.
// NO WARRANTY! See README, and copyright below.
// $Id: HandlerBase.java,v 1.5 2005/04/25 17:22:20 cxh Exp $
package com.microstar.xml;


/**
  * Convenience base class for AElfred handlers.
  * <p>This base class implements the XmlHandler interface with
  * (mostly empty) default handlers.  You are not required to use this,
  * but if you need to handle only a few events, you might find
  * it convenient to extend this class rather than implementing
  * the entire interface.  This example overrides only the
  * <code>charData</code> method, using the defaults for the others:
  * <pre>
  * import com.microstar.xml.HandlerBase;
  *
  * public class MyHandler extends HandlerBase {
  *   public void charData (char ch[], int start, int length)
  *   {
  *     System.out.println("Data: " + new String (ch, start, length));
  *   }
  * }
  * </pre>
  * <p>This class is optional, but if you use it, you must also
  * include the <code>XmlException</code> class.
  * <p>Do not extend this if you are using SAX; extend
  * <code>org.xml.sax.HandlerBase</code> instead.
  * Copyright (c)  1998 by Microstar Software Ltd.
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */
public class HandlerBase implements XmlHandler {
    /**
      * Handle the start of the document.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#startDocument
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void startDocument() throws java.lang.Exception {
    }

    /**
      * Handle the end of the document.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#endDocument
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void endDocument() throws java.lang.Exception {
    }

    /**
      * Resolve an external entity.
      * <p>The default implementation simply returns the supplied
      * system identifier.
      * @see com.microstar.xml.XmlHandler#resolveEntity
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public Object resolveEntity(String publicId, String systemId)
        throws java.lang.Exception {
        return null;
    }

    /**
      * Handle the start of an external entity.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#startExternalEntity
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void startExternalEntity(String systemId) throws java.lang.Exception {
    }

    /**
      * Handle the end of an external entity.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#endExternalEntity
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void endExternalEntity(String systemId) throws java.lang.Exception {
    }

    /**
      * Handle a document type declaration.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#doctypeDecl
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void doctypeDecl(String name, String publicId, String systemId)
        throws java.lang.Exception {
    }

    /**
      * Handle an attribute assignment.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#attribute
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void attribute(String aname, String value, boolean isSpecified)
        throws java.lang.Exception {
    }

    /**
      * Handle the start of an element.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#startElement
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void startElement(String elname) throws java.lang.Exception {
    }

    /**
      * Handle the end of an element.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#endElement
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void endElement(String elname) throws java.lang.Exception {
    }

    /**
      * Handle character data.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#charData
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void charData(char[] ch, int start, int length)
        throws java.lang.Exception {
    }

    /**
      * Handle ignorable whitespace.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#ignorableWhitespace
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void ignorableWhitespace(char[] ch, int start, int length)
        throws java.lang.Exception {
    }

    /**
      * Handle a processing instruction.
      * <p>The default implementation does nothing.
      * @see com.microstar.xml.XmlHandler#processingInstruction
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void processingInstruction(String target, String data)
        throws java.lang.Exception {
    }

    /**
      * Throw an exception for a fatal error.
      * <p>The default implementation throws <code>XmlException</code>.
      * @see com.microstar.xml.XmlHandler#error
      * @exception com.microstar.xml.XmlException A specific parsing error.
      * @exception java.lang.Exception Derived methods may throw exceptions.
      */
    public void error(String message, String systemId, int line, int column)
        throws XmlException, java.lang.Exception {
        throw new XmlException(message, systemId, line, column);
    }
}
