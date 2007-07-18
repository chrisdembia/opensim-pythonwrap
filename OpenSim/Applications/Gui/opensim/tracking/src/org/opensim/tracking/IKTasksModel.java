package org.opensim.tracking;

import java.util.Hashtable;
import java.util.Observable;
import java.util.Vector;
import org.opensim.modeling.AbstractDof;
import org.opensim.modeling.CoordinateSet;
import org.opensim.modeling.IKCoordinateTask;
import org.opensim.modeling.IKMarkerTask;
import org.opensim.modeling.IKTask;
import org.opensim.modeling.IKTaskSet;
import org.opensim.modeling.MarkerData;
import org.opensim.modeling.MarkerSet;
import org.opensim.modeling.Model;
import org.opensim.modeling.Storage;
import org.opensim.tracking.IKTasksModel.ValueType;

//==================================================================
// IKTasksModelEvent
//==================================================================
class IKTasksModelEvent {
   public enum Operation { AllChanged, TaskChanged };
   public Operation op;
   public int index;
   public IKTasksModelEvent(Operation op) { this.op = op; this.index = -1; }
   public IKTasksModelEvent(Operation op, int index) { this.op = op; this.index = index; }
}

//==================================================================
// IKTasksModel
//==================================================================
public abstract class IKTasksModel extends Observable {
   public enum ValueType { FromFile, DefaultValue, ManualValue };

   protected Model model;
   protected Vector<IKTask> tasks = new Vector<IKTask>();

   public IKTasksModel(Model model) {
      this.model = model;
   }

   //------------------------------------------------------------------------
   // Populating values
   //------------------------------------------------------------------------
   public abstract void reset(); // Reset to default values
   public abstract void fromTaskSet(IKTaskSet fullTaskSet);
   public abstract void toTaskSet(IKTaskSet fullTaskSet);

   //------------------------------------------------------------------------
   // Get/Set
   //------------------------------------------------------------------------
   public int size() { return tasks.size(); }

   public String getName(int i) { return tasks.get(i).getName(); }
   public void setName(int i,String name) { tasks.get(i).setName(name); setModified(i); }

   public boolean getEnabled(int i) { return tasks.get(i).getApply(); }
   public void setEnabled(int i,boolean enabled) { if(getEnabled(i)!=enabled) { tasks.get(i).setApply(enabled); setModified(i); } }
  
   public abstract ValueType getValueType(int i);
   public abstract void setValueType(int i,ValueType type);
   public abstract double getValue(int i);
   public abstract double getDefaultValue(int i);
   public abstract double getManualValue(int i);
   public abstract void setManualValue(int i,double value);

   public abstract boolean isLocked(int i);

   public double getWeight(int i) { return isLocked(i) ? 0 : tasks.get(i).getWeight(); }
   public void setWeight(int i,double weight) { if(!isLocked(i) && getWeight(i)!=weight) { tasks.get(i).setWeight(weight); setModified(i); } }

   //------------------------------------------------------------------------
   // Validation
   //------------------------------------------------------------------------

   public abstract boolean isValid(int i);

   public boolean isValid() {
      for(int i=0; i<size(); i++) if(!isValid(i)) return false;
      return true;
   }

   //------------------------------------------------------------------------
   // Observer functions
   //------------------------------------------------------------------------
   protected void setModified() {
      setChanged(); 
      notifyObservers(new IKTasksModelEvent(IKTasksModelEvent.Operation.AllChanged));
   }
   protected void setModified(int i) {
      setChanged(); 
      notifyObservers(new IKTasksModelEvent(IKTasksModelEvent.Operation.TaskChanged, i));
   }
}

//==================================================================
// IKMarkerTasksModel
//==================================================================
class IKMarkerTasksModel extends IKTasksModel {
   private Hashtable<String,Boolean> markerExistsInData = new Hashtable<String,Boolean>();

   public IKMarkerTasksModel(Model model) {
      super(model);
      reset();
      setModified();
   }   

   public void reset() {
      MarkerSet markerSet = model.getDynamicsEngine().getMarkerSet();
      tasks.setSize(markerSet.getSize());
      for(int i=0; i<tasks.size(); i++) {
         IKMarkerTask markerTask = new IKMarkerTask();
         markerTask.setName(markerSet.get(i).getName());
         markerTask.setApply(true);
         markerTask.setWeight(1);
         tasks.set(i, new IKMarkerTask(markerTask)); // Make a copy in C++ side
      }
   }

   public void markerSetChanged() {
      Vector<IKTask> oldTasks = new Vector<IKTask>(tasks);
      reset();
      // Copy over old task values that have same marker name
      for(int i=0; i<tasks.size(); i++)
         for(int j=0; j<oldTasks.size(); j++)
            if(oldTasks.get(j).getName().equals(tasks.get(i).getName())) {
               tasks.set(i, oldTasks.get(j));
               break;
            }
      setModified();
   }

   public void markerDataChanged(MarkerData markerData) {
      markerExistsInData.clear();
      if(markerData!=null) {
         for(int i=0; i<markerData.getMarkerNames().getSize(); i++) {
            markerExistsInData.put(markerData.getMarkerNames().getitem(i),(Boolean)true);
         }
      }
   }

   public void fromTaskSet(IKTaskSet fullTaskSet) {
      reset();
      for(int i=0; i<fullTaskSet.getSize(); i++) {
         if(IKMarkerTask.safeDownCast(fullTaskSet.get(i))!=null) {
            int index = model.getDynamicsEngine().getMarkerSet().getIndex(fullTaskSet.get(i).getName());
            if(index >= 0) tasks.set(index, new IKMarkerTask(IKMarkerTask.safeDownCast(fullTaskSet.get(i))));
         }
      }
      setModified();
   }

