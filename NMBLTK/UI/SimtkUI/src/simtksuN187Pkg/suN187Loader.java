package simtksuN187Pkg;

import simtkModel.*;
public class suN187Loader extends suN187 {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("suN187_D");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public suN187Loader(){
		super("C:\\Work\\WorkFlow_Darryl\\data\\n187\\params.txt", null);
	};

	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
