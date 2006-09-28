package org.opensim.tracking;

import com.realisticDynamics.InvestigationCMCGait;
import java.awt.Component;
import javax.swing.event.ChangeListener;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import org.openide.util.HelpCtx;
import org.opensim.swingui.SwingWorker;

public class RunCMCWizardPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private RunCMCVisualPanel component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new RunCMCVisualPanel();
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
    public boolean isValid() {
        // If it is always OK to press Next or Finish, then:
        return true;
        // If it depends on some condition (form filled out...), then:
        // return someCondition();
        // and when this condition changes (last form field filled in...) then:
        // fireChangeEvent();
        // and uncomment the complicated stuff below.
    }
    
    public final void addChangeListener(ChangeListener l) {}
    public final void removeChangeListener(ChangeListener l) {}
    /*
    private final Set<ChangeListener> listeners = new HashSet<ChangeListener>(1);
    public final void addChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.add(l);
        }
    }
    public final void removeChangeListener(ChangeListener l) {
        synchronized (listeners) {
            listeners.remove(l);
        }
    }
    protected final void fireChangeEvent() {
        Iterator<ChangeListener> it;
        synchronized (listeners) {
            it = new HashSet<ChangeListener>(listeners).iterator();
        }
        ChangeEvent ev = new ChangeEvent(this);
        while (it.hasNext()) {
            it.next().stateChanged(ev);
        }
    }
     */
    
    // You can use a settings object to keep track of state. Normally the
    // settings object will be the WizardDescriptor, so you can use
    // WizardDescriptor.getProperty & putProperty to store information entered
    // by the user.
    public void readSettings(Object settings) {
        descriptor = (WorkflowDescriptor) settings;
        component.updatePanel(descriptor);
    }
    public void storeSettings(Object settings) {
       descriptor = (WorkflowDescriptor) settings;
       component.updateWorkflow(descriptor);
    }

    boolean executeStep() {
        /* String cmd = "cmcgait -S" + "900045_setup_cmcgait.xml";
         try {
             File workingDir = new File("C:\\test\\945\\900045");
             Runtime r = Runtime.getRuntime();
             Process p = r.exec(cmd);
             
             InputStream i_stream = p.getErrorStream();
             InputStreamReader reader = new InputStreamReader(i_stream); 
 
             InputStream out = new BufferedInputStream(p.getInputStream()); 
             
             String s =null;
             
             BufferedReader bf_reader= new BufferedReader(reader); 
             while ((s = bf_reader.readLine()) != null) {
        		 byte[] b = new byte[1024]; 
                 int n = out.read(b);
                 for(int i=0; i<n; i++) 
        		 System.out.print((char)b[i]);
             }
 
             p.waitFor();// wait for application to be ended
             
         }catch(Exception e) {
            System.out.println("execution error" + cmd + e.getMessage());
         } */
        final InvestigationCMCGait cmc = new InvestigationCMCGait(descriptor.getSetupCMCFilename());
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Running CMC ");
        progressHandle.start();

        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                progressHandle.progress((int)cmc.getModel().getTime()*100);
                cmc.run();
                return this;
            };
            public void finished() {
               progressHandle.finish();
            };
         };
        worker.start();

         return true;
    }
    
}

