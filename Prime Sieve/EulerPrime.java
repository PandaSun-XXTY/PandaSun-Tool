public class EulerPrime {
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        int[] prime = Eprime(31623);
        if (prime == null) {
            System.out.println("None of Prime");
            return;
        }
        for (int i = 0; i < prime.length; i++) {
            System.out.print(prime[i] + "\t");
            if (i % 15 == 0) {
               System.out.println();
            }
        }
        System.out.println();
        System.out.println("Total time : " + (System.currentTimeMillis() - start) + "ms");
    }

    public static int[] Eprime(int a) {
        if(a<2){
            return null;
        }
        boolean[] prime = new boolean[a+1];
        prime[0] = prime[1] = true;
        int count = 0;
        for(int i = 2; i <= a; i++){
            if(!prime[i]){
                count++;
            }
            for(int  s = 2;i*s<=a;s++){
                prime[i*s] = true;
                if(i%s==0){
                    break;
                }
            }
        }
        if(count==0){
            return null;
        }
        int[] result = new int[count];
        int index = 0;
        for(int i = 0;i< a;i++){
            if(!prime[i]){
                result[index++] = i;
            }
        }
        return result;
    }
}
