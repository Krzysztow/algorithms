import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.rmi.UnexpectedException;
import java.util.Iterator;
import java.util.LinkedList;
import java.lang.Math;

public class Main {

	static class LinkedListNumber {
		private LinkedList<Integer> mNumber = new LinkedList<Integer>();
		private int mBase = 10;

		public LinkedListNumber(int number) {
			this(number, 10);
		}

		public LinkedListNumber(int number, int base) {
			mBase = base;
			while (0 != number) {
				mNumber.add(number % mBase);
				number = (int) (number / mBase);
			}
		}

		public int digitsNo() {
			return mNumber.size();
		}

		public LinkedListNumber add(LinkedListNumber other)
				throws UnexpectedException {
			if (this.mBase != other.mBase)
				throw new UnexpectedException("Cannot use the method to remove the last node of the list.");

			boolean move = false;
			int intermediate = 0;
			for (int i = 0; i < Math.min(this.digitsNo(), other.digitsNo()); ++i) {
				intermediate = this.mNumber.get(i) + other.mNumber.get(i);

				if (move) {
					intermediate += 1;
					move = false;
				}

				if (intermediate >= mBase) {
					move = true;
					intermediate -= mBase;
				}

				this.mNumber.set(i, intermediate);

			}

			if (move)
				this.mNumber.add(1);

			return this;
		}


		@Override
		public String toString() {
			StringBuilder b = new StringBuilder("(");
			Iterator<Integer> it = mNumber.iterator();

			while (it.hasNext()) {
				b.append(it.next());
				if (it.hasNext())
					b.append(" -> ");
			}

			b.append(")");

			return b.toString();

		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
        if (2 != args.length) {
            System.err.println("Usage: <class-name> <first-no> <second-no>");
            return;
        }

		LinkedListNumber n1 = new LinkedListNumber(Integer.parseInt(args[0]));
		LinkedListNumber n2 = new LinkedListNumber(Integer.parseInt(args[1]));

		try {
		System.out.println(n1 + " + " + n2 + " = " + n1.add(n2));
		} catch (Exception e) {
			System.err.println("Something went wrong: " + e.getMessage());
		}
	}

}
