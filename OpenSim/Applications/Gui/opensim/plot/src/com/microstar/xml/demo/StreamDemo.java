// StreamDemo.java: demonstration application showing &AElig;fred's event stream.
// NO WARRANTY! See README, and copyright below.
// $Id: StreamDemo.java,v 1.9 2005/04/29 20:05:17 cxh Exp $
// Modified 11/8/98 to add package statement.
package com.microstar.xml.demo;

import java.io.FileInputStream;
import java.io.InputStream;

import com.microstar.xml.XmlParser;


/**
  * Demonstration application showing &AElig;fred's event stream from a stream.
  * <p>Usage: <code>java StreamDemo</code>
  * Copyright (c)  1998 by Microstar Software Ltd.;
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
public class StreamDemo extends EventDemo {
    public static void main(String[] args) throws Exception {
        StreamDemo handler = new StreamDemo();
        InputStream is = null;

        if (args.length != 1) {
            System.err.println("Usage: java StreamDemo <file>");
            System.exit(1);
        }

        try {
            is = new FileInputStream(args[0]);

            XmlParser parser = new XmlParser();
            parser.setHandler(handler);
            parser.parse(makeAbsoluteURL(args[0]), null, is, null);
        } finally {
            if (is != null) {
                try {
                    is.close();
                } catch (Throwable throwable) {
                    System.out.println("Failed to close '" + args[0] + "'");
                    throwable.printStackTrace();
                }
            }
        }
    }
}
