package org.opensim.tracking;

import java.awt.Component;
import javax.swing.event.ChangeListener;
import org.openide.WizardDescriptor;
import org.openide.util.HelpCtx;

public class RunInvestigationPanel  extends workflowWizardPanelBase{
    
    /**
     * The visual component that displays this panel. If you need to access the
     * component from this class, just use getComponent().
     */
    private Component component;
    
    // Get the visual component for the panel. In this template, the component
    // is kept separate. This can be more efficient: if the wizard is created
    // but never displayed, or not all panels are displayed, it is better to
    // create only those which really need to be visible.
    public Component getComponent() {
        if (component == null) {
            component = new AnalysisVisualPanel(this);
        }
        return component;
    }
    
    public HelpCtx getHelp() {
        // Show no Help button for this panel:
        return HelpCtx.DEFAULT_HELP;
        // If you have context help:
        // return new HelpCtx(SampleWizardPanel1.class);
    }
    
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
    public void readSettings(Object settings) {}
    public void storeSettings(Object settings) {}

    boolean executeStep() {
/*        String cmd = "cmd /c rra "+"-S 900045_setup_rra_pass1.xml";
         try {
             File workingDir = new File("C:\\test\\wf\\");
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
         }*/
        return true;
    }
    
}

