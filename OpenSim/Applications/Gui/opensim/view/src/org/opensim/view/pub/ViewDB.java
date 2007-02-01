/*
 *
 * ViewDB
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view.pub;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JDialog;
import org.openide.awt.StatusDisplayer;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.openide.windows.TopComponent;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.view.*;
import vtk.AxesActor;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyPath;
import vtk.vtkMatrix4x4;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkProperty;

/**
 *
 * @author Ayman Habib
 *
 * A Database of Displayed models, and displayed windows ModelWindowVTKTopComponents
 * Also keeps track of currently activated model window ModelWindowVTKTopComponent
 */
public final class ViewDB implements Observer {
   // List of view windows currently displayed
   static ArrayList<ModelWindowVTKTopComponent> openWindows = new ArrayList<ModelWindowVTKTopComponent>(4);
   // List of models currently available in all views
   private static ArrayList<SingleModelVisuals> modelVisuals = new ArrayList<SingleModelVisuals>(4);
   // One single vtAssemby for the whole Scene
   private static vtkAssembly sceneAssembly;
   // Map models to visuals
   private Hashtable<AbstractModel, SingleModelVisuals> mapModelsToVisuals =
           new Hashtable<AbstractModel, SingleModelVisuals>();
   
   static ViewDB instance=null;
   // Window currently designated as current.
   private static ModelWindowVTKTopComponent currentModelWindow=null;
   
   static ArrayList<CallableSystemAction> modelCommands = new ArrayList<CallableSystemAction>(10);
   // Flag indicating whether new models are open in a new window or in the same window
   static boolean openModelInNewWindow=true;
   
   //private static AbstractModel currentModel=null;
   private OpenSimObject selectedObject=null;
   
   private vtkAssembly     axesAssembly=null;
   private boolean axesDisplayed=false;
   
   private boolean picking = false;

   /** Creates a new instance of ViewDB */
   private ViewDB() {
   }
   
   /**
    * Enforce a singleton pattern
    */
   public static ViewDB getInstance() {
      if (instance==null){
         instance = new ViewDB();
      }
      return instance;
   }
   
   public static ModelWindowVTKTopComponent getCurrenWindow() {
      return currentModelWindow;
   }
   /**
    * Keep track of current view window so that dialogs are cenetred on top of it if necessary.
    * Just a handy window to use.
    */
   public static void setCurrentModelWindow(ModelWindowVTKTopComponent aCurrentModelWindow) {
      currentModelWindow = aCurrentModelWindow;
   }
   
   /**
    * Model Commands are UI commands that are valid or should be enabled only
    * when at least one model is loaded in the application.
    * Events that change the number of models (e.g. open/close/...) should call
    * updateCommandsVisibility afterwards to update the enable/disable state of commands
    * by calling the setEnabled method.
    */
   public static void registerModelCommand(CallableSystemAction newCommand) {
      modelCommands.add(newCommand);
   }
   
