package simtkView.plot;

import com.microstar.xml.*;
import java.util.*;
import java.net.*;
import java.io.*;

public class NmblPlotTemplateXMLParser extends HandlerBase {
  private SimtkPtPlotDialog _dlg;
  private static String _version="0.1";

  public NmblPlotTemplateXMLParser(SimtkPtPlotDialog dlg) {
    _dlg = dlg;
  }
  /** Start a document.  This method is called just before the parser
   *  attempts to read the first entity (the root of the document).
   *  It is guaranteed that this will be the first method called.
   */
  public void startDocument() throws Exception {
      super.startDocument();
      _attributes = new Hashtable();
}

  public void attribute(String name, String value, boolean specified)
          throws XmlException {
      if (name == null) throw new XmlException("Attribute has no name",
              "???",
              _parser.getLineNumber(),
              _parser.getColumnNumber());
      // NOTE: value may be null if attribute default is #IMPLIED.
      if (value != null) {
          _attributes.put(name, value);
      }
  }
  /** Start an element.
   *  This is called at the beginning of each XML
   *  element.  By the time it is called, all of the attributes
   *  for the element will already have been reported using the
   *  attribute() method.  Unrecognized elements are ignored.
   *  @param elementName The element type name.
   *  @exception XmlException If the element produces an error
   *   in constructing the model.
   */
  public void startElement(String elementName) throws XmlException {
      try {

          if (elementName.equals("nmblPlotTemplate")) {
              String writtenVersion = (String)_attributes.get("version");
              boolean sameVersion=false;
              if (writtenVersion.equals(_version)){
                sameVersion=true;
              }
          }
          else if (elementName.equals("Grid")){
            String rowsString = (String)_attributes.get("rows");
            int rows = (Integer.valueOf(rowsString)).intValue();
            String columnsString = (String)_attributes.get("columns");
            int columns = (Integer.valueOf(columnsString)).intValue();
            _dlg.setGridSize(rows, columns);
            _dlg.repaint();
          }
      } catch (Exception ex) {
          if (ex instanceof XmlException) {
              throw (XmlException)ex;
          } else {
              // FIXME: Temporary for debugging.
              System.err.println(ex.toString());
              ex.printStackTrace();
              String msg = "XML element \"" + elementName
                  + "\" triggers exception:\n  " + ex.toString();
              throw new XmlException(msg,
                      "Entity?",
                      _parser.getLineNumber(),
                      _parser.getColumnNumber());
          }
      }

      _attributes.clear();
  }
  public void parse(URL base, InputStream input) throws Exception {
      parse(base, new InputStreamReader(input));
  }

  /** Parse the given stream as a PlotML file.
   *  A variety of exceptions might be thrown if the parsed
   *  data does not represent a valid PlotML file.
   *  @param reader The stream from which to read XML.
   *  @exception Exception If the parser fails.
   */
  public void parse(URL base, Reader reader) throws Exception {
      _parser.setHandler(this);
      _base = base;
      Reader buffered = new BufferedReader(reader);
      if (base == null) {
          _parser.parse(null, null, buffered);
      } else {
          _parser.parse(base.toExternalForm(), null, buffered);
      }
  }

  /** Parse the given text as PlotML.
   *  A variety of exceptions might be thrown if the parsed
   *  data does not represent valid PlotML data.
   *  @param text The PlotML data.
   *  @exception Exception If the parser fails.
   */
  public void parse(URL base, String text) throws Exception {
      parse(base, new StringReader(text));
  }
  ///////////////////////////////////////////////////////////////////
  ////                         protected members                 ////

  // NOTE: Do not use HashMap here to maintain Java 1.1 compatibility.
  /** Attributes associated with an entity. */
  protected Hashtable _attributes;

  /** The current character data for the current element. */
  protected StringBuffer _currentCharData = new StringBuffer();

  /** The parser. */
  protected XmlParser _parser = new XmlParser();

  private URL _base;

}
