public class EratosthenesPrime {
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        int[] prime = Eprime(400000000);
        if (prime == null) {
            System.out.println("None Prime");
            return;
        }
        /*for (int i = 0; i < prime.length; i++) {
            System.out.print(prime[i] + "\t");
            if (i % 15 == 0) {
                System.out.println();
            }
        }
        System.out.println();*/
        System.out.println("Run over,time:" + (System.currentTimeMillis() - start) + "ms");
    }

    public static int[] Eprime(int a) {

        if (a <= 1) {
            return null;
        }
        boolean[] prime = new boolean[a + 1];
        prime[0] = prime[1] = true;
        int count = 0;
        for (int i = 2; i < a + 1; i++) {
            if (!prime[i]) {
                count++;
                for (int s = i * 2; s < a + 1; s += i) {
                    prime[s] = true;
                }
            }
        }
        if (count == 0) {
            return null;
        }
        int[] result = new int[count];
        int index = 0;
        for (int i = 0; i < a + 1; i++) {
            if (!prime[i]) {
                result[index++] = i;
            }
        }
        return result;
    }
}