   public static void updateCommandsVisibility() {
      boolean enable =  (OpenSimDB.getInstance().getNumModels())>0;
      Iterator<CallableSystemAction> iter = modelCommands.iterator();
      while (iter.hasNext()){
         iter.next().setEnabled(enable);
      }
   }
   /**
    * update Method is called whenever a model s added, removed and/or moved in the GUI
    * Observable should be of type OpenSimDB.
    */
   public void update(Observable o, Object arg) {
      if (o instanceof OpenSimDB){
         if (arg instanceof ModelEvent){
            ModelEvent ev = (ModelEvent)arg;
            // We need to detect if this the first time anything is loaded into the app
            // (or new project) if so we'll open a window, otherwise we will
            // display the new Model in existing views
            if (ev.getOperation()==ModelEvent.Operation.Open){
               createNewViewWindowIfNeeded();
               // Create visuals for the model
               SingleModelVisuals newModelVisual = new SingleModelVisuals(ev.getModel());
               if (sceneAssembly==null){
                  createScene();
                  // Add assembly to all views
                  Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
                  while(windowIter.hasNext()){
                     ModelWindowVTKTopComponent nextWindow = windowIter.next();
                     nextWindow.getCanvas().GetRenderer().AddViewProp(sceneAssembly);
                  }
               }
               // Compute placement so that model does not intersect others
               vtkMatrix4x4 m= getInitialTransform(newModelVisual);
               newModelVisual.getModelDisplayAssembly().SetUserMatrix(m);
               
               sceneAssembly.AddPart(newModelVisual.getModelDisplayAssembly());
               // Check if this refits scene into window
               
               Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
               while(windowIter.hasNext()){
                  ModelWindowVTKTopComponent nextWindow = windowIter.next();
                  // This line may need to be enclosed in a Lock /UnLock pair per vtkPanel
                  synchronized(nextWindow.getCanvas()){
                     nextWindow.getCanvas().GetRenderer().ResetCamera(sceneAssembly.GetBounds());
                  }
           
               }
               
               // add to list of models
               getModelVisuals().add(newModelVisual);
               // add to map from models to modelVisuals so that it's accesisble
               // thru tree picks
               mapModelsToVisuals.put(ev.getModel(), newModelVisual);
               
               repaintAll();
            }
            if (ev.getOperation()==ModelEvent.Operation.Close){
               AbstractModel dModel = ev.getModel();
               SingleModelVisuals visModel = mapModelsToVisuals.get(dModel);
               // Remove from display
               removeObjectFromScene(visModel.getModelDisplayAssembly());
               // Remove from lists
               modelVisuals.remove(visModel);
               updateCommandsVisibility();
            }
            // Current model has changed. For view purposes this affects available commands
            // Changes in the Tree view are handled by the Explorer View
            if (ev.getOperation()==ModelEvent.Operation.SetCurrent) {
               updateCommandsVisibility();
            }
           
         }
      }
   }
   
   public static ArrayList<SingleModelVisuals> getModelVisuals() {
      return modelVisuals;
   }

   public OpenSimObject pickObject(vtkAssemblyPath asmPath) {
      Iterator<SingleModelVisuals> iter = modelVisuals.iterator();
      while(iter.hasNext()){
         SingleModelVisuals nextModel = iter.next();
         OpenSimObject obj = nextModel.pickObject(asmPath);
         if (obj != null){
            // Find corresponding tree node
            
            return obj;
         }
      }
      return null;
   }
   
   /**
    * Get the object corresponding to selected vtkAssemblyPath
    **/
   OpenSimObject getObjectForVtkRep(vtkAssembly prop) {
      Iterator<SingleModelVisuals> iter = modelVisuals.iterator();
      while(iter.hasNext()){
         SingleModelVisuals nextModel = iter.next();
         OpenSimObject obj = nextModel.getObjectForVtkRep(prop);
         if (obj != null)
            return obj;
      }
      return null;
   }
   
   /**
    * Get the vtk object corresponding to passed in opensim object
    **/
   public vtkProp3D getVtkRepForObject(OpenSimObject obj) {
      Iterator<SingleModelVisuals> iter = modelVisuals.iterator();
      while(iter.hasNext()){
         SingleModelVisuals nextModel = iter.next();
         vtkProp3D objAssembly = nextModel.getVtkRepForObject(obj);
         if (objAssembly != null)
            return objAssembly;
      }
      return null;
   }
   /**
    * removeWindow removes the passed in window form the list of windows maintaiined
    * by ViewDB
    **/
   public void removeWindow(ModelWindowVTKTopComponent modelWindowVTKTopComponent) {
      openWindows.remove(modelWindowVTKTopComponent);
   }
   /**
    * Add a new Viewing. window
    */
   public void addViewWindow() {
      // Create the window
      ModelWindowVTKTopComponent win = new ModelWindowVTKTopComponent();
      // Fix name
      int ct=0;
      while(!ViewDB.getInstance().checkValidViewName(win.getDisplayName(), win)){
         win.setTabDisplayName(NbBundle.getMessage(
                 ModelWindowVTKTopComponent.class,
                 "UnsavedModelNameFormat",
                 new Object[] { new Integer(ct++) }
         ));
      };
      win.open();
      win.requestActive();
      setCurrentModelWindow(win);
      // Open it and make it active
      openWindows.add(win);
      win.getCanvas().GetRenderer().AddViewProp(sceneAssembly);
      repaintAll();
   }
   /**
    * Helper function to implement model hide/show.
    *
    */
   public void toggleModelDisplay(AbstractModel model) {
      SingleModelVisuals modelVis = mapModelsToVisuals.get(model);
      modelVis.setVisible(!modelVis.isVisible());
      if (modelVis.isVisible())
         sceneAssembly.AddPart(modelVis.getModelDisplayAssembly());
      else
         sceneAssembly.RemovePart(modelVis.getModelDisplayAssembly());
      repaintAll();
   }
   /**
    * Decide if a new window is needed to be created. Right now this's done only first time the application
    * is started. This may need to be change when a new project is opened
    */
   private void createNewViewWindowIfNeeded() {
      if (openModelInNewWindow){
         ModelWindowVTKTopComponent win = new ModelWindowVTKTopComponent();
         win.open();
         win.requestActive();
         openWindows.add(win);
         openModelInNewWindow=false;
         setCurrentModelWindow(win);
      }
   }
   /**
    * Add an arbirary Object to the scene (all views)
    */
   public void addObjectToScene(vtkProp3D aProp) {
      sceneAssembly.AddPart(aProp);
      repaintAll();
   }
   
