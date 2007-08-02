/*
 * OpenSimSliderUI.java
 *
 * Created on August 1, 2007, 12:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import com.sun.java.swing.plaf.windows.WindowsSliderUI;
import java.awt.*;

import javax.swing.plaf.*;
import javax.swing.*;
import javax.swing.plaf.basic.BasicGraphicsUtils;

/**
 *
 * @author Jeff Reinbolt
 */
public class OpenSimSliderUI extends WindowsSliderUI 
{
    
    public OpenSimSliderUI(JSlider b){
	super(b);
    }

    public static ComponentUI createUI(JComponent b) {
        return new OpenSimSliderUI((JSlider)b);
    }
    
    protected Dimension getThumbSize() {
        Dimension size = new Dimension();

        if ( slider.getOrientation() == JSlider.VERTICAL ) {
	    size.width = 22;
	    size.height = 12;
	}
	else {
	    size.width = 12;
	    size.height = 22;
	}

	return size;
    }
        
    public void paintTrack(Graphics g)  {        

        if ( slider.getOrientation() == JSlider.HORIZONTAL ) {
            int cy, cw, ch;

            Rectangle trackBounds = trackRect;
            cy = (trackBounds.height / 2) - 3;
            cw = trackBounds.width;
            ch = 5;

            g.translate(trackBounds.x, trackBounds.y + cy);

            g.setColor(getShadowColor());
            g.drawLine(0, 0, cw-1, 0);
            g.drawLine(0, 1, 0, ch);
            g.setColor(getHighlightColor());
            g.drawLine(1, ch, cw, ch);
            g.drawLine(cw, 0, cw, ch-1);
            if (slider.isEnabled()) {
                g.setColor(new Color(159, 178, 209));
            }
            else {
                g.setColor(new Color(199, 199, 199));
            }
            g.fillRect(1, 1, cw-1, ch-1);

            g.translate(-trackBounds.x, -(trackBounds.y + cy));
        }
        else {
            super.paintTrack(g);
        }
            
    }

    public void paintThumb(Graphics g)  {    
        if ( slider.getOrientation() == JSlider.HORIZONTAL ) {
            Rectangle knobBounds = thumbRect;
            Image sliderKnob;

            if (slider.isEnabled()) {
                if (slider.getPaintTicks()) {
                    sliderKnob = Toolkit.getDefaultToolkit().getImage(getClass().getResource("/org/opensim/view/sliderKnobArrow.png"));
                }
                else {
                    sliderKnob = Toolkit.getDefaultToolkit().getImage(getClass().getResource("/org/opensim/view/sliderKnob.png"));
                }
            }
            else {
                if (slider.getPaintTicks()) {
                    sliderKnob = Toolkit.getDefaultToolkit().getImage(getClass().getResource("/org/opensim/view/sliderKnobArrow_disabled.png"));
                }
                else {
                    sliderKnob = Toolkit.getDefaultToolkit().getImage(getClass().getResource("/org/opensim/view/sliderKnob_disabled.png"));
                }
            }

            g.drawImage(sliderKnob,knobBounds.x,knobBounds.y,null);
        }
        else {
            super.paintThumb(g);
        }
    }

}
