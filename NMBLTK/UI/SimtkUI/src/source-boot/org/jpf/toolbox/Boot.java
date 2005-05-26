/*****************************************************************************
 * JPF-demo
 * Copyright (C) 2004 Dmitry Olshansky
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *****************************************************************************/
package org.jpf.toolbox;

import org.apache.log4j.*;
import org.apache.commons.logging.*;
import org.java.plugin.IntegrityCheckReport;
import org.java.plugin.PluginManager;
import org.java.plugin.Plugin;

import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.lang.reflect.InvocationTargetException;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Properties;
import java.util.StringTokenizer;

import simtkui.SimtkPluginManager;


/**
 * Main class to get application running.
 */
public final class Boot {
    // Configuration parameters goes here
    private static final String PARAM_PLUGINS_FOLDERS =
        "simtk.pluginsFolders";
    private static final String PARAM_DATA_FOLDER = "simtk.dataFolder";

    private static Log log;

    /**
     * Call this method to start up program.
     * @param args no arguments expected
     * @throws Throwable
     */
    public static void main(String[] args) throws Throwable {
        try {
            // Load start-up configuration
            Properties props = new Properties();
            InputStream strm = new FileInputStream("boot.properties");
            try {
                props.load(strm);
            } finally {
                strm.close();
            }
            // Publish current folder as configuration parameter
            // to get it available as ${applicationRoot} variable
            // when extended properties are supported
            props.put("applicationRoot", ".");
            // Initializing logging system
            PropertyConfigurator.configure(props);
            log = LogFactory.getLog(Boot.class);
            log.info("logging system initialized");
            // Prepare parameters to start plug-in manager
            StringTokenizer st = new StringTokenizer(
                    props.getProperty(PARAM_PLUGINS_FOLDERS), ",", false);
            Map pluginLocations = new HashMap();
            for (; st.hasMoreTokens();) {
                File folder = new File(st.nextToken().trim()).getCanonicalFile();
                log.debug("plug-ins folder - " + folder);
                if (!folder.isDirectory()) {
                    throw new Exception("plug-ins folder " + folder
                            + " doesn't exist");
                }
                File[] pluginFolders = folder.listFiles(
                    new FileFilter() {
                        public boolean accept(File file) {
                            return file.isDirectory();
                        }
                });
                for (int i = 0; i < pluginFolders.length; i++) {
                    File pluginFolder = pluginFolders[i];
                    File manifestFile = getManifestFile(pluginFolder);
                    if (manifestFile != null) {
                      pluginLocations.put(manifestFile, pluginFolder); // Map manifest files to folders
                      SimtkPluginManager.getInstance().addPluginsForResource(pluginFolder.getCanonicalFile());
                    }
                }
            }
            // Create instance of plug-in manager providing collection
            // of discovered plug-in manifests and corresponding plug-in folders
            PluginManager pluginManager =
                    PluginManager.createStandardManager(pluginLocations);
            // Check plug-in's integrity
            IntegrityCheckReport integrityCheckReport =
                pluginManager.getRegistry().checkIntegrity(
                        pluginManager.getPathResolver());
            log.info("integrity check done: errors - " + integrityCheckReport.countErrors() + ", warnings - " + integrityCheckReport.countWarnings());
            if (integrityCheckReport.countErrors() != 0) {
                // Something wrong in plug-ins set
                log.info(integrityCheckReport2str(integrityCheckReport));
                throw new Exception("plug-ins integrity check failed");
            }
            if (log.isTraceEnabled()) {
                log.trace(integrityCheckReport2str(integrityCheckReport));
            }
            File dataFolder = new File(props.getProperty(PARAM_DATA_FOLDER));
            dataFolder = dataFolder.getCanonicalFile();
            log.debug("data folder - " + dataFolder);
            if (!dataFolder.isDirectory()) {
                throw new Exception("data folder " + dataFolder + " doesn't exist");
            }
            // get the start-up plug-in
            Plugin corePlugin = pluginManager.getPlugin("org.jpf.toolbox.core");
            if (corePlugin == null) {
                throw new Exception("can't get plug-in org.jpf.toolbox.core");
            }
            // Now we are ready to RUN! Let's do it!
            // Run Forrest, run!!!

            // We need to use reflection here to call any plug-in method outside
            // of plug-in itself because any directly referenced plug-in class
            // shouldn't be loaded before JPF initializing.
            //
            // We also want to avoid any compile-time dependencies on plugin's
            // classes.
            corePlugin.getClass().getMethod("run",
                    new Class[] {File.class}).invoke(corePlugin,
                            new Object[] {dataFolder});
        } catch (InvocationTargetException ite) {
            // Something get wrong during start up.
            // Just create file with exception data in current folder.
            Throwable t = ite.getTargetException();
            if (t != null) {
                logFatal(t);
            } else {
                logFatal(ite);
            }
        } catch (Throwable t) {
            logFatal(t);
            throw t;
        }
    }

    private static File getManifestFile(File folder) {
        File result = new File(folder, "plugin.xml");
        if (result.isFile()) {
            return result;
        }
        result = new File(folder, "plugin-fragment.xml");
        if (result.isFile()) {
            return result;
        }
        return null;
    }

    private static String integrityCheckReport2str(IntegrityCheckReport report) {
        StringBuffer buf = new StringBuffer();
        buf.append("integrity check report:\r\n");
        buf.append("-------------- REPORT BEGIN -----------------\r\n");
        for (Iterator it = report.getItems().iterator(); it.hasNext();) {
            IntegrityCheckReport.ReportItem item =
                (IntegrityCheckReport.ReportItem)it.next();
            buf.append("\tseverity=").append(item.getSeverity())
                .append("; code=").append(item.getCode())
                .append("; message=").append(item.getMessage())
                .append("; source=").append(item.getSource()).append("\r\n");
        }
        buf.append("-------------- REPORT END -----------------");
        return buf.toString();
    }

    private static void logFatal(Throwable t) {
        try {
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(
                    new FileOutputStream("toolbox-boot-failed.log", false),
                    "UTF-8"));
            try {
                writer.println(new Date());
                t.printStackTrace(writer);
            } finally {
                writer.close();
            }
        } catch (Throwable t2) {
            throw new Error("boot failed", t);
        }
    }
}
