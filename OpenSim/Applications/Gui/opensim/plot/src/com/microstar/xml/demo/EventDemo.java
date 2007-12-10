// EventDemo.java: demonstration application showing &AElig;fred's event stream.
// NO WARRANTY! See README, and copyright below.
// Modified 11/8/98 to add package statement.
package com.microstar.xml.demo;


/**
  * Demonstration application showing &AElig;fred's event stream.
  * <p>Usage: <code>java EventDemo &lt;url&gt;</code>
  * <p>Or, use it as an applet, supplying the URL as the <code>url</code>
  * parameter.
  * Copyright (c)  1997, 1998 by Microstar Software Ltd.;
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
public class EventDemo extends XmlApp {
    /**
      * Entry point for an application.
      */
    public static void main(String[] args) throws Exception {
        EventDemo demo = new EventDemo();

        if (args.length != 1) {
            System.err.println("java EventDemo <uri>");
            System.exit(1);
        } else {
            demo.doParse(args[0]);
        }
    }

    /**
      * Resolve an entity and print an event.
      * @see com.microstar.xml.XmlHandler#resolveEntity
      */
    public Object resolveEntity(String publicId, String systemId) {
        displayText("Resolving entity: pubid=" + publicId + ", sysid="
            + systemId);
        return null;
    }

    public void startExternalEntity(String systemId) {
        displayText("Starting external entity:  " + systemId);
    }

    public void endExternalEntity(String systemId) {
        displayText("Ending external entity:  " + systemId);
    }

    /**
      * Handle the start of the document by printing an event.
      * @see com.microstar.xml.XmlHandler#startDocument
      */
    public void startDocument() {
        displayText("Start document");
    }

    /**
      * Handle the end of the document by printing an event.
      * @see com.microstar.xml.XmlHandler#endDocument
      */
    public void endDocument() {
        displayText("End document");
    }

    /**
      * Handle a DOCTYPE declaration by printing an event.
      * @see com.microstar.xml.XmlHandler#doctypeDecl
      */
    public void doctypeDecl(String name, String pubid, String sysid) {
        displayText("Doctype declaration:  " + name + ", pubid=" + pubid
            + ", sysid=" + sysid);
    }

    /**
      * Handle an attribute value assignment by printing an event.
      * @see com.microstar.xml.XmlHandler#attribute
      */
    public void attribute(String name, String value, boolean isSpecified) {
        String s;

        if (isSpecified) {
            s = " (specified)";
        } else {
            s = " (defaulted)";
        }

        displayText("Attribute:  name=" + name + ", value=" + value + s);
    }

    /**
      * Handle the start of an element by printing an event.
      * @see com.microstar.xml.XmlHandler#startElement
      */
    public void startElement(String name) {
        displayText("Start element:  name=" + name);
    }

    /**
      * Handle the end of an element by printing an event.
      * @see com.microstar.xml.XmlHandler#endElement
      */
    public void endElement(String name) {
        displayText("End element:  " + name);
    }

    /**
      * Handle character data by printing an event.
      * @see com.microstar.xml.XmlHandler#charData
      */
    public void charData(char[] ch, int start, int length) {
        displayText("Character data:  \"" + escape(ch, length) + '"');
    }

    /**
      * Handle ignorable whitespace by printing an event.
      * @see com.microstar.xml.XmlHandler#ignorableWhitespace
      */
    public void ignorableWhitespace(char[] ch, int start, int length) {
        displayText("Ignorable whitespace:  \"" + escape(ch, length) + '"');
    }

    /**
      * Handle a processing instruction by printing an event.
      * @see com.microstar.xml.XmlHandler#processingInstruction
      */
    public void processingInstruction(String target, String data) {
        displayText("Processing Instruction:  " + target + ' '
            + escape(data.toCharArray(), data.length()));
    }
}

// end of EventDemo.java
