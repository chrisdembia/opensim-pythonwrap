package simtkView;

import simtkModel.rdVisibleProperties;
import simtkui.SimtkApp;
import vtk.vtkProperty;

/**
 * This class is our wrapper around the vtkProperty. It serves as an adaptor
 * betweeen the visibleProperties class on the application side
 * (rdVisibleProperties) and the view specific class (vtkProperty)
 *
 * @todo handle colors properly and other options that are not directly supported by vtkProperty
 * for example displaying normals, or bounding-box or none.
 */
public class SimtkVisibleProperties extends rdVisibleProperties {
  private vtkProperty _vtpProperty=null;

  /**
   * SimtkVisibleProperties default constructor
   */
  public SimtkVisibleProperties() {
    _vtpProperty = new vtkProperty();
  }

  /**
   * SimtkVisibleProperties constructor that maps the passed in
   * rdVisibleProperties object to a vtkProperty.
   *
   * @param aProp rdVisibleProperties
   */
  public SimtkVisibleProperties(rdVisibleProperties aProp) {
    _vtpProperty = new vtkProperty();
    int pref = aProp.getDisplayPreference();
    if (pref == rdVisibleProperties.WireFrame)
      _vtpProperty.SetRepresentationToWireframe();
    else if (pref == rdVisibleProperties.FlatShaded)
      _vtpProperty.SetInterpolationToFlat();
    else if (pref == rdVisibleProperties.GouraudShaded)
      _vtpProperty.SetInterpolationToGouraud();
    else if (pref == rdVisibleProperties.PhongShaded)
      _vtpProperty.SetInterpolationToPhong();
    else if (pref == rdVisibleProperties.None ||
             pref == rdVisibleProperties.BoundingBox ||
             pref == rdVisibleProperties.SolidFill) {
            SimtkApp.displayWarningMessage(
                "SimtkVisibleProperties: DisplayPreference " +
                aProp.getDisplayPreference() +
                "has been ignored.");
            _vtpProperty.SetInterpolationToGouraud();
    }
    // Colors

    _vtpProperty.SetAmbientColor(1., 1., 1.);
    _vtpProperty.SetDiffuseColor(1., 1., 1.);
    _vtpProperty.SetSpecularColor(1., 1., 1.);
    _vtpProperty.SetOpacity(1.0);
    _vtpProperty.SetColor(1.0, .8, 0.6);
  }
  vtkProperty getVtkProperty()
  {
    return _vtpProperty;
  }
}
