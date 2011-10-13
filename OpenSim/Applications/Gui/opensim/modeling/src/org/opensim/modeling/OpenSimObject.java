/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class OpenSimObject {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public OpenSimObject(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(OpenSimObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_OpenSimObject(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public boolean equals(Object obj) {
    boolean equal = false;
    if (obj instanceof OpenSimObject)
      equal = (((OpenSimObject)obj).swigCPtr == this.swigCPtr);
    return equal;
  }
  private int cacheId=-1;  // cache the Id to avoid recomputation for hashing purposes
 
  public int hashCode() {
     if (cacheId==-1)
        cacheId=(int)swigCPtr;
     
    return( cacheId );
  }
  // Flag to indicate if an object is pickable in the GUI
  // Example of a non-pickable object would be a PathWrapPoint
  private boolean pickable=true;
  
  public boolean isPickable() {
	 return pickable;
  }
  
  public void setPickable(boolean onOff) {
	 pickable=onOff;
  }
  

  public OpenSimObject() {
    this(opensimModelJNI.new_OpenSimObject__SWIG_0(), true);
  }

  public OpenSimObject(String aFileName, boolean aUpdateFromXMLNode) throws java.io.IOException {
    this(opensimModelJNI.new_OpenSimObject__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public OpenSimObject(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_OpenSimObject__SWIG_2(aFileName), true);
  }

  public OpenSimObject(SWIGTYPE_p_OpenSim__XMLDocument aDocument) {
    this(opensimModelJNI.new_OpenSimObject__SWIG_3(SWIGTYPE_p_OpenSim__XMLDocument.getCPtr(aDocument)), true);
  }

  public OpenSimObject(SWIGTYPE_p_DOMElement aNode) {
    this(opensimModelJNI.new_OpenSimObject__SWIG_4(SWIGTYPE_p_DOMElement.getCPtr(aNode)), true);
  }

  public OpenSimObject(OpenSimObject aObject) {
    this(opensimModelJNI.new_OpenSimObject__SWIG_5(OpenSimObject.getCPtr(aObject), aObject), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.OpenSimObject_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject copy(SWIGTYPE_p_DOMElement aNode) {
    long cPtr = opensimModelJNI.OpenSimObject_copy__SWIG_1(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aNode));
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public static OpenSimObject SafeCopy(OpenSimObject aObject) {
    long cPtr = opensimModelJNI.OpenSimObject_SafeCopy(OpenSimObject.getCPtr(aObject), aObject);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public VisibleObject getDisplayer() {
    long cPtr = opensimModelJNI.OpenSimObject_getDisplayer(swigCPtr, this);
    return (cPtr == 0) ? null : new VisibleObject(cPtr, false);
  }

  public VisibleObject updDisplayer() {
    long cPtr = opensimModelJNI.OpenSimObject_updDisplayer(swigCPtr, this);
    return (cPtr == 0) ? null : new VisibleObject(cPtr, false);
  }

  public void renameChildNode(String aOldName, String aNewName, SWIGTYPE_p_DOMElement startNode) {
    opensimModelJNI.OpenSimObject_renameChildNode__SWIG_0(swigCPtr, this, aOldName, aNewName, SWIGTYPE_p_DOMElement.getCPtr(startNode));
  }

  public void renameChildNode(String aOldName, String aNewName) {
    opensimModelJNI.OpenSimObject_renameChildNode__SWIG_1(swigCPtr, this, aOldName, aNewName);
  }

  public void setType(String aType) {
    opensimModelJNI.OpenSimObject_setType(swigCPtr, this, aType);
  }

  public String getType() {
    return opensimModelJNI.OpenSimObject_getType(swigCPtr, this);
  }

  public void setName(String aName) {
    opensimModelJNI.OpenSimObject_setName(swigCPtr, this, aName);
  }

  public String getName() {
    return opensimModelJNI.OpenSimObject_getName(swigCPtr, this);
  }

  public void setDescription(String aDescrip) {
    opensimModelJNI.OpenSimObject_setDescription(swigCPtr, this, aDescrip);
  }

  public String getDescription() {
    return opensimModelJNI.OpenSimObject_getDescription(swigCPtr, this);
  }

  public String toString() {
    return opensimModelJNI.OpenSimObject_toString(swigCPtr, this);
  }

  public PropertySet getPropertySet() {
    return new PropertySet(opensimModelJNI.OpenSimObject_getPropertySet(swigCPtr, this), false);
  }

  public static void RegisterType(OpenSimObject aObject) {
    opensimModelJNI.OpenSimObject_RegisterType(OpenSimObject.getCPtr(aObject), aObject);
  }

  public static void RenameType(String oldTypeName, OpenSimObject aObjectOfNewType) {
    opensimModelJNI.OpenSimObject_RenameType(oldTypeName, OpenSimObject.getCPtr(aObjectOfNewType), aObjectOfNewType);
  }

  public static void setDebugLevel(int newLevel) {
    opensimModelJNI.OpenSimObject_setDebugLevel(newLevel);
  }

  public static int getDebugLevel() {
    return opensimModelJNI.OpenSimObject_getDebugLevel();
  }

  public static OpenSimObject makeObjectFromFile(String aFileName) {
    long cPtr = opensimModelJNI.OpenSimObject_makeObjectFromFile(aFileName);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public static OpenSimObject newInstanceOfType(String aType) {
    long cPtr = opensimModelJNI.OpenSimObject_newInstanceOfType(aType);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public static void getRegisteredTypenames(ArrayStr rTypeNames) {
    opensimModelJNI.OpenSimObject_getRegisteredTypenames(ArrayStr.getCPtr(rTypeNames), rTypeNames);
  }

  public boolean isValidDefaultType(OpenSimObject aObject) {
    return opensimModelJNI.OpenSimObject_isValidDefaultType(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public void updateFromXMLNode() {
    opensimModelJNI.OpenSimObject_updateFromXMLNode(swigCPtr, this);
  }

  public void updateDefaultObjectsFromXMLNode() {
    opensimModelJNI.OpenSimObject_updateDefaultObjectsFromXMLNode(swigCPtr, this);
  }

  public void updateXMLNode(SWIGTYPE_p_DOMElement aParent, int aNodeIndex) {
    opensimModelJNI.OpenSimObject_updateXMLNode__SWIG_0(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aParent), aNodeIndex);
  }

  public void updateXMLNode(SWIGTYPE_p_DOMElement aParent) {
    opensimModelJNI.OpenSimObject_updateXMLNode__SWIG_1(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aParent));
  }

  public void updateDefaultObjectsXMLNode(SWIGTYPE_p_DOMElement aParent) {
    opensimModelJNI.OpenSimObject_updateDefaultObjectsXMLNode(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aParent));
  }

  public void generateXMLNode(SWIGTYPE_p_DOMElement aParent, int aNodeIndex) {
    opensimModelJNI.OpenSimObject_generateXMLNode__SWIG_0(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aParent), aNodeIndex);
  }

  public void generateXMLNode(SWIGTYPE_p_DOMElement aParent) {
    opensimModelJNI.OpenSimObject_generateXMLNode__SWIG_1(swigCPtr, this, SWIGTYPE_p_DOMElement.getCPtr(aParent));
  }

  public boolean getInlined() {
    return opensimModelJNI.OpenSimObject_getInlined(swigCPtr, this);
  }

  public void setInlined(boolean aInlined, String aFileName) {
    opensimModelJNI.OpenSimObject_setInlined__SWIG_0(swigCPtr, this, aInlined, aFileName);
  }

  public void setInlined(boolean aInlined) {
    opensimModelJNI.OpenSimObject_setInlined__SWIG_1(swigCPtr, this, aInlined);
  }

  public SWIGTYPE_p_OpenSim__XMLDocument getDocument() {
    long cPtr = opensimModelJNI.OpenSimObject_getDocument(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__XMLDocument(cPtr, false);
  }

  public String getDocumentFileName() {
    return opensimModelJNI.OpenSimObject_getDocumentFileName(swigCPtr, this);
  }

  public SWIGTYPE_p_DOMElement getXMLNode() {
    long cPtr = opensimModelJNI.OpenSimObject_getXMLNode(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_DOMElement(cPtr, false);
  }

  public void clearXMLStructures() {
    opensimModelJNI.OpenSimObject_clearXMLStructures(swigCPtr, this);
  }

  public void setAllPropertiesUseDefault(boolean aUseDefault) {
    opensimModelJNI.OpenSimObject_setAllPropertiesUseDefault(swigCPtr, this, aUseDefault);
  }

  public boolean print(String aFileName) {
    return opensimModelJNI.OpenSimObject_print(swigCPtr, this, aFileName);
  }

  public static void PrintPropertyInfo(SWIGTYPE_p_std__ostream aOStream, String aClassNameDotPropertyName) {
    opensimModelJNI.OpenSimObject_PrintPropertyInfo__SWIG_0(SWIGTYPE_p_std__ostream.getCPtr(aOStream), aClassNameDotPropertyName);
  }

  public static void PrintPropertyInfo(SWIGTYPE_p_std__ostream aOStream, String aClassName, String aPropertyName) {
    opensimModelJNI.OpenSimObject_PrintPropertyInfo__SWIG_1(SWIGTYPE_p_std__ostream.getCPtr(aOStream), aClassName, aPropertyName);
  }

  public void addObserver(OpenSimObject aObserver) {
    opensimModelJNI.OpenSimObject_addObserver(swigCPtr, this, OpenSimObject.getCPtr(aObserver), aObserver);
  }

  public void deleteObserver(OpenSimObject aObserver) {
    opensimModelJNI.OpenSimObject_deleteObserver(swigCPtr, this, OpenSimObject.getCPtr(aObserver), aObserver);
  }

  public void addObserverEvent(OpenSimObject aObserver, SWIGTYPE_p_OpenSim__Event aEvent) {
    opensimModelJNI.OpenSimObject_addObserverEvent(swigCPtr, this, OpenSimObject.getCPtr(aObserver), aObserver, SWIGTYPE_p_OpenSim__Event.getCPtr(aEvent));
  }

  public void notifyObservers(SWIGTYPE_p_OpenSim__Event aEvent) {
    opensimModelJNI.OpenSimObject_notifyObservers(swigCPtr, this, SWIGTYPE_p_OpenSim__Event.getCPtr(aEvent));
  }

  public void deleteObservers() {
    opensimModelJNI.OpenSimObject_deleteObservers(swigCPtr, this);
  }

  public int countObservers() {
    return opensimModelJNI.OpenSimObject_countObservers(swigCPtr, this);
  }

  public void update(OpenSimObject aObject, SWIGTYPE_p_OpenSim__Event aEvent) {
    opensimModelJNI.OpenSimObject_update(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject, SWIGTYPE_p_OpenSim__Event.getCPtr(aEvent));
  }

  public static void setSerializeAllDefaults(boolean aBoolean) {
    opensimModelJNI.OpenSimObject_setSerializeAllDefaults(aBoolean);
  }

  public static boolean getSerializeAllDefaults() {
    return opensimModelJNI.OpenSimObject_getSerializeAllDefaults();
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.OpenSimObject_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.OpenSimObject_isA(swigCPtr, this, type);
  }

}
