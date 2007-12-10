// DtdDemo.java: demonstration application showing DTD queries.
// NO WARRANTY! See README, and copyright below.
// $Id: DtdDemo.java,v 1.8 2005/04/29 20:05:17 cxh Exp $
// Modified 11/8/98 to add package statement.
package com.microstar.xml.demo;

import java.util.Enumeration;

import com.microstar.xml.XmlParser;


/**
  * Demonstration application showing DTD queries.
  * <p>Usage: <code>java DtdDemo &lt;url&gt;</code>
  * <p>Or, use it as an applet, supplying the URL as the <code>url</code>
  * parameter.
  * <p>Note: This does not preserve any processing instructions
  * or parameter entities in the DTD; otherwise, produces a fully expanded
  * and normalised version.
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
public class DtdDemo extends XmlApp {
    /**
      * Entry point for an application (applets enter through XmlApp.init()).
      * @see XmlApp
      */
    public static void main(String[] args) throws Exception {
        DtdDemo demo = new DtdDemo();

        if (args.length != 1) {
            System.err.println("Usage: java DtdDemo <uri>");
            System.exit(1);
        } else {
            demo.doParse(args[0]);
        }
    }

    /**
      * Print a comment showing where the DTD (if any) begins.
      */
    public void startDocument() {
        displayText("<-- Start of DTD -->\n");
    }

    /**
      * Print a comment showing where the DTD (if any) ends.
      */
    public void endDocument(int errorCount) {
        displayText("<-- End of DTD -->");
    }

    /**
      * Dump the DTD.
      * <p>Once this event is received, we know that the DTD is
      * completely parsed, and can use AElfred's query routines
      * to reconstruct a normalised version of it.
      * @see #dumpNotations
      * @see #dumpEntities
      * @see #dumpElements
      */
    public void doctypeDecl(String name, String pubid, String sysid) {
        dumpNotations();
        dumpEntities();
        dumpElements();
    }

    /**
      * Produce normalised declarations for all notations.
      * @see #makeExternalIdentifiers
      */
    public void dumpNotations() {
        Enumeration notationNames = parser.declaredNotations();
        String nname;
        String extId;

        // Mark the beginning of a new section.
        displayText("<-- Notation Declarations -->\n");

        // Loop through all declared notations.
        while (notationNames.hasMoreElements()) {
            nname = (String) notationNames.nextElement();
            extId = makeExternalIdentifiers(parser.getNotationPublicId(nname),
                    parser.getNotationSystemId(nname).toString());
            displayText("<!NOTATION " + nname + +' ' + extId + ">\n");
        }
    }

    /**
      * Produce normalised declarations for all general entities.
      * @see #makeLiteral
      * @see #makeExternalIdentifiers
      */
    public void dumpEntities() {
        Enumeration entityNames = parser.declaredEntities();
        String ename;
        String value;

        // Mark the beginning of a new section.
        displayText("<-- Entity Declarations -->\n");

        // Loop through all the declared
        // entities.
        while (entityNames.hasMoreElements()) {
            ename = (String) entityNames.nextElement();

            // Skip parameter entities.
            if (ename.startsWith("%")) {
                continue;
            }

            // Construct a value based on the
            // class of entity.
            value = null;

            switch (parser.getEntityType(ename)) {
            // Internal text entity
            case XmlParser.ENTITY_INTERNAL:
                value = makeLiteral(parser.getEntityValue(ename));
                break;

            // External binary entity
            case XmlParser.ENTITY_NDATA:
                value = makeExternalIdentifiers(parser.getEntityPublicId(ename),
                        parser.getEntitySystemId(ename).toString()) + "NDATA "
                    + parser.getEntityNotationName(ename);
                break;

            // External text entity
            case XmlParser.ENTITY_TEXT:
                value = makeExternalIdentifiers(parser.getEntityPublicId(ename),
                        parser.getEntitySystemId(ename).toString());
                break;
            }

            // Print a normalised declaration.
            displayText("<!ENTITY " + ename + ' ' + value + ">\n");
        }
    }

    /**
      * Produce normalised declarations for all elements.
      * @see #dumpAttributes
      */
    public void dumpElements() {
        Enumeration elementNames = parser.declaredElements();
        String elname;

        // Mark the beginning of a new section.
        displayText("<-- Element Type Declarations -->\n");

        // Loop through all of the declared
        // elements.
        while (elementNames.hasMoreElements()) {
            String contentSpec = "ANY";

            elname = (String) elementNames.nextElement();

            // Construct a content spec based
            // on the element's content type.
            switch (parser.getElementContentType(elname)) {
            case XmlParser.CONTENT_EMPTY:
                contentSpec = "EMPTY";
                break;

            case XmlParser.CONTENT_ANY:
                contentSpec = "ANY";
                break;

            case XmlParser.CONTENT_ELEMENTS:
            case XmlParser.CONTENT_MIXED:
                contentSpec = parser.getElementContentModel(elname);
                break;
            }

            // Print a normalised element type
            // declaration.
            displayText("<!ELEMENT " + elname + ' ' + contentSpec + ">");

            // Print the ATTLIST declaration,
            // if any.
            dumpAttributes(elname);

            // Blank line.
            displayText("");
        }
    }

    /**
      * Dump attributes for an element.
      * @see #makeAttributeType
      * @see #makeAttributeValue
      */
    public void dumpAttributes(String elname) {
        Enumeration attributeNames = parser.declaredAttributes(elname);
        String aname;
        String type;
        String value;

        // Skip if there are no declared
        // attributes for this element
        // type.
        if (attributeNames == null) {
            return;
        }

        // Print the start of the ATTLIST
        // declaration.
        displayText("<!ATTLIST " + elname);

        // Loop through all of the declared
        // attributes.
        while (attributeNames.hasMoreElements()) {
            aname = (String) attributeNames.nextElement();
            type = makeAttributeType(elname, aname);
            value = makeAttributeValue(elname, aname);

            // Print the declaration for a
            // single attribute.
            displayText("  " + aname + ' ' + type + ' ' + value);
        }

        // Finish the ATTLIST declaration.
        displayText(">");
    }

    /**
      * Generate the attribute type as a normalised string.
      */
    public String makeAttributeType(String elname, String aname) {
        // Construct a string equivalent
        // of the attribute type.
        switch (parser.getAttributeType(elname, aname)) {
        case XmlParser.ATTRIBUTE_CDATA:
            return "CDATA";

        case XmlParser.ATTRIBUTE_ID:
            return "ID";

        case XmlParser.ATTRIBUTE_IDREF:
            return "IDREF";

        case XmlParser.ATTRIBUTE_IDREFS:
            return "IDREFS";

        case XmlParser.ATTRIBUTE_ENTITY:
            return "ENTITY";

        case XmlParser.ATTRIBUTE_ENTITIES:
            return "ENTITIES";

        case XmlParser.ATTRIBUTE_NMTOKEN:
            return "NMTOKEN";

        case XmlParser.ATTRIBUTE_NMTOKENS:
            return "NMTOKENS";

        case XmlParser.ATTRIBUTE_ENUMERATED:

            // An enumeration.
            return parser.getAttributeEnumeration(elname, aname);

        case XmlParser.ATTRIBUTE_NOTATION:

            // An enumeration of notations.
            return "NOTATION " + parser.getAttributeEnumeration(elname, aname);
        }

        return null;
    }

    /**
      * Generate a full attribute default value.
      * @see #makeLiteral
      */
    public String makeAttributeValue(String elname, String aname) {
        // Generate a default value based
        // on the type.
        switch (parser.getAttributeDefaultValueType(elname, aname)) {
        case XmlParser.ATTRIBUTE_DEFAULT_IMPLIED:
            return "#IMPLIED";

        case XmlParser.ATTRIBUTE_DEFAULT_SPECIFIED:
            return makeLiteral(parser.getAttributeDefaultValue(elname, aname));

        case XmlParser.ATTRIBUTE_DEFAULT_REQUIRED:
            return "#REQUIRED";

        case XmlParser.ATTRIBUTE_DEFAULT_FIXED:
            return "#FIXED "
            + makeLiteral(parser.getAttributeDefaultValue(elname, aname));
        }

        return null;
    }

    /**
      * Construct a string equivalent of external identifiers.
      * @see #makeLiteral
      */
    public String makeExternalIdentifiers(String pubid, String sysid) {
        String extId = "";

        if (pubid != null) {
            extId = "PUBLIC " + makeLiteral(pubid);

            if (sysid != null) {
                extId = extId + ' ' + makeLiteral(sysid);
            }
        } else {
            extId = "SYSTEM " + makeLiteral(sysid);
        }

        return extId;
    }

    /**
      * Quote a literal, and escape any '"' or non-ASCII characters within it.
      */
    public String makeLiteral(String data) {
        char[] ch = data.toCharArray();
        StringBuffer buf = new StringBuffer();

        buf.append('"');

        for (int i = 0; i < ch.length; i++) {
            if (ch[i] == '"') {
                buf.append("&#22;");
            } else if ((int) ch[i] > 0x7f) {
                buf.append("&#" + (int) ch[i] + ";");
            } else {
                buf.append(ch[i]);
            }
        }

        buf.append('"');

        return buf.toString();
    }
}

// End of DtdDemo.java
