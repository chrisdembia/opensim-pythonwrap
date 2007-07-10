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

import java.awt.Dialog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;
import java.util.Set;
import java.util.prefs.Preferences;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.awt.StatusDisplayer;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ArrayPtrsObj;
import org.opensim.modeling.Model;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.ObjectGroup;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.VisibleObject;
import org.opensim.modeling.VisibleProperties;
import org.opensim.modeling.VisibleProperties.DisplayPreference;
import org.opensim.utils.TheApp;
import org.opensim.view.*;
import vtk.AxesActor;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyPath;
import vtk.vtkFollower;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkProperty;
import vtk.vtkVectorText;

/**
 *
 * @author Ayman Habib
 *
 * A Database of Displayed models, and displayed windows ModelWindowVTKTopComponents
 * Also keeps track of currently activated model window ModelWindowVTKTopComponent
 */
public final class ViewDB extends Observable implements Observer {
   // List of view windows currently displayed
   static ArrayList<ModelWindowVTKTopComponent> openWindows = new ArrayList<ModelWindowVTKTopComponent>(4);
   // List of models currently available in all views
   private static ArrayList<SingleModelVisuals> modelVisuals = new ArrayList<SingleModelVisuals>(4);
   private static ArrayList<Boolean> saveStatus = new ArrayList<Boolean>(4);
   // One single vtAssemby for the whole Scene
   private static vtkAssembly sceneAssembly;
   // Map models to visuals
   private Hashtable<Model, SingleModelVisuals> mapModelsToVisuals =
           new Hashtable<Model, SingleModelVisuals>();
   private Hashtable<Model, SingleModelGuiElements> mapModelsToGuiElements =
           new Hashtable<Model, SingleModelGuiElements>();
   
   private Hashtable<Model, ModelSettingsSerializer> mapModelsToSettings =
           new Hashtable<Model, ModelSettingsSerializer>();
   static ViewDB instance=null;
   // Window currently designated as current.
   private static ModelWindowVTKTopComponent currentModelWindow=null;
   
   static ArrayList<CallableSystemAction> modelCommands = new ArrayList<CallableSystemAction>(10);
   // Flag indicating whether new models are open in a new window or in the same window
   static boolean openModelInNewWindow=true;
   
   private ArrayList<SelectedObject> selectedObjects = new ArrayList<SelectedObject>(0);
   
   private vtkAssembly     axesAssembly=null;
   private boolean axesDisplayed=false;
   
   private boolean picking = false;
   private boolean dragging = false;
   private double draggingZ = 0.0;

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
   
