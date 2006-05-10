package _PACKAGE_NAME_HERE_;

public class _MODEL_NAME_HERE_Loader extends _MODEL_NAME_HERE_ {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("_MODEL_LIBRARY_NAME_HERE_");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public _MODEL_NAME_HERE_Loader(){
		super(null, null);
	};
	
	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
