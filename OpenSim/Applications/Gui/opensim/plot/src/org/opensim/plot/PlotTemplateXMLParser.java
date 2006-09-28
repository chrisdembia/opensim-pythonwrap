package org.opensim.plot;

import com.microstar.xml.*;
import java.util.*;
import java.net.*;
import java.io.*;

public class PlotTemplateXMLParser extends HandlerBase {
  private OpenSimLivePlotDialog _dlg;
  private static String _version="0.1";

  public PlotTemplateXMLParser(OpenSimLivePlotDialog dlg) {
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
   *
   * @todo handle error situations and missing attributes/elements. This handling needs
   * to be documented somewhere for users manually editng the template files.
   */
  public void startElement(String elementName) throws XmlException {
      try {

          if (elementName.equals("nmblPlotTemplate")) {
            // For future migration to later format as needed
            String writtenVersion = (String)_attributes.get("version");
              boolean sameVersion=false;
              if (writtenVersion.equals(_version)){
                sameVersion=true;
              }
          }
          else if (elementName.equals("Grid")){
            // Size of the grid of plots (rows, columns)
            String rowsString = (String)_attributes.get("rows");
            int rows = (Integer.valueOf(rowsString)).intValue();
            String columnsString = (String)_attributes.get("columns");
            int columns = (Integer.valueOf(columnsString)).intValue();
            if (columns==0) columns=1;
            _dlg.setGridSize(rows, columns);
            _dlg.repaint();
          }
          else if (elementName.equals("Figure")){
            // Specification of a single Figure (plot-window)
            String idString = (String)_attributes.get("id");
            int id = (Integer.valueOf(idString)).intValue();
            _currentFigure = _dlg.getFigure(id);
            _currentFigureId = id;
            String titleString = (String)_attributes.get("title");
            if (!titleString.equals("")){
              _currentFigure.setTitle(titleString);
            }
         }
         else if (elementName.equals("xLabel")){
            _currentCharData = new StringBuffer();
         }
         else if (elementName.equals("yLabel")){
           _currentCharData = new StringBuffer();
         }
         else if (elementName.equals("xRange")){
           double[] xRange = new double[2];
           String minString = (String)_attributes.get("min");
           xRange[0] = (Double.valueOf(minString)).doubleValue();
           String maxString = (String)_attributes.get("max");
           xRange[1] = (Double.valueOf(maxString)).doubleValue();
           if (_currentFigure != null)
             _currentFigure.setXRange(xRange[0], xRange[1]);
         }
         else if (elementName.equals("yRange")){
           double[] yRange = new double[2];
           String minString = (String)_attributes.get("min");
           yRange[0] = (Double.valueOf(minString)).doubleValue();
           String maxString = (String)_attributes.get("max");
           yRange[1] = (Double.valueOf(maxString)).doubleValue();
           if (_currentFigure != null)
             _currentFigure.setYRange(yRange[0], yRange[1]);
         }
         else if (elementName.equals("plots")){
           // Nothing to do here, we add individual plots one at a time
         }
         else if (elementName.equals("plot")){
           // reset names for current plot
           _qtyX = null;
           _qtyY = null;
           _legend = null;
           _filters = new Vector();
         }
         else if (elementName.equals("qty")){
           _qtyX = (String)_attributes.get("xName");
           _qtyY = (String)_attributes.get("yName");
         }
         else if (elementName.equals("legend")){
           _legend = (String)_attributes.get("value");
          }
          else if (elementName.equals("showGrid")){
            String toShowGrid = (String)_attributes.get("value");
            _currentFigure.setGrid(toShowGrid.equalsIgnoreCase("true"));
           }
           else if (elementName.equals("filter")){
             String filterType = (String)_attributes.get("name");
             if (filterType.equals("rectify")){
               _filters.add(new PlotRectifyFilter());
             }
             else if (filterType.equals("scale")){
               String scaleValue = (String)_attributes.get("value");
               _filters.add(new PlotScaleFilter(new Double(scaleValue).doubleValue()));
             }
             else if (filterType.equals("offset")){
               String offsetValue = (String)_attributes.get("value");
               _filters.add(new PlotOffsetFilter(new Double(offsetValue).doubleValue()));
             }
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

  public void endElement(String elementName) throws Exception {
    if (elementName.equals("Figure")) {
      _currentFigure = null;
      _currentFigureId = -1;
    }
    else if (elementName.equals("xLabel")){
      if (_currentFigure != null){
        String label = _currentCharData.toString();
        if (!label.equals("null"))
          _currentFigure.setXLabel(label.trim());
      }
    }
    else if (elementName.equals("yLabel")){
      if (_currentFigure != null){
        String label = _currentCharData.toString();
        if (!label.equals("null"))
          _currentFigure.setYLabel(label.trim());
      }
    }
    else if (elementName.equals("plot")){
      // Make dataset using current _qtyX, _qtyY, _legend and add it to current Figure
      if (_currentFigure != null){
        _dlg.addDataSet(_currentFigureId-1, _qtyX, _qtyY, _legend, true, "points", _filters);
      }
    }
    else if (elementName.equals("nmblPlotTemplate")){
      // If done reading, update the dialog to have title, labels consistent with current figure
      _dlg.updateUIWithCurrentFigure();
    }
  }

  /** Handle character data.  In this implementation, the
   *  character data is accumulated in a buffer until the
   *  end element.
   *  &AElig;lfred will call this method once for each chunk of
   *  character data found in the contents of elements.  Note that
   *  the parser may break up a long sequence of characters into
   *  smaller chunks and call this method once for each chunk.
   *  @param chars The character data.
   *  @param offset The starting position in the array.
   *  @param length The number of characters available.
   */
  public void charData(char[] chars, int offset, int length) {
      _currentCharData.append(chars, offset, length);
  }
  public void parse(URL base, InputStream input) throws Exception {
      parse(base, new InputStreamReader(input));
  }

  /** Parse the given stream as a template file.
   *  A variety of exceptions might be thrown if the parsed
   *  data does not represent a valid template file.
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

  /** Parse the given text as template file.
   *  A variety of exceptions might be thrown if the parsed
   *  data does not represent valid template file.
   *  @param text The template.
   *  @exception Exception If the parser fails.
   */
  public void parse(URL base, String text) throws Exception {
      parse(base, new StringReader(text));
  }

  protected Hashtable _attributes;

  /** The current character data for the current element. */
  protected StringBuffer _currentCharData = new StringBuffer();

  /** The parser. */
  protected XmlParser _parser = new XmlParser();

  private URL _base;

  private OpenSimFigure _currentFigure = null;

  private int _currentFigureId = -1;

  private String _qtyX, _qtyY, _legend;

  private Vector _filters;
}
