import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<String> words = Arrays.asList("hi", "hello", "hola", "bye", "goodbye", "adios");

        // P1
        words.forEach(s -> System.out.println("  " + s));

        // P2
        List<String> words2 = words.stream().map(s -> " " + s).toList();
        words2.forEach(System.out::println);

        // P3
        List<String> excitingWords = words.stream().map(s -> s + "!").toList();
        excitingWords.forEach(System.out::println);
        List<String> eyeWords = words.stream().map(s -> s.replace("i", "eye")).toList();
        eyeWords.forEach(System.out::println);
        List<String> upperCaseWords = words.stream().map(String::toUpperCase).toList();
        upperCaseWords.forEach(System.out::println);

        // P4
        List<String> shortWords = words.stream().filter(s -> s.length() < 4).toList();
        shortWords.forEach(System.out::println);
        List<String> wordsWithB = words.stream().filter(s -> s.contains("b")).toList();
        wordsWithB.forEach(System.out::println);
        List<String> evenLengthWords = words.stream().filter(s -> s.length() % 2 == 0).toList();
        evenLengthWords.forEach(System.out::println);

        // P5
        words.stream()
                .map(String::toUpperCase)
                .filter(s -> s.length() < 4)
                .filter(s -> s.contains("E"))
                .findFirst()
                .ifPresent(System.out::println);
        words.stream()
                .map(String::toUpperCase)
                .filter(s -> s.length() < 4 && s.contains("Q"))
                .findFirst()
                .ifPresent(System.out::println);

        // P6
        System.out.println(words
                .stream()
                .reduce("", (acc, s) -> acc + s.toUpperCase()));

        // P7
        System.out.println(words
                .stream()
                .map(String::toUpperCase)
                .reduce((acc, s) -> acc + s));

        // P8
            // v1
            System.out.println(words
                    .stream()
                    .reduce((acc, s) -> acc + "," + s)
                    .orElse(""));

            // v2
            System.out.println(String.join(",", words));

        // P9
            // v1
            System.out.println(words
                    .stream()
                    .map(String::length)
                    .reduce(0, Integer::sum));

            // v2
            System.out.println(words
                    .stream()
                    .mapToInt(String::length)
                    .sum());

        // P10
        System.out.println(words
                .stream()
                .filter(s -> s.contains("h"))
                .count());
    }
}