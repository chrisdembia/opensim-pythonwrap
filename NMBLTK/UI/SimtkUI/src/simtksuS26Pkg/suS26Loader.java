package simtksuS26Pkg;

import simtkModel.*;
public class suS26Loader extends suS26 {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("suS26Gui_D");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public suS26Loader(){
      super("C:\\Work\\DemoFiles\\params.txt", null);
	};

	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
