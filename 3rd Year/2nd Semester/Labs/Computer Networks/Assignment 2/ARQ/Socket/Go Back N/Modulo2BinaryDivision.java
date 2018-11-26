
public class Modulo2BinaryDivision {

	public static String encodeData(String data, String key) {
		String remainder = mod2div(data, key);
		return remainder;
	}

	private static String mod2div(String dividend, String divisor) {
		// Number of bits to be XORed at a time.
		int pick = (divisor).length();

		// Slicing the dividend to appropriate
		// length for particular step
		String tmp = dividend.substring(0, pick);

		while(pick < dividend.length()) {

			if (tmp.charAt(0) == '1') {

				// replace the dividend by the result
				// of XOR and pull 1 bit down
				String xor_value=xor(divisor, tmp);
				tmp = xor_value.substring(1) + dividend.charAt(pick);
			}

			else  { // If leftmost bit is '0'
				// If the leftmost bit of the dividend (or the
				// part used in each step) is 0, the step cannot
				// use the regular divisor; we need to use an
				// all-0s divisor.
				String xor_value=xor(go(pick), tmp);
				tmp = xor_value.substring(1) + dividend.charAt(pick);
			}

			// increment pick to move further
			pick += 1;
		}

		// For the last n bits, we have to carry it out
		// normally as increased value of pick will cause
		// Index Out of Bounds.
		if (tmp.charAt(0) == '1')
			tmp = xor(divisor, tmp);
		else
			tmp = xor(go(pick), tmp);

		String checkword = tmp.substring(1);
		return checkword;

		// Function used at the sender side to encode
		// data by appending remainder of modular divison
		// at the end of data.
	}

	private static String go(int pick) {
		String res="";
		for (int i = 0; i < pick; i++) {
			res+='0';
		}
		return res;
	}

	// Returns XOR of 'a' and 'b'
	// (both of same length)
	private static String xor(String a, String b) {
		// initialize result
		String result = "";

		// Traverse all bits, if bits are
		// same, then XOR is 0, else 1
		for (int i=0;i<b.length();i++) {
			if (a.charAt(i) == b.charAt(i))
				result+=('0');
			else
				result+=('1');
		}

		return (result);
	}
}