    // The setChanged() protected method must overridden to make it public
    public synchronized void setChanged() {
        super.setChanged();
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
               Model model = ev.getModel();
               SingleModelVisuals newModelVisual = new SingleModelVisuals(model);
               SingleModelGuiElements newModelGuiElements = new SingleModelGuiElements(model);
               processSavedSettings(model);
               // add to map from models to modelVisuals so that it's accesisble
               // thru tree picks
               mapModelsToVisuals.put(ev.getModel(), newModelVisual);
               mapModelsToGuiElements.put(ev.getModel(), newModelGuiElements);
               //From here on we're adding things to display so we better lock'
               
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
                  lockDrawingSurfaces(true);
                  nextWindow.getCanvas().GetRenderer().ResetCamera(sceneAssembly.GetBounds());
                  lockDrawingSurfaces(false);
               }
               // add to list of models
               getModelVisuals().add(newModelVisual);
               repaintAll();
            }
            else if (ev.getOperation()==ModelEvent.Operation.Close){
               Model dModel = ev.getModel();
               // Remove model-associated objects from selection list!
               removeObjectsBelongingToModelFromSelection(dModel);
               SingleModelVisuals visModel = mapModelsToVisuals.get(dModel);
               // Remove from display
               removeObjectFromScene(visModel.getModelDisplayAssembly());
               // Remove from lists
               modelVisuals.remove(visModel);
               mapModelsToVisuals.remove(dModel);
               mapModelsToGuiElements.remove(dModel);
               mapModelsToSettings.remove(dModel);
               //StatusDisplayer.getDefault().setStatusText("mapModelsToVisuals size="+mapModelsToVisuals.size());
               updateCommandsVisibility();
            }
            // Current model has changed. For view purposes this affects available commands
            // Changes in the Tree view are handled by the Explorer View
            else if (ev.getOperation()==ModelEvent.Operation.SetCurrent) {
               updateCommandsVisibility();
            }
            else if (ev.getOperation()==ModelEvent.Operation.Save) {
               // If a model is saved then its document filename has changed and we should update the settings file accordingly
               updateSettingsSerializer(ev.getModel());
            }
           
         } else if (arg instanceof NameChangedEvent){
            NameChangedEvent ev = (NameChangedEvent)arg;
            repaintAll();
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
      // If the user manually added a new view, we won't need to automatically create a new one when model is loaded.
      openModelInNewWindow=false;
   }
   /**
    * Helper function to implement model hide/show.
    *
    */
   public void toggleModelDisplay(Model model) {
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
         final ModelWindowVTKTopComponent win = new ModelWindowVTKTopComponent();
         win.requestActive();
         openWindows.add(win);
         openModelInNewWindow=false;
         setCurrentModelWindow(win);
         // open window later rather than now to avoid having a rectangular blank patch appearing over the GUI while
         // the model is loading and the scene is set up
         SwingUtilities.invokeLater(new Runnable(){
            public void run(){
               win.open();
            }});
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
   public boolean getDisplayStatus(Model m) {
      return mapModelsToVisuals.get(m).isVisible();
      
   }
   
   public static Model getCurrentModel() {
      return OpenSimDB.getInstance().getCurrentModel();
   }
   /**
    * Show dialog to adjust display offset and modify display according to user options
    */
   public void adjustModelDisplayOffset(Model abstractModel) {
      // Show dialog for model display ajdustment
      final ModelDisplayOffsetJPanel p = new ModelDisplayOffsetJPanel(abstractModel);
      DialogDescriptor desc = new DialogDescriptor(p, "Model offset control", false, new ActionListener() {

         public void actionPerformed(ActionEvent e) {
            if (e.getActionCommand().equalsIgnoreCase("Cancel"))
               p.restore();
         }
      });
      Dialog dlg = DialogDisplayer.getDefault().createDialog(desc);
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

   public void renderAll() {
      Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
      while(windowIter.hasNext()){
         windowIter.next().getCanvas().Render();
      }
   }
   
   /**
    * Set the color of the passed in object.
    */
   public void setObjectColor(OpenSimObject object, double[] colorComponents) {
      MusclePoint mp = MusclePoint.safeDownCast(object);
      if (mp != null) {
         SingleModelVisuals visuals = getModelVisuals(mp.getMuscle().getModel());
         OpenSimvtkGlyphCloud cloud = visuals.getMusclePointsRep();
         // TODO: since muscle points are colored by a scalar, you need to
         // find the scalar value that most closely matches the passed-in
         // colorComponents.
         // 0.0 = red
         // 0.1 = orange
         // 0.3 = yellow
         // 0.5 = green
         // 0.7 = cyan
         // 1.0 = blue
         // Colors such as purple cannot be represented using this mechanism
         cloud.setScalarDataAtLocation(cloud.getPointId(object), 0.28);
         AbstractMuscle m = mp.getMuscle();
         visuals.updateActuatorGeometry(m, false); //TODO: perhaps overkill for getting musclepoint to update?
      } else { // should check for body here
         vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
         applyColor(colorComponents, asm);
      }
   }

   public void applyColor(final double[] colorComponents, final vtkProp3D asm) {
      ApplyFunctionToActors(asm, new ActorFunctionApplier() {
         public void apply(vtkActor actor) { actor.GetProperty().SetColor(colorComponents); }});
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
      ApplyFunctionToActors(asm, new ActorFunctionApplier() {
         public void apply(vtkActor actor) { actor.GetProperty().SetOpacity(newOpacity); }});
      repaintAll();
   }
   /**
    * Retrieve the display properties for the passed in object.
    */
   public void getObjectProperties(OpenSimObject object, final vtkProperty saveProperty) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      ApplyFunctionToActors(asm, new ActorFunctionApplier() {
         public void apply(vtkActor actor) { 
            saveProperty.SetColor(actor.GetProperty().GetColor());
            saveProperty.SetOpacity(actor.GetProperty().GetOpacity()); }});
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
    * Remove items from selection list which belong to the given model
    */
   public void removeObjectsBelongingToModelFromSelection(Model model)
   {
      boolean modified = false;
      for(int i=selectedObjects.size()-1; i>=0; i--) {
         Model ownerModel = selectedObjects.get(i).getOwnerModel();
         if(Model.getCPtr(model) == Model.getCPtr(ownerModel)) {
            markSelected(selectedObjects.get(i), false, false, true);
            selectedObjects.remove(i);
            modified = true;
         }
      }
      if(modified) {
         statusDisplaySelectedObjects();
         repaintAll();
      }
   }
   
   /**
    * Mark an object as selected (on/off).
    *
    */
   public void markSelected(SelectedObject selectedObject, boolean highlight, boolean sendEvent, boolean updateStatusDisplayAndRepaint) {
      selectedObject.markSelected(highlight);

      if(updateStatusDisplayAndRepaint) {
         statusDisplaySelectedObjects();
         repaintAll();
      }

      if(sendEvent) {
         ObjectSelectedEvent evnt = new ObjectSelectedEvent(this, selectedObject, highlight);
         setChanged();
         notifyObservers(evnt);
      }
   }
   
   public ArrayList<SelectedObject> getSelectedObjects() {
      return selectedObjects;
   }

   public void statusDisplaySelectedObjects() {
      String status="";
      for(int i=0; i<selectedObjects.size(); i++) {
         if(i>0) status += ", ";
         status += selectedObjects.get(i).getStatusText();
      }
      StatusDisplayer.getDefault().setStatusText(status);
   }

   public void setSelectedObject(OpenSimObject obj) {
      clearSelectedObjects();

      if (obj != null) {
         SelectedObject selectedObject = new SelectedObject(obj);
         selectedObjects.add(selectedObject);
         markSelected(selectedObject, true, true, true);
      } else { // this function should never be called with obj = null
         ClearSelectedObjectsEvent evnt = new ClearSelectedObjectsEvent(this);
         setChanged();
         notifyObservers(evnt);
      }
   }

   private int findObjectInSelectedList(OpenSimObject obj) {
      for (int i = 0; i < selectedObjects.size(); i++) 
         if (OpenSimObject.getCPtr(obj) == OpenSimObject.getCPtr(selectedObjects.get(i).getOpenSimObject()))
            return i;
      return -1;
   }

   private boolean removeObjectFromSelectedList(OpenSimObject obj) {
      int i = findObjectInSelectedList(obj);
      if(i >= 0) {
         // mark it as unselected
         markSelected(selectedObjects.get(i), false, true, true);
         // remove the object from the list of selected ones
         selectedObjects.remove(i);
         return true;
      }
      return false;
   }

   public void toggleAddSelectedObject(OpenSimObject obj) {
      // If the object is already in the list, remove it
      if (removeObjectFromSelectedList(obj) == false) {
         // If the object is not already in the list, add it
         SelectedObject selectedObject = new SelectedObject(obj);
         selectedObjects.add(selectedObject);
         // mark it as selected
         markSelected(selectedObject, true, true, true);
      }
   }

   public void replaceSelectedObject(OpenSimObject obj) {
      // If the object is already in the list of selected ones, do nothing (a la Illustrator)
      // If the object is not already in the list, make this object the only selected one
      if(!isSelected(obj)) setSelectedObject(obj);
   }

   public void clearSelectedObjects() {
      for (int i = 0; i < selectedObjects.size(); i++) {
         // mark it as unselected
         markSelected(selectedObjects.get(i), false, true, false);
      }
      selectedObjects.clear();
      statusDisplaySelectedObjects();
      repaintAll();
   }

   public boolean isSelected(OpenSimObject obj) {
      return (findObjectInSelectedList(obj) >= 0);
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
         defaultOffsetDirection=Preferences.userNodeForPackage(TheApp.class).get("DisplayOffsetDir", defaultOffsetDirection);
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
   public SingleModelVisuals getModelVisuals(Model aModel) {
      return mapModelsToVisuals.get(aModel);
   }
   
   /**
    * Get gui elements for passed in model
    */
   public SingleModelGuiElements getModelGuiElements(Model aModel) {
      return mapModelsToGuiElements.get(aModel);
   }
   /**
    * This function is called from a timer thread that runs parallel to the simulation thread
    * Obviously should run as fast as possible. 
    * We could get visModel from animationCallback using getModelVisuals(animationCallback.getModel())
    * but that's another map search.
    */
   public void updateModelDisplay(Model aModel) {
      lockDrawingSurfaces(true);
      mapModelsToVisuals.get(aModel).updateModelDisplay(aModel);
      lockDrawingSurfaces(false);
      repaintAll();
   }
   public void updateModelDisplayNoRepaint(Model aModel) {
      lockDrawingSurfaces(true);
      mapModelsToVisuals.get(aModel).updateModelDisplay(aModel);
      lockDrawingSurfaces(false);
   }

   /**
    * For a single OpenSimObject, toggle display hide/show
    */
   public void toggleObjectsDisplay(OpenSimObject openSimObject, boolean visible) {
      ObjectGroup group = ObjectGroup.safeDownCast(openSimObject);
      if (group != null) {
         ArrayPtrsObj members = group.getMembers();
         for (int i = 0; i < members.getSize(); i++) {
            toggleObjectDisplay(members.get(i), visible);
         }
      } else {
         toggleObjectDisplay(openSimObject, visible);
      }
   }

   public void toggleObjectDisplay(OpenSimObject openSimObject, boolean visible) {
      // use VisibleObject to hold on/off status, and
      // do not repaint the windows or update any geometry because
      // this is now handled by the functions that call toggleObjectDisplay().
      VisibleObject vo = openSimObject.getDisplayer();
      if (vo != null) {
         VisibleProperties vp = vo.getVisibleProperties();
         DisplayPreference dp = vp.getDisplayPreference();
         if (visible == true)
            vp.setDisplayPreference(DisplayPreference.GouraudShaded); // TODO: assumes gouraud is the default
         else
            vp.setDisplayPreference(DisplayPreference.None);
      }

      AbstractActuator act = AbstractActuator.safeDownCast(openSimObject);
      if (act != null) {
         SingleModelVisuals vis = getModelVisuals(act.getModel());
         vis.updateActuatorGeometry(act, visible); // call act.updateGeometry() if actuator is becoming visible
         return;
      }

      // If the object is a vtkAssembly or vtkActor, sets its visibility that way too.
      final int vtkVisible = visible ? 1 : 0;
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(openSimObject);
      ApplyFunctionToActors(asm, new ActorFunctionApplier() {
         public void apply(vtkActor actor) {
            actor.SetVisibility(vtkVisible);
            actor.SetPickable(vtkVisible);
         }});
   }
   /**
    * Return a flag indicating if an object is displayed or not
    **/
   public int getDisplayStatus(OpenSimObject openSimObject) {
      int visible = 0;
      ObjectGroup group = ObjectGroup.safeDownCast(openSimObject);
      if (group != null) {
         boolean foundHidden = false;
         boolean foundShown = false;
         ArrayPtrsObj members = group.getMembers();
         for (int i = 0; i < members.getSize(); i++) {
            VisibleObject vo = members.get(i).getDisplayer();
            if (vo != null) {
               DisplayPreference dp = vo.getVisibleProperties().getDisplayPreference();
               if (dp == DisplayPreference.None)
                  foundHidden = true;
               else
                  foundShown = true;
            }
         }
         // If the group contains hidden members and shown members, return 2 (mixed).
         // If the group contains only hidden members, return 0 (hidden).
         // If the group contains only shown members, return 1 (shown).
         if (foundHidden == true && foundShown == true)
            return 2;
         else if (foundHidden == true)
            return 0;
         else
            return 1;
      } else {
         VisibleObject vo = openSimObject.getDisplayer();
         if (vo != null) {
            DisplayPreference dp = vo.getVisibleProperties().getDisplayPreference();
            if (dp != DisplayPreference.None)
               visible = 1;
         }
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
   public void setObjectRepresentation(OpenSimObject object, final int rep, final int newShading) {
      vtkProp3D asm = ViewDB.getInstance().getVtkRepForObject(object);
      ApplyFunctionToActors(asm, new ActorFunctionApplier() {
         public void apply(vtkActor actor) {
            actor.GetProperty().SetRepresentation(rep);
            if (rep==2){   // Surface shading
               actor.GetProperty().SetInterpolation(newShading);
            }
         }});
      repaintAll();
   }

   public boolean isPicking() {
      return picking;
   }

   public void setPicking(boolean picking) {
      this.picking = picking;
      if (picking)
         dragging = false;
   }

   public boolean isDragging() {
      return dragging;
   }

   public void setDragging(boolean dragging, OpenSimObject obj) {
      this.dragging = dragging;
      if (dragging) {
         // obj not currently used, but it points to the object that was
         // clicked on to initiate dragging
         picking = false;
      }
   }

   public void dragSelectedObjects(OpenSimObject clickedObject, double dragVector[]) {
      DragObjectsEvent evnt = new DragObjectsEvent(clickedObject, dragVector);
      setChanged();
      notifyObservers(evnt);
   }

   private void lockDrawingSurfaces(boolean toLock) {
      Iterator<ModelWindowVTKTopComponent> windowIter = openWindows.iterator();
      while(windowIter.hasNext()){
         ModelWindowVTKTopComponent nextWindow = windowIter.next();
         nextWindow.getCanvas().lockDrawingSurface(toLock);
      }
   }

    public void IsolateCurrentModel() {
        final SingleModelVisuals vis = mapModelsToVisuals.get(getCurrentModel());
        vtkVectorText atext = new vtkVectorText();
        atext.SetText("Current Model");
        vtkPolyDataMapper textMapper = new vtkPolyDataMapper();
        textMapper.SetInput(atext.GetOutput());
        final vtkFollower textActor = new vtkFollower();
        textActor.SetMapper(textMapper);
        textActor.SetScale(0.1, 0.1, 0.1);
        textActor.AddPosition(0., 0., 0.);
        vis.addUserObject(textActor);
        repaintAll();
        
        // start timer to hide annotation in 5 secs
        ActionListener hideAnnotationAction = new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                vis.removeUserObject(textActor);
                repaintAll();
            }};
        Timer hideAnnotationTimer = new Timer(5000, hideAnnotationAction);
        hideAnnotationTimer.setRepeats(false);
        hideAnnotationTimer.start();
        
    }

    public void hideOthers(Model mdl, boolean b) {
        int sz = mapModelsToVisuals.size();
        Set<Model> modelSet=mapModelsToVisuals.keySet();
        Iterator<Model> modelit = modelSet.iterator();
        if (b)
            saveStatus.clear();
        int i=0;
        while(modelit.hasNext()){
            Model nextModel = modelit.next();
            boolean isVisible = getDisplayStatus(nextModel);
            // remember old state then turn off (if b = true)
            if (b){
                saveStatus.add(new Boolean(isVisible));
                if (isVisible && mdl != nextModel)
                    toggleModelDisplay(nextModel);
            }
            else{ // restore from saveStatus array
                boolean savedVis = saveStatus.get(i).booleanValue();
                if (savedVis && nextModel!=mdl)
                    toggleModelDisplay(nextModel);
            }
            i++;
        }
    }

    public OpenSimObject getSelectedGlyphObject(int cellId, vtkActor glyphActor) {
        Iterator<SingleModelVisuals> iter = modelVisuals.iterator();
        while(iter.hasNext()){
            SingleModelVisuals nextModel = iter.next();
            OpenSimvtkGlyphCloud glyph = nextModel.getGlyphObjectForActor(glyphActor);
            if (glyph!=null)
                return glyph.getPickedObject(cellId);
        }
        return null;
    }
    
    /**
     * User Objects manipulation. Delegate to proper model
     */
    public void addUserObject(Model model, vtkActor vtkActor) {
        SingleModelVisuals visModel = mapModelsToVisuals.get(model);
        visModel.addUserObject(vtkActor);
    }

    public void removeUserObject(Model model, vtkActor vtkActor) {
       SingleModelVisuals visModel = mapModelsToVisuals.get(model);
       visModel.removeUserObject(vtkActor);
    }
/*
 * Functions to deal with saved "Settings"
 * processSavedSettings parses the [modelFileWithoutExtension]_settings.xml file
 */
   private String getDefaultSettingsFileName(Model model) {
      String modelFileName = model.getInputFileName(); // TODO: should we use DocumentFileName or InputFileName?
      if(modelFileName==null || modelFileName.length()==0) return null;
      else return modelFileName.substring(0, modelFileName.indexOf("."))+"_settings.xml";
   }
   private void processSavedSettings(Model model) {
      // Read settings file if exist, should have file name =
      // [modelFileWithoutExtension]_settings.xml
      // Should make up a name, use it in emory and change it later per user request if needed.
      ModelSettingsSerializer serializer = new ModelSettingsSerializer(getDefaultSettingsFileName(model), true);
      mapModelsToSettings.put(model, serializer);
   }
   private void updateSettingsSerializer(Model model) {
      ModelSettingsSerializer serializer = mapModelsToSettings.get(model);
      if(serializer != null) serializer.setFilename(getDefaultSettingsFileName(model));
   }
   /**
    * Write ettings to an xml file [model-file]_settings.xml
    */
    public void saveSettings(Model model) {
      mapModelsToSettings.get(model).confirmAndWrite();
   }
   public ModelSettingsSerializer getModelSavedSettings(Model model)
   {
      ModelSettingsSerializer exist = mapModelsToSettings.get(model);
      if (exist!=null)
         return exist;

      return null;
   }

   /**
    * Utility: apply a function to given actor, or to all actors in assembly.
    */
   interface ActorFunctionApplier {
      public void apply(vtkActor actor);
   }
   public static void ApplyFunctionToActors(vtkProp3D asm, ActorFunctionApplier functionApplier)
   {
      if (asm==null) return;
      if (asm instanceof vtkAssembly){
         vtkProp3DCollection parts = ((vtkAssembly)asm).GetParts();
         parts.InitTraversal();
         for (;;) {
            vtkProp3D prop = parts.GetNextProp3D();
            if (prop==null) break;
            else ApplyFunctionToActors(prop, functionApplier); // recur on prop (may be nested assembly?)
         }
      } else if (asm instanceof vtkActor){
         functionApplier.apply((vtkActor)asm);
      }
   }
}