   public void toTaskSet(IKTaskSet fullTaskSet) {
      // Remove existing IKMarkerTasks
      for(int i=fullTaskSet.getSize()-1; i>=0; i--)
         if(IKMarkerTask.safeDownCast(fullTaskSet.get(i))!=null)
            fullTaskSet.remove(i);
      // Append copies of our tasks
      for(int i=0; i<tasks.size(); i++) {
         fullTaskSet.append(new IKMarkerTask(IKMarkerTask.safeDownCast(tasks.get(i))));
      } 
   }

   private IKMarkerTask get(int i) { return (IKMarkerTask)tasks.get(i); }
  
   public ValueType getValueType(int i) { return ValueType.FromFile; }
   public void setValueType(int i,ValueType type) { assert(false); }
   public double getValue(int i) { return 0; }
   public double getDefaultValue(int i) { return 0; }
   public double getManualValue(int i) { return 0; }
   public void setManualValue(int i,double value) { assert(false); }

   public boolean isLocked(int i) { return false; }

   public boolean isValid(int i) {
      return !getEnabled(i) || markerExistsInData.get(getName(i))!=null;
   }
}

//==================================================================
// IKCoordinateTasksModel
//==================================================================
class IKCoordinateTasksModel extends IKTasksModel {
   private Hashtable<String,Boolean> coordinateExistsInData = new Hashtable<String,Boolean>();
   protected Vector<Double> conversion = new Vector<Double>();

   public IKCoordinateTasksModel(Model model) {
      super(model);
      reset();
      setModified();
   }

   public void reset() {
      CoordinateSet coordinateSet = model.getDynamicsEngine().getCoordinateSet();
      tasks.setSize(coordinateSet.getSize());
      conversion.setSize(coordinateSet.getSize());;
      for(int i=0; i<tasks.size(); i++) {
         IKCoordinateTask coordinateTask = new IKCoordinateTask();
         coordinateTask.setName(coordinateSet.get(i).getName());
         coordinateTask.setApply(false);
         coordinateTask.setWeight(0);
         tasks.set(i, new IKCoordinateTask(coordinateTask));
         setValueType(i, ValueType.DefaultValue);
         conversion.set(i, (getMotionType(i)==AbstractDof.DofType.Rotational) ? 180.0/Math.PI : 1);
      }
   }

   public void coordinateDataChanged(Storage coordinateData) {
      coordinateExistsInData.clear();
      if(coordinateData!=null) {
         for(int i=0; i<coordinateData.getColumnLabels().getSize(); i++) {
            coordinateExistsInData.put(coordinateData.getColumnLabels().getitem(i),(Boolean)true);
         }
      }
   }

   public void fromTaskSet(IKTaskSet fullTaskSet) {
      reset();
      for(int i=0; i<fullTaskSet.getSize(); i++) {
         if(IKCoordinateTask.safeDownCast(fullTaskSet.get(i))!=null) {
            int index = model.getDynamicsEngine().getCoordinateSet().getIndex(fullTaskSet.get(i).getName());
            if(index >= 0) tasks.set(index, new IKCoordinateTask(IKCoordinateTask.safeDownCast(fullTaskSet.get(i))));
         }
      }
      setModified();
   }

   public void toTaskSet(IKTaskSet fullTaskSet) {
      // Remove existing IKCoordinateTasks
      for(int i=fullTaskSet.getSize()-1; i>=0; i--)
         if(IKCoordinateTask.safeDownCast(fullTaskSet.get(i))!=null)
            fullTaskSet.remove(i);
      // Append copies of our tasks
      for(int i=0; i<tasks.size(); i++) {
         fullTaskSet.append(new IKCoordinateTask(IKCoordinateTask.safeDownCast(tasks.get(i))));
      } 
   }

   private IKCoordinateTask get(int i) { return (IKCoordinateTask)tasks.get(i); }
   private AbstractDof.DofType getMotionType(int i) { return model.getDynamicsEngine().getCoordinateSet().get(i).getMotionType(); }
  
   public ValueType getValueType(int i) {
      if(get(i).getFromFile()) return ValueType.FromFile;
      else if(get(i).getValueUseDefault()) return ValueType.DefaultValue;
      else return ValueType.ManualValue;
   }
   public void setValueType(int i,ValueType type) {
      if(getValueType(i)!=type) {
         switch(type) {
            case FromFile:
               get(i).setValueUseDefault(true);
               get(i).setFromFile(true);
               break;
            case DefaultValue:
               get(i).setValueUseDefault(true);
               get(i).setFromFile(false);
               break;
            case ManualValue:
               get(i).setValueUseDefault(false);
               get(i).setFromFile(false);
               break;
         }
         setModified(i);
      }
   }
   public double getValue(int i) {
      switch(getValueType(i)) {
         case FromFile:
            return 0;
         case DefaultValue:
            return getDefaultValue(i);
         case ManualValue:
            return getManualValue(i);
      }
      return 0;
   }
   public double getDefaultValue(int i) {
      return conversion.get(i) * model.getDynamicsEngine().getCoordinateSet().get(i).getValue();
   }
   public double getManualValue(int i) {
      return conversion.get(i) * get(i).getValue();
   }
   public void setManualValue(int i, double value) {
      if(getValueType(i)!=ValueType.ManualValue || getValue(i)!=value/conversion.get(i)) {
         setValueType(i, ValueType.ManualValue);
         get(i).setValue(value/conversion.get(i));
         setModified(i);
      }
   }

   public boolean isLocked(int i) { return model.getDynamicsEngine().getCoordinateSet().get(i).getLocked(); }

   public boolean isValid(int i) {
      return !getEnabled(i) || getValueType(i)!=ValueType.FromFile || coordinateExistsInData.get(getName(i))!=null;
   }
}
