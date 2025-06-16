import java.util.Arrays;
import java.util.List;

public class Main {

    public static void pb1() {
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,14,15);

        String values = numbers.stream()
                .filter(number -> number % 2 == 0 || number % 3 == 0)
                .map(number -> "A" + (number+1) + "B")
                .reduce("", (a, b) -> a + b);

        System.out.println(values);
    }

    public static void main(String[] args) {
        pb1();
    }
}