import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;


public class Main {
    /**
     * Returns length of the cstring, by looking for a '\0' character.
     */
    public static int strlen(byte cstring[]) {
        int i = 0;
        byte ch = cstring[i];
        //I could add some limit value, if needed.
        while ('\0' != ch) {
            ++i;
            ch = cstring[i];
        }

        return i;
    }

    public static void reverseCString(byte cstring[]) {
        //int realLength = cstring.length - 1;//1 subtracted since '\0' was added
        int realLength = strlen(cstring);
        for (int i = 0; i < realLength/2; ++i) {
            byte tmp = cstring[i];
            cstring[i] = cstring[realLength - 1 - i];
            cstring[realLength - 1 - i] = tmp;
        }
    }

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if (1 != args.length) {
			System.out.println("Usage <exec> <string-to-reverse>");
			return;
		}

		char inStr[] = args[0].toCharArray();
		byte input[] = new byte[inStr.length + 1];
		for (int i = 0; i < inStr.length; ++i) {
			byte ch = (byte)inStr[i];
			input[i] = ch;
		}
		input[input.length - 1] = '\0';

		reverseCString(input);

		System.out.println("Result: " + new String(input));
	}

}
