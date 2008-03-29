/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * ExcitationRenderer.java
 *
 * Created on October 25, 2007, 10:52 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view.excitationEditor;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CrosshairState;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRendererState;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer.State;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.RectangleEdge;
import org.opensim.modeling.ArrayXYPoint;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.Function;
import org.opensim.view.functionEditor.FunctionRenderer;

/**
 *
 * @author Ayman Habib 
 */
public class ExcitationRenderer extends FunctionRenderer
 {

   private ControlLinear control;
   
   /**
     * Creates a ExcitationRenderer for a single function.
     */
   public ExcitationRenderer(ControlLinear theControl, Function dFunction) {
      super(dFunction);
      control=theControl;
   }

   public ControlLinear getControl() {
      return control;
   }

   public void drawFunctions(Graphics2D g2,
           XYItemRendererState state,
           Rectangle2D dataArea,
           XYPlot plot,
           ValueAxis domainAxis,
           ValueAxis rangeAxis,
           XYDataset dataset,
           CrosshairState crosshairState) {
      shadeMinMax(g2, state, dataArea, plot, domainAxis, rangeAxis, dataset);
      super.drawFunctions(g2, state, dataArea, plot, domainAxis, rangeAxis, dataset, crosshairState);
   }

   public void shadeMinMax(Graphics2D g2,
           XYItemRendererState state,
           Rectangle2D dataArea,
           XYPlot plot,
           ValueAxis domainAxis,
           ValueAxis rangeAxis,
           XYDataset dataset) {

      int seriesCount = dataset.getSeriesCount();
      if (seriesCount < 3)
         return;

      RectangleEdge xAxisLocation = plot.getDomainAxisEdge();
      RectangleEdge yAxisLocation = plot.getRangeAxisEdge();

      State s = (State) state;
      s.seriesPath.reset();
      s.setLastPointGood(false);

      // Go forwards through series 1
      for (int item = 0; item < dataset.getItemCount(1); item++) {
         ArrayXYPoint xyPts = functionList.get(1).renderAsLineSegments(item);
         if (xyPts != null) {
            for (int i = 0; i < xyPts.getSize(); i++) {
               double datax = xyPts.get(i).get_x() * XUnits.convertTo(XDisplayUnits);
               double datay = xyPts.get(i).get_y() * YUnits.convertTo(YDisplayUnits);
               double screenx = domainAxis.valueToJava2D(datax, dataArea, xAxisLocation);
               double screeny = rangeAxis.valueToJava2D(datay, dataArea, yAxisLocation);
               if (!Double.isNaN(screenx) && !Double.isNaN(screeny)) {
                  if (s.isLastPointGood() == false) {
                     s.seriesPath.moveTo((float)screenx, (float)screeny);
                     s.setLastPointGood(true);
                  } else {
                     s.seriesPath.lineTo((float)screenx, (float)screeny);
                  }
               }
            }
            functionList.get(1).deleteXYPointArray(xyPts);
         } else {
            //s.setLastPointGood(false);
         }
      }

      // Go backwards through series 2
      for (int item = dataset.getItemCount(2) - 1; item >= 0; item--) {
         ArrayXYPoint xyPts = functionList.get(2).renderAsLineSegments(item);
         if (xyPts != null) {
            for (int i = xyPts.getSize() - 1; i >= 0; i--) {
               double datax = xyPts.get(i).get_x() * XUnits.convertTo(XDisplayUnits);
               double datay = xyPts.get(i).get_y() * YUnits.convertTo(YDisplayUnits);
               double screenx = domainAxis.valueToJava2D(datax, dataArea, xAxisLocation);
               double screeny = rangeAxis.valueToJava2D(datay, dataArea, yAxisLocation);
               if (!Double.isNaN(screenx) && !Double.isNaN(screeny)) {
                  if (s.isLastPointGood() == false) {
                     s.seriesPath.moveTo((float)screenx, (float)screeny);
                     s.setLastPointGood(true);
                  } else {
                     s.seriesPath.lineTo((float)screenx, (float)screeny);
                  }
               }
            }
            functionList.get(2).deleteXYPointArray(xyPts);
         } else {
            //s.setLastPointGood(false);
         }
      }

      g2.setStroke(getItemStroke(1, 0));
      g2.setPaint(Color.PINK);
      g2.fill(s.seriesPath);
   }

    void setControl(ControlLinear backup) {
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