   /**
    * Remove an arbirary Object from the scene (all views)
    */
   public void removeObjectFromScene(vtkProp3D aProp) {
      sceneAssembly.RemovePart(aProp);
      repaintAll();
   }
   /**
    * Return a flag indicating whether the model is currently shown or hidden
    */
   public boolean getDisplayStatus(AbstractModel m) {
      return mapModelsToVisuals.get(m).isVisible();
      
   }
   
   public static AbstractModel getCurrentModel() {
      return OpenSimDB.getInstance().getCurrentModel();
   }
   
   public void adjustModelDisplayOffset(AbstractModel abstractModel, TopComponent tc) {
      // Show dialog for model display ajdustment
      SingleModelVisuals rep = mapModelsToVisuals.get(abstractModel);
      JDialog dlg = new ModelDisplayEditJDialog(null, false, rep, abstractModel);
      dlg.setLocationRelativeTo(tc);
      dlg.setVisible(true);
      
   }
   /**
    * Cycle through displayed windows and repaint them
    */
   public void repaintAll() {
      Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
      while(windowIter.hasNext()){
         windowIter.next().getCanvas().repaint();
      }
   }
   
   /**
    * Set the color of the passed in object.
    */
   public void setObjectColor(OpenSimObject object, double[] colorComponents) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      applyColor(colorComponents, asm);
   }

   private void applyColor(final double[] colorComponents, final vtkProp3D asm) {
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         vtkProp3D prop = parts.GetNextProp3D();
         vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         while (prop != null) {
            if (part != null)
               part.GetProperty().SetColor(colorComponents);
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      }
      else if (asm instanceof vtkActor){
         ((vtkActor) asm).GetProperty().SetColor(colorComponents);
      }
      repaintAll();
   }
   /**
    * Set the Opacity of the passed in object to newOpacity
    */
   public void setObjectOpacity(OpenSimObject object, double newOpacity) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      applyOpacity(newOpacity, asm);
   }
   
   private void applyOpacity(final double newOpacity, final vtkProp3D asm) {
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         int n =parts.GetNumberOfItems();
         for(int i=0; i<n; i++){
            vtkProp3D prop = parts.GetNextProp3D();
            if (prop instanceof vtkAssembly){   //recur
               applyOpacity(newOpacity, (vtkAssembly) prop);
               // Should continue traversal here
            } else if (prop instanceof vtkActor){ // Could be Actor or ?
               ((vtkActor)prop).GetProperty().SetOpacity(newOpacity);
            }
         }
      }
      else if (asm instanceof vtkActor){
         ((vtkActor) asm).GetProperty().SetOpacity(newOpacity);
      }
      repaintAll();
   }
   /*
   public void applyOpacityToAssembly(vtkAssembly assembly, double opacity) {
      vtkProp3DCollection parts = assembly.GetParts();
      parts.InitTraversal();
      vtkProp3D prop = parts.GetNextProp3D();
      if (prop instanceof vtkActor){  // We're at the lowest level of the assembly
         vtkActor part = (vtkActor)prop;
         while (prop != null) {
            if (part != null)
               part.GetProperty().SetOpacity(opacity);
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      } else if (prop instanceof vtkAssembly){
         applyOpacityToAssembly((vtkAssembly)prop, opacity);
      }
   }
    **/
   /**
    * Retrieve the display properties for the passed in object.
    */
   public void getObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      if (asm==null)  // Object is not displayed for some reason
         return;
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         vtkProp3D prop = parts.GetNextProp3D();
         vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         while (prop != null) {
            if (part != null){
               saveProperty.SetColor(part.GetProperty().GetColor());
               saveProperty.SetOpacity(part.GetProperty().GetOpacity());
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      }
      else if (asm instanceof vtkActor){
         vtkActor part = (vtkActor)asm;
         saveProperty.SetColor(part.GetProperty().GetColor());
         saveProperty.SetOpacity(part.GetProperty().GetOpacity());
      }
   }
   public void setObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
      setObjectColor(object, saveProperty.GetColor());
      setObjectOpacity(object, saveProperty.GetOpacity());
      repaintAll();
   }
   /**
    * Selection related functions
    */
   
   /**
    * Mark an object as selected (on/off).
    * Does nothing ofr now but we may change it to indicate selection by showing in 
    * different color, or in different representation or both
    */
   public void markSelected(OpenSimObject selectedObject, boolean onOff) {

   }
   
   public OpenSimObject getSelectedObject() {
      return selectedObject;
   }
   
   public void setSelectedObject(OpenSimObject selectedObject) {
      this.selectedObject = selectedObject;
      if (selectedObject != null){
         markSelected(selectedObject, true);
         StatusDisplayer.getDefault().setStatusText(selectedObject.getType()+", "+selectedObject.getName());
      } else
         StatusDisplayer.getDefault().setStatusText("");
   }
   /**
    * Check if the name passed in is a valid name for a display window (no duplicates
    * for now, until a more restricted naming is needed
    *
    * returns true if newName is a valid name for the passed in view, false otherwise
    */
   public boolean checkValidViewName(String newName, ModelWindowVTKTopComponent view) {
      boolean valid = true;
      Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
      while(windowIter.hasNext() && valid){
         ModelWindowVTKTopComponent nextWindow = windowIter.next();
         String nextWindowName = nextWindow.getDisplayName();
         if(nextWindowName.equalsIgnoreCase(newName)){
            valid = (view.equals(nextWindow));
         }
      }
      return valid;
   }
   /**
    * Compute initial offset for a model when displayed.
    * To account for user prefs a property is made
    * just put the model somewhere so that it does not intersect other models.
    *
    * newModelVisual has not been added to the list yet.
    *
    * @todo should we allow for rotations as well?
    *
    */
   private vtkMatrix4x4 getInitialTransform(SingleModelVisuals newModelVisual) {
      vtkMatrix4x4 m = new vtkMatrix4x4();
      Iterator<SingleModelVisuals> iter = modelVisuals.iterator();
      double modelBounds[] = newModelVisual.getModelDisplayAssembly().GetBounds();
      // If at least one model exists compute bounding box for the scene
      // and place the new model outside the box along z-axis.
      // This could be made into an option where models are placed along X, Y or Z
      // Also possible to define a default offset in any direction and reuse it.
      if (iter.hasNext()){
         double bounds[]= sceneAssembly.GetBounds();
         String defaultOffsetDirection = NbBundle.getMessage(ViewDB.class,"CTL_DisplayOffsetDir");
         if (defaultOffsetDirection == null)
            defaultOffsetDirection="Z";
         if (defaultOffsetDirection.equalsIgnoreCase("X"))
            m.SetElement(0, 3, bounds[1]-modelBounds[0]);
         else if (defaultOffsetDirection.equalsIgnoreCase("Y"))
            m.SetElement(1, 3, bounds[3]-modelBounds[2]);
         else
            m.SetElement(2, 3, bounds[5]-modelBounds[4]);
      }
      return m;
   }
   /**
    * get method for the visualization transform (to place a model in a scene).
    */
   public vtkMatrix4x4 getModelVisualsTranform(SingleModelVisuals aModelVisual) {
      return aModelVisual.getModelDisplayAssembly().GetUserMatrix();
   }
   /**
    * set method for the visualization transform (to place a model in a scene).
    */
   public void setModelVisualsTranform(SingleModelVisuals aModelVisual, vtkMatrix4x4 newTransform) {
      aModelVisual.getModelDisplayAssembly().SetUserMatrix(newTransform);
   }
   /**
    * Get a box around the whole scene. Used to fill an intial guess of the bounds for the model display
    */
   public double[] getSceneBounds() {
      double[] sceneBounds = new double[6];
      sceneAssembly.GetBounds(sceneBounds);
      return sceneBounds;
   }
   /**
    * createScene is invoked once to create the assembly representing the scene
    * that models attach to. If all windows are closed then this function will not be called again.
    */
   private void createScene() {
      sceneAssembly = new vtkAssembly();
      axesAssembly = new AxesActor();
   }
   
   public void showAxes(boolean trueFalse) {
      if (trueFalse)
         addObjectToScene(axesAssembly);
      else
         removeObjectFromScene(axesAssembly);
      setAxesDisplayed(trueFalse);
   }
   
   public boolean isAxesDisplayed() {
      return axesDisplayed;
   }
   
   public void setAxesDisplayed(boolean axesDisplayed) {
      this.axesDisplayed = axesDisplayed;
   }
   
   /**
    * Search the list of displayed models for the passed in model and if found return
    * its visuals, otherwise return null
    */
   public SingleModelVisuals getModelVisuals(AbstractModel aModel) {
      return mapModelsToVisuals.get(aModel);
   }
   /**
    * This function is called from a timer thread that runs parallel to the simulation thread
    * Obviously should run as fast as possible. 
    * We could get visModel from animationCallback using getModelVisuals(animationCallback.getModel())
    * but that's another map search.
    */
   public void updateModelDisplay(SingleModelVisuals visModel, SimtkAnimationCallback animationCallback) {
      visModel.updateModelDisplay(animationCallback);
      repaintAll();
   }

   /**
    * For a single OpenSimObject, toggle display hide/show
    */
   public void toggleObjectDisplay(OpenSimObject openSimObject) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(openSimObject);
      if (asm==null)  // Object is not displayed for some reason
         return ;
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         vtkProp3D prop = parts.GetNextProp3D();
         vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         boolean visible=false;
         while (prop != null) {
            if (part != null){
               part.SetVisibility(1-part.GetVisibility());
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      }
      else if (asm instanceof vtkActor){
         vtkActor part = (vtkActor)asm;
         part.SetVisibility(1-part.GetVisibility());
      }
      repaintAll();
   }
   /**
    * Return a flag indicating if an object is displayed or not
    **/
   public boolean getDisplayStatus(OpenSimObject openSimObject) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(openSimObject);
      boolean visible=false;
      if (asm==null)  // Object is not displayed for some reason
         return visible;
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         vtkProp3D prop = parts.GetNextProp3D();
         vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         while (prop != null) {
            if (part != null){
               if (part.GetVisibility()==1){ // if any part is visible the object is visible
                  visible=true;
                  break;
               };
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      } else if (asm instanceof vtkActor){
         if (((vtkActor)asm).GetVisibility()==1) // if any part is visible the object is visible
            visible=true;
         
      }
      return visible;
   }
   /**
    * Change representation of a visible object to the one passed in.
    * The encoding is from VTK and is defined as follows:
    * 0. Points
    * 1. Wireframe
    * 2. Surface
    *
    * Shading is defined similarly but only if representation is Surface(2)
    * 0. Flat
    * 1. Gouraud
    * 2. Phong
    * defined in vtkProperty.h
    */
   public void setObjectRepresentation(OpenSimObject object, int rep, int newShading) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         vtkProp3D prop = parts.GetNextProp3D();
         vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         while (prop != null) {
            if (part != null){
               part.GetProperty().SetRepresentation(rep);
               if (rep==2){   // Surface shading
                  part.GetProperty().SetInterpolation(newShading);
               }
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
         }
      } else if (asm instanceof vtkActor){
         vtkActor part = (vtkActor)asm;
         part.GetProperty().SetRepresentation(rep);
         if (rep==2){   // Surface shading
            part.GetProperty().SetInterpolation(newShading);
         }
      }
      repaintAll();
   }

   public boolean isPicking() {
      return picking;
   }

   public void setPicking(boolean picking) {
      this.picking = picking;
   }

}
