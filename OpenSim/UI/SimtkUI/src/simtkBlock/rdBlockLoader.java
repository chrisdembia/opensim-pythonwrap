package simtkBlock;

public class rdBlockLoader extends rdBlock {

    static {
        System.loadLibrary("rdBlock_Model");
    }

    public rdBlockLoader() {
      super(null, null);
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
