// TimerDemo.java: demonstration application showing time elapsed for parse.
// NO WARRANTY! See README, and copyright below.
// $Id: TimerDemo.java,v 1.5 2005/04/25 17:21:45 cxh Exp $
// Modified 11/8/98 to add package statement.
package com.microstar.xml.demo;


/**
  * Demonstration application showing time elapsed for parse.
  * <p>Usage: <code>java TimerDemo &lt;url&gt;</code>
  * <p>Or, use it as an applet, supplying the URL as the <code>url</code>
  * parameter.
  * Copyright (c)  1997, 1998 by Microstar Software Ltd.;
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
public class TimerDemo extends XmlApp {
    /**
      * Entry point for an application.
      */
    public static void main(String[] args) throws java.lang.Exception {
        long start;
        long end;
        TimerDemo demo = new TimerDemo();

        if (args.length != 1) {
            System.err.println("Usage: java TimerDemo <uri>");
            System.exit(1);
        }

        System.out.println("Starting parse...");
        start = System.currentTimeMillis();
        demo.doParse(args[0]);
        end = System.currentTimeMillis();
        System.out.println("Elapsed time: " + (end - start) + " ms");
    }
}

// End of TimerDemo.java
